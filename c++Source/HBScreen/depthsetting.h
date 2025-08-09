#ifndef DEPTH_SETTING_H
#define DEPTH_SETTING_H

#include <QObject>

class DepthSetting : public QObject
{
    Q_OBJECT
    //目的层深度
    Q_PROPERTY(QString DepthTargetLayer READ DepthTargetLayer WRITE setDepthTargetLayer NOTIFY DepthTargetLayerChanged)
    //深度方向
    Q_PROPERTY(int DepthOrientation READ DepthOrientation WRITE setDepthOrientation NOTIFY DepthOrientationChanged)
    //表套深度
    Q_PROPERTY(QString DepthSurfaceCover READ DepthSurfaceCover WRITE setDepthSurfaceCover NOTIFY DepthSurfaceCoverChanged)
    //瞬时深度
    Q_PROPERTY(QString DepthCurrent READ DepthCurrent WRITE setDepthCurrent NOTIFY DepthCurrentChanged)
    //编码器源选择
    Q_PROPERTY(int DepthEncoder READ DepthEncoder WRITE setDepthEncoder NOTIFY DepthEncoderChanged)
    //速度单位
    Q_PROPERTY(int VelocityUnit READ VelocityUnit   WRITE setVelocityUnit   NOTIFY VelocityUnitChanged)
    //脉冲数
    Q_PROPERTY(QString PulseCount READ PulseCount WRITE setPulseCount NOTIFY PulseCountChanged)
    //极限速度
    Q_PROPERTY(QString VelocityLimited READ VelocityLimited WRITE setVelocityLimited NOTIFY VelocityLimitedChanged)

    Q_PROPERTY(int DistanceUnit READ DistanceUnit   WRITE setDistanceUnit   NOTIFY DistanceUnitChanged)
    Q_PROPERTY(int TimeUnit     READ TimeUnit       WRITE setTimeUnit       NOTIFY TimeUnitChanged)

    Q_PROPERTY(QString WheelCircumference READ WheelCircumference WRITE setWheelCircumference NOTIFY WheelCircumferenceChanged)
    Q_PROPERTY(QString EncoderPulseCount READ EncoderPulseCount WRITE setEncoderPulseCount NOTIFY EncoderPulseCountChanged)
    Q_PROPERTY(QString MeasuredWellDepth READ MeasuredWellDepth WRITE setMeasuredWellDepth NOTIFY MeasuredWellDepthChanged)
    Q_PROPERTY(QString ActualWellDepth READ ActualWellDepth WRITE setActualWellDepth NOTIFY ActualWellDepthChanged)
    Q_PROPERTY(QString CorrectedPulseCount READ CorrectedPulseCount WRITE setCorrectedPulseCount NOTIFY CorrectedPulseCountChanged)
    Q_PROPERTY(QString PulsePerMeter READ PulsePerMeter WRITE setPulsePerMeter NOTIFY PulsePerMeterChanged)

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
    static DepthSetting* GetInstance();
    Q_INVOKABLE QString DepthTargetLayer() const;
    Q_INVOKABLE void setDepthTargetLayer(const QString value);

    Q_INVOKABLE int DepthOrientation() const;
    Q_INVOKABLE void setDepthOrientation(const int orientation);

    Q_INVOKABLE QString DepthCurrent() const;
    Q_INVOKABLE void setDepthCurrent(const QString value);

    Q_INVOKABLE QString PulseCount() const;
    Q_INVOKABLE void setPulseCount(const QString value);
    
    Q_INVOKABLE QString VelocityLimited() const;
    Q_INVOKABLE void setVelocityLimited(const QString value);

    Q_INVOKABLE QString DepthSurfaceCover() const;
    Q_INVOKABLE void setDepthSurfaceCover(const QString value);

    Q_INVOKABLE int DepthEncoder() const;
    Q_INVOKABLE void setDepthEncoder(const int value);

    Q_INVOKABLE int VelocityUnit    () const;
    Q_INVOKABLE void setVelocityUnit(const int velocityUnit);

    Q_INVOKABLE int DistanceUnit    () const;
    Q_INVOKABLE void setDistanceUnit(const int distanceUnit);

    Q_INVOKABLE int TimeUnit        () const;
    Q_INVOKABLE void setTimeUnit    (const int timeUnit);

    Q_INVOKABLE QString WheelCircumference() const;
    Q_INVOKABLE void setWheelCircumference(const QString value);

    Q_INVOKABLE QString EncoderPulseCount() const;
    Q_INVOKABLE void setEncoderPulseCount(const QString value);

    Q_INVOKABLE QString MeasuredWellDepth() const;
    Q_INVOKABLE void setMeasuredWellDepth(const QString value);

    Q_INVOKABLE QString ActualWellDepth() const;
    Q_INVOKABLE void setActualWellDepth(const QString value);

    Q_INVOKABLE QString CorrectedPulseCount() const;
    Q_INVOKABLE void setCorrectedPulseCount(const QString value);

    Q_INVOKABLE QString PulsePerMeter() const;
    Q_INVOKABLE void setPulsePerMeter(const QString value);
signals:
    void DepthTargetLayerChanged();
    void DepthOrientationChanged();
    void DepthSurfaceCoverChanged();
    void DepthEncoderChanged();
    void DepthCurrentChanged();
    void PulseCountChanged();
    void VelocityLimitedChanged();
    void VelocityUnitChanged(int unit);
    void DistanceUnitChanged();
    void TimeUnitChanged();
    void WheelCircumferenceChanged(QString value);
    void EncoderPulseCountChanged(QString value);
    void MeasuredWellDepthChanged(QString value);
    void ActualWellDepthChanged(QString value);
    void CorrectedPulseCountChanged();
    void PulsePerMeterChanged();
private:
    explicit DepthSetting(QObject *parent = nullptr);
    DepthSetting(const DepthSetting&) = delete;
    DepthSetting& operator=(const DepthSetting&) = delete;
    static DepthSetting* _ptrDepth;
    QString CalculateOriginalPulse(const QString circumference, const QString pulseCount);
    QString CalculateNewPulse(const QString measuredDepth, const QString actualDepth);

private:
    QString m_DepthTargetLayer;
    int m_depthOrientation;
    QString m_DepthSurfaceCover;
    int m_DepthEncoder;
    QString m_DepthCurrent;
    QString m_PulseCount;
    QString m_VelocityLimited;
    int m_velocityUnit;
    int m_timeUnit;
    int m_distanceUnit;
    QString m_PulsePerMeter;
    QString m_CorrectedPulseCount;
    QString m_WheelCircumference;
    QString m_EncoderPulseCount;
    QString m_MeasuredWellDepth;
    QString m_ActualWellDepth;
};

#endif // DEPTH_SETTING_H
