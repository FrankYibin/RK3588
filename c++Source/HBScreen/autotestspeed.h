#ifndef AUTOTESTSPEED_H
#define AUTOTESTSPEED_H

#include <QObject>
//功能需求不明确
class AutoTestSpeed : public QObject
{
    Q_OBJECT

    //Speed control direction
    Q_PROPERTY(int Direction READ Direction WRITE setDirection NOTIFY DirectionChanged)

    //Control speed
    Q_PROPERTY(int SpeedValue READ SpeedValue WRITE setSpeedValue NOTIFY SpeedValueChanged)


    //深度倒计
    //深度倒计设置
    Q_PROPERTY(int DepthCountDown READ DepthCountDown WRITE setDepthCountDown NOTIFY DepthCountDownChanged)

    //深度倒计当前值
    Q_PROPERTY(int DepthCurrent READ DepthCurrent WRITE setDepthCurrent NOTIFY DepthCurrentChanged)

public:

    static AutoTestSpeed* getInstance();

    Q_INVOKABLE int Direction() const;

    Q_INVOKABLE void setDirection(int newDirection);


    Q_INVOKABLE int SpeedValue();

    Q_INVOKABLE void setSpeedValue(int newSpeedValue);

    Q_INVOKABLE int DepthCountDown();
    Q_INVOKABLE void setDepthCountDown(int newSpeedValue);

    Q_INVOKABLE int DepthCurrent();
    Q_INVOKABLE void setDepthCurrent(int newSpeedValue);

private:
    explicit AutoTestSpeed(QObject *parent = nullptr);

    AutoTestSpeed(const AutoTestSpeed&) = delete;
    AutoTestSpeed& operator=(const AutoTestSpeed&) = delete;
    static AutoTestSpeed* m_autoTestSpeed;

signals:

    void DirectionChanged();

    void SpeedValueChanged();

    void DepthCountDownChanged();

    void DepthCurrentChanged();

private:

    int m_direction = 0;

    int m_speedVlue = 0;

    int m_depthCountDown = 8888;

    int m_depthCount = 0;
};

#endif // AUTOTESTSPEED_H
