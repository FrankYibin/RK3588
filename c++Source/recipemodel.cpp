/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include "recipemodel.h"
#include "recipedef.h"
//#include "productionruninterface.h"
#include "communicationinterface.h"
RecipeModel* RecipeModel::m_pRecipeModeObj = nullptr;
/**************************************************************************//**
*
* \brief Constructor and initialize recipe list that will save all the properties of each recipe.
*
* \param QObject* parent
*
* \return None
*
******************************************************************************/
RecipeModel::RecipeModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_listRecipe.clear();
}

/**************************************************************************//**
*
* \brief  To get RecipeModel singleton object.
*         The class is designed to the singleton class so the recipeModel object can used in the everywhere
*         without any new instantiation.
*         And the recipeModel object can be get easily using the this function
*         without any external declaration before using.
*
*
* \param  none
*
* \return Existing recipeModel object
*
******************************************************************************/
RecipeModel *RecipeModel::getInstance()
{
    if(m_pRecipeModeObj == nullptr)
    {
        m_pRecipeModeObj = new RecipeModel();
    }
    return m_pRecipeModeObj;
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        Note: This function can be invoked via the meta-object system and from QML.
*        To get the recipe list size number.
*
* \param It can be ignored in here.
*
* \return Return recipe list size.
*
******************************************************************************/
int RecipeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listRecipe.count();
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        To locate at the specific object using the Model Index and get the data from the specific object then.
*        Note: This function can be invoked via the meta-object system and from QML.
*        Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param index.row should be in the range of the recipe list.
*
* \return the property data using the role index that has been defined in the RoleNames function.
*
******************************************************************************/
QVariant RecipeModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_listRecipe.count())
        return QVariant();
    QStringList recipeDetails;
    const RecipeGeneral *ptrRecipeObj = m_listRecipe[index.row()];
    switch (role)
    {
    case NumberRole:
        return QString::number(ptrRecipeObj->getRecipeNumber(), 10);
        break;
    case NameRole:
        return ptrRecipeObj->getRecipeName();
        break;
    case ActiveStatusRole:
        return ptrRecipeObj->getRecipeActiveStatus();
        break;
    case ValidateStatusRole:
        return ptrRecipeObj->getRecipeValidateStatus();
        break;
    case ModifiedStatusRole:
        return ptrRecipeObj->getRecipeModifiedStatus();
        break;
    case NewCardStatusRole:
        return ptrRecipeObj->getRecipeNewCardStatus();
        break;
    case WeldModeRole:
        return ptrRecipeObj->getWeldModeEnum();
        break;
    case WeldModeValueRole:
        return ptrRecipeObj->getWeldModeValue();
        break;
    case WeldModeUnitRole:
        return ptrRecipeObj->getWeldModeUnit();
        break;
    case CycleCountRole:
        return ptrRecipeObj->getRecipeWeldCycleCount();
        break;
    default:
        return QVariant();
        break;
    }
    return QVariant();
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        Returns the index of the data in row and column with parent.
*        Note: This function can be invoked via the meta-object system and from QML.
*        Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param index.row should be in the range of the recipe list.
*
* \return If the row is in the range of the recipe list, the QModelIndex index will be created; else return QModelIndex()
*
******************************************************************************/
QModelIndex RecipeModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
        return QModelIndex();

    RecipeGeneral *ptrRecipeObj = nullptr;
    if(index.isValid() == false)
        ptrRecipeObj = m_listRecipe.at(0);
    else
        ptrRecipeObj = static_cast<RecipeGeneral*>(index.internalPointer());

    if (ptrRecipeObj)
        return createIndex(row, column, ptrRecipeObj);
    else
        return QModelIndex();
}

//bool RecipeModel::insertRows(int row, int count, const QModelIndex &index)
//{
//    return true;
//}

//bool RecipeModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    return true;
//}

//bool RecipeModel::removeRows(int row, int count, const QModelIndex &index)
//{
//    return true;
//}

