#ifndef DEPTHSIMAN_H
#define DEPTHSIMAN_H

#include <QObject>

class DepthSiMan : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString DistanceUpperWellSetting READ DistanceUpperWellSetting WRITE setDistanceUpperWellSetting NOTIFY DistanceUpperWellSettingChanged)
    Q_PROPERTY(QString DistanceLowerWellSetting READ DistanceLowerWellSetting WRITE setDistanceLowerWellSetting NOTIFY DistanceLowerWellSettingChanged)
    Q_PROPERTY(QString SlopeAngleWellSetting READ SlopeAngleWellSetting WRITE setSlopeAngleWellSetting NOTIFY SlopeAngleWellSettingChanged)
    Q_PROPERTY(QString DepthStartSetting READ DepthStartSetting WRITE setDepthStartSetting NOTIFY DepthStartSettingChanged)
    Q_PROPERTY(QString DepthFinishSetting READ DepthFinishSetting WRITE setDepthFinishSetting NOTIFY DepthFinishSettingChanged)

    //报警
    Q_PROPERTY(int IndicateSimanAlert READ IndicateSimanAlert WRITE setIndicateSimanAlert NOTIFY IndicateSimanAlertChanged)
    //刹车
    Q_PROPERTY(int IndicateSimanStop READ IndicateSimanStop WRITE setIndicateSimanStop NOTIFY IndicateSimanStopChanged)
    //限速
    Q_PROPERTY(QString VelocitySiman READ VelocitySiman WRITE setVelocitySiman NOTIFY VelocitySimanChanged)

public:

    static DepthSiMan* GetInstance();

    Q_INVOKABLE QString DistanceUpperWellSetting() const;
    Q_INVOKABLE void setDistanceUpperWellSetting(const QString setting);

    Q_INVOKABLE QString DistanceLowerWellSetting() const;
    Q_INVOKABLE void setDistanceLowerWellSetting(const QString setting);

    Q_INVOKABLE QString SlopeAngleWellSetting() const;
    Q_INVOKABLE void setSlopeAngleWellSetting(const QString setting);

    Q_INVOKABLE QString DepthStartSetting() const;
    Q_INVOKABLE void setDepthStartSetting(const QString setting);

    Q_INVOKABLE QString DepthFinishSetting() const;
    Q_INVOKABLE void setDepthFinishSetting(const QString setting);

    Q_INVOKABLE QString VelocitySiman() const;
    Q_INVOKABLE void setVelocitySiman(const QString velocitySiman);

    Q_INVOKABLE int IndicateSimanAlert() const;
    Q_INVOKABLE void setIndicateSimanAlert(int indicateSimanAlert);

    Q_INVOKABLE int IndicateSimanStop() const;
    Q_INVOKABLE void setIndicateSimanStop(int indicateSimanStop);


private:
    explicit DepthSiMan(QObject *parent = nullptr);

    DepthSiMan(const DepthSiMan&) = delete;
    DepthSiMan& operator=(const DepthSiMan&) = delete;
    static DepthSiMan* _ptrDepthSiMan;

signals:

    void DistanceUpperWellSettingChanged();
    void DistanceLowerWellSettingChanged();
    void SlopeAngleWellSettingChanged();
    void DepthStartSettingChanged();
    void DepthFinishSettingChanged();
    void VelocitySimanChanged();
    void IndicateSimanAlertChanged();
    void IndicateSimanStopChanged();

private:
    QString m_DistanceUpperWellSetting;
    QString m_DistanceLowerWellSetting;
    QString m_SlopeAngleWellSetting;
    QString m_DepthStartSetting;
    QString m_DepthFinishSetting;
    QString m_VelocitySiman;
    int m_IndicateSimanAlert;
    int m_IndicateSimanStop;
};


#endif // DEPTHSIMAN_H
