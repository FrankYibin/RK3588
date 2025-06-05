#ifndef TENSIONSAFETY_H
#define TENSIONSAFETY_H

#include <QObject>

class TensionSafety : public QObject
{
    Q_OBJECT


    //MaxTension                极限张力
    // Q_PROPERTY(QString  MaxTension READ MaxTension WRITE setMaxTension NOTIFY MaxTensionChanged );




    // HarnessForce              电缆拉断力
    // Q_PROPERTY(QString HarnessForce READ HarnessForce WRITE setHarnessForce NOTIFY HarnessForceChanged );


    //Safe tension factor       安全张力系数
    Q_PROPERTY(QString TensionSafeFactor READ TensionSafeFactor WRITE setTensionSafeFactor NOTIFY TensionSafeFactorChanged )

    //WorkType                  作业类型
    //Q_PROPERTY(QString WorkType READ WorkType WRITE setWorkType NOTIFY WorkTypeChanged );

    //Weak point pulling force  弱点拉断力
    Q_PROPERTY(QString WeakForce READ WeakForce WRITE setWeakForce NOTIFY WeakForceChanged )

    //Parameter Preview


    //Current Tension Safe    当前安全张力
    Q_PROPERTY(QString CurrentTensionSafe READ CurrentTensionSafe WRITE setCurrentTensionSafe NOTIFY CurrentTensionSafeChanged)

    //MAX Tension Safe
    Q_PROPERTY(QString MAXTensionSafe READ MAXTensionSafe WRITE setMAXTensionSafe NOTIFY MAXTensionSafeChanged)

//    Q_PROPERTY(QString CurrentHarnessTension READ CurrentHarnessTension WRITE setCurrentHarnessTension NOTIFY CurrentHarnessTensionChanged);

    //Trend of tension variation of the cable head  揽头张力变化趋势
    Q_PROPERTY(int CableTensionTrend READ CableTensionTrend WRITE setCableTensionTrend NOTIFY CableTensionTrendChanged )

    //Safe parking time
    Q_PROPERTY(QString Ptime READ Ptime WRITE setPtime NOTIFY PtimeChanged)

    //DepthLoss   深度误差
    Q_PROPERTY(QString DepthLoss READ DepthLoss WRITE setDepthLoss NOTIFY DepthLossChanged)

    //Current Depth1
    Q_PROPERTY(QString CurrentDepth1 READ CurrentDepth1 WRITE setCurrentDepth1 NOTIFY CurrentDepth1Changed)

    //Current Depth2
    Q_PROPERTY(QString CurrentDepth2 READ CurrentDepth2 WRITE setCurrentDepth2 NOTIFY CurrentDepth2Changed)

    //Current Depth3
    Q_PROPERTY(QString CurrentDepth3 READ CurrentDepth3 WRITE setCurrentDepth3 NOTIFY CurrentDepth3Changed)
public:
    enum CABLE_TENSION_TREND
    {
        NORMAL = 0,
        INCREMENT,
        DECREMENT

    };

public:
    static TensionSafety* GetInstance();

    // QString MaxTension() const;
    QString CableWeight() const;
    QString TensionSafeFactor() const;
    QString WeakForce() const;
    QString CurrentTensionSafe() const;
//    QString CurrentHarnessTension() const;
    QString MAXTensionSafe() const;

    QString Ptime() const;
    QString DepthLoss() const;
    QString CurrentDepth1() const;
    QString CurrentDepth2() const;
    QString CurrentDepth3() const;

    // void setMaxTension(const QString &value);
    void setCableWeight(const QString &value);
    void setTensionSafeFactor(const QString &value);
    void setWeakForce(const QString &value);
//    void setCurrentHarnessTension(const QString &value);
    void setCurrentTensionSafe(const QString &value);
    void setMAXTensionSafe(const QString &value);

    void setPtime(const QString &value);
    void setDepthLoss(const QString &value);
    void setCurrentDepth1(const QString &value);
    void setCurrentDepth2(const QString &value);
    void setCurrentDepth3(const QString &value);

    int     CableTensionTrend       () const;
    void    setCableTensionTrend    (const int trend);

signals:
    // void MaxTensionChanged();
    void CableWeightChanged();
    void TensionSafeFactorChanged();
    void WeakForceChanged();
    void CurrentTensionSafeChanged();
    void MAXTensionSafeChanged();

    void PtimeChanged();
    void DepthLossChanged();
    void CurrentDepth1Changed();
    void CurrentDepth2Changed();
    void CurrentDepth3Changed();
//    void CurrentHarnessTensionChanged();

    void CableTensionTrendChanged();

private:

    explicit TensionSafety(QObject *parent = nullptr);

    TensionSafety(const TensionSafety&) = delete;              // 禁止拷贝
    TensionSafety& operator=(const TensionSafety&) = delete;   // 禁止赋值
    static TensionSafety* _ptrTensionSafety;


private:
    // QString m_maxTension;
    QString m_cableWeight = "0" ;
    QString m_TensionSafeFactor = "0";
    QString m_weakForce = "0";
//    QString m_currentHarnessTension;
    QString m_currentTensionSafe = "0";
    QString m_maxTensionSafe = "0";

    QString m_ptime = "0";
    QString m_depthLoss = "0";
    QString m_currentDepth1 = "0";
    QString m_currentDepth2 = "0";
    QString m_currentDepth3 = "0";

    int m_cableTensionTrend;
};

#endif // TENSIONSAFETY_H
