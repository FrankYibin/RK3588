#ifndef SHAREDEFINE_H
#define SHAREDEFINE_H
/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file is a header file and it is used to define some public variable.

 **********************************************************************************************************/


typedef int INT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;




const int SYSINFO_SIZE = 16;
const int MAC_ADDR_SIZE = 18;


enum requestIdentities
{
    HEARTBEAT_IDX = 0,
    GET_USER_PASSWORD,
    SET_USER_PASSWORD,
    GET_USER_DETAILS,
    GET_PASSCODE_VALIDATE,
    GET_BASIC_RECIPE_INFO,
    GET_WELD_RECIPE_LIST,
    GET_SYSTEM_INFORMATION
};



struct SYSTEMINFO
    {
        INT32	psLifeCounter;
        INT32   actuatorlifecounter;
        INT32   generalAlarmCounter;
        INT32   overloadAlarmCounter;
        INT32	actuatorOverloads;
        INT32	actuatorStrokeLength;
        UINT16  psFrequency;
        INT32   psWatt;
        UINT8   calibrationStatus;
        UINT8   psType;
        UINT8   actuatorType;
        char    modelName[SYSINFO_SIZE];
        char    version_SC[SYSINFO_SIZE];
        char    version_PC[SYSINFO_SIZE];
        char    version_AC[SYSINFO_SIZE];
        char    psAssemblyNumber[SYSINFO_SIZE];
        char    actuatorAssembly[SYSINFO_SIZE];
        char    stackAssembly[SYSINFO_SIZE];
        char    psMacID[MAC_ADDR_SIZE];
        char    psIP[SYSINFO_SIZE];
        char    dateTime[2 * SYSINFO_SIZE];
        UINT16  crc_SC;
        UINT16  crc_AC;
    };



#endif // SHAREDEFINE_H
