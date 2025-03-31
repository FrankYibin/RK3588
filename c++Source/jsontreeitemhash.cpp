/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include "jsontreeitemhash.h"
#include "uiscreendef.h"
QMap<QString, JsonTreeItem*>* JsonTreeItemHash::_hashItemIndex = nullptr;
QList<int>* JsonTreeItemHash::_stackHierarchical = nullptr;
QMap<QString, QString>* JsonTreeItemHash::_textIndex = nullptr;
QHash<int, JsonTreeItem*>* JsonTreeItemHash::_hashScreenIndex = nullptr;
/**************************************************************************//**
*
* \brief  Constructor
*         Meanwhile, _hashItemIndex, _hashScreenIndex, _stackHierarchical and _textIndex need to be initialized.
*
* \param  none
*
* \return none
*
******************************************************************************/
JsonTreeItemHash::JsonTreeItemHash()
{
    _hashItemIndex = new QMap<QString, JsonTreeItem*>();
    _hashScreenIndex = new QHash<int, JsonTreeItem*>();
    _stackHierarchical = new QList<int>();
    _textIndex = new QMap<QString, QString>();
}

/**************************************************************************//**
*
* \brief  Destructor
*         If _hashItemIndex, _hashScreenIndex, _stackHierarchical and _textIndex object pointer is not equal to nullptr,
*         the object pointers needs to clear the container and delete the object pointer then.
*
* \param  none
*
* \return none
*
******************************************************************************/
JsonTreeItemHash::~JsonTreeItemHash()
{
    if(_hashItemIndex != nullptr)
    {
        QMap<QString, JsonTreeItem*>::const_iterator iterBegin = _hashItemIndex->constBegin();
        QMap<QString, JsonTreeItem*>::const_iterator iterEnd = _hashItemIndex->constEnd();
        qDeleteAll(iterBegin, iterEnd);
        _hashItemIndex->clear();
        delete _hashItemIndex;
    }
    if(_hashScreenIndex != nullptr)
    {
        QHash<int, JsonTreeItem*>::const_iterator iterBegin = _hashScreenIndex->constBegin();
        QHash<int, JsonTreeItem*>::const_iterator iterEnd = _hashScreenIndex->constEnd();
        qDeleteAll(iterBegin, iterEnd);
        _hashScreenIndex->clear();
        delete _hashScreenIndex;
    }
    if(_stackHierarchical != nullptr)
    {
        _stackHierarchical->clear();
        delete _stackHierarchical;
    }
    if(_textIndex != nullptr)
    {
        _textIndex->clear();
        delete _textIndex;
    }
}

