#ifndef DEPTH_H
#define DEPTH_H

#include <QObject>

class Depth : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int TargetLayerDepth READ TargetLayerDepth WRITE setTargetLayerDepth NOTIFY TargetLayerDepthChanged);

    Q_PROPERTY(int DepthOrientation READ DepthOrientation WRITE setDepthOrientation NOTIFY DepthOrientationChanged);

    Q_PROPERTY(int MeterDepth READ MeterDepth WRITE setMeterDepth NOTIFY MeterDepthChanged);

    Q_PROPERTY(int DepthCalculateType READ DepthCalculateType WRITE setDepthCalculateType NOTIFY DepthCalculateTypeChanged);

    Q_PROPERTY(int VelocityUnit READ VelocityUnit WRITE setVelocityUnit NOTIFY VelocityUnitChanged);

public:
    static Depth* getInstance();

    Q_INVOKABLE int TargetLayerDepth() const;

    Q_INVOKABLE void setTargetLayerDepth(int newTargetLayerDepth);


    Q_INVOKABLE int DepthOrientation() const;

    Q_INVOKABLE void setDepthOrientation(int newTargetLayerDepth);


    Q_INVOKABLE int MeterDepth() const;

    Q_INVOKABLE void setMeterDepth(int newMeterDepth);


    Q_INVOKABLE int DepthCalculateType() const;

    Q_INVOKABLE void setDepthCalculateType(int newDepthCalculateType);


    Q_INVOKABLE int VelocityUnit() const;

    Q_INVOKABLE void setVelocityUnit(int newTVelocityUnit);





signals:
    void TargetLayerDepthChanged();

    void DepthOrientationChanged();

    void MeterDepthChanged();

    void DepthCalculateTypeChanged();

    void VelocityUnitChanged();


private:

    explicit Depth(QObject *parent = nullptr);

    Depth(const Depth&) = delete;
    Depth& operator=(const Depth&) = delete;
    static Depth* m_depth;

private:

    int m_targetLayerDepth;
    int m_depthOrientation;
    int m_meterDepth;
    int m_depthCalculateType;
    int m_velocityUnit;

};

#endif // DEPTH_H
