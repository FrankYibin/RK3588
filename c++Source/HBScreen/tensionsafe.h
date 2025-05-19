#ifndef TENSIONSAFE_H
#define TENSIONSAFE_H

#include <QObject>

class TensionSafe : public QObject
{
    Q_OBJECT
    // parameter set

    //WellType                  油井类型?
    Q_PROPERTY(QString WellType READ WellType WRITE setWellType NOTIFY WellTypeChanged);

    // SensorWeight              仪器串重量
    // Q_PROPERTY(QString SensorWeight READ SensorWeight WRITE setSensorWeight NOTIFY SensorWeightChanged);

    //MaxTension                极限张力
    // Q_PROPERTY(QString  MaxTension READ MaxTension WRITE setMaxTension NOTIFY MaxTensionChanged );


    //Weight per kilometer of cable     电缆每千米重量
    Q_PROPERTY(QString CableWeight READ CableWeight WRITE setCableWeight NOTIFY CableWeightChanged );

    // HarnessForce              电缆拉断力
    // Q_PROPERTY(QString HarnessForce READ HarnessForce WRITE setHarnessForce NOTIFY HarnessForceChanged );


    //Safe tension factor       安全张力系数
    Q_PROPERTY(QString TensionSafeFactor READ TensionSafeFactor WRITE setTensionSafeFactor NOTIFY TensionSafeFactorChanged );

    //WorkType                  作业类型
    //Q_PROPERTY(QString WorkType READ WorkType WRITE setWorkType NOTIFY WorkTypeChanged );

    //Weak point pulling force  弱点拉断力
    Q_PROPERTY(QString WeakForce READ WeakForce WRITE setWeakForce NOTIFY WeakForceChanged );

    //Parameter Preview


    //Current Tension Safe    当前安全张力
    Q_PROPERTY(QString CurrentTensionSafe READ CurrentTensionSafe WRITE setCurrentTensionSafe NOTIFY CurrentTensionSafeChanged);

    //MAX Tension Safe
    Q_PROPERTY(QString MAXTensionSafe READ MAXTensionSafe WRITE setMAXTensionSafe NOTIFY MAXTensionSafeChanged);

//    Q_PROPERTY(QString CurrentHarnessTension READ CurrentHarnessTension WRITE setCurrentHarnessTension NOTIFY CurrentHarnessTensionChanged);

    //Trend of tension variation of the cable head  揽头张力变化趋势
    Q_PROPERTY(QString CableTensionTrend READ CableTensionTrend WRITE setCableTensionTrend NOTIFY CableTensionTrendChanged );

    //Safe parking time
    Q_PROPERTY(QString Ptime READ Ptime WRITE setPtime NOTIFY PtimeChanged);

    //DepthLoss   深度误差
    Q_PROPERTY(QString DepthLoss READ DepthLoss WRITE setDepthLoss NOTIFY DepthLossChanged);

    //Current Depth1
    Q_PROPERTY(QString CurrentDepth1 READ CurrentDepth1 WRITE setCurrentDepth1 NOTIFY CurrentDepth1Changed);

    //Current Depth2
    Q_PROPERTY(QString CurrentDepth2 READ CurrentDepth2 WRITE setCurrentDepth2 NOTIFY CurrentDepth2Changed);

    //Current Depth3
    Q_PROPERTY(QString CurrentDepth3 READ CurrentDepth3 WRITE setCurrentDepth3 NOTIFY CurrentDepth3Changed);

public:
    static TensionSafe* getInstance();


    QString WellType() const;
    // QString MaxTension() const;
    QString CableWeight() const;
    QString TensionSafeFactor() const;
    QString WeakForce() const;
    QString CurrentTensionSafe() const;
//    QString CurrentHarnessTension() const;
    QString MAXTensionSafe() const;
    QString CableTensionTrend() const;
    QString Ptime() const;
    QString DepthLoss() const;
    QString CurrentDepth1() const;
    QString CurrentDepth2() const;
    QString CurrentDepth3() const;

    void setWellType(const QString &value);
    // void setMaxTension(const QString &value);
    void setCableWeight(const QString &value);
    void setTensionSafeFactor(const QString &value);
    void setWeakForce(const QString &value);
//    void setCurrentHarnessTension(const QString &value);
    void setCurrentTensionSafe(const QString &value);
    void setMAXTensionSafe(const QString &value);
    void setCableTensionTrend(const QString &value);
    void setPtime(const QString &value);
    void setDepthLoss(const QString &value);
    void setCurrentDepth1(const QString &value);
    void setCurrentDepth2(const QString &value);
    void setCurrentDepth3(const QString &value);



signals:

    void WellTypeChanged();
    // void MaxTensionChanged();
    void CableWeightChanged();
    void TensionSafeFactorChanged();
    void WeakForceChanged();
    void CurrentTensionSafeChanged();
    void MAXTensionSafeChanged();
    void CableTensionTrendChanged();
    void PtimeChanged();
    void DepthLossChanged();
    void CurrentDepth1Changed();
    void CurrentDepth2Changed();
    void CurrentDepth3Changed();
//    void CurrentHarnessTensionChanged();

private:

    explicit TensionSafe(QObject *parent = nullptr);

    TensionSafe(const TensionSafe&) = delete;              // 禁止拷贝
    TensionSafe& operator=(const TensionSafe&) = delete;   // 禁止赋值
    static TensionSafe* m_tensionSafe;


private:

    QString m_wellType;
    // QString m_maxTension;
    QString m_cableWeight;
    QString m_TensionSafeFactor;
    QString m_weakForce;
//    QString m_currentHarnessTension;
    QString m_currentTensionSafe;
    QString m_maxTensionSafe;
    QString m_cableTensionTrend;
    QString m_ptime;
    QString m_depthLoss;
    QString m_currentDepth1;
    QString m_currentDepth2;
    QString m_currentDepth3;
};

#endif // TENSIONSAFE_H
