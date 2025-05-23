#include "depthsafe.h"

DepthSafe* DepthSafe::m_depthSafe = nullptr;

DepthSafe::DepthSafe(QObject *parent)
    : QObject{parent}
{}

DepthSafe *DepthSafe::getInstance()
{
    if (!m_depthSafe) {
        m_depthSafe = new DepthSafe();
    }
    return m_depthSafe;
}

int DepthSafe::DepthPreset() const
{
    return m_depthPreset;
}
void DepthSafe::setDepthPreset(int newDepthPreset)
{
    if ( m_depthPreset == newDepthPreset )
        return;
    m_depthPreset = newDepthPreset;
    emit DepthPresetChanged();

}

int DepthSafe::WellWarnig() const
{
    return m_wellWarnig;
}

void DepthSafe::setWellWarnig(int newDWellWarnig)
{
    if ( m_wellWarnig == newDWellWarnig )
        return;
    m_wellWarnig = newDWellWarnig;
    emit WellWarnigChanged();

}

int DepthSafe::Brake() const
{
    return m_brake;
}

void DepthSafe::setBrake(int newBrake)
{
    if ( m_brake == newBrake )
        return;
    m_brake = newBrake;
    emit BrakeChanged();
}

int DepthSafe::VelocityLimit() const
{
    return m_velocityLimit;
}

void DepthSafe::setVelocityLimit(int newTVelocityLimit)
{
    if ( m_velocityLimit == newTVelocityLimit )
        return;
    m_velocityLimit = newTVelocityLimit;
    emit VelocityLimitChanged();
}

int DepthSafe::DepthWarning() const
{
    return m_depthWarning;
}

void DepthSafe::setDepthWarning(int newDepthWarning)
{
    if ( m_depthWarning == newDepthWarning )
        return;
    m_depthWarning = newDepthWarning;
    emit DepthWarningChanged();

}

int DepthSafe::TotalDepth() const
{
    return m_totalDepth;
}

void DepthSafe::setTotalDepth(int newTotalDepth)
{
    if ( m_totalDepth == newTotalDepth )
        return;
    m_totalDepth = newTotalDepth;
    emit TotalDepthhanged();
}

int DepthSafe::DepthBrake() const
{
    return m_depthBrake;
}

void DepthSafe::setDepthBrake(int newDepthbrake)
{
    if ( m_depthBrake == newDepthbrake )
        return;
    m_depthBrake = newDepthbrake;
    emit DepthBrakeChanged();
}

int DepthSafe::DepthVelocityLimit() const
{
    return m_depthVelocityLimit;
}

void DepthSafe::setDepthVelocityLimit(int newDepthVelocityLimit)
{
    if ( m_depthVelocityLimit == newDepthVelocityLimit )
        return;
    m_depthVelocityLimit = newDepthVelocityLimit;
    emit DepthVelocityLimitChanged();
}




