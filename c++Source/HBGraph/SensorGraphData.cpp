#include "SensorGraphData.h"

SensorGraphData::~SensorGraphData()
{

}

int SensorGraphData::appendSamples(QAbstractSeries *a_series, quint8 a_type)
{
    return 0;
}

void SensorGraphData::setAxisMinParameters(QList<qreal> &a_axisVal)
{

}

void SensorGraphData::setAxisMaxParameters(QList<qreal> &a_axisVal)
{

}

QList<qreal> SensorGraphData::getAxisMinParameters()
{

}

QList<qreal> SensorGraphData::getAxisMaxParameters()
{

}

void SensorGraphData::clearGraph()
{

}

void SensorGraphData::generateRandomNumber()
{

}

SensorGraphData::SensorGraphData(QObject *parent)
    : QObject{parent}
{}

void SensorGraphData::calculateLargest(qreal &a_axisVal, qreal a_val)
{

}

void SensorGraphData::calculateSmallest(qreal &a_axisVal, qreal a_val)
{

}
