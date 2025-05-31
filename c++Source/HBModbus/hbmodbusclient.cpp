#include "hbmodbusclient.h"
#include <QDebug>
#include <QSerialPort>
#include <QModbusReply>
#include "c++Source/HBQmlEnum.h"
#include "c++Source/HBScreen/hbhome.h"
#include "c++Source/HBScreen/tensionsafe.h"
#include "c++Source/HBDefine.h"
#include "c++Source/HBData/hbdatabase.h"
#include "c++Source/HBScreen/wellparameter.h"
#include "c++Source/HBScreen/tensiometer.h"
#include <QtConcurrent>
HBModbusClient::MODBUS_REGISTER HBModbusClient::m_ReceivedReg;
HBModbusClient::MODBUS_REGISTER HBModbusClient::m_PrevReg;
QModbusClient* HBModbusClient::_ptrModbus = nullptr;
int HBModbusClient::m_timerIdentifier = -1;
QMap<int, int> HBModbusClient::m_RegisterSendMap;
QMutex HBModbusClient::m_mutexSending;
HBModbusClient::HBModbusClient(QObject *parent)
    : QObject{parent}
{
    _ptrModbus = new QModbusRtuSerialMaster(this);
    connectToServer();
    m_timerIdentifier = startTimer(500);
    m_RegisterSendMap.clear();
}

HBModbusClient::~HBModbusClient()
{
    if (_ptrModbus)
        _ptrModbus->disconnectDevice();
    delete _ptrModbus;
}

void HBModbusClient::connectToServer()
{
    if (_ptrModbus == nullptr)
        return;
#ifdef RK3588
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "ttyS3");
#else
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM6");
#endif
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    _ptrModbus->setTimeout(1000);
    _ptrModbus->setNumberOfRetries(5);
    if (!_ptrModbus->connectDevice())
    {
        qWarning() << "Connection failed:" << _ptrModbus->errorString();
    }
    else
    {
        qDebug() << "Modbus serial connection established.";
    }
}

