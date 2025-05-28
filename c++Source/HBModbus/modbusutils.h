#ifndef MODBUSUTILS_H
#define MODBUSUTILS_H

#include <QObject>
#include <QPair>
#include <QVector>


class HBModbusClient;

class ModbusUtils : public QObject
{
    Q_OBJECT
public:
    explicit ModbusUtils(QObject *parent = nullptr);

    // // 将浮动数转换为 Modbus 寄存器格式（假设精度为 0.01）
    // Q_INVOKABLE QList<quint16> floatToModbusRegisters(float value);

    // // 将 Modbus 寄存器格式转换为浮动数
    // Q_INVOKABLE float modbusRegistersToFloat(const QList<quint16>& registers);

    Q_INVOKABLE void writeScaledValue(const QString &value, int address, float scale = 100.0f);

    // Q_INVOKABLE QString readScaledModbusValue( int address) const;


    // 设置 ModbusClient（需注入）
    void setModbusClient(HBModbusClient *client);
signals:

private:
     HBModbusClient *m_client = nullptr;
};

#endif // MODBUSUTILS_H
