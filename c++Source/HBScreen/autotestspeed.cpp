#include "autotestspeed.h"

AutoTestSpeed* AutoTestSpeed::_ptrAutoTestSpeed = nullptr;


AutoTestSpeed::AutoTestSpeed(QObject *parent)
    : QObject{parent}
{
    m_isDownCountStart = false;
}

AutoTestSpeed *AutoTestSpeed::GetInstance()
{
    if (!_ptrAutoTestSpeed) {
        _ptrAutoTestSpeed = new AutoTestSpeed();
    }
    return _ptrAutoTestSpeed;
}

int AutoTestSpeed::VelocityStatus() const
{
    return m_VelocityStatus;
}

void AutoTestSpeed::setVelocityStatus(const int status)
{
    if ( m_VelocityStatus == status )
        return;
    m_VelocityStatus = status;
    emit VelocityStatusChanged();
}
QString AutoTestSpeed::VelocitySetting() const
{
    return m_VelocitySetting;
}
void AutoTestSpeed::setVelocitySetting(QString velocity)
{
    if ( m_VelocitySetting == velocity )
        return;
    m_VelocitySetting = velocity;
    emit VelocitySettingChanged();
}

int AutoTestSpeed::EnableVelocityControl() const
{
    return m_EnableVelocityControl;
}

void AutoTestSpeed::setEnableVelocityControl(const int enable)
{
    if ( m_EnableVelocityControl == enable )
        return;
    m_EnableVelocityControl = enable;
    emit EnableVelocityControlChanged();
}

QString AutoTestSpeed::DepthDeviationSetting() const
{
    return m_DepthDeviationSetting;
}
void AutoTestSpeed::setDepthDeviationSetting(const QString deviation)
{
    if (m_DepthDeviationSetting == deviation)
        return;
    m_DepthDeviationSetting = deviation;
    m_isDownCountStart = false;
    emit DepthDeviationSettingChanged();
}
QString AutoTestSpeed::DepthDeviationCurrent() const
{
    return m_DepthDeviationCurrent;
}
void AutoTestSpeed::setDepthDeviationCurrent(const QString current)
{
    if (m_DepthDeviationCurrent == current)
        return;
    m_DepthDeviationCurrent = current;
    emit DepthDeviationChanged();
}

void AutoTestSpeed::startDepthDownCount()
{
    m_DepthBase = m_DepthCurrent;
    m_isDownCountStart = true;
}

QString AutoTestSpeed::DepthCurrent() const
{
    return m_DepthCurrent;
}

void AutoTestSpeed::setDepthCurrent(QString depth)
{
    QString str;
    if(m_DepthCurrent == depth )
        return;
    m_DepthCurrent = depth;
    if(m_isDownCountStart == true)
    {
        double delta = m_DepthCurrent.toDouble() - m_DepthBase.toDouble();
        str = QString::number(delta, 'f', 2); // 'f' for fixed-point, 2 decimal places
    }
    else
    {
        str = "0.00";
        setDepthDeviationCurrent(str);
    }
}

bool AutoTestSpeed::IsDownCountStart() const
{
    return m_isDownCountStart;
}
void AutoTestSpeed::setIsDownCountStart(const bool isStart)
{
    if (m_isDownCountStart == isStart)
        return;
    m_isDownCountStart = isStart;
    emit IsDownCountStartChanged();
}
