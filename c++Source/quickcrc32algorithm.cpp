/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Quick CRC32 Algorithm module
 
 **********************************************************************************************************/

#include "quickcrc32algorithm.h"
/**************************************************************************//**
*
* \brief Constructor, Here we define all the function as the static
*       so the function can be run directly what is not owned by any object.
*       The class QuickCRC32Algorithm is the wrapper to limit the function can be used directly be the external.
*
*
* \param none
*
* \return QuickCRC32Algorithm object.
*
******************************************************************************/
QuickCRC32Algorithm::QuickCRC32Algorithm()
{

}

/**************************************************************************//**
*
* \brief It is the interface to calculate the crc32 result.
*        The function is defined as the static so it can be recalled using the class name.
*
* \param buf is the first data address of the buffer that you want to calculate the crc32 for.
*        len is the buffer length.
*
* \return crc32 result.
*
******************************************************************************/
unsigned int QuickCRC32Algorithm::crc32_ccitt(const void *buf, int len)
{
    int counter = 0;
    unsigned int crc32 = 0xFFFFFFFF;
    for (counter = 0; counter < len; counter++)
    {
        crc32 = (crc32 << CRC_8BIT_SHIFT)
            ^ crc32_table[((crc32 >> CRC_24BIT_SHIFT) ^ *(unsigned char *)buf) & 0x00FF];
        buf = ((char *) buf) + 1;
    }
    return crc32;
}
