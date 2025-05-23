#include "depthmeter.h"
DepthMeter* DepthMeter::m_depthMeter = nullptr;


DepthMeter::DepthMeter(QObject *parent)
    : QObject{parent}
{}

DepthMeter *DepthMeter::getInstance()
{
    if (!m_depthMeter) {
        m_depthMeter = new DepthMeter();
    }
    return m_depthMeter;

}

int DepthMeter::DepthPreset() const
{
    return m_depthPreset;
}

void DepthMeter::setDepthPreset(int newDepthPreset)
{
    if (m_depthPreset != newDepthPreset) {
        m_depthPreset = newDepthPreset;
        emit DepthPresetChanged();
    }

}

int DepthMeter::CurrentDepth() const
{
    return m_currentDepth;
}

void DepthMeter::setCurrentDepth(int newCurrentDepth)
{

    if(m_currentDepth != newCurrentDepth){
        m_currentDepth = newCurrentDepth;
        emit CurrentDepthChanged();
    }
}

