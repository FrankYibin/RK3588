#ifndef SENSORGRAPHDATA_H
#define SENSORGRAPHDATA_H

#include <QObject>
#include <QTextStream>
#include <QtCharts>
#include <QAbstractSeries>
#define PARAMETER_COUNT_PER_GRAPH_SAMPLE 9
#define MAX_PERCENTAGE 100
class SensorGraphData : public QObject
{
    Q_OBJECT
public:
public:
    static SensorGraphData* GetInstance();
    ~SensorGraphData();
public:
    Q_INVOKABLE int appendSamples(QAbstractSeries* a_series, quint8 a_type);

    Q_INVOKABLE void setAxisMinParameters(QList<qreal> &a_axisVal);
    Q_INVOKABLE void setAxisMaxParameters(QList<qreal> &a_axisVal);

    Q_INVOKABLE QList<qreal> getAxisMinParameters();
    Q_INVOKABLE QList<qreal> getAxisMaxParameters();

    Q_INVOKABLE void clearGraph();

    Q_INVOKABLE void generateRandomNumber();
protected:
    explicit SensorGraphData(QObject *parent = nullptr);
private:
    inline void calculateLargest(qreal &a_axisVal , qreal a_val);
    inline void calculateSmallest(qreal &a_axisVal , qreal a_val);
    int receiveWeldGraphData(double *receiveData, int length);

private:
    static SensorGraphData* m_objInstance;

    int m_GraphPointsCount;
    static double m_RoughData[9000];

    QVector<QPointF> m_TimePoints ;
    QVector<QPointF> m_DepthPoints ;
    QVector<QPointF> m_VelocityPoints ;
    QVector<QPointF> m_TensionsPoints;
    QVector<QPointF> m_TensionIncrementPoints;

    /* Axis Parameters */
    QList<qreal> m_axisMinParameters ;
    QList<qreal> m_axisMaxParameters;

signals:

};

#endif // SENSORGRAPHDATA_H
