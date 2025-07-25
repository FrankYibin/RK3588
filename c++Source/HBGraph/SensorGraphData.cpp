﻿#include "SensorGraphData.h"
#include <QRandomGenerator>
#include "c++Source/HBData/hbdatabase.h"
#include "c++Source/HBGraph/GraphAxisDefineHB.h"
#include "c++Source/HBUtility/hbutilityclass.h"
#include <QList>
#include <QDateTime>


SensorGraphData* SensorGraphData::m_objInstance = nullptr;

SensorGraphData *SensorGraphData::GetInstance()
{
    if (!m_objInstance) {
        m_objInstance = new SensorGraphData();
    }
    return m_objInstance;

}

SensorGraphData::SensorGraphData(QObject *parent) : QObject{parent}
{

}


SensorGraphData::~SensorGraphData()
{
    if(m_objInstance != nullptr)
    {
        delete m_objInstance;
        m_objInstance = nullptr;
    }
}

void SensorGraphData::loadSensorGraphPoint(const QDateTime &start, const QDateTime &end)
{
    clearGraph();
    HBDatabase &db = HBDatabase::GetInstance();

    QList<qreal> axisMinValues;
    QList<qreal> axisMaxValues;
    if(db.LoadGraphPoints(start, end, m_TimeRealPoints, m_DepthRealPoints,
                           m_VelocityRealPoints, m_TensionRealPoints, m_TensionDeltaRealPoints) == true)
    {
        for(int i = HBGraphAxisEnum::DEPTH_IDX; i < HBGraphAxisEnum::TOTAL_IDX; i++)
        {
            axisMinValues.append(0);
            axisMaxValues.append(99999.99);
        }

        for(int i = HBGraphAxisEnum::DEPTH_IDX; i < HBGraphAxisEnum::TOTAL_IDX; i++)
        {
            axisMinValues.replace(i - HBGraphAxisEnum::DEPTH_IDX, 99999.99);
            axisMaxValues.replace(i - HBGraphAxisEnum::DEPTH_IDX, 0);
        }

        for(int i = 0; i < m_TimeRealPoints.size(); i++)
        {
            HBUtilityClass::GetInstance()->CalculateLargest(axisMaxValues[0],              m_DepthRealPoints[i]);
            HBUtilityClass::GetInstance()->CalculateLargest(axisMaxValues[1],           m_VelocityRealPoints[i]);
            HBUtilityClass::GetInstance()->CalculateLargest(axisMaxValues[2],           m_TensionRealPoints[i]);
            HBUtilityClass::GetInstance()->CalculateLargest(axisMaxValues[3],  m_TensionDeltaRealPoints[i]);

            HBUtilityClass::GetInstance()->CalculateSmallest(axisMinValues[0],             m_DepthRealPoints[i]);
            HBUtilityClass::GetInstance()->CalculateSmallest(axisMinValues[1],          m_VelocityRealPoints[i]);
            HBUtilityClass::GetInstance()->CalculateSmallest(axisMinValues[2],          m_TensionRealPoints[i]);
            HBUtilityClass::GetInstance()->CalculateSmallest(axisMinValues[3], m_TensionDeltaRealPoints[i]);
        }

        setAxisMaxParameters(axisMaxValues);
        setAxisMinParameters(axisMinValues);
    }
    emit isDataReady();
}

void SensorGraphData::exportData()
{

}

QVariantList SensorGraphData::getDateTimes() const
{
    QVariantList list;
    for (const QDateTime &dt : m_TimeRealPoints)
    {
        list.append(dt);
    }
    return list;
}

QVariantList SensorGraphData::getDepths() const
{
    QVariantList list;
    for (const qreal &dt : m_DepthRealPoints)
    {
        list.append(dt);
    }
    return list;
}

QVariantList SensorGraphData::getVelocitys() const
{
    QVariantList list;
    for (const qreal &dt : m_VelocityRealPoints)
    {
        list.append(dt);
    }
    return list;
}

QVariantList SensorGraphData::getTensions() const
{
    QVariantList list;
    for (const qreal &dt : m_TensionRealPoints)
    {
        list.append(dt);
    }
    return list;
}

QVariantList SensorGraphData::getTensionDeltas() const
{
    QVariantList list;
    for (const qreal &dt : m_TensionDeltaRealPoints)
    {
        list.append(dt);
    }
    return list;
}

void SensorGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
{
    m_axisMinParameters.clear();
    m_axisMinParameters.append(a_axisVal);
}

void SensorGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
{
    m_axisMaxParameters.clear();
    m_axisMaxParameters.append(a_axisVal);
}

QList<qreal> SensorGraphData::getAxisMinParameters()
{
    return  m_axisMinParameters;
}

QList<qreal> SensorGraphData::getAxisMaxParameters()
{
    return  m_axisMaxParameters;
}


void SensorGraphData::clearGraph()
{

}

void SensorGraphData::replaceSeriesPoints(const int index, QLineSeries* series,
                                          int start, int end)
{
    QVector<QPointF> points;
    int n = m_TimeRealPoints.size();
    if(start > n)
        start = n;
    if(end > n)
        end = n;
    points.reserve(n);
    switch(index)
    {
    case HBGraphAxisEnum::DEPTH_IDX:
        for (int i = start; i < end; ++i)
        {
            // xList[i] 是 JS 的毫秒时间戳
            QDateTime dt = m_TimeRealPoints[i];
            qreal x = dt.toMSecsSinceEpoch(); // 转为毫秒时间戳
            qreal y = m_DepthRealPoints[i];
            points.append(QPointF(x, y));
        }
        break;
    case HBGraphAxisEnum::VELOCITY_IDX:
        for (int i = start; i < end; ++i)
        {
            // xList[i] 是 JS 的毫秒时间戳
            QDateTime dt = m_TimeRealPoints[i];
            qreal x = dt.toMSecsSinceEpoch(); // 转为毫秒时间戳
            qreal y = m_VelocityRealPoints[i];
            points.append(QPointF(x, y));
        }
        break;
    case HBGraphAxisEnum::TENSIONS_IDX:
        for (int i = start; i < end; ++i)
        {
            // xList[i] 是 JS 的毫秒时间戳
            QDateTime dt = m_TimeRealPoints[i];
            qreal x = dt.toMSecsSinceEpoch(); // 转为毫秒时间戳
            qreal y = m_TensionRealPoints[i];
            points.append(QPointF(x, y));
        }
        break;
    case HBGraphAxisEnum::TENSION_INCREMENT_IDX:
        for (int i = start; i < end; ++i)
        {
            // xList[i] 是 JS 的毫秒时间戳
            QDateTime dt = m_TimeRealPoints[i];
            qreal x = dt.toMSecsSinceEpoch(); // 转为毫秒时间戳
            qreal y = m_TensionDeltaRealPoints[i];
            points.append(QPointF(x, y));
        }
        break;
    default:
        for (int i = start; i < end; ++i)
        {
            // xList[i] 是 JS 的毫秒时间戳
            QDateTime dt = m_TimeRealPoints[i];
            qreal x = dt.toMSecsSinceEpoch(); // 转为毫秒时间戳
            qreal y = m_DepthRealPoints[i];
            points.append(QPointF(x, y));
        }
        break;
    }
    series->replace(points);
}
