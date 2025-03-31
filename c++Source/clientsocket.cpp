/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 TLS/SSL tcp/ip socket implementation

**********************************************************************************************************/
#include "clientsocket.h"
#include "protocolformat.h"
#include <QDebug>

#include <QSslConfiguration>
#include <QSslError>
QMutex clientSocket::mutex;
HeartbeatFormat clientSocket::m_HeartbeatValue;
/**************************************************************************//**
*
* \brief Constructor
*        Meanwhile, create a timer to handle with the socket TCP/IP link connecting.
*        Initialize Branson specific slots to connect the readyRead, stateChanged of the QAbstractSocket itself signals.
*        The moveToThread that define all the defined slot function in the object will be run in the thread.
*
* \param address is the server address, port is the server port
*
* \return clientSocket object
*
******************************************************************************/
clientSocket::clientSocket(QHostAddress address, unsigned short port)
    : m_HostAddress(address)
    , m_port(port)
{
    m_PackageDebugRevCounter = 0;
    m_PackageDebugTmtCounter = 0;
    m_ThreadObj = new QThread();
    m_reconnectingTimer = new QTimer();
    connect(m_reconnectingTimer, &QTimer::timeout, this, &clientSocket::slotSocketConnecting);
    connect(this, &QAbstractSocket::readyRead, this, &clientSocket::slotDataReceiving);
    connect(this, &clientSocket::signalMessageReadyToSend, this, &clientSocket::slotDataSending);
    connect(this, &QAbstractSocket::stateChanged, this, &clientSocket::slotSocketStateChange, Qt::QueuedConnection);
    connect(this, &clientSocket::signalSocketReadyToClose, this, &clientSocket::slotSocketDisconnected);
    connect(this, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));

    m_SocketErr = clientSocket::NoErr;
    m_RecvBuffMap.clear();
    m_SendBuffMap.clear();
    m_reconnectingTimer->setInterval(MAX_CONNECT_WAIT_TIME_CLIENT);
    // m_reconnectingTimer->start();
    this->moveToThread(m_ThreadObj);
    m_ThreadObj->start();

}

/**************************************************************************//**
*
* \brief Destructor
*        Destroy m_ThreadObj object.
*        Destroy the reconnectingTimer object.
*        Close the existing TCP/IP link.
* \param none
*
* \return none
*
******************************************************************************/
clientSocket::~clientSocket()
{
    if(m_ThreadObj != nullptr)
    {
        m_ThreadObj->quit();
        m_ThreadObj->wait();
        m_ThreadObj->deleteLater();
    }
    this->deleteLater();
}

/**************************************************************************//**
*
* \brief The Interface function for the data sending for the external function call.
*
* \param key is the command, buff is what data will be sent out from buff.
*
* \return If the socket is not connected, it will return false.
*
******************************************************************************/
bool clientSocket::insertMessageToMap(const int key, const QByteArray buff)
{
    bool bResult = false;
    if(this->state() == QAbstractSocket::ConnectedState)
    {
        if(this->isEncrypted())
            m_SendBuffMap.insert(key, buff);
        bResult = true;
        emit signalMessageReadyToSend();
    }
    else
        bResult = false;
    return bResult;
}

/**************************************************************************//**
*
* \brief The interface function for the data extracted from the external function call.
*
* \param key is the command that indicate what the data should be get from m_RecvBuffMap.
*        buff is the value section only of the protocol format that has been parsed in the data slotDataReceiving function.
*
* \return if the request command is not any response so there is not any data in the m_RecvBuffMap, it will return false.
*
******************************************************************************/
bool clientSocket::getMessageFromMap(const int key, QByteArray &buff)
{
    bool bResult = false;
    if(m_RecvBuffMap.contains(key) == false)
        bResult = false;
    else
    {
        buff = m_RecvBuffMap[key];
        m_RecvBuffMap.remove(key);
        bResult = true;
    }
    return bResult;
}

