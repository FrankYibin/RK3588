#ifndef DEPTHSAFE_H
#define DEPTHSAFE_H

#include <QObject>

class DepthSafe : public QObject
{
    Q_OBJECT

    //井口段
    //深度预置
    Q_PROPERTY(int DepthPreset READ DepthPreset WRITE setDepthPreset NOTIFY DepthPresetChanged)
    //报警
    Q_PROPERTY(int WellWarnig READ WellWarnig WRITE setWellWarnig NOTIFY WellWarnigChanged)
    //刹车
    Q_PROPERTY(int Brake READ Brake WRITE setBrake NOTIFY BrakeChanged)
    //限速
    Q_PROPERTY(int VelocityLimit READ VelocityLimit WRITE setVelocityLimit NOTIFY VelocityLimitChanged)


    //报警
    Q_PROPERTY(int DepthWarning READ DepthWarning WRITE setDepthWarning NOTIFY DepthWarningChanged)
    //总深度
    Q_PROPERTY(int TotalDepth READ TotalDepth WRITE setTotalDepth NOTIFY TotalDepthhanged)
    //刹车
    Q_PROPERTY(int DepthBrake READ DepthBrake WRITE setDepthBrake NOTIFY DepthBrakeChanged)
    //井低限速
    Q_PROPERTY(int DepthVelocityLimit READ DepthVelocityLimit WRITE setDepthVelocityLimit NOTIFY DepthVelocityLimitChanged)

public:

    static DepthSafe* getInstance();

    Q_INVOKABLE int DepthPreset() const;

    Q_INVOKABLE void setDepthPreset(int newDepthPreset);

    Q_INVOKABLE int WellWarnig() const;

    Q_INVOKABLE void setWellWarnig(int newDepthPreset);


    Q_INVOKABLE int Brake() const;

    Q_INVOKABLE void setBrake(int newBrake);


    Q_INVOKABLE int VelocityLimit() const;

    Q_INVOKABLE void setVelocityLimit(int newTVelocityLimit);


    Q_INVOKABLE int DepthWarning() const;

    Q_INVOKABLE void setDepthWarning(int newDepthWarning);


    Q_INVOKABLE int TotalDepth() const;

    Q_INVOKABLE void setTotalDepth(int newTotalDepth);


    Q_INVOKABLE int DepthBrake() const;

    Q_INVOKABLE void setDepthBrake(int newDepthbrake);

    Q_INVOKABLE int DepthVelocityLimit() const;

    Q_INVOKABLE void setDepthVelocityLimit(int newDepthWarning);


private:
    explicit DepthSafe(QObject *parent = nullptr);

    DepthSafe(const DepthSafe&) = delete;
    DepthSafe& operator=(const DepthSafe&) = delete;
    static DepthSafe* m_depthSafe;

signals:

    void DepthPresetChanged();

    void WellWarnigChanged();

    void BrakeChanged();

    void VelocityLimitChanged();

    void DepthWarningChanged();

    void TotalDepthhanged();

    void DepthBrakeChanged();

    void DepthVelocityLimitChanged();



private:

    int m_depthPreset;
    int m_wellWarnig;
    int m_brake;
    int m_velocityLimit;

    int m_depthWarning;
    int m_totalDepth;
    int m_depthBrake;
    int m_depthVelocityLimit;




};


#endif // DEPTHSAFE_H
