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
    m_DepthTargetLayer = "";
    m_depthOrientation = 0;
    m_DepthSurfaceCover = "";
    m_DepthEncoder = -1;

    m_codeOption = 0;

    m_velocityUnit = -1;
    int tmpVelocity = M_PER_HOUR;
    //get tmpVelocity from database
    setVelocityUnit(tmpVelocity);
    setDepthTargetLayer("99999.99");
    setDepthSurfaceCover("99999.99");
    setDepthEncoder(ENCODER_1);
}

QString Depth::DepthTargetLayer() const
{
    return m_DepthTargetLayer;
}

void Depth::setDepthTargetLayer(const QString value)
{
    if ( m_DepthTargetLayer == value)
        return;
    m_DepthTargetLayer = value;
    emit DepthTargetLayerChanged();
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

QString Depth::DepthSurfaceCover() const
{
    return m_DepthSurfaceCover;
}


void Depth::setDepthSurfaceCover(const QString value)
{
    if (m_DepthSurfaceCover == value)
        return;
    m_DepthSurfaceCover = value;
    emit DepthSurfaceCoverChanged();

}

int Depth::DepthEncoder() const
{
    return m_DepthEncoder;
}

void Depth::setDepthEncoder(const int value)
{
    if ( m_DepthEncoder == value )
        return;
    m_DepthEncoder = value;
    emit DepthEncoderChanged();

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



