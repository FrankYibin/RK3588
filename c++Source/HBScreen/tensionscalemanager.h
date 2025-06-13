#ifndef TENSIONSCALEMANAGER_H
#define TENSIONSCALEMANAGER_H
#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QString>
#include <QTextStream>
#include <QtCharts>
#include <QAbstractSeries>

class TensionScaleManager : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString TensiometerNumber READ TensiometerNumber WRITE setTensiometerNumber NOTIFY TensiometerNumberChanged)
    Q_PROPERTY(QString QuantityOfCalibration READ QuantityOfCalibration WRITE setQuantityOfCalibration NOTIFY QuantityOfCalibrationChanged)
public:
    enum TensionScaleRoles
    {
        IndexRole = Qt::UserRole + 1,
        ScaleValueRole,
        TensionValueRole
    };
    struct SCALE_DATA
    {
        QString ScaleValue;
        QString TensionValue;
    };

    struct SCALE_RAW_DATA
    {
        int ScaleRaw;
        int TensionRaw;
    };

    static TensionScaleManager* GetInstance();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;


    Q_INVOKABLE void resetModel();
    Q_INVOKABLE void initModel(int quantity);
    Q_INVOKABLE void loadModel();
    Q_INVOKABLE void saveModel();

    Q_INVOKABLE void setTensionValue(const int index, const QString tension);
    Q_INVOKABLE void getScaleCurrent(const int index);

    void SetTensiometerIndex(const int index);

    Q_INVOKABLE QString TensiometerNumber() const;
    Q_INVOKABLE void setTensiometerNumber(const QString number);
    Q_INVOKABLE QString QuantityOfCalibration() const;
    Q_INVOKABLE void setQuantityOfCalibration(const QString quantity);

    Q_INVOKABLE void setAxisMinParameters(const QList<qreal> &a_axisVal);
    Q_INVOKABLE void setAxisMaxParameters(const QList<qreal> &a_axisVal);

    Q_INVOKABLE QList<qreal> getAxisMinParameters();
    Q_INVOKABLE QList<qreal> getAxisMaxParameters();

    Q_INVOKABLE int appendSamples(QAbstractSeries *a_series, quint8 a_type);


protected:

    explicit TensionScaleManager(QObject *parent = nullptr);

private:
    QString m_TensiometerNumber;
    QString m_QuantityOfCalibration;
    int     m_TensiometerIndex;

    static QList<SCALE_DATA> m_ScaleList;  // 存储刻度点数据
    static QList<SCALE_RAW_DATA> m_ScaleRawList; //Raw Data;
    static QVector<QPointF> m_ScalePoint;
    static QList<qreal> m_axisMinParameters;
    static QList<qreal> m_axisMaxParameters;

    static TensionScaleManager* _ptrScaleManager;
    void LoadGraphPoint();
    // void

signals:
    void TensiometerNumberChanged();
    void QuantityOfCalibrationChanged();
    void TensiometerChanged(const int index, const QString scale);
};

#endif // TENSIONSCALEMANAGER_H
