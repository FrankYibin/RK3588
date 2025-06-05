#ifndef TENSIONSAFETY_H
#define TENSIONSAFETY_H

#include <QObject>

class TensionSafety : public QObject
{
    Q_OBJECT

    //1 WellType  油气井类型
    Q_PROPERTY(int WellType READ WellType WRITE setWellType NOTIFY WellTypeChanged)
    //2 WeightEachKilometerCable
    Q_PROPERTY(QString WeightEachKilometerCable READ WeightEachKilometerCable WRITE setWeightEachKilometerCable NOTIFY WeightEachKilometerCableChanged)
    //3 WorkType
    Q_PROPERTY(int WorkType READ WorkType WRITE setWorkType NOTIFY WorkTypeChanged)
    //4 WeightInstrumentString
    Q_PROPERTY(QString WeightInstrumentString READ WeightInstrumentString WRITE setWeightInstrumentString NOTIFY WeightInstrumentStringChanged)
    //5 BreakingForceCable
    Q_PROPERTY(QString BreakingForceCable READ BreakingForceCable WRITE setBreakingForceCable NOTIFY BreakingForceCableChanged)
    //6 BreakingForceWeakness
    Q_PROPERTY(QString BreakingForceWeakness READ BreakingForceWeakness WRITE setBreakingForceWeakness NOTIFY BreakingForceWeaknessChanged)
    //7 TensionLimited                极限张力
    Q_PROPERTY(QString TensionLimited READ TensionLimited WRITE setTensionLimited NOTIFY TensionLimitedChanged);
    //8 TensionSafetyCoefficient
    Q_PROPERTY(QString TensionSafetyCoefficient READ TensionSafetyCoefficient WRITE setTensionSafetyCoefficient NOTIFY TensionSafetyCoefficientChanged FINAL)

    //Parameter Preview
    //9 TensionCurrentSafety    当前安全张力
    Q_PROPERTY(QString TensionCurrentSafety READ TensionCurrentSafety WRITE setTensionCurrentSafety NOTIFY TensionCurrentSafetyChanged)

    //10 MAX Tension Safe 最大安全张力
    Q_PROPERTY(QString TensionLimitedSafety READ TensionLimitedSafety WRITE setTensionLimitedSafety NOTIFY TensionLimitedSafetyChanged)

    //11 当前缆头张力
    Q_PROPERTY(QString TensionCableHead READ TensionCableHead WRITE setTensionCableHead NOTIFY TensionCableHeadChanged);

    //12 Trend of tension variation of the cable head  揽头张力变化趋势
    Q_PROPERTY(int TensionCableHeadTrend READ TensionCableHeadTrend WRITE setTensionCableHeadTrend NOTIFY TensionCableHeadTrendChanged )

    //13 Safe parking time
    Q_PROPERTY(QString TimeSafetyStop READ TimeSafetyStop WRITE setTimeSafetyStop NOTIFY TimeSafetyStopChanged)

    //14 DepthLoss   深度误差
    Q_PROPERTY(QString DepthTolerance READ DepthTolerance WRITE setDepthTolerance NOTIFY DepthToleranceChanged)

    //15 Current Depth1
    Q_PROPERTY(QString DepthEncoder1 READ DepthEncoder1 WRITE setDepthEncoder1 NOTIFY DepthEncoder1Changed)

    //16 Current Depth2
    Q_PROPERTY(QString DepthEncoder2 READ DepthEncoder2 WRITE setDepthEncoder2 NOTIFY DepthEncoder2Changed)

    //17 Current Depth3
    Q_PROPERTY(QString DepthEncoder3 READ DepthEncoder3 WRITE setDepthEncoder3 NOTIFY DepthEncoder3Changed)
public:
    enum TENSION_CABLE_HEAD_TREND
    {
        NORMAL = 0,
        INCREMENT,
        DECREMENT
    };

public:
    static TensionSafety* GetInstance();

