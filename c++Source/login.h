/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>

class Login : public QObject
{
    Q_OBJECT
private:
    static Login* m_pLoginObj;
protected:
    explicit Login(QObject *parent = nullptr);
public:
    static Login* getInstance(QObject *parent = nullptr);
    Q_INVOKABLE int loginValidate(const QString userName, const QString password);
    Q_INVOKABLE int loginValidate(const QString passcode);

signals:

};

#endif // LOGIN_H
