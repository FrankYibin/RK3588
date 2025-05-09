#include "hbmodbusclient.h"
#include <QDebug>
#include <QSerialPort>
#include <QModbusReply>
#include "c++Source/HBQmlEnum.h"
#include "c++Source/HBScreen/hbhome.h"

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

    modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM7");
    // modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "ttyS0");
    modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
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

    if (auto *reply = modbus->sendReadRequest(request, 1)) { // Slave ID 1
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
    // 每次定时器触发，连续发三次读取
    readRegister(HQmlEnum::DEPTH_H,HQmlEnum::DEPTH_L); //9-29
    readRegister(HQmlEnum::TENSION_H,HQmlEnum::SPEED_CONTROL_L); //32-58
    readRegister(HQmlEnum::TENSION_BAR_TONNAGE,HQmlEnum::DEPTH_TENSION_STATE); //67-84

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
        case HQmlEnum::DEPTH_H: // DEPTH_H
            Depth_H = value;
            break;
        case HQmlEnum::DEPTH_L: // DEPTH_L
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
        case HQmlEnum::MAX_SPEED_H: // MAX_SPEED_H
            MaxSpeed_H = value;
            break;
        case HQmlEnum::MAX_SPEED_L: // MAX_SPEED_L
            MaxSpeed_L = value;
            maxSpeed = (MaxSpeed_H << 16) | MaxSpeed_L;
            HBHome::getInstance()->setMaxSpeed(maxSpeed);
            qDebug() << "Address" << currentAddress << "- Updated maxSpeed:" << maxSpeed;
            break;
        case HQmlEnum::MAX_DEPTH_H: // MAX_SPEED_H
            TargetDepth_H = value;
            break;
        case HQmlEnum::MAX_DEPTH_L: // MAX_SPEED_L
            TargetDepth_L = value;
            targetDepth = (TargetDepth_H << 16) | TargetDepth_L;
            HBHome::getInstance()->setTargetDepth(targetDepth);
            qDebug() << "Address" << currentAddress << "- Updated maxSpeed:" << maxSpeed;
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

        default:
            // 其他地址不处理
            break;
        }

    }
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