    //1 WellType
    int     WellType() const;
    void    setWellType(const int wellType);
    //2 WeightEachKilometerCable
    QString WeightEachKilometerCable() const;
    void    setWeightEachKilometerCable(const QString &value);
    //3 WorkType
    int     WorkType() const;
    void    setWorkType(const int workType);
    //4 WeightInstrumentString
    QString WeightInstrumentString() const;
    void    setWeightInstrumentString(const QString &value);
    //5 BreakingForceCable
    QString BreakingForceCable() const;
    void    setBreakingForceCable(const QString &value);
    //6 BreakingForceWeakness
    QString BreakingForceWeakness() const;
    void    setBreakingForceWeakness(const QString &value);
    //7 TensionLimited
    QString TensionLimited() const;
    void    setTensionLimited(const QString &value);
    //8 TensionSafetyCoefficient
    QString TensionSafetyCoefficient() const;
    void    setTensionSafetyCoefficient(const QString &value);
    //9 TensionCurrentSafety
    QString TensionCurrentSafety() const;
    void    setTensionCurrentSafety(const QString &value);
    //10 TensionLimitedSafety
    QString TensionLimitedSafety() const;
    void    setTensionLimitedSafety(const QString &value);
    //11 TensionCableHead
    QString TensionCableHead() const;
    void    setTensionCableHead(const QString &value);
    //12 TensionCableHeadTrend
    int     TensionCableHeadTrend() const;
    void    setTensionCableHeadTrend(const int trend);
    //13 TimeSafetyStop
    QString TimeSafetyStop() const;
    void    setTimeSafetyStop(const QString &value);
    //14 DepthTolerance
    QString DepthTolerance() const;
    void    setDepthTolerance(const QString &value);
    QString DepthEncoder1() const;
    void    setDepthEncoder1(const QString &value);
    //15 Current Depth1
    QString DepthEncoder2() const;
    void    setDepthEncoder2(const QString &value);
    //16 Current Depth2
    QString DepthEncoder3() const;
    void    setDepthEncoder3(const QString &value);
    //17 Current Depth3
    int     CableTensionTrend() const;
    void    setCableTensionTrend(const int trend);

signals:
    //1. WellTypeChanged
    void WellTypeChanged();
    //2. WeightEachKilometerCableChanged
    void WeightEachKilometerCableChanged();
    //3. WorkTypeChanged
    void WorkTypeChanged();
    //4. WeightInstrumentStringChanged
    void WeightInstrumentStringChanged();
    //5. BreakingForceCableChanged
    void BreakingForceCableChanged();
    //6. BreakingForceWeaknessChanged
    void BreakingForceWeaknessChanged();
    //7. TensionLimitedChanged
    void TensionLimitedChanged();
    //8. TensionSafetyCoefficientChanged
    void TensionSafetyCoefficientChanged();
    //9. TensionCurrentSafetyChanged
    void TensionCurrentSafetyChanged();
    //10. TensionLimitedSafetyChanged
    void TensionLimitedSafetyChanged();
    //11. TensionCableHeadChanged
    void TensionCableHeadChanged();
    //12. TensionCableHeadTrendChanged
    void TensionCableHeadTrendChanged();
    //13. TimeSafetyStopChanged
    void TimeSafetyStopChanged();
    //14. DepthToleranceChanged
    void DepthToleranceChanged();
    //15. DepthEncoder1Changed
    void DepthEncoder1Changed();
    //16. DepthEncoder2Changed
    void DepthEncoder2Changed();
    //17. DepthEncoder3Changed
    void DepthEncoder3Changed();

private:
    explicit TensionSafety(QObject *parent = nullptr);
    TensionSafety(const TensionSafety&) = delete;              // 禁止拷贝
    TensionSafety& operator=(const TensionSafety&) = delete;   // 禁止赋值
    static TensionSafety* _ptrTensionSafety;


private:
    //1. WellType
    int m_WellType;
    //2. WeightEachKilometerCable
    QString m_WeightEachKilometerCable;
    //3. WorkType
    int m_WorkType;
    //4. WeightInstrumentString
    QString m_WeightInstrumentString;
    //5. BreakingForceCable
    QString m_BreakingForceCable;
    //6. BreakingForceWeakness
    QString m_BreakingForceWeakness;
    //7. TensionLimited
    QString m_TensionLimited;
    //8. TensionSafetyCoefficient
    QString m_TensionSafetyCoefficient;
    //9. TensionCurrentSafety
    QString m_TensionCurrentSafety;
    //10. TensionLimitedSafety
    QString m_TensionLimitedSafety;
    //11. TensionCableHead
    QString m_TensionCableHead;
    //12. TensionCableHeadTrend
    int m_TensionCableHeadTrend;
    //13. TimeSafetyStop
    QString m_TimeSafetyStop;
    //14. DepthTolerance
    QString m_DepthTolerance;
    //15. DepthEncoder1
    QString m_DepthEncoder1;
    //16. DepthEncoder2
    QString m_DepthEncoder2;
    //17. DepthEncoder3
    QString m_DepthEncoder3;
};

#endif // TENSIONSAFETY_H