void HBModbusClient::readRegister(int address, int count)
{
    QModbusDataUnit request(QModbusDataUnit::HoldingRegisters, address, count);

    if (auto *reply = _ptrModbus->sendReadRequest(request, 1)) {
        connect(reply, &QModbusReply::finished, this, [this, reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit result = reply->result();
                handleReadResult(result);
            } else {
                qWarning() << "Read failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send read request:" << _ptrModbus->errorString();
    }
}

void HBModbusClient::timerEvent(QTimerEvent *event)
{
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState)
    {
        // qWarning() << "Modbus is not connected.";
        return;
    }

    if(event->timerId() == m_timerIdentifier)
    {
        readRegister(0, HQmlEnum::MAX_REGISTR);
        readCoils();
    }
}

void HBModbusClient::handleReadResult(const QModbusDataUnit &result)
{
    int startAddress = result.startAddress();
    int count = result.valueCount();

    qDebug() << "Batch read from address" << startAddress << "count" << count;

    for (int i = 0; i < count; ++i)
    {
        int currentAddress = startAddress + i;
        qDebug() << "Start Address: " << currentAddress;
        quint16 value = result.value(i);

        switch (currentAddress) {
        case HQmlEnum::HOLOD_DEPTH_H: // DEPTH_H
            Depth_H = value;
            break;
        case HQmlEnum::HOLOD_DEPTH_L: // DEPTH_L
            Depth_L = value;
            m_ReceivedReg.m_Depth.Data = (Depth_H << 16) | Depth_L;
            m_ReceivedReg.m_Depth.Address = currentAddress;
            // HBHome::getInstance()->setDepth(m_ReceivedReg.m_Depth.Data);
            // qDebug() << "Address" << currentAddress << "- Updated depth:" << depth;
            break;
        case HQmlEnum::SPEED_H: // SPEED_H
            Speed_H = value;
            break;
        case HQmlEnum::SPEED_L: // SPEED_H
            Speed_L = value;
            m_ReceivedReg.m_Speed.Data = (Speed_H << 16) | Speed_L;
            m_ReceivedReg.m_Speed.Address = currentAddress;
            // HBHome::getInstance()->setSpeed(speed);
            // qDebug() << "Address" << currentAddress << "- Updated speed:" << speed;
            break;
        case HQmlEnum::MAX_SPEED_H: // MAX_SPEED_H
            MaxSpeed_H = value;
            break;
        case HQmlEnum::MAX_SPEED_L: // MAX_SPEED_L
            MaxSpeed_L = value;
            m_ReceivedReg.m_MaxSpeed.Data = (MaxSpeed_H << 16) | MaxSpeed_L;
            m_ReceivedReg.m_MaxSpeed.Address = currentAddress;
            // HBHome::getInstance()->setMaxSpeed(maxSpeed);
            // qDebug() << "Address" << currentAddress << "- Updated maxSpeed:" << maxSpeed;
            break;
        case HQmlEnum::TARGET_DEPTH_H: // MAX_SPEED_H
            TargetDepth_H = value;
            break;
        case HQmlEnum::TARGET_DEPTH_L: // MAX_SPEED_L
            TargetDepth_L = value;
            m_ReceivedReg.m_TargetLayerDepth.Data = (TargetDepth_H << 16) | TargetDepth_L;
            m_ReceivedReg.m_TargetLayerDepth.Address = currentAddress;
            // HBHome::getInstance()->setTargetDepth(targetDepth);
            // qDebug() << "Address" << currentAddress << "- Updated targetDepth:" << targetDepth;
            break;

        case HQmlEnum::METER_DEPTH_H: // 表套深度高
            TargetDepth_H = value;
            break;
        case HQmlEnum::METER_DEPTH_L: //
            TargetDepth_L = value;
            m_ReceivedReg.m_MeterDepth.Data = (TargetDepth_H << 16) | TargetDepth_L;
            m_ReceivedReg.m_MeterDepth.Address = currentAddress;
            // HBHome::getInstance()->setTargetDepth(targetDepth);
            // qDebug() << "Address" << currentAddress << "- Updated targetDepth:" << targetDepth;
            break;
        case HQmlEnum::PULSE: // PULSE
            m_ReceivedReg.m_Pulse.Data = value;
            m_ReceivedReg.m_Pulse.Address = currentAddress;
            // HBHome::getInstance()->setPulse(plus);
            // qDebug() << "Address" << currentAddress << "- Updated plus:" << plus;
            break;
        case HQmlEnum::TENSION_H: // TENSION_H
            Tension_H = value;
            break;
        case HQmlEnum::TENSION_L: // TENSION_L
            Tension_L = value;
            m_ReceivedReg.m_Tension.Data = (Tension_H << 16) | Tension_L;
            m_ReceivedReg.m_Tension.Address = currentAddress;
            // HBHome::getInstance()->setTension(tension);
            // qDebug() << "Address" << currentAddress << "- Updated tension:" << tension;
            break;
        case HQmlEnum::TENSION_INCREMENT_H: // TENSION_INCREMENT_H
            TensionIncrement_H = value;
            break;
        case HQmlEnum::TENSION_INCREMENT_L: // TENSION_INCREMENT_L
            TensionIncrement_L = value;
            m_ReceivedReg.m_TensionIncrement.Data = (TensionIncrement_H << 16) | TensionIncrement_L;
            m_ReceivedReg.m_TensionIncrement.Address = currentAddress;
            // HBHome::getInstance()->setTensionIncrement(tensionIncrement);
            // qDebug() << "Address" << currentAddress << "- Updated tensionIncrement:" << tensionIncrement;
            break;
        case HQmlEnum::K_VALUE:
            m_ReceivedReg.m_K_Value.Data = value;
            m_ReceivedReg.m_K_Value.Address = currentAddress;
            // HBHome::getInstance()->setKValue(K_Value);
            // qDebug() << "Address" << currentAddress << "- Updated K_Value:" << K_Value;
            break;
        case HQmlEnum::MAX_TENSION_H: // MAX_TENSION_H
            MaxTension_H = value;
            break;
        case HQmlEnum::MAX_TENSION_L: // MAX_TENSION_L
            MaxTension_L = value;
            m_ReceivedReg.m_MaxTension.Data = (MaxTension_H << 16) | MaxTension_L;
            m_ReceivedReg.m_MaxTension.Address = currentAddress;
            // HBHome::getInstance()->setMaxTension(maxTension);
            // qDebug() << "Address" << currentAddress << "- Updated maxTension:" << maxTension;
            break;
        case HQmlEnum::MAX_TENSION_INCREMENT_H: // MAX_TENSION_INCREMENT_L
            MaxTensionIncrement_H = value;
            break;
        case HQmlEnum::MAX_TENSION_INCREMENT_L: // MAX_TENSION_INCREMENT_L
            MaxTensionIncrement_L = value;
            m_ReceivedReg.m_MaxTensionIncrement.Data = (MaxTensionIncrement_H << 16) | MaxTensionIncrement_L;
            m_ReceivedReg.m_MaxTensionIncrement.Address = currentAddress;
            // HBHome::getInstance()->setMaxTensionIncrement(maxTensionIncrement);
            // qDebug() << "Address" << currentAddress << "- Updated maxTensionIncrement:" << maxTensionIncrement;
            break;

        case HQmlEnum::CABLE_TENSION_H: // CABLE_TENSION_H
            CableTension_H = value;
            break;
        case HQmlEnum::CABLE_TENSION_L: // CABLE_TENSION_L
            CableTension_L = value;
            m_ReceivedReg.m_CableTension.Data = (CableTension_H << 16) | CableTension_L;
            m_ReceivedReg.m_CableTension.Address = currentAddress;
            // HBHome::getInstance()->setHarnessTension(cableTension);
            // qDebug() << "Address" << currentAddress << "- Updated cableTension:" << cableTension;
            break;

        case HQmlEnum::CURRENT_TENSION_SAFE_H: // CURRENT_TENSION_SAFE_H
            currentTensionSafe_H = value;
            break;
        case HQmlEnum::CURRENT_TENSION_SAFE_L: // CURRENT_TENSION_SAFE_L
            currentTensionSafe_L = value;
            m_ReceivedReg.m_CurrentSafetyTension.Data = (currentTensionSafe_H << 16) | currentTensionSafe_L;
            m_ReceivedReg.m_CurrentSafetyTension.Address = currentAddress;
            // TensionSafe::getInstance()->setCurrentTensionSafe( QString::number(currentTensionSafe));
            // qDebug() << "Address" << currentAddress << "- Updated currentTensionSafe:" << currentTensionSafe;
            break;

        case HQmlEnum::CIRRENT_TENSION_MAX_H: // CIRRENT_TENSION_MAX_H
            maxTensionSafe_H = value;
            break;
        case HQmlEnum::CIRRENT_TENSION_MAX_L: // CIRRENT_TENSION_MAX_L
            maxTensionSafe_L = value;
            m_ReceivedReg.m_CurrentMaxTension.Data = (maxTensionSafe_H << 16) | maxTensionSafe_L;
            m_ReceivedReg.m_CurrentMaxTension.Address = currentAddress;
            // TensionSafe::getInstance()->setMAXTensionSafe(QString::number(maxTensionSafe));
            // qDebug() << "Address" << currentAddress << "- Updated maxTensionSafe:" << maxTensionSafe;
            break;
        case HQmlEnum::HARNESS_TENSION_TREND: // HARNESS_TENSION_TREND
            m_ReceivedReg.m_CableTensionTrend.Data = value;
            m_ReceivedReg.m_CableTensionTrend.Address = currentAddress;
            // TensionSafe::getInstance()->setCableTensionTrend(QString::number(cableTensionTrend));
            // qDebug() << "Address" << currentAddress << "- Updated cableTensionTrend:" << cableTensionTrend;
            break;

        case HQmlEnum::PARKING_SAFE_TIME: // PARKING_SAFE_TIME
            m_ReceivedReg.m_ParkStopTimeStamp.Data = value;
            m_ReceivedReg.m_ParkStopTimeStamp.Address = currentAddress;
            // TensionSafe::getInstance()->setPtime(QString::number(ptime));
            // qDebug() << "Address" << currentAddress << "- Updated cableTensionTrend:" << cableTensionTrend;
            break;

        case HQmlEnum::CODE_COUNT_H: // CODE_COUNT_H
            depthLoss_H = value;
            break;

        case HQmlEnum::CODE_COUNT_L: // CODE_COUNT_L
            depthLoss_L = value;
            m_ReceivedReg.m_DeltaEncoderDepth.Data = (depthLoss_H << 16) | depthLoss_L;
            m_ReceivedReg.m_DeltaEncoderDepth.Address = currentAddress;
            // TensionSafe::getInstance()->setDepthLoss(QString::number(depthLoss));
            // qDebug() << "Address" << currentAddress << "- Updated depthLoss:" << depthLoss;
            break;

        case HQmlEnum::DEPTH_CODE1_H: // DEPTH_CODE1_H
            currentDepth1_H = value;
            break;

        case HQmlEnum::DEPTH_CODE1_L: // DEPTH_CODE1_L
            currentDepth1_L = value;
            m_ReceivedReg.m_EncoderDepth1.Data = (currentDepth1_H << 16) | currentDepth1_L;
            m_ReceivedReg.m_EncoderDepth1.Address = currentAddress;
            // TensionSafe::getInstance()->setDepthLoss(QString::number(currentDepth1));
            // qDebug() << "Address" << currentAddress << "- Updated currentDepth1:" << currentDepth1;
            break;

        case HQmlEnum::DEPTH_CODE2_H: // DEPTH_CODE2_H
            currentDepth2_H = value;
            break;

        case HQmlEnum::DEPTH_CODE2_L: // DEPTH_CODE2_L
            currentDepth2_L = value;
            m_ReceivedReg.m_EncoderDepth2.Data = (currentDepth2_H << 16) | currentDepth2_L;
            m_ReceivedReg.m_EncoderDepth2.Address = currentAddress;
            // TensionSafe::getInstance()->setDepthLoss(QString::number(currentDepth2));
            // qDebug() << "Address" << currentAddress << "- Updated currentDepth2:" << currentDepth2;
            break;

        case HQmlEnum::DEPTH_CODE3_H: // DEPTH_CODE3_H
            currentDepth3_H = value;
            break;

        case HQmlEnum::DEPTH_CODE3_L: // DEPTH_CODE3_L
            currentDepth3_L = value;
            m_ReceivedReg.m_EncoderDepth3.Data = (currentDepth3_H << 16) | currentDepth3_L;
            m_ReceivedReg.m_EncoderDepth3.Address =  currentAddress;
            // TensionSafe::getInstance()->setDepthLoss(QString::number(currentDepth3));
            // qDebug() << "Address" << currentAddress << "- Updated currentDepth3:" << currentDepth3;
            break;

        case HQmlEnum::SCALE_1_H:
            scale1_H = value;
            break;

        case HQmlEnum::SCALE_1_L:
            scale1_L = value;
            m_ReceivedReg.m_Point1Scale.Data = (scale1_H << 16) | scale1_L;
            m_ReceivedReg.m_Point1Scale.Address = currentAddress;
            // Tensiometer::getInstance()->setScale1(m_scale1);
            // qDebug() << "Address" << currentAddress << "- Updated m_scale1:" << m_scale1;
            break;

        case HQmlEnum::SCALE_2_H:
            scale2_H = value;
            break;

        case HQmlEnum::SCALE_2_L:
            scale2_L = value;
            m_ReceivedReg.m_Point2Scale.Data = (scale2_H << 16) | scale2_L;
            m_ReceivedReg.m_Point2Scale.Address = currentAddress;
            // Tensiometer::getInstance()->setScale2(m_scale2);
            // qDebug() << "Address" << currentAddress << "- Updated m_scale2:" << m_scale2;
            break;

        case HQmlEnum::SCALE_3_H:
            scale3_H = value;
            break;

        case HQmlEnum::SCALE_3_L:
            scale3_L = value;
            m_ReceivedReg.m_Point3Scale.Data = (scale3_H << 16) | scale3_L;
            m_ReceivedReg.m_Point3Scale.Address = currentAddress;
            // Tensiometer::getInstance()->setScale3(m_scale3);
            // qDebug() << "Address" << currentAddress << "- Updated scale3_L:" << scale3_L;
            break;
        case HQmlEnum::SCALE_4_H:
            scale4_H = value;
            break;

        case HQmlEnum::SCALE_4_L:
            scale4_L = value;
            m_ReceivedReg.m_Point4Scale.Data = (scale4_H << 16) | scale4_L;
            m_ReceivedReg.m_Point4Scale.Address = currentAddress;
            // Tensiometer::getInstance()->setScale1(m_scale4);
            // qDebug() << "Address" << currentAddress << "- Updated m_scale4:" << m_scale4;
            break;
        case HQmlEnum::SCALE_5_H:
            scale5_H = value;
            break;

        case HQmlEnum::SCALE_5_L:
            scale5_L = value;
            m_ReceivedReg.m_Point5Scale.Data = (scale5_H << 16) | scale5_L;
            m_ReceivedReg.m_Point5Scale.Address = currentAddress;
            // Tensiometer::getInstance()->setScale1(m_scale5);
            // qDebug() << "Address" << currentAddress << "- Updated m_scale5:" << m_scale5;
            break;

        default:
            // 其他地址不处理
            break;
        }
    }
    insertDataToDatabase();
}

void HBModbusClient::writeRegister(int address, const QVector<quint16> &values)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, values.size());
    for (int i = 0; i < values.size(); ++i)
    {
        writeUnit.setValue(i, values[i]);
    }

    if (QModbusReply *reply = _ptrModbus->sendWriteRequest(writeUnit, 1)) { // Slave ID = 1
        connect(reply, &QModbusReply::finished, this, [reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "Write successful.";
            } else {
                qWarning() << "Write failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send write request:" << _ptrModbus->errorString();
    }

}

void HBModbusClient::writeRegister(int address, const QVariantList &values)
{
    QVector<quint16> data;
    for (const QVariant &v : values) {
        data.append(static_cast<quint16>(v.toUInt()));
    }
    writeRegister(address, data);
}

bool HBModbusClient::writeRegister(int address, const int value)
{
    m_mutexSending.lock();
    m_RegisterSendMap.insert(address, value);
    m_mutexSending.unlock();
    return true;
}

void HBModbusClient::readCoils()
{
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus not connected";
        return;
    }

    QModbusDataUnit request(QModbusDataUnit::Coils, HQmlEnum::ALARM_SPEED, 12);

    if (auto *reply = _ptrModbus->sendReadRequest(request, 1)) {
        connect(reply, &QModbusReply::finished, this, [this, reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                handleCoilResult(reply->result());
            } else {
                qWarning() << "Coil read failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send coil read request:" << _ptrModbus->errorString();
    }
}

void HBModbusClient::handleCoilResult(const QModbusDataUnit &result)
{
    int startAddress = result.startAddress();
    int count = result.valueCount();

    for (int i = 0; i < count; ++i) {
        int address = startAddress + i;
        bool val = result.value(i);
        handleAlarm(address, val);
    }
}

void HBModbusClient::handleAlarm(int address, bool value)
{
    QString alarmName;
    bool alarmActive = value;

    switch (address) {
    case HQmlEnum::ALARM_SPEED:
        alarmName = "速度报警";
        if (alarmActive) {

            qDebug() << alarmName << "触发 - 限速或者停止设备";

        } else {
            qDebug() << alarmName << "解除 - 恢复正常运行";

        }
        break;

    case HQmlEnum::ALARM_WELL:
        alarmName = "井口报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 井口异常，执行安全停机";

        } else {
            qDebug() << alarmName << "解除 - 井口正常";
        }
        break;

    case HQmlEnum::ALARM_TARGETLAYERDEPTH:
        alarmName = "目的层报警";

        qDebug() << alarmName << (alarmActive ? "触发" : "解除");
        break;

    case HQmlEnum::ALARM_METERDEPTH:
        alarmName = "表套深度报警";
        if (alarmActive) {


        } else {
            qDebug() << alarmName << "解除";

        }
        break;

    case HQmlEnum::ALARM_TENSION:
        alarmName = "张力报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }
        break;


    case HQmlEnum::ALARM_TENSIONINC_1:
        alarmName = "张力增量报警（遇阻）";
        qDebug() << alarmName << (alarmActive ? "触发" : "解除");
        break;

    case HQmlEnum::ALARM_TENSIONINC_2:
        alarmName = "张力增量报警（遇卡）";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }
        break;

    case HQmlEnum::ALARM_CABLETENSION_1:
        alarmName = "揽头张力遇阻报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CABLETENSION_2:
        alarmName = "揽头张力遇卡报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CODE1:
        alarmName = "编码器1报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CODE2:
        alarmName = "编码器2报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CODE3:
        alarmName = "编码器3报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    default:
        break;
    }
}

