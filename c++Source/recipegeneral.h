/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef RECIPEGENERAL_H
#define RECIPEGENERAL_H

#include <QString>
#include "recipedef.h"

class RecipeGeneral
{
public:
    RecipeGeneral();
    RecipeGeneral(const int& iRecipeNum, const QString& strRecipeName, const int& iWeldMode,
                         const QString& strWeldModeUnit, const QString& strWeldModeValue,
                         const bool& bActiveStatus, const bool& bValidateStatus,
                         const bool& bModifiedStatus, const bool& bNewCardStatus,
                         const int& iCycleCount);

private:
    int m_iRecipeNumber;
    QString m_strRecipeName;
    int m_iWeldMode;
    QString m_strWeldModeUnit;
    QString m_strWeldModeValue;
    bool m_bActiveStatus;
    bool m_bValidateStatus;
    bool m_bModifiedStatus;
    bool m_bNewCardStatus;
    int m_iCycleCount;
public:
    int getRecipeNumber() const;
    QString getRecipeName() const;
    int getWeldModeEnum() const;
    QString getWeldModeUnit() const;
    QString getWeldModeValue() const;
    bool getRecipeActiveStatus() const;
    void setRecipeActiveStatus(const int activeflag);
    bool getRecipeValidateStatus() const;
    bool getRecipeModifiedStatus() const;
    bool getRecipeNewCardStatus() const;
    int getRecipeWeldCycleCount() const;
    void setRecipeWeldCycleCount(const int cycleNumber);
};

#endif // RECIPEGENERAL_H
