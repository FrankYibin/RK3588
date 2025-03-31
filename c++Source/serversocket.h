/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/
#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QThread>
#include <QDateTime>
#include <QTcpSocket>
class TcpSocket;
class serverThread;
class serverSocket : public QTcpServer
{
    Q_OBJECT
public:
    explicit serverSocket(QObject *parent = Q_NULLPTR,const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    ~serverSocket();

protected:
    void incomingConnection(qintptr socketDescriptor);

private slots:
    void recvData( const QByteArray &data);
};
class serverThread : public QThread
{
    Q_OBJECT
public:
    serverThread(int sockDesc, QObject *parent = Q_NULLPTR);
    ~serverThread();

private:
    void run(void);

public slots:
    void sendDataSlot(const QByteArray &data);
signals:
    void dataReady(const QByteArray &data);
    void sendData(const QByteArray &data);
private slots:
    void recvDataSlot(const QByteArray &data);
private:
    TcpSocket *m_socket;
    int m_sockDesc;
};
class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = Q_NULLPTR);
    ~TcpSocket();

signals:
    void dataReady( const QByteArray &data);
    void signalSocketState(QString status);
public slots:
    /*
    **Receive data sent by customer service
    */
    void recvData();
    /*
    **Send data to the server
    */
    void sendData(const QByteArray &data);
    /*
    **Monitor socket status
    */
    void slotSocketStateChange(QAbstractSocket::SocketState socketState);
    /*
    **network disconnection
    */
    void slotDisconnected();
};
#endif // SERVER_H
