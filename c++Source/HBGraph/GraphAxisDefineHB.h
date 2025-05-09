/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef GRAPHAXISDEFINEHB_H
#define GRAPHAXISDEFINEHB_H

#include <QObject>
#include <QQmlEngine>

#define GRAPHAXISENUM_HB_URI_NAME "Com.Branson.HBGraphAxisEnum"
#define GRAPHAXISENUM_HB_QML_MAJOR_VERSION 1
#define GRAPHAXISENUM_HB_QML_MINOR_VERSION 0
#define GRAPHAXISENUM_HB_QML_NAME "HBGraphAxisEnum"

class HBGraphAxisEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(HBGRAPHAXISINDEX)
public:
    enum HBGRAPHAXISINDEX
    {
        NONE_IDX =              -1,
        DEPTH_IDX =             0,
        VELOCITY_IDX =          1,
        TENSIONS_IDX =          2,
        TENSION_INCREMENT_IDX = 3,
        TIME_IDX =              4,
        TOTAL_IDX =             5,
    };

    static void registerQMLType()
    {
        qmlRegisterType<HBGraphAxisEnum>(GRAPHAXISENUM_HB_URI_NAME,
                                       GRAPHAXISENUM_HB_QML_MAJOR_VERSION,
                                       GRAPHAXISENUM_HB_QML_MINOR_VERSION,
                                       GRAPHAXISENUM_HB_QML_NAME);
    }
};

#endif // GRAPHAXISDEFINEHB_H
