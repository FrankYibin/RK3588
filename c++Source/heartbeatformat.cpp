/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 heartbeat information class implement
 *********************************************************************************************************/
#include "heartbeatformat.h"
/**************************************************************************//**
*
* \brief Constructor
*        Initialize m_activeRecipeNum, m_cycleTime, m_cycleNum, m_powerValue and m_alarmId variables.
*
* \param none
*
* \return return HeartbeatFormat object
*
******************************************************************************/
HeartbeatFormat::HeartbeatFormat()
    :m_activeRecipeNum(0)
    ,m_cycleTime(0)
    ,m_cycleNum(0)
    ,m_powerValue(0)
    ,m_alarmId(0)
{

}

/**************************************************************************//**
*
* \brief It is the function to overload the operator "="
* so the heartbeatformat object can be easily assigned by the another object for the external.
*
* \param heartbeatFormat object
*
* \return heartbeatFormat object
*
******************************************************************************/
HeartbeatFormat& HeartbeatFormat::operator =(const HeartbeatFormat &obj)
{
    if(this == &obj)
        return *this;

    this->m_activeRecipeNum = obj.m_activeRecipeNum;
    this->m_cycleNum = obj.m_cycleNum;
    this->m_cycleTime = obj.m_cycleTime;
    this->m_powerValue = obj.m_powerValue;
    return *this;
}

/**************************************************************************//**
*
* \brief It is the function to overload the operator "!="
* so the heartbeatformat objects can be easily compared each other for the external.
*
* \param heartbeatFormat object
*
* \return if the object is not equal to this, it will be return true otherwise it will be return false.
*
******************************************************************************/
bool HeartbeatFormat::operator !=(const HeartbeatFormat &obj)
{
    if(this == &obj)
        return false;
    bool bResult = false;
    if(this->m_activeRecipeNum != obj.m_activeRecipeNum)
        bResult = true;
    else if(this->m_cycleNum != obj.m_cycleNum)
        bResult = true;
    else if(this->m_cycleTime != obj.m_cycleTime)
        bResult = true;
    else if(this->m_powerValue != obj.m_powerValue)
        bResult = true;
    else
        bResult = false;
    return bResult;
}
