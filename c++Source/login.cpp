/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Login back-end code for the login qml screen
 
 **********************************************************************************************************/

#include "login.h"
#include "communicationinterface.h"
#include "logindef.h"
#include "shareDefine.h"
Login* Login::m_pLoginObj = nullptr;
/**************************************************************************//**
*
* \brief Constructor
*
* \param parent object
*
* \return login object
*
******************************************************************************/
Login::Login(QObject *parent) : QObject(parent)
{

}

/**************************************************************************//**
*
* \brief To get Login singleton object.
*        The class is designed to the singleton class so the login object can be registered to the QML.
*        See main.cpp
*
* \param parent object
*
* \return login object
*
******************************************************************************/
Login *Login::getInstance(QObject *parent)
{
    if(m_pLoginObj == nullptr)
    {
        m_pLoginObj = new Login(parent);
    }
    return m_pLoginObj;
}

/**************************************************************************//**
*
* \brief The function is for the user name and password validation with SC
*
* \param user name and password
*
* \return the validation result that has been defined in the LoginIndexEnum.
*
******************************************************************************/
int Login::loginValidate(const QString userName, const QString password)
{
    QString strMessage = "";
    strMessage = userName + "," + password;
    int iResult = LoginIndexEnum::LOGIN_FAIL;
    QByteArray message = strMessage.toUtf8();
    if(CommunicationInterface::getInstance()->sendMessage(requestIdentities::GET_USER_DETAILS, message) == true)
    {
        message.clear();
        if(CommunicationInterface::getInstance()->receivedMessage(requestIdentities::GET_USER_DETAILS, message) == true)
        {
            memcpy(&iResult, message.data(), sizeof(unsigned int));
            iResult = message.toInt();
        }
    }
    return iResult;
}

/**************************************************************************//**
*
* \brief The function is for the passcode validation with SC
*
* \param string passcode
*
* \return the validation result that has been defined in the LoginIndexEnum.
*
******************************************************************************/
int Login::loginValidate(const QString passcode)
{
    QString strMessage = "";
    strMessage = passcode;
    int iResult = LoginIndexEnum::LOGIN_FAIL;
    QByteArray message = strMessage.toUtf8();
    if(CommunicationInterface::getInstance()->sendMessage(requestIdentities::GET_PASSCODE_VALIDATE, message) == true)
    {
        message.clear();
        if(CommunicationInterface::getInstance()->receivedMessage(requestIdentities::GET_PASSCODE_VALIDATE, message) == true)
        {
            memcpy(&iResult, message.data(), sizeof(unsigned int));
        }
    }
    return iResult;
}
