#include "depthsiman.h"
#include <QDebug>

DepthSiMan* DepthSiMan::_ptrDepthSiMan = nullptr;

DepthSiMan::DepthSiMan(QObject *parent)
    : QObject{parent}
{}

DepthSiMan *DepthSiMan::GetInstance()
{
    if (!_ptrDepthSiMan) {
        _ptrDepthSiMan = new DepthSiMan();
    }
    return _ptrDepthSiMan;
}
QString DepthSiMan::DistanceUpperWellSetting() const
{
    return m_DistanceUpperWellSetting;
}

void DepthSiMan::setDistanceUpperWellSetting(const QString setting)
{
    if ( m_DistanceUpperWellSetting == setting )
        return;
    m_DistanceUpperWellSetting = setting;
    emit DistanceUpperWellSettingChanged();
}

QString DepthSiMan::DistanceLowerWellSetting() const
{
    return m_DistanceLowerWellSetting;
}

void DepthSiMan::setDistanceLowerWellSetting(const QString setting)
{
    if ( m_DistanceLowerWellSetting == setting )
        return;
    m_DistanceLowerWellSetting = setting;
    emit DistanceLowerWellSettingChanged();
}

QString DepthSiMan::SlopeAngleWellSetting() const
{
    return m_SlopeAngleWellSetting;
}

void DepthSiMan::setSlopeAngleWellSetting(const QString setting)
{
    if ( m_SlopeAngleWellSetting == setting )
        return;
    m_SlopeAngleWellSetting = setting;
    emit SlopeAngleWellSettingChanged();
}

QString DepthSiMan::DepthStartSetting() const
{
    return m_DepthStartSetting;
}

void DepthSiMan::setDepthStartSetting(const QString setting)
{
    if ( m_DepthStartSetting == setting )
        return;
    m_DepthStartSetting = setting;
    emit DepthStartSettingChanged();
}

QString DepthSiMan::DepthFinishSetting() const
{
    return m_DepthFinishSetting;
}

void DepthSiMan::setDepthFinishSetting(const QString setting)
{
    if ( m_DepthFinishSetting == setting )
        return;
    m_DepthFinishSetting = setting;
    emit DepthFinishSettingChanged();
}


QString DepthSiMan::VelocitySiman() const
{
    return m_VelocitySiman;
}
void DepthSiMan::setVelocitySiman(const QString newTVelocitySiman)
{
    if ( m_VelocitySiman == newTVelocitySiman )
        return;
    m_VelocitySiman = newTVelocitySiman;
    emit VelocitySimanChanged();
}

int DepthSiMan::IndicateSimanAlert() const
{
    return m_IndicateSimanAlert;
}

void DepthSiMan::setIndicateSimanAlert(int indicateSimanAlert)
{
    if ( m_IndicateSimanAlert == indicateSimanAlert )
        return;
    m_IndicateSimanAlert = indicateSimanAlert;
    emit IndicateSimanAlertChanged();
}

int DepthSiMan::IndicateSimanStop() const
{
    return m_IndicateSimanStop;
}

void DepthSiMan::setIndicateSimanStop(int indicateSimanStop)
{
    if ( m_IndicateSimanStop == indicateSimanStop )
        return;
    m_IndicateSimanStop = indicateSimanStop;
    emit IndicateSimanStopChanged();
}




