#include "tensiometer.h"

Tensiometer* Tensiometer::m_tensiometer = nullptr;

Tensiometer::Tensiometer(QObject *parent)
    : QObject{parent},m_tensiometerNumber("2512001"),
    m_tensiometerType(0),
    m_tensiometerRange(0),
    m_tensiometerSignal(0),
    m_tensionUnits(0)
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

int Tensiometer::TensiometerSignal() const
{
    return m_tensiometerSignal;
}

void Tensiometer::setTensiometerNumber(const QString &number)
{
    if (m_tensiometerNumber != number) {
        m_tensiometerNumber = number;
        emit TensiometerNumberChanged();
    }
}

void Tensiometer::setTensiometerType(int newTensiometerType)
{
    if (m_tensiometerType != newTensiometerType) {
        m_tensiometerType = newTensiometerType;
        emit TensiometerTypeChanged();
    }
}

void Tensiometer::setTensiometerRange(int newTensiometerRange)
{
    if (m_tensiometerRange != newTensiometerRange) {
        m_tensiometerRange = newTensiometerRange;
        emit TensiometerRangeChanged();
    }
}

void Tensiometer::setTensiometerSignal(int newTensiometerSignal)
{
    if (m_tensiometerSignal != newTensiometerSignal) {
        m_tensiometerSignal = newTensiometerSignal;
        emit TensiometerSignalChanged();
    }
}

int Tensiometer::TensionUnits() const
{
    return m_tensionUnits;
}

void Tensiometer::setTensionUnits(int newTensionUnits)
{
    if (m_tensionUnits != newTensionUnits) {
        m_tensionUnits = newTensionUnits;
        emit TensionUnitsChanged();
    }
}
