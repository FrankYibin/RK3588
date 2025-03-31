/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "recipegeneral.h"

class RecipeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RecipesRoles {
        IndexRole = Qt::UserRole + 1,
        NumberRole,
        NameRole,
        CompanyNameRole,
        WeldModeRole,
        WeldModeUnitRole,
        WeldModeValueRole,
        ActiveStatusRole,
        ValidateStatusRole,
        ModifiedStatusRole,
        NewCardStatusRole,
        CycleCountRole

    };
public:
    static RecipeModel* getInstance();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &index = QModelIndex()) const override;
//    bool insertRows(int row, int count, const QModelIndex &index = QModelIndex()) override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
//    bool removeRows(int row, int count, const QModelIndex &index = QModelIndex()) override;

    //Branson definition interface for the QML actions
    Q_INVOKABLE bool insertRow(int row);
    Q_INVOKABLE bool removeRow(int row);
    Q_INVOKABLE bool resetCycleCount(int index);
    Q_INVOKABLE bool setAsActive(int index);
    Q_INVOKABLE bool loadRecipeCards();
private:
    void createNewRecipe();
    void clearRecipes();
    void addNewRecipe(RecipeGeneral *recipe);
    bool initProductionValue();
protected:
    QHash<int, QByteArray> roleNames() const override;
    explicit RecipeModel(QObject *parent = nullptr);
private:
    QList<RecipeGeneral*> m_listRecipe;
    const QString strNewRecipeName = "New Recipe";
    const QString strNewRecipeValue = "0.001";
    const QString strNewRecipeUnit  = "s";
    static RecipeModel* m_pRecipeModeObj;
signals:

};

#endif // RECIPEMODEL_H
