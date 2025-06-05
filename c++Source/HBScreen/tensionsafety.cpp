#include "tensionsafety.h"
#include "wellparameter.h"
TensionSafety* TensionSafety::_ptrTensionSafety = nullptr;

TensionSafety::TensionSafety(QObject *parent)
    : QObject{parent}
{
    //1. WellType
    m_WellType = -1;
    setWellType(WellParameter::VERTICAL);
    //2. WeightEachKilometerCable
    m_WeightEachKilometerCable = "0";
    setWeightEachKilometerCable("500");
    //3. WorkType
    m_WorkType = -1;
    setWorkType(WellParameter::PERFORATION);
    //4. WeightInstrumentString
    m_WeightInstrumentString = "0";
    setWeightInstrumentString("300");
    //5. BreakingForceCable
    m_BreakingForceCable = "0";
    setBreakingForceCable("4000");
    //6. BreakingForceWeakness
    m_BreakingForceWeakness = "0";
    setBreakingForceWeakness("1800");
    //7. TensionLimited
    m_TensionLimited = "0";
    setTensionLimited("67443.00");
    //8. TensionSafetyCoefficient
    m_TensionSafetyCoefficient = "0";
    setTensionSafetyCoefficient("0.75");
    //9. TensionCurrentSafety
    m_TensionCurrentSafety = "0";
    setTensionCurrentSafety("67443.00");
    //10. TensionLimitedSafety
    m_TensionLimitedSafety = "0";
    setTensionLimitedSafety("67443.00");
    //11. TensionCableHead
    QString m_TensionCableHead = "0";
    setTensionCableHead("67443.00");
    //12. TensionCableHeadTrend
    m_TensionCableHeadTrend = -1;
    setTensionCableHeadTrend(NORMAL);
    //13. TimeSafetyStop
    m_TimeSafetyStop = "0";
    setTimeSafetyStop("600.00");
    //14. DepthTolerance
    m_DepthTolerance = "0";
    setDepthTolerance("99999.99");
    //15. DepthEncoder1
    m_DepthEncoder1 = "0";
    setDepthEncoder1("99999.99");
    //16. DepthEncoder2
    m_DepthEncoder2 = "0";
    setDepthEncoder2("99999.99");
    //17. DepthEncoder3
    m_DepthEncoder3 = "0";
    setDepthEncoder3("99999.99");
}

TensionSafety *TensionSafety::GetInstance()
{
    if (!_ptrTensionSafety) {
        _ptrTensionSafety = new TensionSafety();
    }
    return _ptrTensionSafety;
}

int TensionSafety::WellType() const
{
    return m_WellType;
}

