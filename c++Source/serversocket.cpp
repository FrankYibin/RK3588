/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 xxxxx

 **********************************************************************************************************/
#include "serversocket.h"
#include <QDebug>
quint64 receiveDataNum = 0;
quint64 SendDataNum = 0;
serverSocket::serverSocket(QObject *parent, const QHostAddress &address, quint16 port) :
    QTcpServer(parent)
{
    listen(address,port);
}

serverSocket::~serverSocket()
{

}

void serverSocket::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<qPrintable(QString("start time:  %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz")));
    serverThread *thread = new serverThread(socketDescriptor);
    connect(thread, &serverThread::finished, thread, &QObject::deleteLater);
    connect(thread, &serverThread::dataReady,this,&serverSocket::recvData);
    thread->start();
}

void serverSocket::recvData( const QByteArray &data)
{
    Q_UNUSED(data)
}

serverThread::serverThread(int sockDesc, QObject *parent) :
    QThread(parent),
    m_sockDesc(sockDesc)
{

}

serverThread::~serverThread()
{
    m_socket->close();
    m_socket->disconnectFromHost();
}

void serverThread::run(void)
{
    m_socket = new TcpSocket;
    if (!m_socket->setSocketDescriptor(m_sockDesc)) {
        return ;
    }
    connect(m_socket,&TcpSocket::dataReady,this, &serverThread::recvDataSlot);
    connect(this, &serverThread::sendData,m_socket, &TcpSocket::sendData);
    this->exec();
}

void serverThread::sendDataSlot(const QByteArray &data)
{
    if (data.isEmpty()) {
        return ;
    }
    emit sendData( data);
}


void serverThread::recvDataSlot( const QByteArray &data)
{
    emit dataReady(data);
}
TcpSocket::TcpSocket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this,&QAbstractSocket::readyRead, this, &TcpSocket::recvData);
    connect(this,&QAbstractSocket::stateChanged,this,&TcpSocket::slotSocketStateChange);
    connect(this,&QAbstractSocket::disconnected,this,&TcpSocket::slotDisconnected);
}

TcpSocket::~TcpSocket()
{

}

void TcpSocket::sendData(const QByteArray &data)
{
    if (!data.isEmpty()){
        SendDataNum+=QString(data).toLocal8Bit().size();
        this->write(data);
    }
}

void TcpSocket::slotSocketStateChange(QAbstractSocket::SocketState socketState)
{

    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        qDebug()<<"Socket status：UnconnectedState";
        break;
    case QAbstractSocket::HostLookupState:
        qDebug()<<"Socket status：HostLookupState";
        break;
    case QAbstractSocket::ConnectingState:
        qDebug()<<"Socket status：ConnectingState";
        break;
    case QAbstractSocket::ConnectedState:
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
    }

}

void TcpSocket::slotDisconnected()
{
    qDebug()<<qPrintable(QString("end time:  %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss.zzz")));
    qDebug()<<qPrintable(QString("Received:%1 %2").arg(receiveDataNum).arg("Bytes"));
    qDebug()<<qPrintable(QString("Sent Outd:%1 %2").arg(SendDataNum).arg("Bytes"));
}

void TcpSocket::recvData()
{
    while(bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(bytesAvailable());
        read(datagram.data(),datagram.size());
        receiveDataNum+=QString(datagram.data()).toLocal8Bit().size();
        emit dataReady(datagram.data());
    }
}
