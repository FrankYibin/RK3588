#ifndef HBDEFINE_H
#define HBDEFINE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QPointF>


// Ground serial port system

struct _GroundSerial
{
    int Port;
    int BaudRate;
    int DataBit;
    int SerialType;
};

//Ground gauge

struct _Ground_Network
{
    int GProtocol;       //networking protocol
    QString GLocalIP;    //local ip
    int GLocalPort;      //local port
    int GRemoteIP;       //remote ip
    QString GRemotePort; //remote port
};

//cloud platform
struct _Cloud_Network
{
    int CProtocol;        //networking protocol
    QString CLocalIP;     //local ip
    int CLocalPort;       //local port
    int CRemoteIP;        //remote ip
    QString CRemotePort;  //remote ip
};






//

#endif // HBDEFINE_H
