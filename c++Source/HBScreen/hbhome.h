#ifndef HBHOME_H
#define HBHOME_H

#include <QObject>

class HBHome : public QObject
{
    Q_OBJECT

    //depth        深度
    Q_PROPERTY(int Depth READ Depth WRITE setDepth NOTIFY DepthChanged);

    //speed        速度
    Q_PROPERTY(int Speed READ Speed WRITE setSpeed NOTIFY SpeedChanged);

    //tension      张力
    Q_PROPERTY(int Tension READ Tension WRITE setTension NOTIFY TensionChanged);

    //tensionIncrement  张力增量
    Q_PROPERTY(int TensionIncrement READ TensionIncrement WRITE setTensionIncrement NOTIFY TensionIncrementChanged);

    //pulse count  脉冲数
    Q_PROPERTY(int Pulse READ Pulse WRITE setPulse NOTIFY PulseChanged);

    //MaxTension 极限张力
    Q_PROPERTY(int MaxTension READ MaxTension WRITE setMaxTension NOTIFY MaxTensionChanged);

    //TargetDepth   目的深度
    Q_PROPERTY(int TargetDepth READ TargetDepth WRITE setTargetDepth NOTIFY TargetDepthChanged);

    //MaxSpeed    极限速度
    Q_PROPERTY(int MaxSpeed READ MaxSpeed WRITE setMaxSpeed NOTIFY MaxSpeedChanged);

    //MaxTensionIncrement  极限张力增量
    Q_PROPERTY(int MaxTensionIncrement READ MaxTensionIncrement WRITE setMaxTensionIncrement NOTIFY MaxTensionIncrementChanged );

    //K_Value           k值
    Q_PROPERTY(int KValue READ KValue WRITE setKValue NOTIFY KValueChanged );

    //HarnessTension
    Q_PROPERTY(int HarnessTension READ HarnessTension WRITE setHarnessTension NOTIFY HarnessTensionChanged );

    //MaxParameterStatus  极限参数状态
    Q_PROPERTY(int MaxParameterStatus READ MaxParameterStatus WRITE setMaxParameterStatus NOTIFY MaxParameterStatusChanged);

    //NetworkStatus   网络状态
    Q_PROPERTY(int NetworkStatus READ NetworkStatus WRITE setNetworkStatus NOTIFY NetworkStatusChanged);

public:

    static HBHome* getInstance();

    Q_INVOKABLE int Depth() const;
    Q_INVOKABLE void setDepth(int newDepth);

    Q_INVOKABLE int Speed() const;
    Q_INVOKABLE void setSpeed(int newSpeed);

    Q_INVOKABLE int Tension() const;
    Q_INVOKABLE void setTension(int newTension);

    Q_INVOKABLE int TensionIncrement() const;
    Q_INVOKABLE void setTensionIncrement(int newTensionIncrement);

    Q_INVOKABLE int Pulse() const;
    Q_INVOKABLE void setPulse(int newPulse);

    Q_INVOKABLE int MaxTension() const;
    Q_INVOKABLE void setMaxTension(int newMaxTension);

    Q_INVOKABLE int TargetDepth() const;
    Q_INVOKABLE void setTargetDepth(int newTargetDepth);

    Q_INVOKABLE int MaxSpeed() const;
    Q_INVOKABLE void setMaxSpeed(int newMaxSpeed);

    Q_INVOKABLE int MaxTensionIncrement() const;
    Q_INVOKABLE void setMaxTensionIncrement(int newMaxTensionIncrement);

    Q_INVOKABLE int KValue() const;
    Q_INVOKABLE void setKValue(int newKValue);

    Q_INVOKABLE int HarnessTension() const;
    Q_INVOKABLE void setHarnessTension(int newHarnessTension);

    Q_INVOKABLE int MaxParameterStatus() const;
    Q_INVOKABLE void setMaxParameterStatus(int newMaxParameterStatus);

    Q_INVOKABLE int NetworkStatus() const;
    Q_INVOKABLE void setNetworkStatus(int newNetworkStatus);



signals:

    void DepthChanged();

    void SpeedChanged();

    void TensionChanged();

    void TensionIncrementChanged();

    void PulseChanged();

    void MaxTensionChanged();

    void TargetDepthChanged();

    void MaxSpeedChanged();

    void MaxTensionIncrementChanged();

    void KValueChanged();

    void HarnessTensionChanged();

    void MaxParameterStatusChanged();

    void NetworkStatusChanged();

private:
    explicit HBHome(QObject *parent = nullptr);

    HBHome(const HBHome&) = delete;              // 禁止拷贝
    HBHome& operator=(const HBHome&) = delete;   // 禁止赋值
    static HBHome* m_home;

private:

    int m_depth = 0;
    int m_speed = 0;
    int m_tension = 0;
    int m_tensionIncrement = 0;
    int m_pulse = 0;
    int m_maxTension = 0;
    int m_targetDepth = 0;
    int m_maxSpeed = 0;
    int m_maxTensionIncrement = 0;
    int m_kValue = 0;
    int m_harnessTension = 0;
    int m_maxParameterStatus = 0;
    int m_networkStatus = 0;

};

#endif // HBHOME_H
