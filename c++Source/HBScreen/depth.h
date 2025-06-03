#ifndef DEPTH_H
#define DEPTH_H

#include <QObject>

class Depth : public QObject
{
    Q_OBJECT
    //目的层深度
    Q_PROPERTY(QString DepthTargetLayer READ DepthTargetLayer WRITE setDepthTargetLayer NOTIFY DepthTargetLayerChanged)
    //深度方向
    Q_PROPERTY(int DepthOrientation READ DepthOrientation WRITE setDepthOrientation NOTIFY DepthOrientationChanged)
    //表套深度
    Q_PROPERTY(QString DepthSurfaceCover READ DepthSurfaceCover WRITE setDepthSurfaceCover NOTIFY DepthSurfaceCoverChanged)
    //编码器源选择
    Q_PROPERTY(int DepthEncoder READ DepthEncoder WRITE setDepthEncoder NOTIFY DepthEncoderChanged)
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
        FT_PER_HOUR,
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

    enum ENCODER_SOURCE
    {
        ENCODER_1 = 0,
        ENCODER_2,
        ENCODER_3,
        ENCODER_1_2,
        ENCODER_2_3,
        ENCODER_1_3
    };

public:
    static Depth* GetInstance();
    Q_INVOKABLE QString DepthTargetLayer() const;
    Q_INVOKABLE void setDepthTargetLayer(const QString value);

    Q_INVOKABLE int DepthOrientation() const;
    Q_INVOKABLE void setDepthOrientation(int newTargetLayerDepth);
    Q_INVOKABLE QString DepthSurfaceCover() const;
    Q_INVOKABLE void setDepthSurfaceCover(const QString value);
    Q_INVOKABLE int DepthEncoder() const;
    Q_INVOKABLE void setDepthEncoder(const int value);
    Q_INVOKABLE int VelocityUnit    () const;
    Q_INVOKABLE int DistanceUnit    () const;
    Q_INVOKABLE int TimeUnit        () const;
    Q_INVOKABLE void setVelocityUnit(const int velocityUnit);
    Q_INVOKABLE void setDistanceUnit(const int distanceUnit);
    Q_INVOKABLE void setTimeUnit    (const int timeUnit);


    Q_INVOKABLE int CodeOption() const;
    Q_INVOKABLE void setCodeOption(int newTCodeOption);
signals:
    void DepthTargetLayerChanged();
    void DepthOrientationChanged();
    void DepthSurfaceCoverChanged();
    void DepthEncoderChanged();
    void CodeOptionChanged();

    void VelocityUnitChanged    ();
    void DistanceUnitChanged    ();
    void TimeUnitChanged        ();



private:
    explicit Depth(QObject *parent = nullptr);
    Depth(const Depth&) = delete;
    Depth& operator=(const Depth&) = delete;
    static Depth* _ptrDepth;

private:
    QString m_DepthTargetLayer;
    int m_depthOrientation;
    QString m_DepthSurfaceCover;
    int m_DepthEncoder;
    int m_codeOption;
    int m_velocityUnit;
    int m_timeUnit;
    int m_distanceUnit;

};

#endif // DEPTH_H
