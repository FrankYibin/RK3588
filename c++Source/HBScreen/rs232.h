#ifndef RS232_H
#define RS232_H

#include <QObject>

class RS232 : public QObject
{
    Q_OBJECT

    //port

    Q_PROPERTY(int SerialPort READ SerialPort WRITE setSerialPort NOTIFY SerialPortChanged);

    //Baud Rate

    Q_PROPERTY(int BaudRate READ BaudRate WRITE setBaudRate NOTIFY BaudRateChanged);

    //Data Bits
    Q_PROPERTY(int DataBits READ DataBits WRITE setDataBits NOTIFY DataBitsChanged );

    //SerialType

    Q_PROPERTY(int SerialType READ SerialType WRITE setSerialType NOTIFY SerialTypeChanged FINAL)


public:
    explicit RS232(QObject *parent = nullptr);

    Q_INVOKABLE int SerialPort() const;

    Q_INVOKABLE void setSerialPort(int port);

    Q_INVOKABLE int BaudRate() const;

    Q_INVOKABLE void setBaudRate(int baud);

    Q_INVOKABLE int DataBits() const;

    Q_INVOKABLE void setDataBits(int bits);

    Q_INVOKABLE int SerialType() const;

    Q_INVOKABLE  void setSerialType(int type);


signals:

    void SerialPortChanged();
    void BaudRateChanged();
    void DataBitsChanged();
    void SerialTypeChanged();

private:

    int m_serialPort;
    int m_baudRate;
    int m_dataBits;
    int m_serialType;


};

#endif // RS232_H
