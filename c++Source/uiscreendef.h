/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef UISCREENDEF_H
#define UISCREENDEF_H
#include <QObject>
#include <QQmlEngine>

#define UISCREENENUM_URI_NAME "Com.Branson.UIScreenEnum"
#define UISCREENENUM_QML_MAJOR_VERSION 1
#define UISCREENENUM_QML_MINOR_VERSION 0
#define UISCREENENUM_QML_NAME "UIScreenEnum"

class UIScreenEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(UISCREEN)
public:
    enum UISCREEN
    {
        NONESCREEN = -1,
        LOGIN = 0,
        DASHBOARD,
        LEFTMENU,
        RIGHTMENU,
        RECIPES,
        RECIPES_LAB,
        RECIPES_LAB_SETTING,
        RECIPES_LAB_WELDMODE,
        RECIPES_LAB_WELDPROCESS,
        RECIPES_LAB_WELDPROCESS_PRETRIGGER,
        RECIPES_LAB_WELDPROCESS_AFTERBURST,
        RECIPES_LAB_PARAMETERA2Z,
        RECIPES_LAB_LIMITS,
        RECIPES_LAB_LIMITS_SETUP,
        RECIPES_LAB_LIMITS_CONTROL,
        RECIPES_LAB_LIMITS_SUSPECT_REJECT,
        RECIPES_LAB_STACKRECIPE,
        RECIPES_LAB_RESULTVIEW,
        RECIPES_LAB_GRAPHSETTING,
        WELDMODE_VALUE_LOWERSTRING,
        PRODUCTION,
        ANALYTICS,
        ANALYTICS_RESULT_GRAPH_VIEW,
        ANALYTICS_RESULT_GRAPH_RIGHT_SETTING,
        ANALYTICS_RESULT_GRAPH_HEADER_SETTING,
        ANALYTICS_RESULT_GRAPH_AXIS,
        SYSTEM,
        SYSTEM_INFO,
        SYSTEM_SOFTWARE_UPGRADE,
        SYSTEM_SOFTWARE_UPGRADE_WELDER,
        SYSTEM_SOFTWARE_UPGRADE_RASPPI,
        ACTUATORSETUP,
        DIAGNOSTICS,
        IMPORTEXPORT,
        LANGUAGE,
        LOGOUT,
        EXIT,
        NUMPAD,
        SELECTLANGUAGE,
		ALARM,
        ALARM_GENERAL,
        ALARM_NAME,
        ALARM_DESCRIPTION,

        HB_PROFILE,
        HB_DASHBOARD,
        HB_SETTING,
        HB_VELOCITY,

        HB_HISTORY_DATA,
        HB_SYSTEM_CONFIG,
        HB_WELL_PARAMETERS,
        HB_TENSIONS_SETTING,
        HB_TENSIONS_VIEW,
        HB_DEPTH_SETTING,
        HB_USER_MANAGEMENT,
        HB_HELP,
        HB_RETURN
    };

    static void registerQMLType()
    {
        qmlRegisterType<UIScreenEnum>(UISCREENENUM_URI_NAME,
                                       UISCREENENUM_QML_MAJOR_VERSION,
                                       UISCREENENUM_QML_MINOR_VERSION,
                                       UISCREENENUM_QML_NAME);
    }
};
#endif // UISCREENDEF_H
