/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Communication interface class provides the interface for the external that needs to exchange the data with SC.
 
 **********************************************************************************************************/

#include <QDebug>
#include <QtNetwork>
#include "communicationinterface.h"
#include "alarmindexdef.h"
#include "shareDefine.h"
clientSocket* CommunicationInterface::m_ptrSocketObj = nullptr;
int CommunicationInterface::m_TimerId = -1;
CommunicationInterface* CommunicationInterface::m_pCIObj = nullptr;

/**************************************************************************//**
*
* \brief Constructor, to instantiate client socket object in here.
*       Meanwhile start the timer to send heartbeat request with 1s interval.
*
* \param parent object
*
* \return CommunicationInterface object
*
******************************************************************************/
CommunicationInterface::CommunicationInterface(QObject *parent)
    :QObject(parent)
    ,m_iHeartbeatRetried(0)
{
//    m_ptrSocketObj = new clientSocket(QHostAddress("192.168.101.1"), 8080);
    m_ptrSocketObj = new clientSocket(QHostAddress("192.168.1.100"), 1600);
    m_TimerId = startTimer(HEARTBEAT_RATE);
    connect(m_ptrSocketObj, &clientSocket::signalErrorCodeChanged, this, &CommunicationInterface::slotErrorCodeChanged);
    connect(m_ptrSocketObj, &clientSocket::signalAlarmCodeToNotify, this, &CommunicationInterface::slotAlarmCodeToNotify);
    connect(m_ptrSocketObj, &clientSocket::signalHeartbeatUpdated, this, &CommunicationInterface::signalHeartbeatUpdated);
}

/**************************************************************************//**
*
* \brief To build the relationship between the Alarm Index and Socket Error Code.
*
* \param errCode is defined in the ErrorCode enumeration of the clientSocket class.
*
* \return the specific alarm index
*
******************************************************************************/
int CommunicationInterface::mapToAlarmIndex(int errCode)
{
    int alarmId = 0;
    switch (errCode)
    {
    case clientSocket::SocketErr:
//        qDebug()<<"Socket error!";
        alarmId = AlarmIndexEnum::ALARM_HW_PROFINET_OR_IP_NOT_ID;
        break;
    case clientSocket::ConnectErr:
//        qDebug()<<"Connecting error";
        alarmId = AlarmIndexEnum::ALARM_INTERNAL_COMM_ENET;
        break;
    case clientSocket::DataFormatErr:
//        qDebug()<<"Data format error";
        alarmId = 0;
        break;
    case clientSocket::ResponseErr:
//        qDebug()<<"response error";
        alarmId = 0;
        break;
    default:
        alarmId = 0;
        break;
    }
    return alarmId;
}

/**************************************************************************//**
*
* \brief It is the slot to receive the socket status changed signal.
*
* \param None
*
* \return None
*
******************************************************************************/
void CommunicationInterface::slotErrorCodeChanged()
{
    int errcode = m_ptrSocketObj->getSocketErrorCode();
    int alarmId = mapToAlarmIndex(errcode);
    emit signalNotifyAlarm(alarmId);
}

/**************************************************************************//**
*
* \brief It the slot function to map to the clientSocket::signalAlarmCodeToNotify signal. It is the wrap for the clientSocket signal.
* Why we need to design this wrap, because the client socket is the child class in the communication class so it is not able to
* provide any functions/ interface to the external.
*
* \param alarmCode: it will be sent to the Alarm Notification screen for the alarm message showing.
*
* \return none.
*
******************************************************************************/
void CommunicationInterface::slotAlarmCodeToNotify(int alarmCode)
{
    Q_UNUSED(alarmCode)
//    qDebug()<<"Alarm ID: "<<alarmCode;
}

/**************************************************************************//**
*
* \brief To get CommunicationInterface singleton object.
*        The class is designed to the singleton class so the CommunicationInterface object can used in the everywhere
*        without any new instantiation.
*        And the CommunicationInterface object can be get easily using the this function
*        without any external declaration before using.
*
* \param parent object
*
* \return CommunicationInterface singleton object
*
******************************************************************************/
CommunicationInterface *CommunicationInterface::getInstance(QObject *parent)
{
    if(m_pCIObj == nullptr)
    {
        m_pCIObj = new CommunicationInterface(parent);
    }
    return m_pCIObj;
}

