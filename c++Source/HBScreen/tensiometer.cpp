#include "tensiometer.h"

Tensiometer* Tensiometer::m_tensiometer = nullptr;

Tensiometer::Tensiometer(QObject *parent)
    : QObject{parent}
{}

Tensiometer *Tensiometer::getInstance()
{
    if (!m_tensiometer) {
        m_tensiometer = new Tensiometer();
    }
    return m_tensiometer;

}

QString Tensiometer::TensiometerNumber() const
{
    return m_tensiometerNumber;
}

int Tensiometer::TensiometerType() const
{
    return m_tensiometerType;
}

int Tensiometer::TensiometerRange() const
{
    return m_tensiometerRange;
}

int Tensiometer::TensionSignal() const
{
    return m_tensionSignal;
}

void Tensiometer::setTensiometerNumber(const QString &number)
{
    if (m_tensiometerNumber != number) {
        m_tensiometerNumber = number;
        emit TensiometerNumberChanged();
    }
}

void Tensiometer::setTensiometerType(int type)
{
    if (m_tensiometerType != type) {
        m_tensiometerType = type;
        emit TensiometerTypeChanged();
    }
}

void Tensiometer::setTensiometerRange(int range)
{
    if (m_tensiometerRange != range) {
        m_tensiometerRange = range;
        emit TensiometerRangeChanged();
    }
}

void Tensiometer::setTensionSignal(int signal)
{
    if (m_tensionSignal != signal) {
        m_tensionSignal = signal;
        emit TensionSignalChanged();
    }
}

int Tensiometer::TensionUnit() const
{
    return m_tensiometerType;
}

void Tensiometer::setTensionUnit(int tensionUnit)
{
    if (m_tensionUnit != tensionUnit) {
        m_tensionUnit = tensionUnit;
        emit TensionUnitChanged();
    }
}
