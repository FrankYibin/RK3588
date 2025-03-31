/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Communication interface definition
 
 **********************************************************************************************************/

#ifndef COMMUNICATIONINTERFACE_H
#define COMMUNICATIONINTERFACE_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include "clientsocket.h"
#define HEARTBEAT_RATE 500
class CommunicationInterface: public QObject
{
    Q_OBJECT
private:
    static int m_TimerId;
    static clientSocket* m_ptrSocketObj;
    static CommunicationInterface* m_pCIObj;
    int m_iHeartbeatRetried;
public:
    static CommunicationInterface* getInstance(QObject *parent = nullptr);
    ~CommunicationInterface();

    bool sendMessage(const int reqMessageID, const QByteArray message);
    bool receivedMessage(const int resMessageID, QByteArray& message);
    bool resetSocketAlarm();

    Q_INVOKABLE void closeSocket();
protected:
    void timerEvent(QTimerEvent *event) override;
    explicit CommunicationInterface(QObject *parent = nullptr);
private:
    int mapToAlarmIndex(int errCode);
signals:
    void signalNotifyAlarm(int alarmId);
    void signalHeartbeatUpdated(void* _obj);
private slots:
    void slotErrorCodeChanged();
    void slotAlarmCodeToNotify(int alarmCode);
};

#endif // COMMUNICATIONINTERFACE_H
