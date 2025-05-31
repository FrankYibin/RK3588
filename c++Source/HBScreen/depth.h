#ifndef DEPTH_H
#define DEPTH_H

#include <QObject>

class Depth : public QObject
{
    Q_OBJECT
    //目的层深度
    Q_PROPERTY(int TargetLayerDepth READ TargetLayerDepth WRITE setTargetLayerDepth NOTIFY TargetLayerDepthChanged)
    //深度方向
    Q_PROPERTY(int DepthOrientation READ DepthOrientation WRITE setDepthOrientation NOTIFY DepthOrientationChanged)
    //表套深度
    Q_PROPERTY(int MeterDepth READ MeterDepth WRITE setMeterDepth NOTIFY MeterDepthChanged)
    //深度计算方式
    Q_PROPERTY(int DepthCalculateType READ DepthCalculateType WRITE setDepthCalculateType NOTIFY DepthCalculateTypeChanged)
    //编码器编号
    Q_PROPERTY(int CodeOption READ CodeOption WRITE setCodeOption NOTIFY CodeOptionChanged)
    //速度单位
    Q_PROPERTY(int VelocityUnit READ VelocityUnit   WRITE setVelocityUnit   NOTIFY VelocityUnitChanged)
    Q_PROPERTY(int DistanceUnit READ DistanceUnit   WRITE setDistanceUnit   NOTIFY DistanceUnitChanged)
    Q_PROPERTY(int TimeUnit     READ TimeUnit       WRITE setTimeUnit       NOTIFY TimeUnitChanged)

public:
    enum VELOCITY_UNIT
    {
        M_PER_HOUR = 0,   //Used by Modbus
        M_PER_MIN,
        FT_HOUR,
        FT_PER_MIN,
    };

    enum DISTANCE_UNIT
    {
        METER = 0,
        FEET
    };

    enum TIME_UNIT
    {
        HOUR = 0,
        MIN,

    };

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
    Q_INVOKABLE int VelocityUnit    () const;
    Q_INVOKABLE int DistanceUnit    () const;
    Q_INVOKABLE int TimeUnit        () const;
    Q_INVOKABLE void setVelocityUnit(const int velocityUnit);
    Q_INVOKABLE void setDistanceUnit(const int distanceUnit);
    Q_INVOKABLE void setTimeUnit    (const int timeUnit);


    Q_INVOKABLE int CodeOption() const;
    Q_INVOKABLE void setCodeOption(int newTCodeOption);
signals:
    void TargetLayerDepthChanged();
    void DepthOrientationChanged();
    void MeterDepthChanged();
    void DepthCalculateTypeChanged();
    void CodeOptionChanged();

    void VelocityUnitChanged    ();
    void DistanceUnitChanged    ();
    void TimeUnitChanged        ();



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
    int m_codeOption;
    int m_velocityUnit;
    int m_timeUnit;
    int m_distanceUnit;

};

#endif // DEPTH_H
