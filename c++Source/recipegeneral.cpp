/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include "recipegeneral.h"
/**************************************************************************//**
*
* \brief Constructor and initialize as following variables...
*        1. m_iRecipeNumber;
*        2. m_strRecipeName;
*        3. m_strCompanyName;
*        4. m_iWeldMode;
*        5. m_strWeldModeUnit;
*        6. m_strWeldModeValue;
*        7. m_bActiveStatus;
*        8. m_bValidateStatus;
*        9. m_bModifiedStatus;
*        10. m_bNewCardStatus;
*        11. m_iCycleCount
*
* \param none
*
* \return none
*
******************************************************************************/
RecipeGeneral::RecipeGeneral()
    :m_iRecipeNumber(-1)
    ,m_strRecipeName("N/A")
    ,m_iWeldMode(RecipeEnum::NONE_IDX)
    ,m_strWeldModeUnit("N/A")
    ,m_strWeldModeValue("N/A")
    ,m_bActiveStatus(false)
    ,m_bValidateStatus(false)
    ,m_bModifiedStatus(false)
    ,m_bNewCardStatus(true)
    ,m_iCycleCount(0)
{

}

/**************************************************************************//**
*
* \brief Constructor and initialize as following variables...
*        1. m_iRecipeNumber;
*        2. m_strRecipeName;
*        3. m_strCompanyName;
*        4. m_iWeldMode;
*        5. m_strWeldModeUnit;
*        6. m_strWeldModeValue;
*        7. m_bActiveStatus;
*        8. m_bValidateStatus;
*        9. m_bModifiedStatus;
*        10. m_bNewCardStatus;
*        11. m_iCycleCount
*
* \param 1. iRecipeNum: Recipe Number;
*        2. strRecipeName: Recipe Name
*        3. strCompanyName: Customer Company Name
*        4. iWeldMode: Weld Mode enum that defined in recipedef.h
*        5. strWeldModeUnit: the value unit related to the specific weld mode of the recipe card.
*        6. strWeldModeValue: the value related to the specific weld mode of the recipe card.
*        7. bActiveStatus: active status
*        8. bValidateStatus: validate status
*        9. bModifiedStatus: modified status
*        10. bNewCardStatus: Is the new card for creating
*        11. iCycleCount: cycle count
*
* \return none
*
******************************************************************************/
RecipeGeneral::RecipeGeneral(const int &iRecipeNum, const QString &strRecipeName,
                         const int &iWeldMode,
                         const QString &strWeldModeUnit, const QString &strWeldModeValue,
                         const bool &bActiveStatus, const bool &bValidateStatus,
                         const bool &bModifiedStatus, const bool &bNewCardStatus, const int &iCycleCount)
    :m_iRecipeNumber(iRecipeNum)
    ,m_strRecipeName(strRecipeName)
    ,m_iWeldMode(iWeldMode)
    ,m_strWeldModeUnit(strWeldModeUnit)
    ,m_strWeldModeValue(strWeldModeValue)
    ,m_bActiveStatus(bActiveStatus)
    ,m_bValidateStatus(bValidateStatus)
    ,m_bModifiedStatus(bModifiedStatus)
    ,m_bNewCardStatus(bNewCardStatus)
    ,m_iCycleCount(iCycleCount)
{

}

/**************************************************************************//**
*
* \brief To get the Recipe Number
*
* \param none
*
* \return the recipe number of the object.
*
******************************************************************************/
int RecipeGeneral::getRecipeNumber() const
{
    return m_iRecipeNumber;
}

/**************************************************************************//**
*
* \brief To get the Recipe Name
*
* \param none
*
* \return the recipe name of the object
*
******************************************************************************/
QString RecipeGeneral::getRecipeName() const
{
    return m_strRecipeName;
}

/**************************************************************************//**
*
* \brief To get the weld mode enum index
*
* \param none.
*
* \return the weld mode enum index of the object.
*
******************************************************************************/
int RecipeGeneral::getWeldModeEnum() const
{
    return m_iWeldMode;
}

/**************************************************************************//**
*
* \brief To get the value unit that related to the specific weld mode of the recipe
*
* \param none.
*
* \return the parameter unit string.
*
******************************************************************************/
QString RecipeGeneral::getWeldModeUnit() const
{
    return m_strWeldModeUnit;
}

/**************************************************************************//**
*
* \brief To get the value that related to the specific weld mode of the recipe.
*
* \param none
*
* \return the parameter value string.
*
******************************************************************************/
QString RecipeGeneral::getWeldModeValue() const
{
    return m_strWeldModeValue;
}

/**************************************************************************//**
*
* \brief To get the recipe active status.
*       The flag is used for the recipe what will be available for the current weld cycle.
*
* \param none.
*
* \return the boolean active status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeActiveStatus() const
{
    return m_bActiveStatus;
}

/**************************************************************************//**
*
* \brief
*
* \param
*
* \return
*
******************************************************************************/
void RecipeGeneral::setRecipeActiveStatus(const int activeflag)
{
    if(m_bActiveStatus != activeflag)
        m_bActiveStatus = activeflag;
}

/**************************************************************************//**
*
* \brief To get the recipe validate status
*
* \param none
*
* \return the boolean validate status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeValidateStatus() const
{
    return m_bValidateStatus;
}

/**************************************************************************//**
*
* \brief To get the recipe modified status.
*        If there is any change of the recipe without saved, the status will be set true.
*
* \param none
*
* \return the boolean modified status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeModifiedStatus() const
{
    return m_bModifiedStatus;
}

/**************************************************************************//**
*
* \brief To get the new card status.
*        If the recipe card is the empty, the flag is the true.
*
* \param none.
*
* \return the boolean new card status.
*
******************************************************************************/
bool RecipeGeneral::getRecipeNewCardStatus() const
{
    return m_bNewCardStatus;
}

/**************************************************************************//**
*
* \brief To get the recipe cycle count
*
* \param none
*
* \return the integer cycle count
*
******************************************************************************/
int RecipeGeneral::getRecipeWeldCycleCount() const
{
    return m_iCycleCount;
}

/**************************************************************************//**
*
* \brief To set the recipe cycle count.
*        If the numnber is not equal to the m_iCycleCount, the m_iCycleCount will be reset with the cycleNumber.
*
* \param cycleNumber: the new number that will be set to the m_iCycleCount
*
* \return none.
*
******************************************************************************/
void RecipeGeneral::setRecipeWeldCycleCount(const int cycleNumber)
{
    if(m_iCycleCount != cycleNumber)
        m_iCycleCount = cycleNumber;
}