void TensionSafety::setWellType(const int wellType)
{
    if (m_WellType != wellType) {
        m_WellType = wellType;
        emit WellTypeChanged();
    }
}
QString TensionSafety::WeightEachKilometerCable() const
{
    return m_WeightEachKilometerCable;
}
void TensionSafety::setWeightEachKilometerCable(const QString &value)
{
    if (m_WeightEachKilometerCable != value) {
        m_WeightEachKilometerCable = value;
        emit WeightEachKilometerCableChanged();
    }
}
int TensionSafety::WorkType() const
{
    return m_WorkType;
}
void TensionSafety::setWorkType(const int workType)
{
    if (m_WorkType != workType) {
        m_WorkType = workType;
        emit WorkTypeChanged();
    }
}
QString TensionSafety::WeightInstrumentString() const
{
    return m_WeightInstrumentString;
}
void TensionSafety::setWeightInstrumentString(const QString &value)
{
    if (m_WeightInstrumentString != value) {
        m_WeightInstrumentString = value;
        emit WeightInstrumentStringChanged();
    }
}
QString TensionSafety::BreakingForceCable() const
{
    return m_BreakingForceCable;
}
void TensionSafety::setBreakingForceCable(const QString &value)
{
    if (m_BreakingForceCable != value) {
        m_BreakingForceCable = value;
        emit BreakingForceCableChanged();
    }
}
QString TensionSafety::BreakingForceWeakness() const
{
    return m_BreakingForceWeakness;
}
void TensionSafety::setBreakingForceWeakness(const QString &value)
{
    if (m_BreakingForceWeakness != value) {
        m_BreakingForceWeakness = value;
        emit BreakingForceWeaknessChanged();
    }
}
QString TensionSafety::TensionLimited() const
{
    return m_TensionLimited;
}
void TensionSafety::setTensionLimited(const QString &value)
{
    if (m_TensionLimited != value) {
        m_TensionLimited = value;
        emit TensionLimitedChanged();
    }
}
QString TensionSafety::TensionSafetyCoefficient() const
{
    return m_TensionSafetyCoefficient;
}
void TensionSafety::setTensionSafetyCoefficient(const QString &value)
{
    if (m_TensionSafetyCoefficient != value) {
        m_TensionSafetyCoefficient = value;
        emit TensionSafetyCoefficientChanged();
    }
}
QString TensionSafety::TensionCurrentSafety() const
{
    return m_TensionCurrentSafety;
}
void TensionSafety::setTensionCurrentSafety(const QString &value)
{
    if (m_TensionCurrentSafety != value) {
        m_TensionCurrentSafety = value;
        emit TensionCurrentSafetyChanged();
    }
}
QString TensionSafety::TensionLimitedSafety() const
{
    return m_TensionLimitedSafety;
}
void TensionSafety::setTensionLimitedSafety(const QString &value)
{
    if (m_TensionLimitedSafety != value) {
        m_TensionLimitedSafety = value;
        emit TensionLimitedSafetyChanged();
    }
}
QString TensionSafety::TensionCableHead() const
{
    return m_TensionCableHead;
}
void TensionSafety::setTensionCableHead(const QString &value)
{
    if (m_TensionCableHead != value) {
        m_TensionCableHead = value;
        emit TensionCableHeadChanged();
    }
}
int TensionSafety::TensionCableHeadTrend() const
{
    return m_TensionCableHeadTrend;
}
void TensionSafety::setTensionCableHeadTrend(const int trend)
{
    if (m_TensionCableHeadTrend != trend) {
        m_TensionCableHeadTrend = trend;
        emit TensionCableHeadTrendChanged();
    }
}
QString TensionSafety::TimeSafetyStop() const
{
    return m_TimeSafetyStop;
}
void TensionSafety::setTimeSafetyStop(const QString &value)
{
    if (m_TimeSafetyStop != value) {
        m_TimeSafetyStop = value;
        emit TimeSafetyStopChanged();
    }
}
QString TensionSafety::DepthTolerance() const
{
    return m_DepthTolerance;
}
void TensionSafety::setDepthTolerance(const QString &value)
{
    if (m_DepthTolerance != value) {
        m_DepthTolerance = value;
        emit DepthToleranceChanged();
    }
}
QString TensionSafety::DepthEncoder1() const
{
    return m_DepthEncoder1;
}
void TensionSafety::setDepthEncoder1(const QString &value)
{
    if (m_DepthEncoder1 != value) {
        m_DepthEncoder1 = value;
        emit DepthEncoder1Changed();
    }
}
QString TensionSafety::DepthEncoder2() const
{
    return m_DepthEncoder2;
}
void TensionSafety::setDepthEncoder2(const QString &value)
{
    if (m_DepthEncoder2 != value) {
        m_DepthEncoder2 = value;
        emit DepthEncoder2Changed();
    }
}
QString TensionSafety::DepthEncoder3() const
{
    return m_DepthEncoder3;
}
void TensionSafety::setDepthEncoder3(const QString &value)
{
    if (m_DepthEncoder3 != value) {
        m_DepthEncoder3 = value;
        emit DepthEncoder3Changed();
    }
}