/**************************************************************************//**
*
* \brief Destructor
*        To destroy socket object.
*
* \param none
*
* \return none
*
******************************************************************************/
CommunicationInterface::~CommunicationInterface()
{
    delete m_ptrSocketObj;
    m_ptrSocketObj = nullptr;
}

/**************************************************************************//**
*
* \brief It is the interface function for the external in case of any business what want to talk with SC.
*
* \param reqMessageID is the command Id, message is the content that need to send to SC following the command.
*
* \return none.
*
******************************************************************************/
bool CommunicationInterface::sendMessage(const int reqMessageID, const QByteArray message)
{
    if(reqMessageID > 0)
        qDebug()<<"Request MessageID:"<<reqMessageID;
    return m_ptrSocketObj->insertMessageToMap(reqMessageID, message);
}

/**************************************************************************//**
*
* \brief It is the interface function for the external in case of any message what want to recall from SC.
*
* \param resMessageID is the command Id, message is the content what need to recall from SC.
*
* \return If there is not any can be recall from SC, it will return false.
*
******************************************************************************/
bool CommunicationInterface::receivedMessage(const int resMessageID, QByteArray &message)
{
    bool bResult = false;
    int dwTimeout = 50; //5 sec 5*1000/10 10 for every 10mil sec loop is going on;
    while (dwTimeout > 0)
    {
        if(m_ptrSocketObj->getMessageFromMap(resMessageID, message) == true)
        {
            bResult = true;
            break;
        }
        else
        {
            QThread::msleep(10);
            dwTimeout--;
        }
    }
    if(resMessageID > 0)
        qDebug()<<"Received MessageID:"<< resMessageID;
    return bResult;
}

/**************************************************************************//**
*
* \brief To reset Socket ErrorCode and set m_SocketErr as the NoErr
*
* \param None
*
* \return true
*
******************************************************************************/
bool CommunicationInterface::resetSocketAlarm()
{
    m_ptrSocketObj->setSocketErrorCode(clientSocket::NoErr);
    return true;
}

/**************************************************************************//**
*
* \brief It is the interface to close the disconnect socket.
*        As we design socket architecture, the socket object has to run in the child thread in order to
*        avoid any more influence on the HMI running performance due to the socket communication.
*        stop heartbeat timer and emit the signal to notify the socket we can close socket now. So the any socket activity will be
*        not able to be recalled by main thread.
*
* \param none
*
* \return none
*
******************************************************************************/
void CommunicationInterface::closeSocket()
{
    killTimer(m_TimerId);
    m_ptrSocketObj->socketReadyToClose();
}

/**************************************************************************//**
*
* \brief It is the Qt timer event interface and is override function by us for the heartbeat request sending and response parsing.
*
* \param event pointer.
*
* \return none.
*
******************************************************************************/
void CommunicationInterface::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
//    qDebug() << "Timer ID:" << event->timerId();
#ifndef QT_DEBUG
    QByteArray recvMessage;
    recvMessage.clear();
    if(m_ptrSocketObj->getMessageFromMap(requestIdentities::HEARTBEAT_IDX, recvMessage) == true) //heartbeat command
    {
        m_iHeartbeatRetried = 0;
    }
    else if(m_iHeartbeatRetried > 3)
    {
        m_iHeartbeatRetried = 0;
        if(m_ptrSocketObj->state() == QAbstractSocket::ConnectedState)
        {
            m_ptrSocketObj->socketCloseForReconnect();
        }
    }
    else
    {
        m_iHeartbeatRetried++;
    }
#endif
    QByteArray transMessage;
    transMessage.clear();
    m_ptrSocketObj->insertMessageToMap(requestIdentities::HEARTBEAT_IDX, transMessage);
}


