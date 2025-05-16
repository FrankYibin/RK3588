#include "modbusutils.h"

ModbusUtils::ModbusUtils(QObject *parent)
    : QObject{parent}
{}
QList<quint16> ModbusUtils::floatToModbusRegisters(float value)
{
    quint16 high = static_cast<quint16>(value * 100);  // 精度 0.01 转换为整数
    quint16 low = static_cast<quint16>(value * 100) >> 16;
    return QList<quint16>{high, low};
}

float ModbusUtils::modbusRegistersToFloat(const QList<quint16>& registers)
{
    if (registers.size() == 2) {
        quint16 high = registers[0];
        quint16 low = registers[1];
        float value = high + low / 100.0f;  // 还原为浮动数
        return value;
    }
    return 0.0f;  // 处理错误情况
}
