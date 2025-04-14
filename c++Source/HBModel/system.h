#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

class System : public QObject
{
    Q_OBJECT
    ///Ground system serial port

    //serial port
    Q_PROPERTY(int SerialPort READ SerialPort WRITE setSerialPort NOTIFY SerialPortChanged FINAL);

    //Baud rate
    Q_PROPERTY(int Baudrate READ Baudrate WRITE setBaudrate NOTIFY BaudrateChanged FINAL);

    //Data bit
    Q_PROPERTY(int DataBit READ DataBit WRITE setDataBit NOTIFY DataBitChanged FINAL);

    //serial Type
    Q_PROPERTY(int SerialType READ SerialType WRITE setSerialType NOTIFY SerialTypeChanged FINAL);

    ///Ground Gauge

    //Ground protocol
    Q_PROPERTY(int GProtocol READ GProtocol WRITE setGProtocol NOTIFY GProtocolChanged FINAL);



public:
    explicit System(QObject *parent = nullptr);



    //serialConnection
    void serialConnection();

signals:

    void SerialPortChanged();

    void BaudrateChanged();

};

#endif // SYSTEM_H
