#include "depth.h"
#include <QtDebug>


Depth* Depth::m_depth = nullptr;

Depth *Depth::getInstance()
{
    if (!m_depth) {
        m_depth = new Depth();
    }
    return m_depth;

}

Depth::Depth(QObject *parent)
    : QObject{parent}
{
    m_targetLayerDepth = 0;
    m_depthOrientation = 0;
    m_meterDepth = 0;
    m_depthCalculateType = 0;

    m_codeOption = 0;

    m_velocityUnit = -1;
    int tmpVelocity = M_PER_HOUR;
    //get tmpVelocity from database
    setVelocityUnit(tmpVelocity);
}

int Depth::TargetLayerDepth() const
{
    return m_targetLayerDepth;
}

void Depth::setTargetLayerDepth(int newTargetLayerDepth)
{
    if ( m_targetLayerDepth == newTargetLayerDepth )
        return;
    m_targetLayerDepth = newTargetLayerDepth;
    emit TargetLayerDepthChanged();
}

int Depth::DepthOrientation() const
{
    return m_depthOrientation;
}

void Depth::setDepthOrientation(int newDepthOrientation)
{
    if ( m_depthOrientation == newDepthOrientation )
        return;
    m_depthOrientation = newDepthOrientation;
    emit DepthOrientationChanged();
}

int Depth::MeterDepth() const
{

    return m_meterDepth;
}


void Depth::setMeterDepth(int newMeterDepth)
{
    if ( m_meterDepth == newMeterDepth )
        return;
    m_meterDepth = newMeterDepth;
    emit MeterDepthChanged();

}

int Depth::DepthCalculateType() const
{
    return m_depthCalculateType;
}

void Depth::setDepthCalculateType(int newDepthCalculateType)
{
    if ( m_depthCalculateType == newDepthCalculateType )
        return;
    m_depthCalculateType = newDepthCalculateType;
    emit DepthCalculateTypeChanged();

}

int Depth::VelocityUnit() const
{
    return m_velocityUnit;

}

int Depth::DistanceUnit() const
{
    return m_distanceUnit;
}

int Depth::TimeUnit() const
{
    return m_timeUnit;
}

void Depth::setVelocityUnit(const int velocityUnit)
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
    case FT_HOUR:
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

void Depth::setDistanceUnit(const int distanceUnit)
{
    if(m_distanceUnit == distanceUnit)
        return;
    m_distanceUnit = distanceUnit;
    emit DistanceUnitChanged();
}

void Depth::setTimeUnit(const int timeUnit)
{
    if(m_timeUnit == timeUnit)
        return;
    m_timeUnit = timeUnit;
    emit TimeUnitChanged();
}

int Depth::CodeOption() const
{

    return m_codeOption;
}

void Depth::setCodeOption(int newTCodeOption)
{
    qDebug() << "Set CodeOption called. New value:" << newTCodeOption;

    if ( m_codeOption == newTCodeOption )
        return;
    m_codeOption = newTCodeOption;
    emit CodeOptionChanged();
}