/**************************************************************************//**
*
* \brief The interface function for the socket close.
*        1. stop reconnecting timer and delete timer object.
*        2. clear m_RecvBuffMap and m_SendBuffMap.
*        3. emit signal so the socket object destory can be run on the thread.
*
* \param none
*
* \return none
*
******************************************************************************/
void clientSocket::socketReadyToClose()
{
    if(m_reconnectingTimer->isActive() == true)
        m_reconnectingTimer->stop();
    delete m_reconnectingTimer;
    m_reconnectingTimer = nullptr;
    m_RecvBuffMap.clear();
    m_SendBuffMap.clear();
    emit signalSocketReadyToClose();
}

/**************************************************************************//**
*
* \brief In order to disconnect the current socket link from the external,
* the socket provides the interface to handle with this request.
* We have to use the signal to close the socket link, because the socket is running on the child thread.
*
* \param none
*
* \return none
*
******************************************************************************/
void clientSocket::socketCloseForReconnect()
{
    emit signalSocketReadyToClose();
}

/**************************************************************************//**
*
* \brief In order to set the current socket status and notify the status to the external when the status changes,
* 		 there is the interface for the current socket status setting.
* 		 If the status changes is different with previous,
* 		 the m_SocketErr status will be changed and the notification signal will be sent out as well.
*
* \param SocketErr it has defined in the Enum ErrorCode.
*
* \return None.
*
******************************************************************************/
void clientSocket::setSocketErrorCode(const clientSocket::ErrorCode SocketErr)
{
    if(SocketErr != m_SocketErr)
    {
        m_SocketErr = SocketErr;
        emit signalErrorCodeChanged();
    }
}

/**************************************************************************//**
*
* \brief In order to get the current Socket status, there is the interface for the external recall in any time.
*
* \param None.
*
* \return m_SocketErr
*
******************************************************************************/
clientSocket::ErrorCode clientSocket::getSocketErrorCode()
{
    return m_SocketErr;
}

/**************************************************************************//**
*
* \brief heartbeat Message Process. It is the interface function. Once the heartbeat message is parsed,
* the Cycle Number and Active Recipe Number will be updated.
* If there is any alarm happened, the alarm ID will be sent out and notify the alarm message screen to show up the alarm message.
*
* \param message is the received heartbeat response message.
*
* \return If the message doesn't match up the heartbeat structure, it will return the false result.
*
******************************************************************************/
bool clientSocket::heartbeatMessageProcess(const QByteArray message)
{
    bool bResult = false;
    HeartbeatFormat heartbeatStructure;
    if(ProtocolFormat::parseHeartbeatMessage(message, &heartbeatStructure) == true)
    {
#ifdef COMMUNICATION_TEST
        qDebug()<<"Cycle Number: "<<heartbeatStructure.m_cycleNum;
        qDebug()<<"Cycle Time: "<<heartbeatStructure.m_cycleTime;
        qDebug()<<"Active Recipe Number: "<<heartbeatStructure.m_activeRecipeNum;
        qDebug()<<"Alarm ID: "<<heartbeatStructure.m_alarmId;
        qDebug()<<"Power Value: "<<heartbeatStructure.m_powerValue;
#endif
        if(heartbeatStructure != m_HeartbeatValue)
        {
            m_HeartbeatValue = heartbeatStructure;
            emit signalHeartbeatUpdated(&m_HeartbeatValue);
        }
        if(heartbeatStructure.m_alarmId != 0)
            emit signalAlarmCodeToNotify(heartbeatStructure.m_alarmId);
        bResult = true;
    }
    return bResult;
}

