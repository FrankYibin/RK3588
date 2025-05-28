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

HBModbusClient::HBModbusClient(QObject *parent)
    : QObject{parent}
{
    modbus = new QModbusRtuSerialMaster(this);

    // this->connectToServer();

    // this->readRegister(0);

    modbus = new QModbusRtuSerialMaster(this);

    refreshTimer = new QTimer(this);
    refreshTimer->setInterval(500); // 0.5秒刷新

    connect(refreshTimer, &QTimer::timeout, this, &HBModbusClient::startBatchRead);

    connectToServer();
}

HBModbusClient::~HBModbusClient()
{
    if (modbus)
        modbus->disconnectDevice();
}

void HBModbusClient::connectToServer()
{
    if (!modbus)
        return;

   // modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM6");
    modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "ttyS3");
   // modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "usbmon3")
    modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
    modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    modbus->setTimeout(1000);
    modbus->setNumberOfRetries(5);

    if (!modbus->connectDevice()) {
        qWarning() << "Connection failed:" << modbus->errorString();
    } else {
        qDebug() << "Modbus serial connection established.";

        refreshTimer->start();
    }
}

// void HBModbusClient::readRegister(int address, int count)
// {
//     if (!modbus || modbus->state() != QModbusDevice::ConnectedState) {
//         qWarning() << "Modbus is not connected.";
//         return;
//     }

//     QModbusDataUnit request(QModbusDataUnit::HoldingRegisters, address, count);

//     if (auto *reply = modbus->sendReadRequest(request, 1)) { // Slave ID 1
//         connect(reply, &QModbusReply::finished, this, [reply]() {
//             if (reply->error() == QModbusDevice::NoError) {
//                 const QModbusDataUnit result = reply->result();
//                 for (int i = 0; i < result.valueCount(); ++i) {
//                     qDebug() << "Address:" << result.startAddress() + i << "Value:" << result.value(i);
//                 }
//             } else {
//                 qWarning() << "Read failed:" << reply->errorString();
//             }
//             reply->deleteLater();
//         });
//     } else {
//         qWarning() << "Failed to send read request:" << modbus->errorString();
//     }
// }

void HBModbusClient::readRegister(int address, int count)
{
    if (!modbus || modbus->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus is not connected.";
        return;
    }

    QModbusDataUnit request(QModbusDataUnit::HoldingRegisters, address, count);

    if (auto *reply = modbus->sendReadRequest(request, 1)) {
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
        qWarning() << "Failed to send read request:" << modbus->errorString();
    }
}

void HBModbusClient::startBatchRead()
{
    readRegister(0,HQmlEnum::HIGH_ANGLE_WELL);

    readCoils();

}

