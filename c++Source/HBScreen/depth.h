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
    Q_PROPERTY(int VelocityUnit READ VelocityUnit WRITE setVelocityUnit NOTIFY velocityUnitChanged)

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

    Q_INVOKABLE int CodeOption() const;

    Q_INVOKABLE void setCodeOption(int newTCodeOption);






signals:
    void TargetLayerDepthChanged();

    void DepthOrientationChanged();

    void MeterDepthChanged();

    void DepthCalculateTypeChanged();

    void velocityUnitChanged();

    void CodeOptionChanged();


private:

    explicit Depth(QObject *parent = nullptr);

    Depth(const Depth&) = delete;
    Depth& operator=(const Depth&) = delete;
    static Depth* m_depth;

private:

    int m_targetLayerDepth = 0;
    int m_depthOrientation = 0;
    int m_meterDepth = 0;
    int m_depthCalculateType = 0;
    int m_velocityUnit = 0;
    int m_codeOption = 0;

};

#endif // DEPTH_H
