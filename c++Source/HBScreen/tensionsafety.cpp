#include "tensionsafety.h"

TensionSafety* TensionSafety::_ptrTensionSafety = nullptr;

TensionSafety::TensionSafety(QObject *parent)
    : QObject{parent}
{
    m_cableTensionTrend = -1;
    setCableTensionTrend(NORMAL);
}

TensionSafety *TensionSafety::GetInstance()
{
    if (!_ptrTensionSafety) {
        _ptrTensionSafety = new TensionSafety();
    }
    return _ptrTensionSafety;
}

// QString TensionSafe::MaxTension() const { return m_maxTension; }
// void TensionSafe::setMaxTension(const QString &value) {
//     if (m_maxTension != value) {
//         m_maxTension = value;
//         emit MaxTensionChanged();
//     }
// }

QString TensionSafety::CableWeight() const
{
    return m_cableWeight;
}
void TensionSafety::setCableWeight(const QString &value)
{
    if (m_cableWeight != value) {
        m_cableWeight = value;
        emit CableWeightChanged();
    }
}

QString TensionSafety::TensionSafeFactor() const
{
    return m_TensionSafeFactor;
}
void TensionSafety::setTensionSafeFactor(const QString &value)
{
    if (m_TensionSafeFactor != value) {
        m_TensionSafeFactor = value;
        emit TensionSafeFactorChanged();
    }
}

QString TensionSafety::WeakForce() const
{
    return m_weakForce;
}
void TensionSafety::setWeakForce(const QString &value)
{
    if (m_weakForce != value) {
        m_weakForce = value;
        emit WeakForceChanged();
    }
}

//void TensionSafe::setCurrentHarnessTension(const QString &value)
//{
//    if (m_currentHarnessTension != value) {
//        m_currentHarnessTension = value;
//        emit CurrentHarnessTensionChanged();
//    }
//}
//QString TensionSafe::CurrentHarnessTension() const
//{
//    return m_currentHarnessTension;
//}

QString TensionSafety::CurrentTensionSafe() const
{
    return m_currentTensionSafe;
}
void TensionSafety::setCurrentTensionSafe(const QString &value)
{
    if (m_currentTensionSafe != value)
    {
        m_currentTensionSafe = value;
        emit CurrentTensionSafeChanged();
    }
}

QString TensionSafety::MAXTensionSafe() const
{
    return m_maxTensionSafe;
}
void TensionSafety::setMAXTensionSafe(const QString &value)
{
    if (m_maxTensionSafe != value)
    {
        m_maxTensionSafe = value;
        emit MAXTensionSafeChanged();
    }
}

int TensionSafety::CableTensionTrend() const
{
    return m_cableTensionTrend;
}
void TensionSafety::setCableTensionTrend(const int trend)
{
    if (m_cableTensionTrend != trend)
    {
        m_cableTensionTrend = trend;
        emit CableTensionTrendChanged();
    }
}

QString TensionSafety::Ptime() const
{
    return m_ptime;
}
void TensionSafety::setPtime(const QString &value)
{
    if (m_ptime != value)
    {
        m_ptime = value;
        emit PtimeChanged();
    }
}

QString TensionSafety::DepthLoss() const
{
    return m_depthLoss;
}
void TensionSafety::setDepthLoss(const QString &value)
{
    if (m_depthLoss != value)
    {
        m_depthLoss = value;
        emit DepthLossChanged();
    }
}

QString TensionSafety::CurrentDepth1() const
{
    return m_currentDepth1;
}
void TensionSafety::setCurrentDepth1(const QString &value)
{
    if (m_currentDepth1 != value)
    {
        m_currentDepth1 = value;
        emit CurrentDepth1Changed();
    }
}

QString TensionSafety::CurrentDepth2() const
{
    return m_currentDepth2;
}
void TensionSafety::setCurrentDepth2(const QString &value)
{
    if (m_currentDepth2 != value)
    {
        m_currentDepth2 = value;
        emit CurrentDepth2Changed();
    }
}

QString TensionSafety::CurrentDepth3() const
{
    return m_currentDepth3;
}
void TensionSafety::setCurrentDepth3(const QString &value)
{
    if (m_currentDepth3 != value)
    {
        m_currentDepth3 = value;
        emit CurrentDepth3Changed();
    }
}
