#ifndef AUTOTESTSPEED_H
#define AUTOTESTSPEED_H

#include <QObject>
//功能需求不明确
class AutoTestSpeed : public QObject
{
    Q_OBJECT

    //Speed control direction
    Q_PROPERTY(int VelocityStatus READ VelocityStatus WRITE setVelocityStatus NOTIFY VelocityStatusChanged)
    Q_PROPERTY(int EnableVelocityControl READ EnableVelocityControl WRITE setEnableVelocityControl NOTIFY EnableVelocityControlChanged)

    //Control speed
    Q_PROPERTY(QString VelocitySetting READ VelocitySetting WRITE setVelocitySetting NOTIFY VelocitySettingChanged)


    //深度倒计
    //深度倒计设置
    Q_PROPERTY(QString DepthDeviationSetting READ DepthDeviationSetting WRITE setDepthDeviationSetting NOTIFY DepthDeviationSettingChanged)
    Q_PROPERTY(QString DepthDeviationCurrent READ DepthDeviationCurrent WRITE setDepthDeviationCurrent NOTIFY DepthDeviationChanged)

    //深度倒计当前值
    Q_PROPERTY(int DepthCurrent READ DepthCurrent WRITE setDepthCurrent NOTIFY DepthCurrentChanged)

    Q_PROPERTY(bool IsDownCountStart READ IsDownCountStart WRITE setIsDownCountStart NOTIFY IsDownCountStartChanged)
public:

    static AutoTestSpeed* GetInstance();

    Q_INVOKABLE int VelocityStatus() const;
    Q_INVOKABLE void setVelocityStatus(const int status);

    Q_INVOKABLE QString VelocitySetting() const;
    Q_INVOKABLE void setVelocitySetting(QString velocity);

    Q_INVOKABLE int EnableVelocityControl() const;//功能需求不明确
    Q_INVOKABLE void setEnableVelocityControl(const int enable);//功能需求不明确

    Q_INVOKABLE QString DepthDeviationSetting() const;
    Q_INVOKABLE void setDepthDeviationSetting(const QString deviation);

    Q_INVOKABLE int DepthCurrent() const;
    Q_INVOKABLE void setDepthCurrent(const int depth);

    Q_INVOKABLE QString DepthDeviationCurrent() const;
    Q_INVOKABLE void setDepthDeviationCurrent(const QString current);

    Q_INVOKABLE void startDepthDownCount();

    Q_INVOKABLE bool IsDownCountStart() const;
    Q_INVOKABLE void setIsDownCountStart(const bool isStart);

    

private:
    enum VOICE_STATUS
    {
        OFF = 0,
        ON = 1
    };
    explicit AutoTestSpeed(QObject *parent = nullptr);

    AutoTestSpeed(const AutoTestSpeed&) = delete;
    AutoTestSpeed& operator=(const AutoTestSpeed&) = delete;
    static AutoTestSpeed* _ptrAutoTestSpeed;
    static constexpr int MAX_TIMEOUT = 5;
    static int timeout;

signals:

    void VelocityStatusChanged();
    void VelocitySettingChanged();
    void EnableVelocityControlChanged(); //功能需求不明确

    void DepthDeviationSettingChanged();
    void DepthDeviationChanged();

    void DepthCurrentChanged();
    void IsDownCountStartChanged();
private slots:
    void onDistanceUnitChanged();

private:

    int m_VelocityStatus;
    int m_EnableVelocityControl; //功能需求不明确

    QString m_VelocitySetting;

    QString m_DepthDeviationSetting;
    int     m_RawDeviationSetting;
    QString m_DepthDeviationCurrent;

    int     m_RawDepthCurrent;
    int     m_RawDepthBase;
    bool    m_isDownCountStart;
};

#endif // AUTOTESTSPEED_H