/**************************************************************************//**
*
* \brief  Insert item object (language text string) to Map
*
* \param  _obj : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeItemHash::insertItemObjectToItemMap(JsonTreeItem *_obj)
{
    QString strIndex = "";
    if(_stackHierarchical != nullptr)
    {
        for(int i = 0; i < _stackHierarchical->size(); i++)
        {
            strIndex += QString::number(_stackHierarchical->at(i)) + ",";
        }
        strIndex = strIndex.left(strIndex.length() - 1);
        if(_hashItemIndex != nullptr)
        {
            _hashItemIndex->insert(strIndex, _obj);
        }
    }
}

/**************************************************************************//**
*
* \brief  Insert item Object (screen title text string) to Hash
*
* \param  screenName: QString; _obj : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeItemHash::insertItemObjectToScreenHash(QString screenName, JsonTreeItem *_obj)
{
    if(screenName == "leftMenu")
        _hashScreenIndex->insert(UIScreenEnum::LEFTMENU, _obj);
    else if(screenName == "rightMenu")
        _hashScreenIndex->insert(UIScreenEnum::RIGHTMENU, _obj);
    else if(screenName == "Recipes")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES, _obj);
    else if(screenName == "RecipesLab")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB, _obj);
    else if(screenName == "RecipeSettings")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_SETTING, _obj);
    else if(screenName == "RecipeWeldMode")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDMODE, _obj);
    else if(screenName == "RecipeWeldProcess")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDPROCESS, _obj);
    else if(screenName == "Pretrigger")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDPROCESS_PRETRIGGER, _obj);
    else if(screenName == "Afterburst")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_WELDPROCESS_AFTERBURST, _obj);
    else if(screenName == "ParametersAZ")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_PARAMETERA2Z, _obj);
    else if(screenName == "Limits")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS, _obj);
    else if(screenName == "Setup")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS_SETUP, _obj);
    else if(screenName == "Control")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS_CONTROL, _obj);
    else if(screenName == "SuspectReject")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_LIMITS_SUSPECT_REJECT, _obj);
    else if(screenName == "StackRecipe")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_STACKRECIPE, _obj);
    else if(screenName == "ResultView")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_RESULTVIEW, _obj);
    else if(screenName == "GraphSettings")
        _hashScreenIndex->insert(UIScreenEnum::RECIPES_LAB_GRAPHSETTING, _obj);
    else if(screenName == "Production")
        _hashScreenIndex->insert(UIScreenEnum::PRODUCTION, _obj);
    else if(screenName == "Analytics")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS, _obj);
    else if(screenName == "graphView")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_VIEW, _obj);
    else if(screenName == "graphRightSetting")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_RIGHT_SETTING, _obj);
    else if(screenName == "graphHeaderSetting")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_HEADER_SETTING, _obj);
    else if(screenName == "graphAxis")
        _hashScreenIndex->insert(UIScreenEnum::ANALYTICS_RESULT_GRAPH_AXIS, _obj);
    else if(screenName == "System")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM, _obj);
    else if(screenName == "Information")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_INFO, _obj);
    else if(screenName == "SoftwareUpgrade")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE, _obj);
    else if(screenName == "InsertUSBtoWelder")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE_WELDER, _obj);
    else if(screenName == "InsertUSBtoRaspPi")
        _hashScreenIndex->insert(UIScreenEnum::SYSTEM_SOFTWARE_UPGRADE_RASPPI, _obj);
    else if(screenName == "Actuator Setup")
        _hashScreenIndex->insert(UIScreenEnum::ACTUATORSETUP, _obj);
    else if(screenName == "Diagnostics")
        _hashScreenIndex->insert(UIScreenEnum::DIAGNOSTICS, _obj);
    else if(screenName == "Import/ Export")
        _hashScreenIndex->insert(UIScreenEnum::IMPORTEXPORT, _obj);
    else if(screenName == "Logout")
        _hashScreenIndex->insert(UIScreenEnum::LOGOUT, _obj);
    else if(screenName == "selectLanguage")
        _hashScreenIndex->insert(UIScreenEnum::SELECTLANGUAGE, _obj);
    else if(screenName == "LowerWeldModeValue")
        _hashScreenIndex->insert(UIScreenEnum::WELDMODE_VALUE_LOWERSTRING, _obj);
    else if(screenName == "Login")
        _hashScreenIndex->insert(UIScreenEnum::LOGIN, _obj);
    else if(screenName == "NumericKeypad")
        _hashScreenIndex->insert(UIScreenEnum::NUMPAD, _obj);
    else if(screenName == "alarm")
        _hashScreenIndex->insert(UIScreenEnum::ALARM, _obj);
    else if(screenName == "alarmGeneral")
        _hashScreenIndex->insert(UIScreenEnum::ALARM_GENERAL, _obj);
    else if(screenName == "alarmName")
        _hashScreenIndex->insert(UIScreenEnum::ALARM_NAME, _obj);
    else if(screenName == "alarmDescription")
        _hashScreenIndex->insert(UIScreenEnum::ALARM_DESCRIPTION, _obj);
    else
        _hashScreenIndex->insert(UIScreenEnum::NONESCREEN, _obj);
}
