#include "autotestspeed.h"
#include "depthsetting.h"
#include "../HBUtility/hbutilityclass.h"
#include "../HBVoice/hbvoice.h"
#include <QDebug>

AutoTestSpeed* AutoTestSpeed::_ptrAutoTestSpeed = nullptr;
int AutoTestSpeed::timeout = 0;

AutoTestSpeed::AutoTestSpeed(QObject *parent)
    : QObject{parent}
{
    m_isDownCountStart = false;
    m_RawDeviationSetting = 0;
    connect(DepthSetting::GetInstance(), &DepthSetting::DistanceUnitChanged,
            this, &AutoTestSpeed::onDistanceUnitChanged);
}

void AutoTestSpeed::onDistanceUnitChanged()
{
    QString strDeviation = "";
    switch (DepthSetting::GetInstance()->DistanceUnit())
    {
    case DepthSetting::FEET:
        strDeviation = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET, m_RawDeviationSetting);
        break;
    case DepthSetting::METER:
        strDeviation = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, m_RawDeviationSetting);
        break;
    default:
        strDeviation = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET, m_RawDeviationSetting);
        break;
    }
    setDepthDeviationSetting(strDeviation);
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
    switch (DepthSetting::GetInstance()->DistanceUnit())
    {
    case DepthSetting::FEET:
        m_RawDeviationSetting = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2FEET, deviation);
        break;
    case DepthSetting::METER:
        m_RawDeviationSetting = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2METER, deviation);
        break;
    default:
        m_RawDeviationSetting = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2FEET, deviation);
        break;
    }
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
    int tmp = m_RawDepthCurrent + m_RawDeviationSetting;
    m_RawDepthBase = tmp;
    m_isDownCountStart = true;
    timeout = 0;
}

int AutoTestSpeed::DepthCurrent() const
{
    return m_RawDepthCurrent;
}

void AutoTestSpeed::setDepthCurrent(int depth)
{
    m_RawDepthCurrent = depth;
    QString str = "";
    int delta = 0;
    if(m_isDownCountStart == true)
    {
        delta = m_RawDepthBase - m_RawDepthCurrent;
        if(timeout == MAX_TIMEOUT)
            timeout = OFF;
        else if(timeout > 0)
            timeout++;
        else
        {
            if(delta <= 0)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_0);
                timeout = MAX_TIMEOUT;
            }
            else if(delta < 10)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_1);
                timeout = ON;
            }
            else if(delta < 20)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_2);
                timeout = ON;
            }
            else if(delta < 30)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_3);
                timeout = ON;
            }
            else if(delta < 40)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_4);
                timeout = ON;
            }
            else if(delta < 50)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_5);
                timeout = ON;
            }
            else if(delta < 60)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_6);
                timeout = ON;
            }
            else if(delta < 70)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_7);
                timeout = ON;
            }
            else if(delta < 80)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_8);
                timeout = ON;
            }
            else if(delta < 90)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_0_9);
                timeout = ON;
            }
            else if(delta < 100)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_0);
                timeout = ON;
            }
            else if(delta < 110)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_1);
                timeout = ON;
            }
            else if(delta < 120)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_2);
                timeout = ON;
            }
            else if(delta < 130)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_3);
                timeout = ON;
            }
            else if(delta < 140)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_4);
                timeout = ON;
            }
            else if(delta < 150)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_5);
                timeout = ON;
            }
            else if(delta < 160)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_6);
                timeout = ON;
            }
            else if(delta < 170)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_7);
                timeout = ON;
            }
            else if(delta < 180)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_8);
                timeout = ON;
            }
            else if(delta < 190)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_1_9);
                timeout = ON;
            }
            else if(delta < 200)
            {
                HBVoice::GetInstance()->PlayVoice(HBVoice::METER_2_0);
                timeout = ON;
            }
            else
            {

            }
        }
    }

    switch (DepthSetting::GetInstance()->DistanceUnit())
    {
    case DepthSetting::FEET:
        str = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET, delta);
        break;
    case DepthSetting::METER:
        str = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, delta);
        break;
    default:
        str = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET, delta);
        break;
    }
    setDepthDeviationCurrent(str);
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
