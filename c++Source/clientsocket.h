/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 TLS/SSL TCP/IP class definition
 *********************************************************************************************************/
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
// #include <QSslSocket>
#include <QTimer>
#include <QTime>
#include <QHostAddress>
#include <QtNetwork>
#include <QThread>
#include "protocolformat.h"
#include "heartbeatformat.h"
#define MAX_READ_WAIT_TIME_CLIENT 3000 // milliseconds.  2000 milliseconds required if network is too busy.
#define MAX_WRITE_WAIT_TIME_CLIENT 2000
#define MAX_CONNECT_WAIT_TIME_CLIENT 5000
#define MAX_DISCONNECT_WAIT_TIME_CLIENT 1000
#define MAX_READ_BUFF_LEN 10240
class clientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    enum ErrorCode
    {
        SocketErr = -5,
        ConnectErr = -4,
        SecurityErr = -3,
        DataFormatErr = -2,
        ResponseErr = -1,
        NoErr = 0,
        AlreadyConnected = 1,
        NewDataComming = 2,
        SocketClosed = 3
    };
public:
    //TODO The IP address should be from the configuration file.
    explicit clientSocket(QHostAddress address = QHostAddress("127.0.0.1"), unsigned short port = 1600);
    ~clientSocket();
    bool insertMessageToMap(const int key, const QByteArray buff);
    bool getMessageFromMap(const int key, QByteArray& buff);
    void socketReadyToClose();
    void socketCloseForReconnect();
    void setSocketErrorCode(const ErrorCode SocketErr);
    ErrorCode getSocketErrorCode();
private:
    bool heartbeatMessageProcess(const QByteArray message);
    void handleSslError(const QSslError &error);
signals:
    void signalMessageReadyToSend();
    void signalSocketReadyToClose();
    void signalErrorCodeChanged();
    void signalAlarmCodeToNotify(int alarmCode);
    void signalHeartbeatUpdated(void*);
private:
    /*
    ** Start timer reconnect network when the client side is disconnected from the server
    */
    QTimer *m_reconnectingTimer;
    /*
    ** The network address used to save the current connection
    */
    QHostAddress m_HostAddress;
    /*
    ** The network port number used to save the current connection
    */
    unsigned short m_port;
    QMap<int, QByteArray>   m_RecvBuffMap;
    QMap<int, QByteArray>   m_SendBuffMap;
    QThread *m_ThreadObj;
    static QMutex mutex;
    ErrorCode m_SocketErr;

    unsigned int m_PackageDebugRevCounter;
    unsigned int m_PackageDebugTmtCounter;

    QList<QSslError> expectedSslErrors;

    static HeartbeatFormat m_HeartbeatValue;

private slots:
    /*
    **Receive data sent by the server
    */
    void slotDataReceiving();
    void slotSocketStateChange(QAbstractSocket::SocketState socketState);
    /*
    **Start the timer when you disconnect from the network
    */
    void slotSocketDisconnected();
    /*
    **Connect the server
    */
    void slotSocketConnecting();
    void slotDataSending();

    void slotSslErrors(const QList<QSslError> &errors);

};

#endif // CLIENTSOCKET_H
