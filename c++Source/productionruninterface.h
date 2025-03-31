/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef PRODUCTIONRUN_H
#define PRODUCTIONRUN_H

#include <QObject>
#include <QThread>
#include <QMutex>
class ProductionRun : public QThread
{
    Q_OBJECT
    Q_PROPERTY(int ActiveRecipeNum READ getActiveRecipeNum WRITE updateActiveRecipeNum NOTIFY OnActiveRecipeNumChanged)
    Q_PROPERTY(QString ActiveRecipeName READ getActiveRecipeName WRITE updateActiveRecipeName NOTIFY OnActiveRecipeNameChanged)

    Q_PROPERTY(int RecipeWeldMode READ getRecipeWeldMode WRITE updateRecipeWeldMode NOTIFY OnRecipeWeldModeChanged )
    Q_PROPERTY(QString RecipeWeldModeUnit READ getRecipeWeldModeUnit WRITE updateRecipeWeldModeUnit NOTIFY OnRecipeWeldModeUnitChanged)
    Q_PROPERTY(QString RecipeWeldModeValue READ getRecipeWeldModeValue WRITE updateRecipeWeldModeValue NOTIFY OnRecipeWeldModeValueChanged)

    Q_PROPERTY(QString TotalCycleTime READ getTotalCycleTime WRITE updateTotalCycleTime NOTIFY OnTotalCycleTimeChanged)
    Q_PROPERTY(QString CycleCount READ getCycleCount  WRITE updateCycleCount NOTIFY OnCycleCountChanged)
    Q_PROPERTY(float PeakPowerRatio READ getPeakPowerRatio WRITE updatePeakPowerRatio NOTIFY OnPeakPowerRatioChanged)
private:
    static ProductionRun* m_pProductionRunObj;
    static QMutex mutex;
    int     m_iActiveRecipeNum;
    QString m_strActiveRecipeName;
    int     m_iRecipeWeldMode;
    QString m_strRecipeWeldModeUnit;
    QString m_strRecipeWeldModeValue;
    QString m_strTotalCycleTime;
    QString m_strCycleCount;
    float   m_realPeakPowerRatio;
public:
    static ProductionRun* getInstance();
    int getActiveRecipeNum() const;
    void updateActiveRecipeNum(const int& iRecipeNum);

    QString getActiveRecipeName() const;
    void updateActiveRecipeName(const QString& strRecipeName);

    int getRecipeWeldMode() const;
    void updateRecipeWeldMode(const int& weldMode);

    QString getRecipeWeldModeUnit() const;
    void updateRecipeWeldModeUnit(const QString& weldModeUnit);

    QString getRecipeWeldModeValue() const;
    void updateRecipeWeldModeValue(const QString& weldModeValue);

    QString getTotalCycleTime() const;
    void updateTotalCycleTime(const QString& totalCycleTime);

    QString getCycleCount() const;
    void updateCycleCount(const QString& cycleCount);

    float getPeakPowerRatio() const;
    void updatePeakPowerRatio(const float& peakPowerRatio);
private:
    void updateActiveRecipeBasicInfo();
protected:
    explicit ProductionRun(QObject *parent = nullptr);
    void run() override;
signals:
    void OnActiveRecipeNumChanged();
    void OnActiveRecipeNameChanged();
    void OnRecipeWeldModeChanged();
    void OnRecipeWeldModeUnitChanged();
    void OnRecipeWeldModeValueChanged();

    void OnTotalCycleTimeChanged();
    void OnCycleCountChanged();
    void OnPeakPowerRatioChanged();
private slots:
    void slotHeartbeatUpdated(void*);
};

#endif // PRODUCTIONRUN_H
