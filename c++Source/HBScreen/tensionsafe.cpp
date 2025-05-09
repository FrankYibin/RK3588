#include "tensionsafe.h"

TensionSafe::TensionSafe(QObject *parent)
    : QObject{parent}
{}

QString TensionSafe::WellType() const { return m_wellType; }
void TensionSafe::setWellType(const QString &value) {
    if (m_wellType != value) {
        m_wellType = value;
        emit WellTypeChanged();
    }
}

// QString TensionSafe::MaxTension() const { return m_maxTension; }
// void TensionSafe::setMaxTension(const QString &value) {
//     if (m_maxTension != value) {
//         m_maxTension = value;
//         emit MaxTensionChanged();
//     }
// }

QString TensionSafe::CableWeight() const { return m_cableWeight; }
void TensionSafe::setCableWeight(const QString &value) {
    if (m_cableWeight != value) {
        m_cableWeight = value;
        emit CableWeightChanged();
    }
}

QString TensionSafe::TensionSafeFactor() const { return m_TensionSafeFactor; }
void TensionSafe::setTensionSafeFactor(const QString &value) {
    if (m_TensionSafeFactor != value) {
        m_TensionSafeFactor = value;
        emit TensionSafeFactorChanged();
    }
}

QString TensionSafe::WeakForce() const { return m_weakForce; }
void TensionSafe::setWeakForce(const QString &value) {
    if (m_weakForce != value) {
        m_weakForce = value;
        emit WeakForceChanged();
    }
}

QString TensionSafe::CurrentTensionSafe() const { return m_currentTensionSafe; }
void TensionSafe::setCurrentTensionSafe(const QString &value) {
    if (m_currentTensionSafe != value) {
        m_currentTensionSafe = value;
        emit CurrentTensionSafeChanged();
    }
}

QString TensionSafe::MAXTensionSafe() const { return m_maxTensionSafe; }
void TensionSafe::setMAXTensionSafe(const QString &value) {
    if (m_maxTensionSafe != value) {
        m_maxTensionSafe = value;
        emit MAXTensionSafeChanged();
    }
}

QString TensionSafe::CableTensionTrend() const { return m_cableTensionTrend; }
void TensionSafe::setCableTensionTrend(const QString &value) {
    if (m_cableTensionTrend != value) {
        m_cableTensionTrend = value;
        emit CableTensionTrendChanged();
    }
}

QString TensionSafe::Ptime() const { return m_ptime; }
void TensionSafe::setPtime(const QString &value) {
    if (m_ptime != value) {
        m_ptime = value;
        emit PtimeChanged();
    }
}

QString TensionSafe::DepthLoss() const { return m_depthLoss; }
void TensionSafe::setDepthLoss(const QString &value) {
    if (m_depthLoss != value) {
        m_depthLoss = value;
        emit DepthLossChanged();
    }
}

QString TensionSafe::CurrentDepth1() const { return m_currentDepth1; }
void TensionSafe::setCurrentDepth1(const QString &value) {
    if (m_currentDepth1 != value) {
        m_currentDepth1 = value;
        emit CurrentDepth1Changed();
    }
}

QString TensionSafe::CurrentDepth2() const { return m_currentDepth2; }
void TensionSafe::setCurrentDepth2(const QString &value) {
    if (m_currentDepth2 != value) {
        m_currentDepth2 = value;
        emit CurrentDepth2Changed();
    }
}

QString TensionSafe::CurrentDepth3() const { return m_currentDepth3; }
void TensionSafe::setCurrentDepth3(const QString &value) {
    if (m_currentDepth3 != value) {
        m_currentDepth3 = value;
        emit CurrentDepth3Changed();
    }
}