void HBModbusClient::handleReadResult(const QModbusDataUnit &result)
{
    int startAddress = result.startAddress();
    int count = result.valueCount();

    qDebug() << "Batch read from address" << startAddress << "count" << count;

    for (int i = 0; i < count; ++i) {
        int currentAddress = startAddress + i;
        quint16 value = result.value(i);

        switch (currentAddress) {
        case HQmlEnum::HOLOD_DEPTH_H: // DEPTH_H
            Depth_H = value;
            break;
        case HQmlEnum::HOLOD_DEPTH_L: // DEPTH_L
            Depth_L = value;
            depth = (Depth_H << 16) | Depth_L;
            HBHome::getInstance()->setDepth(depth);
            qDebug() << "Address" << currentAddress << "- Updated depth:" << depth;
            break;
        case HQmlEnum::SPEED_H: // SPEED_H
            Speed_H = value;
            break;
        case HQmlEnum::SPEED_L: // SPEED_H
            Speed_L = value;
            speed = (Speed_H << 16) | Speed_L;
            HBHome::getInstance()->setSpeed(speed);
            qDebug() << "Address" << currentAddress << "- Updated speed:" << speed;
            break;
        case HQmlEnum::MAX_SPEED_H: // MAX_SPEED_H
            MaxSpeed_H = value;
            break;
        case HQmlEnum::MAX_SPEED_L: // MAX_SPEED_L
            MaxSpeed_L = value;
            maxSpeed = (MaxSpeed_H << 16) | MaxSpeed_L;
            HBHome::getInstance()->setMaxSpeed(maxSpeed);
            qDebug() << "Address" << currentAddress << "- Updated maxSpeed:" << maxSpeed;
            break;
        case HQmlEnum::TARGET_DEPTH_H: // MAX_SPEED_H
            TargetDepth_H = value;
            break;
        case HQmlEnum::TARGET_DEPTH_L: // MAX_SPEED_L
            TargetDepth_L = value;
            targetDepth = (TargetDepth_H << 16) | TargetDepth_L;
            HBHome::getInstance()->setTargetDepth(targetDepth);
            qDebug() << "Address" << currentAddress << "- Updated targetDepth:" << targetDepth;
            break;

        case HQmlEnum::METER_DEPTH_H: // 表套深度高
            TargetDepth_H = value;
            break;
        case HQmlEnum::METER_DEPTH_L: //
            TargetDepth_L = value;
            targetDepth = (TargetDepth_H << 16) | TargetDepth_L;
            HBHome::getInstance()->setTargetDepth(targetDepth);
            qDebug() << "Address" << currentAddress << "- Updated targetDepth:" << targetDepth;
            break;
        case HQmlEnum::PULSE: // PULSE
            plus = value;
            HBHome::getInstance()->setPulse(plus);
            qDebug() << "Address" << currentAddress << "- Updated plus:" << plus;
            break;
        case HQmlEnum::TENSION_H: // TENSION_H
            Tension_H = value;
            break;
        case HQmlEnum::TENSION_L: // TENSION_L
            Tension_L = value;
            tension = (Tension_H << 16) | Tension_L;
            HBHome::getInstance()->setTension(tension);
            qDebug() << "Address" << currentAddress << "- Updated tension:" << tension;
            break;
        case HQmlEnum::TENSION_INCREMENT_H: // TENSION_INCREMENT_H
            TensionIncrement_H = value;
            break;
        case HQmlEnum::TENSION_INCREMENT_L: // TENSION_INCREMENT_L
            TensionIncrement_L = value;
            tensionIncrement = (TensionIncrement_H << 16) | TensionIncrement_L;
            HBHome::getInstance()->setTensionIncrement(tensionIncrement);
            qDebug() << "Address" << currentAddress << "- Updated tensionIncrement:" << tensionIncrement;
            break;
        case HQmlEnum::K_VALUE:
            K_Value = value;
            HBHome::getInstance()->setKValue(K_Value);
            qDebug() << "Address" << currentAddress << "- Updated K_Value:" << K_Value;
            break;
        case HQmlEnum::MAX_TENSION_H: // MAX_TENSION_H
            MaxTension_H = value;
            break;
        case HQmlEnum::MAX_TENSION_L: // MAX_TENSION_L
            MaxTension_L = value;
            maxTension = (MaxTension_H << 16) | MaxTension_L;
            HBHome::getInstance()->setMaxTension(maxTension);
            qDebug() << "Address" << currentAddress << "- Updated maxTension:" << maxTension;
            break;
        case HQmlEnum::MAX_TENSION_INCREMENT_H: // MAX_TENSION_INCREMENT_L
            MaxTensionIncrement_H = value;
            break;
        case HQmlEnum::MAX_TENSION_INCREMENT_L: // MAX_TENSION_INCREMENT_L
            MaxTensionIncrement_L = value;
            maxTensionIncrement = (MaxTensionIncrement_H << 16) | MaxTensionIncrement_L;
            HBHome::getInstance()->setMaxTensionIncrement(maxTensionIncrement);
            qDebug() << "Address" << currentAddress << "- Updated maxTensionIncrement:" << maxTensionIncrement;
            break;

        case HQmlEnum::CABLE_TENSION_H: // CABLE_TENSION_H
            CableTension_H = value;
            break;
        case HQmlEnum::CABLE_TENSION_L: // CABLE_TENSION_L
            CableTension_L = value;
            cableTension = (CableTension_H << 16) | CableTension_L;
            HBHome::getInstance()->setHarnessTension(cableTension);
            qDebug() << "Address" << currentAddress << "- Updated cableTension:" << cableTension;
            break;

        case HQmlEnum::CURRENT_TENSION_SAFE_H: // CURRENT_TENSION_SAFE_H
            currentTensionSafe_H = value;
            break;
        case HQmlEnum::CURRENT_TENSION_SAFE_L: // CURRENT_TENSION_SAFE_L
            currentTensionSafe_L = value;
            currentTensionSafe = (currentTensionSafe_H << 16) | currentTensionSafe_L;
            TensionSafe::getInstance()->setCurrentTensionSafe( QString::number(currentTensionSafe));
            qDebug() << "Address" << currentAddress << "- Updated currentTensionSafe:" << currentTensionSafe;
            break;

        case HQmlEnum::CIRRENT_TENSION_MAX_H: // CIRRENT_TENSION_MAX_H
            maxTensionSafe_H = value;
            break;
        case HQmlEnum::CIRRENT_TENSION_MAX_L: // CIRRENT_TENSION_MAX_L
            maxTensionSafe_L = value;
            maxTensionSafe = (maxTensionSafe_H << 16) | maxTensionSafe_L;
            TensionSafe::getInstance()->setMAXTensionSafe(QString::number(maxTensionSafe));
            qDebug() << "Address" << currentAddress << "- Updated maxTensionSafe:" << maxTensionSafe;
            break;

//        case HQmlEnum::CABLE_TENSION_H: // CIRRENT_TENSION_MAX_H
//            currentHarnessTension_H = value;
//            break;
//        case HQmlEnum::CABLE_TENSION_L: // CIRRENT_TENSION_MAX_L
//            currentHarnessTension_L = value;
//            currentHarnessTension = (currentHarnessTension_H << 16) | currentHarnessTension_L;
//            TensionSafe::getInstance()->setMAXTensionSafe(QString::number(currentHarnessTension));
//            qDebug() << "Address" << currentAddress << "- Updated currentHarnessTension:" << currentHarnessTension;
//            break;

        case HQmlEnum::HARNESS_TENSION_TREND: // HARNESS_TENSION_TREND
            cableTensionTrend = value;
            TensionSafe::getInstance()->setCableTensionTrend(QString::number(cableTensionTrend));
            qDebug() << "Address" << currentAddress << "- Updated cableTensionTrend:" << cableTensionTrend;
            break;

        case HQmlEnum::PARKING_SAFE_TIME: // PARKING_SAFE_TIME
            ptime = value;
            TensionSafe::getInstance()->setPtime(QString::number(ptime));
            qDebug() << "Address" << currentAddress << "- Updated cableTensionTrend:" << cableTensionTrend;
            break;

        case HQmlEnum::CODE_COUNT_H: // CODE_COUNT_H
            depthLoss_H = value;
            break;

        case HQmlEnum::CODE_COUNT_L: // CODE_COUNT_L
            depthLoss_L = value;
            depthLoss = (depthLoss_H << 16) | depthLoss_L;
            TensionSafe::getInstance()->setDepthLoss(QString::number(depthLoss));
            qDebug() << "Address" << currentAddress << "- Updated depthLoss:" << depthLoss;
            break;

        case HQmlEnum::DEPTH_CODE1_H: // DEPTH_CODE1_H
            currentDepth1_H = value;
            break;

        case HQmlEnum::DEPTH_CODE1_L: // DEPTH_CODE1_L
            currentDepth1_L = value;
            currentDepth1 = (currentDepth1_H << 16) | currentDepth1_L;
            TensionSafe::getInstance()->setDepthLoss(QString::number(currentDepth1));
            qDebug() << "Address" << currentAddress << "- Updated currentDepth1:" << currentDepth1;
            break;

        case HQmlEnum::DEPTH_CODE2_H: // DEPTH_CODE2_H
            currentDepth2_H = value;
            break;

        case HQmlEnum::DEPTH_CODE2_L: // DEPTH_CODE2_L
            currentDepth2_L = value;
            currentDepth2 = (currentDepth2_H << 16) | currentDepth2_L;
            TensionSafe::getInstance()->setDepthLoss(QString::number(currentDepth2));
            qDebug() << "Address" << currentAddress << "- Updated currentDepth2:" << currentDepth2;
            break;

        case HQmlEnum::DEPTH_CODE3_H: // DEPTH_CODE3_H
            currentDepth3_H = value;
            break;

        case HQmlEnum::DEPTH_CODE3_L: // DEPTH_CODE3_L
            currentDepth3_L = value;
            currentDepth3 = (currentDepth3_H << 16) | currentDepth3_L;
            TensionSafe::getInstance()->setDepthLoss(QString::number(currentDepth3));
            qDebug() << "Address" << currentAddress << "- Updated currentDepth3:" << currentDepth3;
            break;

        case HQmlEnum::SCALE_1_H:
            scale1_H = value;
            break;

        case HQmlEnum::SCALE_1_L:
            scale1_L = value;
            m_scale1 = (scale1_H << 16) | scale1_L;
            Tensiometer::getInstance()->setScale1(m_scale1);
            qDebug() << "Address" << currentAddress << "- Updated m_scale1:" << m_scale1;
            break;

        case HQmlEnum::SCALE_2_H:
            scale2_H = value;
            break;

        case HQmlEnum::SCALE_2_L:
            scale2_L = value;
            m_scale2 = (scale2_H << 16) | scale2_L;
            Tensiometer::getInstance()->setScale2(m_scale2);
            qDebug() << "Address" << currentAddress << "- Updated m_scale2:" << m_scale2;
            break;

        case HQmlEnum::SCALE_3_H:
            scale3_H = value;
            break;

        case HQmlEnum::SCALE_3_L:
            scale3_L = value;
            m_scale3 = (scale3_H << 16) | scale3_L;
            Tensiometer::getInstance()->setScale3(m_scale3);
            qDebug() << "Address" << currentAddress << "- Updated scale3_L:" << scale3_L;
            break;
        case HQmlEnum::SCALE_4_H:
            scale4_H = value;
            break;

        case HQmlEnum::SCALE_4_L:
            scale4_L = value;
            m_scale4 = (scale4_H << 16) | scale4_L;
            Tensiometer::getInstance()->setScale1(m_scale4);
            qDebug() << "Address" << currentAddress << "- Updated m_scale4:" << m_scale4;
            break;
        case HQmlEnum::SCALE_5_H:
            scale5_H = value;
            break;

        case HQmlEnum::SCALE_5_L:
            scale5_L = value;
            m_scale5 = (scale5_H << 16) | scale5_L;
            Tensiometer::getInstance()->setScale1(m_scale5);
            qDebug() << "Address" << currentAddress << "- Updated m_scale5:" << m_scale5;
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
    if (!modbus || modbus->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus is not connected.";
        return;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, values.size());
    for (int i = 0; i < values.size(); ++i) {
        writeUnit.setValue(i, values[i]);
    }

    if (QModbusReply *reply = modbus->sendWriteRequest(writeUnit, 1)) { // Slave ID = 1
        connect(reply, &QModbusReply::finished, this, [reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "Write successful.";
            } else {
                qWarning() << "Write failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send write request:" << modbus->errorString();
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

void HBModbusClient::readCoils()
{
    if (!modbus || modbus->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus not connected";
        return;
    }

    QModbusDataUnit request(QModbusDataUnit::Coils, HQmlEnum::ALARM_SPEED, 12);

    if (auto *reply = modbus->sendReadRequest(request, 1)) {
        connect(reply, &QModbusReply::finished, this, [this, reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                handleCoilResult(reply->result());
            } else {
                qWarning() << "Coil read failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send coil read request:" << modbus->errorString();
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

    ModbusData modData;
    modData.wellNumber = WellParameter::getInstance()->WellNumber();
    modData.operateType = WellParameter::getInstance()->OperatorType();
    modData.operater = WellParameter::getInstance()->UserName();
    modData.depth = depth;
    modData.velocity = speed;
    modData.tensions = tension;
    modData.tensionIncrement = tensionIncrement;
    modData.harnessTension = cableTension;
    modData.maxTension = maxTension;
    modData.safetyTension = currentTensionSafe;
    modData.exception = "无";

    // HBDatabase::getInstance().insertHistoryData(modData);
    QtConcurrent::run([modData]() {
        HBDatabase::getInstance().insertHistoryData(modData);
    });
}

void HBModbusClient::writeCoil(int address, int value)
{
    if (!modbus || modbus->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus not connected";
        return;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, address, 1);
    writeUnit.setValue(0, value ? 1 : 0); // 确保是 0 或 1

    int serverAddress = 1;

    if (auto *reply = modbus->sendWriteRequest(writeUnit, serverAddress)) {
        connect(reply, &QModbusReply::finished, this, [reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "Coil write successful";
            } else {
                qWarning() << "Failed to write coil:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send coil write request:" << modbus->errorString();
    }
}
