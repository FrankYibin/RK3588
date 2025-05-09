#include "rs232.h"

RS232::RS232(QObject *parent)
    : QObject(parent){}

int RS232::SerialPort() const
{
    return m_serialPort;
}

int RS232::BaudRate() const
{
    return m_baudRate;
}

int RS232::DataBits() const
{
    return m_dataBits;
}

int RS232::SerialType() const
{
    return m_serialType;
}

// Setters
void RS232::setSerialPort(int port)
{
    if (m_serialPort != port) {
        m_serialPort = port;
        emit SerialPortChanged();
    }
}

void RS232::setBaudRate(int baud)
{
    if (m_baudRate != baud) {
        m_baudRate = baud;
        emit BaudRateChanged();
    }
}

void RS232::setDataBits(int bits)
{
    if (m_dataBits != bits) {
        m_dataBits = bits;
        emit DataBitsChanged();
    }
}

void RS232::setSerialType(int type)
{
    if (m_serialType != type) {
        m_serialType = type;
        emit SerialTypeChanged();
    }
}
