/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Protocol Utility Module
 
 **********************************************************************************************************/

#include "protocolformat.h"
#include "quickcrc32algorithm.h"
/**************************************************************************//**
*
* \brief Constructor, Here we define all the function as the static
*       so the function can be run directly what is not owned by any object.
*       The class ProtocolFormat is the wrapper to limit the function can be used directly be the external.
*
* \param none
*
* \return ProtocolFormat object
*
******************************************************************************/
ProtocolFormat::ProtocolFormat()
{

}

/**************************************************************************//**
*
* \brief To build the request package following key and message
*
* \param key is the command id, message is what content HMI want to send to SC.
*        buff is the integrated package with crc32 checksum.
*
* \return result
*
******************************************************************************/
bool ProtocolFormat::buildProtocolPackage(const int key, const QByteArray message, QByteArray &buff)
{
    bool bResult = false;
    const char* tmpBuf;
    int offset = 0;
    QByteArray tmpByteArray;
    offset = sizeof(int);

    tmpBuf = reinterpret_cast<const char*>(&key);
    tmpByteArray.append(tmpBuf, offset);

    int dataLen = message.size();
    tmpBuf = reinterpret_cast<const char*>(&dataLen);
    tmpByteArray.append(tmpBuf, offset);

    tmpByteArray.append(message);

    unsigned int checkSum = QuickCRC32Algorithm::crc32_ccitt(tmpByteArray.data(), tmpByteArray.size());
    tmpBuf = reinterpret_cast<const char*>(&checkSum);
    tmpByteArray.append(tmpBuf, offset);

    buff = tmpByteArray;
    bResult = true;
    return bResult;
}

/**************************************************************************//**
*
* \brief To parse the response package that received from SC
*
* \param key is the command id, message is the data field of the response package.
*        buff is the received response package.
*
* \return If there is any issue during the parsing, it will return false.
*
******************************************************************************/
bool ProtocolFormat::parseProtocolPackage(int &key, QByteArray &message, const QByteArray buff)
{
    bool bResult = false;
    int offset = 0, dataLen = 0, position = 0;
    unsigned int responseCode = 0xffffffff;
    QByteArray tmpBuf;
    message.clear();

    offset = sizeof(unsigned int);
    tmpBuf = buff.left(offset);
    memcpy(&key, tmpBuf.data(), offset);
    position += offset;

    offset = sizeof(unsigned int);
    tmpBuf = buff.mid(position, offset);
    memcpy(&dataLen, tmpBuf.data(), offset);
    position += offset;

    offset = sizeof(unsigned int);
    tmpBuf = buff.mid(position, offset);
    memcpy(&responseCode, tmpBuf.data(), offset);
    position += offset;

    if(responseCode == 0)
    {
        offset = dataLen - sizeof(unsigned int);
        message = buff.mid(position, offset);
        bResult = true;
    }
    return bResult;
}

/**************************************************************************//**
*
* \brief To check if there is a integrated package from the received data.
*
* \param sourceBuff is all received data from SC, onePackageBuff is the extracted integrated package.
*
* \return if there is a integrated package in the sourceBuff, it will return true, otherwise it will return false.
*
******************************************************************************/
bool ProtocolFormat::isFullProtocolPackage(const QByteArray sourceBuff, QByteArray &onePackageBuff)
{
    bool bResult = false;
    QByteArray tmpBuff;
    int position = 0, buffLen = sourceBuff.size();
    int offset = 0, command = 0, dataLen = 0;
    unsigned int checksum = 0xffffffff;
    onePackageBuff.clear();

    // command id parsing
    offset = sizeof(command);
    if((position + offset) > buffLen)
        return false;
    tmpBuff = sourceBuff.left(offset);
    onePackageBuff.append(tmpBuff);
    memcpy(&command, tmpBuff.data(), offset);
    position += offset;

    // data length parsing
    offset = sizeof(dataLen);
    if((position + offset) > buffLen)
    {
        onePackageBuff.clear();
        return false;
    }
    tmpBuff = sourceBuff.mid(position, offset);
    onePackageBuff.append(tmpBuff);
    memcpy(&dataLen, tmpBuff.data(), offset);
    position += offset;

    // data message parsing
    offset = dataLen;
    if((position + offset) > buffLen)
    {
        onePackageBuff.clear();
        return false;
    }
    tmpBuff = sourceBuff.mid(position, offset);
    onePackageBuff.append(tmpBuff);
    position += offset;

    // checksum parsing
    offset = sizeof(checksum);
    if((position + offset) > buffLen)
    {
        onePackageBuff.clear();
        return false;
    }
    tmpBuff = sourceBuff.mid(position, offset);
    memcpy(&checksum, tmpBuff.data(), offset);

    if(checksum == QuickCRC32Algorithm::crc32_ccitt(onePackageBuff.data(), position))
        bResult = true;
    onePackageBuff.append(tmpBuff);
    return bResult;
}

/**************************************************************************//**
*
* \brief It is the heartbeat message parsing. As our protocol format definition,
* the heartbeat message should include three parts, such as Cycle#, Active Recipe# and Alarm Id.
* All the data should be the 32bits
* \param message is heartbeat message, heartbeatStruture is HEARTBEAT struct.
*
* \return If there is any error during the parsing, it will return false.
*
******************************************************************************/
bool ProtocolFormat::parseHeartbeatMessage(const QByteArray message, HeartbeatFormat *heartbeatStructure)
{
    bool bResult = false;
    int offset = sizeof(unsigned int) * 5, position = 0;
    QByteArray tmpBuff;
    if(message.size() < offset)
        return bResult;

    tmpBuff.clear();
    offset = sizeof(unsigned int);

    tmpBuff = message.left(offset);
    memcpy(&heartbeatStructure->m_cycleNum, tmpBuff.data(), offset);
    position += offset;

    tmpBuff = message.mid(position, offset);
    memcpy(&heartbeatStructure->m_activeRecipeNum, tmpBuff.data(), offset);
    position += offset;

    tmpBuff = message.mid(position, offset);
    memcpy(&heartbeatStructure->m_alarmId, tmpBuff.data(), offset);
    position += offset;

    tmpBuff = message.mid(position, offset);
    memcpy(&heartbeatStructure->m_powerValue, tmpBuff.data(), offset);
    position += offset;

    tmpBuff = message.mid(position, offset);
    memcpy(&heartbeatStructure->m_cycleTime, tmpBuff.data(), offset);
    bResult = true;
    return bResult;
}
