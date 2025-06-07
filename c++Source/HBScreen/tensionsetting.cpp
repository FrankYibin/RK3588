#include "tensionsetting.h"
#include <QDebug>
TensionSetting* TensionSetting::_ptrTensionSetting = nullptr;
TensionSetting *TensionSetting::GetInstance()
{
    if (!_ptrTensionSetting)
    {
        _ptrTensionSetting = new TensionSetting();
    }
    return _ptrTensionSetting;

}

TensionSetting::~TensionSetting()
{
    delete _ptrTensionSetting;
    _ptrTensionSetting = nullptr;
}

TensionSetting::TensionSetting(QObject *parent)
    : QObject{parent}
{
    m_TensionUnit = -1;
    setTensionUnit(LB);
}

int TensionSetting::TensionUnit() const
{
    return m_TensionUnit;
}

void TensionSetting::setTensionUnit(const int unit)
{
    if (m_TensionUnit != unit)
    {
        m_TensionUnit = unit;
        qDebug() << "C++ emit tensionUnitChanged, new value:" << m_TensionUnit;
        emit TensionUnitChanged();
    }
}
QString TensionSetting::KValue() const
{
    return m_KValue;
}
void TensionSetting::setKValue(const QString &value)
{
    if (m_KValue != value)
    {
        m_KValue = value;
        emit KValueChanged();
    }
}

QString TensionSetting::TensionLimited() const
{
    return m_TensionLimited;
}
void TensionSetting::setTensionLimited(const QString &value)
{
    if (m_TensionLimited != value)
    {
        m_TensionLimited = value;
        emit TensionLimitedChanged();
    }
}

QString TensionSetting::TensionLimitedDelta() const
{
    return m_TensionLimitedDelta;
}
void TensionSetting::setTensionLimitedDelta(const QString &value)
{
    if (m_TensionLimitedDelta != value)
    {
        m_TensionLimitedDelta = value;
        emit TensionLimitedDeltaChanged();
    }
}
