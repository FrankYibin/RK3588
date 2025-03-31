/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Alarm notification class definition
 
 **********************************************************************************************************/

#ifndef ALARMNOTIFICATION_H
#define ALARMNOTIFICATION_H

#include <QObject>

class AlarmNotification : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int AlarmIndex READ getAlarmIndex WRITE setAlarmIndex NOTIFY signalAlarmIndexChanged)
public:
    static AlarmNotification* getInstance(QObject *parent = nullptr);

    int getAlarmIndex() const;
    void setAlarmIndex(const int tmpIndex);

    Q_INVOKABLE bool resetSpecificAlarm(const int tmpIndex);

protected:
    explicit AlarmNotification(QObject *parent = nullptr);
private:
    static AlarmNotification* m_pAlarmObj;
    int m_AlarmIndex;
signals:
    void signalAlarmIndexChanged();
private slots:
    void slotNotifyAlarm(int alarmId);

};

#endif // ALARMNOTIFICATION_H