/**************************************************************************//**
*
* \brief handle with some specific ssl error that can be ignored for the communication.
*
* \param QSsError that is the enum
*
* \return none
*
******************************************************************************/
void clientSocket::handleSslError(const QSslError &error)
{
    qDebug() << error.errorString();
    switch(error.error())
    {
    case QSslError::NoError:
        break;
    case QSslError::UnableToGetIssuerCertificate:
        break;
    case QSslError::UnableToDecryptCertificateSignature:
        break;
    case QSslError::UnableToDecodeIssuerPublicKey:
        break;
    case QSslError::CertificateSignatureFailed:
        break;
    case QSslError::CertificateNotYetValid:
        break;
    case QSslError::CertificateExpired:
        this->ignoreSslErrors();
        break;
    case QSslError::InvalidNotBeforeField:
        break;
    case QSslError::InvalidNotAfterField:
        break;
    case QSslError::SelfSignedCertificate:
        this->ignoreSslErrors();
        break;
    case QSslError::SelfSignedCertificateInChain:
        break;
    case QSslError::UnableToGetLocalIssuerCertificate:
        break;
    case QSslError::UnableToVerifyFirstCertificate:
        break;
    case QSslError::CertificateRevoked:
        break;
    case QSslError::InvalidCaCertificate:
        break;
    case QSslError::PathLengthExceeded:
        break;
    case QSslError::InvalidPurpose:
        break;
    case QSslError::CertificateUntrusted:
        break;
    case QSslError::CertificateRejected:
        break;
    case QSslError::SubjectIssuerMismatch:
        break;
    case QSslError::AuthorityIssuerSerialNumberMismatch:
        break;
    case QSslError::NoPeerCertificate:
        break;
    case QSslError::HostNameMismatch:
        this->ignoreSslErrors();
        break;
    case QSslError::UnspecifiedError:
        this->ignoreSslErrors();
        break;
    case QSslError::NoSslSupport:
        break;
    default:
        qDebug() << "no match any ssl error.";
        break;
    }
}

/**************************************************************************//**
*
* \brief It is the slot function to read the data to the cache buffer when the readyRead signal happened.
*
*
* \param none.
*
* \return none.
*
******************************************************************************/
void clientSocket::slotDataReceiving()
{
    QByteArray dataBuff;
    QByteArray oneFullProtocolPackage, message;
    int key;

    while(this->bytesAvailable() > 0)
    {
        //TODO still need to do the protocol integrity checking and to insert to the m_RecvBuffMap then.
        /* dataBuff is the test code only.*/
        dataBuff.append(this->readAll());
        oneFullProtocolPackage.clear();

        if(ProtocolFormat::isFullProtocolPackage(dataBuff, oneFullProtocolPackage) == false)
        {
            setSocketErrorCode(clientSocket::DataFormatErr);
        }
        else
        {
            if(ProtocolFormat::parseProtocolPackage(key, message, oneFullProtocolPackage))
            {
                if(key == 0) //heartbeat command
                {
                    if(heartbeatMessageProcess(message) == false)
                        qDebug()<<"There are some data missing in the heartbeat message";
                }
#ifdef COMMUNICATION_TEST
                m_PackageDebugRevCounter++;
                QDateTime current_date_time = QDateTime::currentDateTime();
                QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
                qDebug()<<"Total Received packages: "<<m_PackageDebugRevCounter<<"------"<<current_date;
#endif
                m_RecvBuffMap.insert(key, message);
                setSocketErrorCode(clientSocket::NewDataComming);
            }
            else
            {
                setSocketErrorCode(clientSocket::ResponseErr);
            }
            dataBuff.remove(0, oneFullProtocolPackage.size());
        }
    }
    dataBuff.clear();
}

