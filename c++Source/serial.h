#ifndef SERIAL_H
#define SERIAL_H
#include <QtSerialPort/QSerialPort>
#include <QObject>
class Serial : public QSerialPort
{
    Q_OBJECT
private:
    int m_iDevNum;
    QString                 m_strDevName;
    int                     m_iBandrate;
    QSerialPort::DataBits   m_DataBits;
    QSerialPort::Parity     m_Parity;
    QSerialPort::StopBits   m_StopBits;
    static Serial* _ptrSerial;
public:
    static Serial* GetInstance();
    ~Serial();
    bool Open_Serial_Port();
    bool SetDevName(const QString name);
    bool SetBandrate(const int bandrate);
    bool SetDataBits(const QSerialPort::DataBits dataBits);
    bool SetParity(const QSerialPort::Parity parity);
    bool SetStopBits(const QSerialPort::StopBits stopBits);
    bool Close_Serial_Port();
    bool Write_Serial_Port(QByteArray array);
    void SetDevNum(const int devNum);
    int GetDevNum() const;
    bool GetStatus() const;
protected:
    explicit Serial(QSerialPort *parent = nullptr);
    void timerEvent(QTimerEvent *event) override;
public slots:
    void slotReadyToRead();
    void slotErrorOccurred(QSerialPort::SerialPortError error);
signals:
    void signalResultReady(int iDev, QString strResult); //Send the signal to Serial APP
};

#endif // SERIAL_H
