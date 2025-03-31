/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef UPGRADESOFTWAREDEF_H
#define UPGRADESOFTWAREDEF_H
#include <QObject>
#include <QQmlEngine>

#define UPGRADEENUM_URI_NAME "Com.Branson.UpgradeSoftwareEnum"
#define UPGRADEENUM_QML_MAJOR_VERSION 1
#define UPGRADEENUM_QML_MINOR_VERSION 0
#define UPGRADEENUM_QML_NAME "UpgradeSoftwareEnum"

class UpgradeSoftwareEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(UPGRADEINDEX)
public:
    enum UPGRADEINDEX
    {
        NONE_IDX = -1,
        WELDER_SOFTWARE_IDX = 0,
        UICONTROLLER_SOFTWARE_IDX = 1,
    };

    static void registerQMLType()
    {
        qmlRegisterType<UpgradeSoftwareEnum>(UPGRADEENUM_URI_NAME,
                                    UPGRADEENUM_QML_MAJOR_VERSION,
                                    UPGRADEENUM_QML_MINOR_VERSION,
                                    UPGRADEENUM_QML_NAME);
    }
};
#endif // UPGRADESOFTWAREDEF_H
