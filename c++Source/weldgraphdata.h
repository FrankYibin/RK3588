/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef WELDGRAPH_H
#define WELDGRAPH_H

#include <QObject>
#include <QTextStream>
#include <QtCharts>
#include <QAbstractSeries>
#define PARAMETER_COUNT_PER_GRAPH_SAMPLE 9
#define MAX_PERCENTAGE 100
class WeldGraphData : public QObject
{
    Q_OBJECT
public:
public:
    static WeldGraphData* getInstance();
    ~WeldGraphData();
public:
    Q_INVOKABLE int appendSamples(QAbstractSeries* a_series, quint8 a_type);

    Q_INVOKABLE void setAxisMinParameters(QList<qreal> &a_axisVal);
    Q_INVOKABLE void setAxisMaxParameters(QList<qreal> &a_axisVal);

    Q_INVOKABLE QList<qreal> getAxisMinParameters();
    Q_INVOKABLE QList<qreal> getAxisMaxParameters();

    Q_INVOKABLE void clearGraph();

    Q_INVOKABLE void generateRandomNumber();
protected:
    explicit WeldGraphData(QObject *parent = nullptr);
private:
    inline void calculateLargest(qreal &a_axisVal , qreal a_val);
    inline void calculateSmallest(qreal &a_axisVal , qreal a_val);
    int receiveWeldGraphData(double *receiveData, int lenght);

private:
    static WeldGraphData* m_pInstance;

    int m_GraphPointsCount;
    static double m_SonicsData[9000];
    QVector<QPointF> m_TimePoints ;
    QVector<QPointF> m_FreqPoints ;
    QVector<QPointF> m_PowerPoints ;
    QVector<QPointF> m_AmpPoints;
    QVector<QPointF> m_EnergyPoints;
    QVector<QPointF> m_ForcePoints;
    QVector<QPointF> m_CollapsePoints;
    QVector<QPointF> m_AbsolutePoints;
    QVector<QPointF> m_VelocityPoints;
    QVector<QPointF> m_CurrPoints;
    QVector<QPointF> m_PhasPoints;

    /* Axis Parameters */
    QList<qreal> m_axisMinParameters ;
    QList<qreal> m_axisMaxParameters;

signals:

};

#endif // WELDGRAPH_H
