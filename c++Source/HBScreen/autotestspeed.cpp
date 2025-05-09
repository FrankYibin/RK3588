#include "autotestspeed.h"

AutoTestSpeed::AutoTestSpeed(QObject *parent)
    : QObject{parent}
{}

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
