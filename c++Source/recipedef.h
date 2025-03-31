/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef RECIPEDEF_H
#define RECIPEDEF_H
#include <QObject>
#include <QQmlEngine>

#define RECIPEENUM_URI_NAME "Com.Branson.RecipeEnum"
#define RECIPEENUM_QML_MAJOR_VERSION 1
#define RECIPEENUM_QML_MINOR_VERSION 0
#define RECIPEENUM_QML_NAME "RecipeEnum"

#define RECIPE_CARD_MAXIMUM 13

class RecipeEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(WELDMODEINDEX)
    Q_ENUMS(RECIPEACTIONS)
public:
    enum WELDMODEINDEX
    {
        NONE_IDX = -1,
        TIME_IDX = 0,
        ENERGY_IDX,
        PEAKPOWER_IDX,
        COLDISTANCE_IDX,
        ABSDISTANCE_IDX,
        GROUND_IDX,
        TOTALWELDMODE_IDX
    };

    enum RECIPEACTIONS
    {
        CREATE_NEW_IDX = 0,
        PRODUCTION_RUN_IDX,
        EDIT_IDX,
        RESET_CYCLE_COUNT_IDX,
        SET_AS_ACTIVE_IDX,
        DELETE_IDX,
        COPY_IDX,
        INFORMATION_IDX
    };

    static void registerQMLType()
    {
        qmlRegisterType<RecipeEnum>(RECIPEENUM_URI_NAME,
                                    RECIPEENUM_QML_MAJOR_VERSION,
                                    RECIPEENUM_QML_MINOR_VERSION,
                                    RECIPEENUM_QML_NAME);
    }
};
#endif // RECIPEDEF_H