/**************************************************************************//**
*
* \brief Insert a single recipe for the qml request action, such as Copy and Create a New Recipe.
*        Note: This function calls the virtual method insertRows.
*        Returns true if the row is inserted; otherwise returns false.
*        If the row is 0, it will be to create a new recipe for the qml Create New request,
*        else it will be copy the indicated recipe using the row number.
*
*
* \param row is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::insertRow(int row)
{
    if(row < 0 || row >= m_listRecipe.size())
        return false;
    if(m_listRecipe.size() >= RECIPE_CARD_MAXIMUM)
        return false;
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    RecipeGeneral* ptrSrcRecipeObj = m_listRecipe.at(row);
    RecipeGeneral* ptrDecRecipeObj = nullptr;

    /*******************************************************************************/
    /* Here is the test code only for the ADD NEW and COPY functionalities testing */
    //TODO All the data should be from SC so we need to add the communication code in here later.
    /*******************************************************************************/

    if(row != 0)
    {
        ptrDecRecipeObj = new RecipeGeneral(m_listRecipe.size(), ptrSrcRecipeObj->getRecipeName(),
                                                       ptrSrcRecipeObj->getWeldModeEnum(),
                                                       ptrSrcRecipeObj->getWeldModeUnit(), ptrSrcRecipeObj->getWeldModeValue(),
                                                       ptrSrcRecipeObj->getRecipeActiveStatus(), ptrSrcRecipeObj->getRecipeValidateStatus(),
                                                       ptrSrcRecipeObj->getRecipeModifiedStatus(), false,
                                                       ptrSrcRecipeObj->getRecipeWeldCycleCount());
    }
    else
    {
        ptrDecRecipeObj = new RecipeGeneral(m_listRecipe.size(), strNewRecipeName,
                                                       RecipeEnum::TIME_IDX,
                                                       strNewRecipeUnit, strNewRecipeValue,
                                                       ptrSrcRecipeObj->getRecipeActiveStatus(), ptrSrcRecipeObj->getRecipeValidateStatus(),
                                                       ptrSrcRecipeObj->getRecipeModifiedStatus(), false,
                                                       ptrSrcRecipeObj->getRecipeWeldCycleCount());
    }
    m_listRecipe.append(ptrDecRecipeObj);
    endInsertRows();
    return true;
}

/**************************************************************************//**
*
* \brief Delete a single recipe for the qml request action, Delete.
*        Note: This function calls the virtual method removeRows.
*        Returns true if the row is deleted; otherwise returns false.
*        The empty card is not able to be removed, the screen always keep the empty card available upon the screen.
*
* \param row is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::removeRow(int row)
{
    if(row <= 0 || row >= m_listRecipe.size())
        return false;
    beginRemoveRows(QModelIndex(), row, row);
    RecipeGeneral *ptrRecipeObj = m_listRecipe.at(row);
    delete ptrRecipeObj;
    m_listRecipe.removeAt(row);
    endRemoveRows();
    return true;
}

/**************************************************************************//**
*
* \brief To reset cycle count for the response from the qml.
*
* \param index is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::resetCycleCount(int index)
{
    if(index <= 0 || index >= m_listRecipe.size())
        return false;
    RecipeGeneral *ptrRecipeObj = m_listRecipe.at(index);
    ptrRecipeObj->setRecipeWeldCycleCount(0);

    QModelIndex row = createIndex(index, 0, ptrRecipeObj);
    emit dataChanged(row, row, {RecipeModel::CycleCountRole});
    return true;
}

/**************************************************************************//**
*
* \brief To set Active status for the response from the qml
*
* \param index is the recipe location where is saved at the recipe list.
*
* \return true is the insert successful, false is not successful.
*
******************************************************************************/
bool RecipeModel::setAsActive(int index)
{
    if(index <= 0 || index >= m_listRecipe.size())
        return false;
    RecipeGeneral *ptrRecipeObj = nullptr;
    for(int i = 0; i < m_listRecipe.size(); i++)
    {
        ptrRecipeObj = m_listRecipe.at(i);
        if(i != index)
        {
            if(ptrRecipeObj->getRecipeActiveStatus() != false)
            {
                ptrRecipeObj->setRecipeActiveStatus(false);
            }
        }
        else
        {
            if(ptrRecipeObj->getRecipeActiveStatus() != true)
            {
                ptrRecipeObj->setRecipeActiveStatus(true);
                initProductionValue();
            }
        }
        QModelIndex row = createIndex(i, 0, ptrRecipeObj);
        emit dataChanged(row, row, {RecipeModel::ActiveStatusRole});
    }
    return true;
}

