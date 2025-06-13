#include "tensiometer.h"
#include <QDebug>
Tensiometer* Tensiometer::_ptrTensiometer = nullptr;

Tensiometer::Tensiometer(QObject *parent)
    : QObject{parent}
{
    m_TensiometerNumber = "";
    m_TensiometerEncoder = -1; // 0: Tensiometer, 1: Encoder
    m_TensiometerRange = -1; // 0: 0-1000N, 1: 0-2000N, 2: 0-5000N
    m_TensiometerAnalog = -1; // 0: Analog, 1: Digital
    m_Point1Scale = "";
    m_Point2Scale = "";
    m_Point3Scale = "";
    m_Point4Scale = "";
    m_Point5Scale = "";
    m_Point1Tension = "";
    m_Point2Tension = "";
    m_Point3Tension = "";
    m_Point4Tension = "";
    m_Point5Tension = "";

    setTensiometerNumber("2512001");
    setTensiometerEncoder(0); // Default to Tensiometer
    setTensiometerRange(0); // Default to 0-1000N
    setTensiometerAnalog(0); // Default to Analog
    setPoint1Scale("10.00");
    setPoint2Scale("20.00");
    setPoint3Scale("30.00");
    setPoint4Scale("40.00");
    setPoint5Scale("50.00");
    setPoint1Tension("0.50");
    setPoint2Tension("1.00");
    setPoint3Tension("1.50");
    setPoint4Tension("2.00");
    setPoint5Tension("2.50");
}

Tensiometer *Tensiometer::GetInstance()
{
    if (!_ptrTensiometer)
    {
        _ptrTensiometer = new Tensiometer();
    }
    return _ptrTensiometer;

}

QString Tensiometer::TensiometerNumber() const
{
    return m_TensiometerNumber;
}

int Tensiometer::TensiometerEncoder() const
{
    return m_TensiometerEncoder;
}

int Tensiometer::TensiometerRange() const
{
    return m_TensiometerRange;
}

int Tensiometer::TensiometerAnalog() const
{
    return m_TensiometerAnalog;
}

void Tensiometer::setTensiometerNumber(const QString number)
{
    if (m_TensiometerNumber != number) 
    {
        m_TensiometerNumber = number;
        emit TensiometerNumberChanged();
    }
}

void Tensiometer::setTensiometerEncoder(int encoder)
{
    if (m_TensiometerEncoder != encoder) 
    {
        m_TensiometerEncoder = encoder;
        emit TensiometerEncoderChanged();
    }
}

void Tensiometer::setTensiometerRange(int range)
{
    if (m_TensiometerRange != range) 
    {
        m_TensiometerRange = range;
        emit TensiometerRangeChanged();
    }
}

void Tensiometer::setTensiometerAnalog(int analog)
{
    if (m_TensiometerAnalog != analog)
    {
        m_TensiometerAnalog = analog;
        emit TensiometerAnalogChanged();
    }
}

QString Tensiometer::ScaleCurrent() const
{
    return m_ScaleCurrent;
}

void Tensiometer::setScaleCurrent(const QString scale)
{
    if (m_ScaleCurrent != scale) 
    {
        m_ScaleCurrent = scale;
        emit ScaleCurrentChanged();
    }
}

QString Tensiometer::Point1Scale() const
{
    return m_Point1Scale;
}

void Tensiometer::setPoint1Scale(const QString scale)
{
    if (m_Point1Scale != scale) 
    {
        m_Point1Scale = scale;
        emit Point1ScaleChanged();
    }
}

QString Tensiometer::Point2Scale() const
{
    return m_Point2Scale;
}

void Tensiometer::setPoint2Scale(const QString scale)
{
    if (m_Point2Scale != scale) 
    {
        m_Point2Scale = scale;
        emit Point2ScaleChanged();
    }
}

QString Tensiometer::Point3Scale() const
{
    return m_Point3Scale;
}

void Tensiometer::setPoint3Scale(const QString scale)
{
    if (m_Point3Scale != scale) 
    {
        m_Point3Scale = scale;
        emit Point3ScaleChanged();
    }
}

QString Tensiometer::Point4Scale() const
{
    return m_Point4Scale;
}

void Tensiometer::setPoint4Scale(const QString scale)
{
    if (m_Point4Scale != scale) 
    {
        m_Point4Scale = scale;
        emit Point4ScaleChanged();
    }
}

QString Tensiometer::Point5Scale() const
{
    return m_Point5Scale;
}

void Tensiometer::setPoint5Scale(const QString scale)
{
    if (m_Point5Scale != scale) 
    {
        m_Point5Scale = scale;
        emit Point5ScaleChanged();
    }
}

QString Tensiometer::Point1Tension() const
{
    return m_Point1Tension;
}

void Tensiometer::setPoint1Tension(const QString tension)
{
    if (m_Point1Tension != tension) 
    {
        m_Point1Tension = tension;
        emit Point1TensionChanged();
    }
}

QString Tensiometer::Point2Tension() const
{
    return m_Point2Tension;
}

void Tensiometer::setPoint2Tension(const QString tension)
{
    if (m_Point2Tension != tension) 
    {
        m_Point2Tension = tension;
        emit Point2TensionChanged();
    }
}

QString Tensiometer::Point3Tension() const
{
    return m_Point3Tension;
}

void Tensiometer::setPoint3Tension(const QString tension)
{
    if (m_Point3Tension != tension) 
    {
        m_Point3Tension = tension;
        emit Point3TensionChanged();
    }
}

QString Tensiometer::Point4Tension() const
{
    return m_Point4Tension;
}

void Tensiometer::setPoint4Tension(const QString tension)
{
    if (m_Point4Tension != tension) 
    {
        m_Point4Tension = tension;
        emit Point4TensionChanged();
    }
}

QString Tensiometer::Point5Tension() const
{
    return m_Point5Tension;
}

void Tensiometer::setPoint5Tension(const QString tension)
{
    if (m_Point5Tension != tension) 
    {
        m_Point5Tension = tension;
        emit Point5TensionChanged();
    }
}
