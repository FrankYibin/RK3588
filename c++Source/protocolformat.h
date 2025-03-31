/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Protocol Utility Module
 
 **********************************************************************************************************/

#ifndef PROTOCOLFORMAT_H
#define PROTOCOLFORMAT_H
#include <QObject>
#include "heartbeatformat.h"
class ProtocolFormat
{
public:
    ProtocolFormat();
    static bool buildProtocolPackage(const int key, const QByteArray message, QByteArray& buff);
    static bool parseProtocolPackage(int& key, QByteArray& message, const QByteArray buff);
    static bool isFullProtocolPackage(const QByteArray sourceBuff, QByteArray& onePackageBuff);
    static bool parseHeartbeatMessage(const QByteArray message, HeartbeatFormat *heartbeatStructure);
};

#endif // PROTOCOLFORMAT_H