/**************************************************************************//**
*
* \brief To initialize parameters that needs to show upon the Production Run Screen.
*        Once the current Active recipe card is changed, the parameters need to synchronize with Production Run mode.
*
* \param None.
*
* \return If there is any issue on the parameters updating, the result is false; else the result is true.
*
******************************************************************************/
bool RecipeModel::initProductionValue()
{
//    RecipeGeneral *ptrRecipeObj = nullptr;
//    ProductionRun *ptrProductionRunObj = ProductionRun::getInstance();
//    for(int i = 0; i < m_listRecipe.size(); i++)
//    {
//        ptrRecipeObj = m_listRecipe.at(i);
//        if(ptrRecipeObj->getRecipeActiveStatus() == true)
//        {
//            ptrProductionRunObj->updateActiveRecipeName(ptrRecipeObj->getRecipeName());
//            ptrProductionRunObj->updateCycleCount(QString::number(ptrRecipeObj->getRecipeWeldCycleCount(), 10));
//            ptrProductionRunObj->updateRecipeWeldMode(ptrRecipeObj->getWeldModeEnum());
//            ptrProductionRunObj->updateRecipeWeldModeValue(ptrRecipeObj->getWeldModeValue());
//            ptrProductionRunObj->updateRecipeWeldModeUnit(ptrRecipeObj->getWeldModeUnit());
//            break;
//        }
//    }


    return true;
}

/**************************************************************************//**
*
* \brief To append a new recipe object to the recipe list.
*
* \param recipe object
*
* \return none
*
******************************************************************************/
void RecipeModel::addNewRecipe(RecipeGeneral *recipe)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_listRecipe.append(recipe);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief To clear the recipe list before the entire recipes are loaded for SC so
*        the data of recipe list can be synchronize with SC.    .
*
* \param none
*
* \return none
*
******************************************************************************/
void RecipeModel::clearRecipes()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    qDeleteAll(m_listRecipe);
    m_listRecipe.clear();
    endRemoveRows();
}

/**************************************************************************//**
*
* \brief The load recipes business that will add the communication code in later
*        so it can recall the recipes from SC and create the objects from these recipes.
*        Note: If the recipe loading from SC is successful, return true; else it will return false.
* \param none
*
* \return loading result
*
******************************************************************************/
bool RecipeModel::loadRecipeCards()
{
    clearRecipes();
    /*Test Code for the Recipe*/
    createNewRecipe();
//    QByteArray supportedModes;
//    CommunicationInterface::getInstance()->sendMessage(requestIdentities::GET_WELD_RECIPE_LIST, supportedModes);
//    QByteArray receiveBuffer;
//    CommunicationInterface::getInstance()->receivedMessage(requestIdentities::GET_WELD_RECIPE_LIST, receiveBuffer);
    //TODO add the communication for the existing recipe list getting
    RecipeGeneral* ptrRecipeObj = nullptr;
    ptrRecipeObj = new RecipeGeneral(7, "SpeakerBox", RecipeEnum::COLDISTANCE_IDX, "mm",   "0.55",     false,  false, false, false, 1);
    addNewRecipe(ptrRecipeObj);
    ptrRecipeObj = new RecipeGeneral(6, "shure",      RecipeEnum::TIME_IDX,        "s",    "0.215",    true,   false, false, false, 2);
    addNewRecipe(ptrRecipeObj);
    ptrRecipeObj = new RecipeGeneral(5, "GoCapOuter", RecipeEnum::ENERGY_IDX,      "J",    "200",      false,  false, false, false, 3);
    addNewRecipe(ptrRecipeObj);
    ptrRecipeObj = new RecipeGeneral(4, "Jerry",      RecipeEnum::PEAKPOWER_IDX,   "W",    "100",      false,  false, false, false, 4);
    addNewRecipe(ptrRecipeObj);

//    if(m_listRecipe.isEmpty() != true)
//        initProductionValue();
    return true;
}

/**************************************************************************//**
*
* \brief To create a empty recipe only for the new recipe creating card shown on the screen.
*
* \param none
*
* \return none
*
******************************************************************************/
void RecipeModel::createNewRecipe()
{
    RecipeGeneral* ptrRecipeObj = new RecipeGeneral();
    addNewRecipe(ptrRecipeObj);
}

/**************************************************************************//**
*
* \brief Define which properties need to expose to QML under the recipe Model.
*        Generate a link table between Model and list data.
*
* \param None
*
* \return Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> RecipeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RecipesRoles::NumberRole]         = "assignedNum";
    roles[RecipesRoles::NameRole]           = "assignedName";
    roles[RecipesRoles::CompanyNameRole]    = "companyName";
    roles[RecipesRoles::ActiveStatusRole]   = "isActive";
    roles[RecipesRoles::ValidateStatusRole] = "isValidate";
    roles[RecipesRoles::ModifiedStatusRole] = "isModefied";
    roles[RecipesRoles::NewCardStatusRole]  = "isNewCard";
    roles[RecipesRoles::WeldModeRole]       = "weldModeEnum";
    roles[RecipesRoles::WeldModeValueRole]  = "weldModeValue";
    roles[RecipesRoles::WeldModeUnitRole]   = "weldModeUnit";
    roles[RecipesRoles::CycleCountRole]     = "cycleCount";
    return roles;
}
