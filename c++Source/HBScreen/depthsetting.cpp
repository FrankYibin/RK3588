#include "depthsetting.h"
#include "../HBModbus/hbmodbusclient.h"
#include "../HBQmlEnum.h"
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
//    int tmpVelocity = M_PER_HOUR;
    //get tmpVelocity from database
//    setVelocityUnit(tmpVelocity);
    setDepthTargetLayer("99999.99");
    setDepthSurfaceCover("99999.99");
    setDepthEncoder(ENCODER_1);
}

QString DepthSetting::CalculateOriginalPulse(const QString circumference, const QString pulseCount)
{
    double f_circumference = circumference.toDouble();
    int i_count = pulseCount.toInt();
    int pulse = 0;
    if(f_circumference > 0)
        pulse = i_count / f_circumference;
    QString strPulse = QString::number(pulse);
    return strPulse;
}

QString DepthSetting::CalculateNewPulse(const QString measuredDepth, const QString actualDepth)
{
    double f_measuredDepth = measuredDepth.toDouble();
    double f_actualDepth = actualDepth.toDouble();
    int i_originalPulse = m_PulsePerMeter.toInt();
    int pulse = 0;
    if(f_actualDepth > 0)
        pulse = f_measuredDepth * i_originalPulse / f_actualDepth;
    QString strPulse = QString::number(pulse);
    return strPulse;
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

//    HBUtilityClass::GetInstance()->settings().setValue("Unit/VelocityUnit", m_velocityUnit);
    emit VelocityUnitChanged(velocityUnit);
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

QString DepthSetting::WheelCircumference() const
{
    return m_WheelCircumference;
}
void DepthSetting::setWheelCircumference(const QString value)
{
    if (m_WheelCircumference == value)
        return;
    m_WheelCircumference = value;
    emit WheelCircumferenceChanged(value);
    QString strPulse = CalculateOriginalPulse(m_WheelCircumference, m_EncoderPulseCount);
    setPulsePerMeter(strPulse);
}

QString DepthSetting::EncoderPulseCount() const
{
    return m_EncoderPulseCount;
}
void DepthSetting::setEncoderPulseCount(const QString value)
{
    if (m_EncoderPulseCount == value)
        return;
    m_EncoderPulseCount = value;
    emit EncoderPulseCountChanged(value);
    QString strPulse = CalculateOriginalPulse(m_WheelCircumference, m_EncoderPulseCount);
    setPulsePerMeter(strPulse);
}

QString DepthSetting::MeasuredWellDepth() const
{
    return m_MeasuredWellDepth;
}
void DepthSetting::setMeasuredWellDepth(const QString value)
{
    if (m_MeasuredWellDepth == value)
        return;
    m_MeasuredWellDepth = value;
    emit MeasuredWellDepthChanged(value);
    QString strPulse = CalculateNewPulse(m_MeasuredWellDepth, m_ActualWellDepth);
    setCorrectedPulseCount(strPulse);
}

QString DepthSetting::ActualWellDepth() const
{
    return m_ActualWellDepth;
}
void DepthSetting::setActualWellDepth(const QString value)
{
    if (m_ActualWellDepth == value)
        return;
    m_ActualWellDepth = value;
    emit ActualWellDepthChanged(value);
    QString strPulse = CalculateNewPulse(m_MeasuredWellDepth, m_ActualWellDepth);
    setCorrectedPulseCount(strPulse);
}

QString DepthSetting::CorrectedPulseCount() const
{
    return m_CorrectedPulseCount;
}
void DepthSetting::setCorrectedPulseCount(const QString value)
{
    if (m_CorrectedPulseCount == value)
        return;
    m_CorrectedPulseCount = value;
    emit CorrectedPulseCountChanged();
    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::PULSE_COUNT, m_CorrectedPulseCount);
}

QString DepthSetting::PulsePerMeter() const
{
    return m_PulsePerMeter;
}
void DepthSetting::setPulsePerMeter(const QString value)
{
    if (m_PulsePerMeter == value)
        return;
    m_PulsePerMeter = value;
    emit PulsePerMeterChanged();
    QString strPulse = CalculateNewPulse(m_MeasuredWellDepth, m_ActualWellDepth);
    setCorrectedPulseCount(strPulse);
}