/**************************************************************************//**
*
* \brief It is the slot function for the TCP/IP link state checking and debug.
*
* \param none
*
* \return none
*
******************************************************************************/
void clientSocket::slotSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        setSocketErrorCode(clientSocket::ConnectErr);
        qDebug()<<"Socket status：UnconnectedState";
        break;
    case QAbstractSocket::HostLookupState:
        qDebug()<<"Socket status：HostLookupState";
        break;
    case QAbstractSocket::ConnectingState:
        qDebug()<<"Socket status：ConnectingState";
        break;
    case QAbstractSocket::ConnectedState:
        setSocketErrorCode(clientSocket::NoErr);
        qDebug()<<"Socket status：ConnectedState";
        break;
    case QAbstractSocket::BoundState:
        qDebug()<<"Socket status：BoundState";
        break;
    case QAbstractSocket::ClosingState:
        qDebug()<<"Socket status：ClosingState";
        break;
    case QAbstractSocket::ListeningState:
        qDebug()<<"Socket status：ListeningState";
        break;
    }
}

/**************************************************************************//**
*
* \brief It is the slot function to implement TCP/IP link connecting.
* Once the link disconnected is detected, the reconnecting timer will be restarted.
*
* \param none.
*
* \return none.
*
******************************************************************************/
void clientSocket::slotSocketConnecting()
{
    if(this->state() == QAbstractSocket::ConnectedState)
    {
        if(!this->isEncrypted())
        {
            this->slotSocketDisconnected();
            setSocketErrorCode(clientSocket::SecurityErr);
        }
		else
		{
        	setSocketErrorCode(clientSocket::AlreadyConnected);
		}
        return;
    }
    qDebug()<<"reconnecting...";
    this->connectToHostEncrypted(m_HostAddress.toString(), m_port);
    if(!this->waitForEncrypted(MAX_CONNECT_WAIT_TIME_CLIENT))
    {
//        qDebug()<<this->errorString();
        setSocketErrorCode(clientSocket::ConnectErr);
    }
}

/**************************************************************************//**
*
* \brief Socket Disconnect slot. As the description, the any socket operation should be at the same level thread.
* 		 We need to use signal and slot to run the socket closing process in the child thread.
* 		 In order to avoid any crash from SC,
* 		 there is the time waiting to make sure the last package can be sent out from SC before the socket close.
*
* \param None.
*
* \return None.
*
******************************************************************************/
void clientSocket::slotSocketDisconnected()
{
    this->waitForReadyRead(MAX_READ_WAIT_TIME_CLIENT);
    this->disconnectFromHost();
    if (this->state() == QAbstractSocket::UnconnectedState
        || this->waitForDisconnected(MAX_DISCONNECT_WAIT_TIME_CLIENT)) {
            qDebug("Disconnected!");
    }
    this->close();
    setSocketErrorCode(clientSocket::SocketClosed);
}

/**************************************************************************//**
*
* \brief Implement data sending. Define static mutex to avoid any reentrancy happens.
*        The slot will run in the thread.
* \param None
*
* \return None
*
******************************************************************************/
void clientSocket::slotDataSending()
{
    QByteArray dataBuff;
    int firstKey;
    int retried = 0;
    mutex.lock();
    while((m_SendBuffMap.size() > 0) && (this->state() == QAbstractSocket::ConnectedState))
    {
        firstKey = m_SendBuffMap.firstKey();
        ProtocolFormat::buildProtocolPackage(firstKey, m_SendBuffMap[firstKey], dataBuff);
        if((this->write(dataBuff) != -1) && this->waitForBytesWritten() != false)
        {
#ifdef COMMUNICATION_TEST
            m_PackageDebugTmtCounter++;
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
            qDebug()<<"Total Sent out packages: "<<m_PackageDebugTmtCounter<<"------"<<current_date;
#endif
            m_SendBuffMap.remove(firstKey);
        }
        else if(retried < 3)
        {
            qDebug()<<this->errorString();
            retried++;
        }
        else
        {
            m_SendBuffMap.clear();
            slotSocketDisconnected();
            setSocketErrorCode(clientSocket::SocketErr);
            break;
        }
    }
    mutex.unlock();
}

void clientSocket::slotSslErrors(const QList<QSslError> &errors)
{
    for(int i = 0 ;i < errors.count(); i++)
    {
        QSslError SslError = errors.at(i);
        handleSslError(SslError);
    }
}
