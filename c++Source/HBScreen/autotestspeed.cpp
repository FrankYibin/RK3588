#include "autotestspeed.h"

AutoTestSpeed* AutoTestSpeed::m_autoTestSpeed = nullptr;


AutoTestSpeed::AutoTestSpeed(QObject *parent)
    : QObject{parent}
{}

AutoTestSpeed *AutoTestSpeed::getInstance()
{
    if (!m_autoTestSpeed) {
        m_autoTestSpeed = new AutoTestSpeed();
    }
    return m_autoTestSpeed;

}
int AutoTestSpeed::Direction() const
{
    return m_direction;
}

void AutoTestSpeed::setDirection(int newDirection)
{
    if ( m_direction == newDirection )
        return;
    m_direction = newDirection;
    emit DirectionChanged();
}

int AutoTestSpeed::SpeedValue()
{
    return m_speedVlue;
}

void AutoTestSpeed::setSpeedValue(int newSpeedValue)
{
    if ( m_speedVlue == newSpeedValue )
        return;
    m_speedVlue = newSpeedValue;
    emit SpeedValueChanged();
}


int AutoTestSpeed::DepthCountDown()
{
    return m_direction;
}

void AutoTestSpeed::setDepthCountDown(int newDepthCountDown)
{
    if ( m_direction == newDepthCountDown )
        return;
    m_direction = newDepthCountDown;
    emit DepthCurrentChanged();
}

int AutoTestSpeed::DepthCurrent()
{
    return m_depthCount;
}

void AutoTestSpeed::setDepthCurrent(int newDepthCurrent)
{
    if ( m_depthCount == newDepthCurrent )
        return;
    m_depthCount = newDepthCurrent;
    emit DepthCurrentChanged();
}
