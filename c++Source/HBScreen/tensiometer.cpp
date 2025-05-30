#include "tensiometer.h"
#include <QDebug>

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
         qDebug() << "C++ emit tensionUnitsChanged, new value:" << m_tensionUnits;
        emit tensionUnitsChanged();
    }
}

int Tensiometer::Scale1() const
{
 return m_scale1;
}

void Tensiometer::setScale1(int newScale1)
{
    if (m_scale1 != newScale1) {
        m_scale1 = newScale1;
        emit Scale1Changed();
    }
}

int Tensiometer::Scale2() const
{
 return m_scale2;
}

void Tensiometer::setScale2(int newScale2)
{    if (m_scale2 != newScale2) {
        m_scale2 = newScale2;
        emit Scale2Changed();
    }

}
int Tensiometer::Scale3() const
{
 return m_scale3;
}

void Tensiometer::setScale3(int newScale3)
{  if (m_scale3 != newScale3) {
        m_scale3 = newScale3;
        emit Scale3Changed();
    }


}
int Tensiometer::Scale4() const
{
 return m_scale4;
}

void Tensiometer::setScale4(int newScale4)
{  if (m_scale4 != newScale4) {
        m_scale4 = newScale4;
        emit Scale4Changed();
    }


}
int Tensiometer::Scale5() const
{
 return m_scale5;
}

void Tensiometer::setScale5(int newScale5)
{ if (m_scale5 != newScale5) {
        m_scale5 = newScale5;
        emit Scale5Changed();
    }

}