void HBModbusClient::insertDataToDatabase()
{
    HBHome* _dashboard = HBHome::getInstance();
    ModbusData modData;
    modData.wellNumber = WellParameter::getInstance()->WellNumber();
    modData.operateType = WellParameter::getInstance()->OperatorType();
    modData.operater = WellParameter::getInstance()->UserName();
    modData.depth = _dashboard->Depth();
    modData.velocity = _dashboard->Speed();
    modData.tensions = _dashboard->Tension();
    modData.tensionIncrement = _dashboard->TensionIncrement();
    modData.harnessTension = m_ReceivedReg.m_CableTension.Data;
    modData.maxTension = _dashboard->MaxTension();
    modData.safetyTension = m_ReceivedReg.m_CurrentSafetyTension.Data;
    modData.exception = "none";

    // HBDatabase::getInstance().insertHistoryData(modData);
    QtConcurrent::run([modData]() {
        HBDatabase::getInstance().insertHistoryData(modData);
    });
}

void HBModbusClient::writeCoil(int address, int value)
{
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState)
    {
        qWarning() << "Modbus not connected";
        return;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, address, 1);
    writeUnit.setValue(0, value ? 1 : 0); // 确保是 0 或 1

    int serverAddress = 1;

    if (auto *reply = _ptrModbus->sendWriteRequest(writeUnit, serverAddress))
    {
        connect(reply, &QModbusReply::finished, this, [reply]()
                {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "Coil write successful";
            } else {
                qWarning() << "Failed to write coil:" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
    else
    {
        qWarning() << "Failed to send coil write request:" << _ptrModbus->errorString();
    }
}
