/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef GRAPHAXISDEF_H
#define GRAPHAXISDEF_H

#include <QObject>
#include <QQmlEngine>

#define GRAPHAXISENUM_URI_NAME "Com.Branson.GraphAxisEnum"
#define GRAPHAXISENUM_QML_MAJOR_VERSION 1
#define GRAPHAXISENUM_QML_MINOR_VERSION 0
#define GRAPHAXISENUM_QML_NAME "GraphAxisEnum"

class GraphAxisEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(GRAPHAXISINDEX)
public:
    enum GRAPHAXISINDEX
    {
        NONE_IDX =          -1,
        PHASE_IDX =         0,
        ENERGY_IDX =        1,
        FREQ_IDX =          2,
        AMP_IDX =           3,
        CURRENT_IDX =       4,
        POWER_IDX =         5,
        FORCE_IDX =         6,
        VELOCITY_IDX =      7,
        ABSOLUTEDIST_IDX =  8,
        COLLAPSEDIST_IDX =  9,
        TIME_IDX =          10,
        TOTAL_IDX =         11,
    };

    static void registerQMLType()
    {
        qmlRegisterType<GraphAxisEnum>(GRAPHAXISENUM_URI_NAME,
                                       GRAPHAXISENUM_QML_MAJOR_VERSION,
                                       GRAPHAXISENUM_QML_MINOR_VERSION,
                                       GRAPHAXISENUM_QML_NAME);
    }
};

#endif // GRAPHAXISDEF_H
