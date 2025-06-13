#include "SensorGraphData.h"
#include <QRandomGenerator>
#include "c++Source/HBData/hbdatabase.h"
#include "c++Source/HBGraph/GraphAxisDefineHB.h"

SensorGraphData* SensorGraphData::m_objInstance = nullptr;
double SensorGraphData::m_RoughData[9000] = {0};

SensorGraphData *SensorGraphData::GetInstance()
{
    if (!m_objInstance) {
        m_objInstance = new SensorGraphData();
    }
    return m_objInstance;

}

SensorGraphData::SensorGraphData(QObject *parent)
    : QObject{parent},m_GraphPointsCount(0)
{
    m_TimePoints.clear();
    m_DepthPoints.clear();
    m_VelocityPoints.clear();
    m_TensionsPoints.clear();
    m_TensionIncrementPoints.clear();
}


SensorGraphData::~SensorGraphData()
{
    delete m_objInstance;
    m_objInstance = nullptr;
}

int SensorGraphData::appendSamples(QAbstractSeries *a_series, quint8 a_type)
{
    QVector<QPointF>* container = nullptr;
    switch (a_type) {
    case HBGraphAxisEnum::TIME_IDX:               container = &m_TimePoints;             break;
    case HBGraphAxisEnum::DEPTH_IDX:              container = &m_DepthPoints;            break;
    case HBGraphAxisEnum::VELOCITY_IDX:           container = &m_VelocityPoints;         break;
    case HBGraphAxisEnum::TENSIONS_IDX:           container = &m_TensionsPoints;         break;
    case HBGraphAxisEnum::TENSION_INCREMENT_IDX:  container = &m_TensionIncrementPoints; break;
    default:
        return -1;
    }

    auto *line = qobject_cast<QLineSeries*>(a_series);
    if (!line) return -1;

    line->replace(*container);


    qreal minVal = std::numeric_limits<qreal>::max();
    qreal maxVal = std::numeric_limits<qreal>::lowest();
    for (auto &pt : *container) {
        calculateSmallest(minVal, pt.y());
        calculateLargest (maxVal, pt.y());
    }
    m_axisMinParameters[a_type] = minVal;
    m_axisMaxParameters[a_type] = maxVal;

    return container->size();
}

void SensorGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
{
    m_axisMinParameters = a_axisVal;
}

void SensorGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
{
    m_axisMaxParameters = a_axisVal;

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
    m_TimePoints.clear();
    m_DepthPoints.clear();
    m_VelocityPoints.clear();
    m_TensionsPoints.clear();
    m_TensionIncrementPoints.clear();
    m_GraphPointsCount = 0;

    m_axisMinParameters = { 0,  0,  0,  0,  0 };
    m_axisMaxParameters = { 1, 10, 10, 10,  1 };
}

void SensorGraphData::generateRandomNumber()
{
    // QRandomGenerator* rand = new QRandomGenerator(QTime(0,0,0).secsTo(QTime::currentTime()));
    // for(int i = 0; i < 9000; i++)
    // {
    //     m_RoughData[i] = rand->generate() % 10;
    // }
    // delete rand;
    // receiveWeldGraphData(m_RoughData, 9000);

}


void SensorGraphData::calculateLargest(qreal &a_axisVal, qreal a_val)
{
    if (a_val > a_axisVal) a_axisVal = a_val;
}

void SensorGraphData::calculateSmallest(qreal &a_axisVal, qreal a_val)
{
    if (a_val < a_axisVal) a_axisVal = a_val;
}

void SensorGraphData::loadHistoryCurve(QAbstractSeries* series, const QString& fieldName)
{
    if (!series)
        return;

    QLineSeries* lineSeries = qobject_cast<QLineSeries*>(series);
    if (!lineSeries)
        return;

    lineSeries->clear();

    QVector<QPointF> points = HBDatabase::GetInstance().loadGraphPoints(fieldName);
    for (const QPointF& pt : points) {
        lineSeries->append(pt);
    }
}
