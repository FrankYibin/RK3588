#include "depthsetting.h"
#include <QtDebug>


DepthSetting* DepthSetting::_ptrDepth = nullptr;

DepthSetting *DepthSetting::GetInstance()
{
    if (!_ptrDepth) {
        _ptrDepth = new DepthSetting();
    }
    return _ptrDepth;

}

DepthSetting::DepthSetting(QObject *parent)
    : QObject{parent}
{
    m_DepthTargetLayer = "";
    m_depthOrientation = 0;
    m_DepthSurfaceCover = "";
    m_DepthEncoder = -1;
    m_velocityUnit = -1;
    int tmpVelocity = M_PER_HOUR;
    //get tmpVelocity from database
    setVelocityUnit(tmpVelocity);
    setDepthTargetLayer("99999.99");
    setDepthSurfaceCover("99999.99");
    setDepthEncoder(ENCODER_1);
}

QString DepthSetting::DepthTargetLayer() const
{
    return m_DepthTargetLayer;
}

void DepthSetting::setDepthTargetLayer(const QString value)
{
    if ( m_DepthTargetLayer == value)
        return;
    m_DepthTargetLayer = value;
    emit DepthTargetLayerChanged();
}

int DepthSetting::DepthOrientation() const
{
    return m_depthOrientation;
}

void DepthSetting::setDepthOrientation(const int orientation)
{
    if ( m_depthOrientation == orientation )
        return;
    m_depthOrientation = orientation;
    emit DepthOrientationChanged();
}

QString DepthSetting::DepthSurfaceCover() const
{
    return m_DepthSurfaceCover;
}


void DepthSetting::setDepthSurfaceCover(const QString value)
{
    if (m_DepthSurfaceCover == value)
        return;
    m_DepthSurfaceCover = value;
    emit DepthSurfaceCoverChanged();

}

int DepthSetting::DepthEncoder() const
{
    return m_DepthEncoder;
}

void DepthSetting::setDepthEncoder(const int value)
{
    if ( m_DepthEncoder == value )
        return;
    m_DepthEncoder = value;
    emit DepthEncoderChanged();

}

int DepthSetting::VelocityUnit() const
{
    return m_velocityUnit;

}

int DepthSetting::DistanceUnit() const
{
    return m_distanceUnit;
}

int DepthSetting::TimeUnit() const
{
    return m_timeUnit;
}

void DepthSetting::setVelocityUnit(const int velocityUnit)
{
    if (m_velocityUnit == velocityUnit)
        return;
    m_velocityUnit = velocityUnit;
    switch(m_velocityUnit)
    {
    case M_PER_HOUR:
        setTimeUnit(HOUR);
        setDistanceUnit(METER);
        break;
    case M_PER_MIN:
        setTimeUnit(MIN);
        setDistanceUnit(METER);
        break;
    case FT_PER_HOUR:
        setTimeUnit(HOUR);
        setDistanceUnit(FEET);
        break;
    case FT_PER_MIN:
        setTimeUnit(MIN);
        setDistanceUnit(FEET);
        break;
    default:
        m_velocityUnit = M_PER_HOUR;
        setTimeUnit(HOUR);
        setDistanceUnit(METER);
        break;
    }
    emit VelocityUnitChanged();
}

void DepthSetting::setDistanceUnit(const int distanceUnit)
{
    if(m_distanceUnit == distanceUnit)
        return;
    m_distanceUnit = distanceUnit;
    emit DistanceUnitChanged();
}

void DepthSetting::setTimeUnit(const int timeUnit)
{
    if(m_timeUnit == timeUnit)
        return;
    m_timeUnit = timeUnit;
    emit TimeUnitChanged();
}
QString DepthSetting::DepthCurrent() const
{
    return m_DepthCurrent;
}
void DepthSetting::setDepthCurrent(const QString value)
{
    if (m_DepthCurrent == value)
        return;
    m_DepthCurrent = value;
    emit DepthCurrentChanged();
}

QString DepthSetting::PulseCount() const
{
    return m_PulseCount;
}
void DepthSetting::setPulseCount(const QString value)
{
    if (m_PulseCount == value)
        return;
    m_PulseCount = value;
    emit PulseCountChanged();
}

QString DepthSetting::VelocityLimited() const
{
    return m_VelocityLimited;
}
void DepthSetting::setVelocityLimited(const QString value)
{
    if (m_VelocityLimited == value)
        return;
    m_VelocityLimited = value;
    emit VelocityLimitedChanged();
}




