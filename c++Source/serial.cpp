#include "serial.h"
#include <QDebug>
// #include <QSerialPort>
Serial* Serial::_ptrSerial = nullptr;
Serial::Serial(QSerialPort *parent)
    : QSerialPort{parent}
{
    //Register QSerialPort::SerialPortError type
    qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
    m_iDevNum = -1;
#ifdef RK3588
    m_strDevName = "/dev/ttyS8";
#else
    m_strDevName = "/dev/ttyUSB0";
#endif
    m_iBandrate = 9600;
    m_DataBits = QSerialPort::Data8;
    m_Parity = QSerialPort::NoParity;
    m_StopBits = QSerialPort::OneStop;
    if(this->isOpen() == true)
        this->close();

}

Serial *Serial::GetInstance()
{
    if (!_ptrSerial) {
        _ptrSerial = new Serial();
    }
    return _ptrSerial;
}

Serial::~Serial()
{
    if(this->isOpen() == true)
        this->close();
}

bool Serial::Open_Serial_Port()
{
    bool bResult = false;
    if(this->isOpen() == true)
        return bResult;
    this->setPortName(m_strDevName);
    qDebug() << "name: " << this->portName();
    this->setBaudRate(m_iBandrate);
    qDebug() << "Baudrate: " << this->baudRate();
    this->setDataBits(m_DataBits);
    qDebug() << "Databits: " << this->dataBits();
    this->setParity(m_Parity);
    qDebug() << "Parity: " << this->parity();
    this->setStopBits(m_StopBits);
    qDebug() << "Stop: " << this->stopBits();
    this->setFlowControl(QSerialPort::NoFlowControl);
    connect(this, SIGNAL(readyRead()),      this, SLOT(slotReadyToRead()), Qt::QueuedConnection);
    connect(this, &QSerialPort::errorOccurred,  this, &Serial::slotErrorOccurred, Qt::QueuedConnection);
    if(this->open(QIODevice::ReadWrite) == false)
    {
        this->close();
    }
    else
    {
        this->clearError();
        this->clear();
        bResult = true;
        qDebug() << this->portName() << " is Open!!!";
    }
    return bResult;
}

bool Serial::SetDevName(const QString name)
{
    m_strDevName = name;
    return true;
}

bool Serial::SetBandrate(const int bandrate)
{
    m_iBandrate = bandrate;
    return true;
}

bool Serial::SetDataBits(const QSerialPort::DataBits dataBits)
{
    m_DataBits = dataBits;
    return true;
}

bool Serial::SetParity(const QSerialPort::Parity parity)
{
    m_Parity = parity;
    return true;
}

bool Serial::SetStopBits(const QSerialPort::StopBits stopBits)
{
    m_StopBits = stopBits;
    return true;
}

bool Serial::Close_Serial_Port()
{
    if(this->isOpen() == true)
    {
        this->close();
        disconnect(this, &QSerialPort::readyRead,       this, &Serial::slotReadyToRead);
        disconnect(this, &QSerialPort::errorOccurred,   this, &Serial::slotErrorOccurred);
    }
    return true;
}

bool Serial::Write_Serial_Port(QByteArray array)
{

    if(this->isOpen() == true)
    {
        this->write(array.constData(), array.count());
    }
    return true;
}

void Serial::SetDevNum(const int devNum)
{
    m_iDevNum = devNum;
}

int Serial::GetDevNum() const
{
    return m_iDevNum;
}

bool Serial::GetStatus() const
{
    if(this->isOpen() == true)
        return true;
    else
        return false;
}

void Serial::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
}

void Serial::slotReadyToRead()
{
    while(this->waitForReadyRead(1000) == true);
    QByteArray DataBuffer;
    QString strBuffer;
    DataBuffer.clear();
    DataBuffer = this->readAll();
    strBuffer = DataBuffer.data();
    if(strBuffer.size() == 0)
        return;
    try
    {
        qDebug() << "Receive: " << strBuffer;
        emit signalResultReady(m_iDevNum, strBuffer); //Send the signal to Serial APP
        strBuffer.clear();
    }
    catch(...)
    {
        qDebug() << this->portName() << ":" << this->errorString();
    }
}

void Serial::slotErrorOccurred(QSerialPort::SerialPortError error)
{
    switch(error)
    {
    case QSerialPort::WriteError:
        qDebug()<< QString("An I/O error occurred while writing the data to port 1%, error: %2")
                    .arg(this->portName()).arg(this->errorString());
        break;
    case QSerialPort::ReadError:
        qDebug()<< QString("An I/O error occurred while reading the data to port 1%, error: %2")
                    .arg(this->portName()).arg(this->errorString());
        break;
    default:
        break;
    }
}
