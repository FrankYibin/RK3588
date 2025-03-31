/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef UPGRADESOFTWARE_H
#define UPGRADESOFTWARE_H

#include <QObject>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QDebug>
#include <QTime>
#include <QProcess>

class SoftwareUpgrading : public QObject
{
    Q_OBJECT
public:
    static SoftwareUpgrading* getInstance();
    Q_PROPERTY(float CurrentProgressValue READ getCurrentProgressValue WRITE setCurrentProgressValue NOTIFY signalCurrentProgressValueChanged)
    Q_INVOKABLE bool retrieveTargetSoftware(int currentIndex, QStringList strFileName);
    Q_INVOKABLE bool runUpgradeProcess(int currentIndex);
public:
    float getCurrentProgressValue() const;
    void setCurrentProgressValue(const float& realProgressValue);
protected:
    explicit SoftwareUpgrading(QObject *parent = nullptr);
private:
    static SoftwareUpgrading* m_ptrInstance;
    QString m_strTargetFilePath;
    float m_realProgressValue;
signals:
    void signalCurrentProgressValueChanged();
};

#endif // UPDATESOFTWARE_H
