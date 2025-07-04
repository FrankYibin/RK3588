﻿#include "modbusutils.h"
#include "hbmodbusclient.h"
#include <QDebug>
#include <QtMath>
#include "c++Source/HBQmlEnum.h"

ModbusUtils::ModbusUtils(QObject *parent)
    : QObject{parent}
{}
// QList<quint16> ModbusUtils::floatToModbusRegisters(float value)
// {
//     quint32 scaled = static_cast<quint32>(value * 100); // 精度 0.01
//     quint16 high = static_cast<quint16>((scaled >> 16) & 0xFFFF);
//     quint16 low  = static_cast<quint16>(scaled & 0xFFFF);
//     return QList<quint16>{high, low};
// }

// float ModbusUtils::modbusRegistersToFloat(const QList<quint16>& registers)
// {
//     if (registers.size() == 2) {
//         quint32 combined = (static_cast<quint32>(registers[0]) << 16) | registers[1];
//         return static_cast<float>(combined) / 100.0f;
//     }
//     return 0.0f;
// }

void ModbusUtils::setModbusClient(HBModbusClient *client)
{
    m_client = client;
}

void ModbusUtils::writeScaledValue(const QString &value, int address, float scale)
{
    if (!m_client)
        return;

    bool ok = false;
    float floatValue = value.toFloat(&ok);
    if (!ok) {
        qWarning() << "Invalid float string:" << value;
        return;
    }

    int scaledInt = static_cast<int>(floatValue * scale);
    quint16 high = static_cast<quint16>((scaledInt >> 16) & 0xFFFF);
    quint16 low  = static_cast<quint16>(scaledInt & 0xFFFF);

    // m_client->writeRegister(address, QVector<quint16>{high, low});
}


void ModbusUtils::writeScaledValueByIndex(const QString &value, int index, float scale)
{
    int address = -1;

    switch (index) {
    // case 1: address = HQmlEnum::SCALE_1_TENSION_H; break;
    // case 2: address = HQmlEnum::SCALE_2_TENSION_H; break;
    // case 3: address = HQmlEnum::SCALE_3_TENSION_H; break;
    // case 4: address = HQmlEnum::SCALE_4_TENSION_H; break;
    // case 5: address = HQmlEnum::SCALE_5_TENSION_H; break;
    default:
        qWarning() << "Invalid index in writeScaledValueByIndex:" << index;
        return;
    }
    writeScaledValue(value, address, scale);
}
