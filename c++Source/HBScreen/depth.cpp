#include "depth.h"
#include <QtDebug>


Depth* Depth::m_depth = nullptr;

Depth *Depth::getInstance()
{
    if (!m_depth) {
        m_depth = new Depth();
    }
    return m_depth;

}

Depth::Depth(QObject *parent)
    : QObject{parent}
{}

int Depth::TargetLayerDepth() const
{
    return m_targetLayerDepth;
}

void Depth::setTargetLayerDepth(int newTargetLayerDepth)
{
    if ( m_targetLayerDepth == newTargetLayerDepth )
        return;
    m_targetLayerDepth = newTargetLayerDepth;
    emit TargetLayerDepthChanged();
}

int Depth::DepthOrientation() const
{
    return m_depthOrientation;
}

void Depth::setDepthOrientation(int newDepthOrientation)
{
    if ( m_depthOrientation == newDepthOrientation )
        return;
    m_depthOrientation = newDepthOrientation;
    emit DepthOrientationChanged();
}

int Depth::MeterDepth() const
{

    return m_meterDepth;
}


void Depth::setMeterDepth(int newMeterDepth)
{
    if ( m_meterDepth == newMeterDepth )
        return;
    m_meterDepth = newMeterDepth;
    emit MeterDepthChanged();

}

int Depth::DepthCalculateType() const
{
    return m_depthCalculateType;
}

void Depth::setDepthCalculateType(int newDepthCalculateType)
{
    if ( m_depthCalculateType == newDepthCalculateType )
        return;
    m_depthCalculateType = newDepthCalculateType;
    emit DepthCalculateTypeChanged();

}

int Depth::VelocityUnit() const
{
    return m_velocityUnit;

}

void Depth::setVelocityUnit(int newTVelocityUnit)
{
    if ( m_velocityUnit == newTVelocityUnit )
        return;
    m_velocityUnit = newTVelocityUnit;
      qDebug() << "C++ emit velocityUnitChanged, new value:" << m_velocityUnit;
    emit velocityUnitChanged();
}

int Depth::CodeOption() const
{

    return m_codeOption;
}

void Depth::setCodeOption(int newTCodeOption)
{
    qDebug() << "Set CodeOption called. New value:" << newTCodeOption;

    if ( m_codeOption == newTCodeOption )
        return;
    m_codeOption = newTCodeOption;
    emit CodeOptionChanged();
}



