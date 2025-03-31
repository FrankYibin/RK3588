/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 Heartbeat information class definition
 *********************************************************************************************************/
#ifndef HEARTBEATFORMAT_H
#define HEARTBEATFORMAT_H


class HeartbeatFormat
{
public:
    unsigned int m_activeRecipeNum;
    unsigned int m_cycleTime;
    unsigned int m_cycleNum;
    unsigned int m_powerValue;
    unsigned int m_alarmId;
public:
    HeartbeatFormat();
    HeartbeatFormat &operator =(const HeartbeatFormat &obj);
    bool operator !=(const HeartbeatFormat &obj);
};

#endif // HEARTBEATFORMAT_H
