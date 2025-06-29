#include "hbhome.h"
#include "tensiometer.h"
#include <QDebug>
HBHome* HBHome::_ptrHome = nullptr;

HBHome::HBHome(QObject *parent)
    : QObject{parent}
{
    setStatusNetwork(1);
}

HBHome *HBHome::GetInstance()
{
    if (!_ptrHome)
    {
        _ptrHome = new HBHome();
    }
    return _ptrHome;

}

QString HBHome::DepthCurrent() const
{
    return m_DepthCurrent;
}

void HBHome::setDepthCurrent(const QString value)
{
    if(m_DepthCurrent == value)
        return;
    m_DepthCurrent = value;
    emit DepthCurrentChanged();

}

QString HBHome::VelocityCurrent() const
{
    return m_VelocityCurrent;
}

void HBHome::setVelocityCurrent(const QString value)
{
    if(m_VelocityCurrent == value)
        return;
    m_VelocityCurrent = value;
    emit VelocityCurrentChanged();

}

QString HBHome::TensionCurrent() const
{
    return m_TensionCurrent;
}

void HBHome::setTensionCurrent(const QString value)
{
    if(m_TensionCurrent == value)
        return;
    m_TensionCurrent = value;
    emit TensionCurrentChanged();

}

QString HBHome::TensionCurrentDelta() const
{
    return m_TensionCurrentDelta;
}

void HBHome::setTensionCurrentDelta(const QString value)
{
    if(m_TensionCurrentDelta == value)
        return;
    m_TensionCurrentDelta = value;
    emit TensionCurrentDeltaChanged();
}

QString HBHome::PulseCount() const
{
    return m_PulseCount;
}

void HBHome::setPulseCount(const QString value)
{
    if(m_PulseCount == value)
        return;
    m_PulseCount = value;
    emit PulseCountChanged();

}

QString HBHome::TensionLimited() const
{
    return m_TensionLimited;
}

void HBHome::setTensionLimited(const QString value)
{
    if(m_TensionLimited == value)
        return;
    m_TensionLimited = value;
    emit TensionLimitedChanged();
}

QString HBHome::DepthTargetLayer() const
{
    return m_DepthTargetLayer;
}

void HBHome::setDepthTargetLayer(const QString value)
{
    if(m_DepthTargetLayer == value)
        return;
    m_DepthTargetLayer = value;
    emit DepthTargetLayerChanged();
}

QString HBHome::VelocityLimited() const
{
    return m_VelocityLimited;
}

void HBHome::setVelocityLimited(const QString value)
{
    if(m_VelocityLimited == value)
        return;
    m_VelocityLimited = value;
    emit VelocityLimitedChanged();
}

QString HBHome::TensionLimitedDelta() const
{
    return m_TensionLimitedDelta;
}

void HBHome::setTensionLimitedDelta(const QString value)
{
    if(m_TensionLimitedDelta == value)
        return;
    m_TensionLimitedDelta = value;
    emit TensionLimitedDeltaChanged();
}

QString HBHome::KValue() const
{
    return m_KValue;
}

void HBHome::setKValue(const QString value)
{
    if(m_KValue == value)
        return;
    m_KValue = value;
    emit KValueChanged();
}

QString HBHome::TensionCableHead() const
{
    return m_TensionCableHead;
}

void HBHome::setTensionCableHead(const QString value)
{
    if(m_TensionCableHead == value)
        return;
    m_TensionCableHead = value;
    emit TensionCableHeadChanged();
}

int HBHome::StatusLimitedPara() const
{
    return m_StatusLimitedPara;
}

void HBHome::setStatusLimitedPara(const int status)
{
    if(m_StatusLimitedPara == status)
        return;
    m_StatusLimitedPara = status;
    emit StatusLimitedParaChanged();

}

int HBHome::StatusNetwork() const
{
    return m_StatusNetwork;
}

void HBHome::setStatusNetwork(const int status)
{
    if(m_StatusNetwork == status)
        return;
    m_StatusNetwork = status;
    emit StatusNetworkChanged();

}

QString HBHome::TensiometerNumber() const
{
    return m_TensiometerNumber;
}
void HBHome::setTensiometerNumber(const QString value)
{
    if(m_TensiometerNumber == value)
        return;
    m_TensiometerNumber = value;
    emit tensiometerNumberChanged();
}
QString HBHome::TensionEncoder() const
{
    return m_TensionEncoder;
}
void HBHome::setTensionEncoder(const QString value)
{
    if(m_TensionEncoder == value)
        return;
    m_TensionEncoder = value;
    emit TensionEncoderChanged();
}

void HBHome::setTensionEncoder(const int value)
{
    switch(value)
    {
    case Tensiometer::WIRE:
        setTensionEncoder(tr("数字有线"));
        break;
    case Tensiometer::WIRELESS:
        setTensionEncoder(tr("数字无线"));
        break;
    case Tensiometer::ANALOG_WIRE:
        setTensionEncoder(tr("模拟有线"));
        break;
    case Tensiometer::ANALOG_WIRELESS:
        setTensionEncoder(tr("模拟无线"));
        break;
    default:
        setTensionEncoder(tr("有线"));
        break;
    }
}

QString HBHome::StatusTensiometerOnline() const
{
    return m_StatusTensiometerOnline;
}

bool HBHome::isTensiometerOnline() const
{
    return m_isTensiometerOnline;
}
void HBHome::setStatusTensiometerOnline(const QString status)
{
    if(m_StatusTensiometerOnline == status)
        return;
    m_StatusTensiometerOnline = status;
    emit StatusTensiometerOnlineChanged();
}

void HBHome::setStatusTensiometerOnline(const int status)
{
    if(status == 0)
    {
        setStatusTensiometerOnline(tr("离线"));
        m_isTensiometerOnline = false;
    }
    else
    {
        setStatusTensiometerOnline(tr("在线"));
        m_isTensiometerOnline = true;
    }
}





