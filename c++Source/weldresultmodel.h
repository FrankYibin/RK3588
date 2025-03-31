/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef WELDRESULTMODEL_H
#define WELDRESULTMODEL_H

#include <QObject>
#include <QAbstractTableModel>

class WeldResultModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WeldResultModel(QObject *parent = nullptr);
protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

signals:

};

#endif // WELDRESULTMODEL_H
