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

    Q_INVOKABLE void setAxisMinParameters(QList<qreal> &a_axisVal);
    Q_INVOKABLE void setAxisMaxParameters(QList<qreal> &a_axisVal);

    Q_INVOKABLE QList<qreal> getAxisMinParameters();
    Q_INVOKABLE QList<qreal> getAxisMaxParameters();

    Q_INVOKABLE void clearGraph();
    Q_INVOKABLE void loadSensorGraphPoint(const QDateTime &start, const QDateTime &end);
    Q_INVOKABLE void exportData();

    Q_INVOKABLE QVariantList getDateTimes() const;
    Q_INVOKABLE QVariantList getDepths() const;
    Q_INVOKABLE QVariantList getVelocitys() const;
    Q_INVOKABLE QVariantList getTensions() const;
    Q_INVOKABLE QVariantList getTensionDeltas() const;


protected:
    explicit SensorGraphData(QObject *parent = nullptr);
private:
    inline void calculateLargest(qreal &a_axisVal , qreal a_val);
    inline void calculateSmallest(qreal &a_axisVal , qreal a_val);


private:
    static SensorGraphData* m_objInstance;

    QList<QDateTime> m_TimeRealPoints;
    QList<qreal> m_DepthRealPoints;
    QList<qreal> m_VelocityRealPoints;
    QList<qreal> m_TensionRealPoints;
    QList<qreal> m_TensionDeltaRealPoints;

    /* Axis Parameters */
    QList<qreal> m_axisMinParameters ;
    QList<qreal> m_axisMaxParameters;

signals:
    void isDataReady();
};

#endif // SENSORGRAPHDATA_H
