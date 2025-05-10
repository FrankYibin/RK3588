#ifndef DEPTHSAFE_H
#define DEPTHSAFE_H

#include <QObject>

class DepthSafe : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int DepthPreset READ DepthPreset WRITE setDepthPreset NOTIFY DepthPresetChanged);

    Q_PROPERTY(int WellWarnig READ WellWarnig WRITE setWellWarnigNOTIFY NOTIFY WellWarnigChanged);

    Q_PROPERTY(int Brake READ Brake WRITE setBrake NOTIFY BrakeChanged);

    Q_PROPERTY(int VelocityLimit READ VelocityLimit WRITE setVelocityLimit NOTIFY VelocityLimitChanged);



    Q_PROPERTY(int DepthWarning READ DepthWarning WRITE setDepthWarning NOTIFY DepthWarningChanged);

    Q_PROPERTY(int TotalDepth READ TotalDepth WRITE setTotalDepth NOTIFY TotalDepthhanged);

    Q_PROPERTY(int Depthbrake READ Depthbrake WRITE setDepthbrake NOTIFY DepthbrakeChanged);

    Q_PROPERTY(int DepthVelocityLimit READ DepthVelocityLimit WRITE setDepthVelocityLimit NOTIFY DepthVelocityLimitChanged);

public:

    static DepthSafe* getInstance();

    Q_INVOKABLE int DepthPreset() const;

    Q_INVOKABLE void setDepthPreset(int newDepthPreset);

    Q_INVOKABLE int WellWarnig() const;

    Q_INVOKABLE void setWellWarnigNOTIFY(int newDepthPreset);


    Q_INVOKABLE int Brake() const;

    Q_INVOKABLE void setBrake(int newBrake);


    Q_INVOKABLE int VelocityLimit() const;

    Q_INVOKABLE void setVelocityLimit(int newTVelocityLimit);


    Q_INVOKABLE int DepthWarning() const;

    Q_INVOKABLE void setDepthWarning(int newDepthWarning);


    Q_INVOKABLE int TotalDepth() const;

    Q_INVOKABLE void setTotalDepth(int newTotalDepth);


    Q_INVOKABLE int Depthbrake() const;

    Q_INVOKABLE void setDepthbrake(int newDepthbrake);

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

    void DepthbrakeChanged();

    void DepthVelocityLimitChanged();



private:

    int m_depthPreset;
    int m_wellWarnig;
    int m_brake;
    int m_velocityLimit;

    int m_depthWarning;
    int m_totalDepth;
    int m_depthbrake;
    int m_depthVelocityLimit;




};


#endif // DEPTHSAFE_H
