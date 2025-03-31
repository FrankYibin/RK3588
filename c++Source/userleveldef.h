/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef USERLEVELDEF_H
#define USERLEVELDEF_H

#include <QObject>
#include <QQmlEngine>

#define USERLEVELENUM_URI_NAME "Com.Branson.UserLevelEnum"
#define USERLEVELENUM_QML_MAJOR_VERSION 1
#define USERLEVELENUM_QML_MINOR_VERSION 0
#define USERLEVELENUM_QML_NAME "UserLevelEnum"

class UserLevelEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(USERLEVEL)
public:
    enum USERLEVEL
    {
        EXECUTIVE = 1,
        SUPERVISOR,
        TECHNICIAN,
        OPERATOR
    };

    static void registerQMLType()
    {
        qmlRegisterType<UserLevelEnum>(USERLEVELENUM_URI_NAME,
                                       USERLEVELENUM_QML_MAJOR_VERSION,
                                       USERLEVELENUM_QML_MINOR_VERSION,
                                       USERLEVELENUM_QML_NAME);
    }
};

#endif // USERLEVELDEF_H
