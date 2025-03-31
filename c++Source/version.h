/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 software version definition

 **********************************************************************************************************/
#ifndef VERSION_H
#define VERSION_H

//UIC_VERSION_NUM to be shown on HMI under System Information
#define UIC_VERSION_NUM_MAJOR 0
#define UIC_VERSION_NUM_MINOR 0
#define UIC_VERSION_NUM_BUILD 1
#define UIC_VERSION_NUM_AUTOS 4

enum VERSION
{
    VERSION_UIC = 0,
    VERSION_SC,
    VERSION_AC,
    VERSION_PC
};

#endif // VERSION_H
