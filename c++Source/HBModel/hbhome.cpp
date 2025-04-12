#include "hbhome.h"

HBHome::HBHome(QObject *parent)
    : QObject{parent}
{}

int HBHome::Depth() const
{
    return m_depth;
}

void HBHome::setDepth(int newDepth)
{
    if ( m_depth == newDepth )
        return;
    m_depth = newDepth;
    emit DepthChanged();

}

int HBHome::Speed() const
{
    return m_speed;
}

void HBHome::setSpeed(int newSpeed)
{
    if ( m_speed == newSpeed )
        return;
    m_speed = newSpeed;
    emit SpeedChanged();

}

int HBHome::Tension() const
{
    return m_tension;
}

void HBHome::setTension(int newTension)
{
    if ( m_tension == newTension )
        return;
    m_tension = newTension;
    emit TensionChanged();

}

int HBHome::TensionIncrement() const
{
    return m_tensionIncrement;
}

void HBHome::setTensionIncrement(int newTensionIncrement)
{
    if ( m_tensionIncrement == newTensionIncrement )
        return;
    m_tensionIncrement = newTensionIncrement;
    emit TensionIncrementChanged();
}

int HBHome::Pulse() const
{
    return m_pulse;
}

void HBHome::setPulse(int newPulse)
{
    if ( m_pulse == newPulse )
        return;
    m_pulse = newPulse;
    emit PulseChanged();

}

int HBHome::MaxTension() const
{
    return m_maxTension;
}

void HBHome::setMaxTension(int newMaxTension)
{
    if ( m_maxTension == newMaxTension )
        return;
    m_maxTension = newMaxTension;
    emit MaxTensionChanged();
}

int HBHome::TargetDepth() const
{
    return m_targetDepth;
}

void HBHome::setTargetDepth(int newTargetDepth)
{
    if ( m_targetDepth == newTargetDepth )
        return;
    m_targetDepth = newTargetDepth;
    emit MaxTensionIncrementChanged();
}

int HBHome::MaxSpeed() const
{
    return m_maxSpeed;
}

void HBHome::setMaxSpeed(int newMaxSpeed)
{
    if ( m_maxSpeed == newMaxSpeed )
        return;
    m_maxSpeed = newMaxSpeed;
    emit MaxTensionIncrementChanged();
}

int HBHome::MaxTensionIncrement() const
{
    return m_maxTensionIncrement;
}

void HBHome::setMaxTensionIncrement(int newMaxTensionIncrement)
{
    if ( m_maxTensionIncrement == newMaxTensionIncrement )
        return;
    m_maxTensionIncrement = newMaxTensionIncrement;
    emit MaxTensionIncrementChanged();
}

int HBHome::KValue() const
{
    return m_kValue;
}

void HBHome::setKValue(int newKValue)
{
    if ( m_kValue == newKValue )
        return;
    newKValue = newKValue;
    emit KValueChanged();
}

int HBHome::HarnessTension() const
{
    return m_harnessTension;
}

void HBHome::setHarnessTension(int newHarnessTension)
{
    if ( m_harnessTension == newHarnessTension )
        return;
    m_harnessTension = newHarnessTension;
    emit HarnessTensionChanged();
}

int HBHome::MaxParameterStatus() const
{
    return m_maxParameterStatus;
}

void HBHome::setMaxParameterStatus(int newMaxParameterStatus)
{
    if ( m_maxParameterStatus == newMaxParameterStatus )
        return;
    m_maxParameterStatus = newMaxParameterStatus;
    emit MaxParameterStatusChanged();

}

int HBHome::NetworkStatus() const
{
    return m_networkStatus;
}

void HBHome::setNetworkStatus(int newNetworkStatus)
{
    if ( m_networkStatus == newNetworkStatus )
        return;
    m_networkStatus = newNetworkStatus;
    emit NetworkStatusChanged();

}





