#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QSettings>

class Configuration : public QObject
{
    Q_OBJECT
    //RS232
    Q_PROPERTY(QString BaudRate READ BaudRate WRITE setBaudRate NOTIFY BaudRateChanged)

    Q_PROPERTY(QString DataBits READ DataBits WRITE setDataBits NOTIFY DataBitsChanged)

    Q_PROPERTY(QString Parity READ Parity WRITE setParity NOTIFY ParityChanged)

    Q_PROPERTY(QString StopBits READ StopBits WRITE setStopBits NOTIFY StopBitsChanged)

    //Network

    Q_PROPERTY(QString LocalIP READ LocalIP WRITE setLocalIP NOTIFY LocalIPChanged)

    Q_PROPERTY(QString LocalPort READ LocalPort WRITE setLocalPort NOTIFY LocalPortChanged)

    Q_PROPERTY(QString RemoteIP READ RemoteIP WRITE setRemoteIP NOTIFY RemoteIPChanged)

    Q_PROPERTY(QString RemotePort READ RemotePort WRITE setRemotePort NOTIFY RemotePortChanged)

    //Version info

    Q_PROPERTY(QString DeviceID READ DeviceID WRITE setDeviceID NOTIFY DeviceIDChanged)

    Q_PROPERTY(QString SoftwareVersion READ SoftwareVersion WRITE setSoftwareVersion NOTIFY SoftwareVersionChanged)

    Q_PROPERTY(QString HardwareVersion READ HardwareVersion WRITE setHardwareVersion NOTIFY HardwareVersionChanged)

    //Theme
    Q_PROPERTY(int ThemeIndex READ ThemeIndex WRITE setThemeIndex NOTIFY ThemeIndexChanged)

    //Language
    Q_PROPERTY(int LanguageIndex READ LanguageIndex WRITE setLanguageIndex NOTIFY LanguageIndexChanged)

public:

    static Configuration* GetInstance();

    // RS232
    Q_INVOKABLE QString BaudRate() const;
    Q_INVOKABLE void setBaudRate(const QString baudRate);

    Q_INVOKABLE QString DataBits() const;
    Q_INVOKABLE void setDataBits(const QString dataBits);

    Q_INVOKABLE QString Parity() const;
    Q_INVOKABLE void setParity(const QString parity);

    Q_INVOKABLE QString StopBits() const;
    Q_INVOKABLE void setStopBits(const QString stopBits);

    // Network
    Q_INVOKABLE QString LocalIP() const;
    Q_INVOKABLE void setLocalIP(const QString ip);

    Q_INVOKABLE QString LocalPort() const;
    Q_INVOKABLE void setLocalPort(const QString port);

    Q_INVOKABLE QString RemoteIP() const;
    Q_INVOKABLE void setRemoteIP(const QString ip);

    Q_INVOKABLE QString RemotePort() const;
    Q_INVOKABLE void setRemotePort(const QString port);

    // Version Info
    Q_INVOKABLE QString DeviceID() const;
    Q_INVOKABLE void setDeviceID(const QString id);

    Q_INVOKABLE QString SoftwareVersion() const;
    Q_INVOKABLE void setSoftwareVersion(const QString version);

    Q_INVOKABLE QString HardwareVersion() const;
    Q_INVOKABLE void setHardwareVersion(const QString version);


    Q_INVOKABLE int ThemeIndex() const;
    Q_INVOKABLE void setThemeIndex(int themeIndex);

    Q_INVOKABLE int LanguageIndex() const;
    Q_INVOKABLE void setLanguageIndex(int languageIndex);

signals:

    void BaudRateChanged();
    void DataBitsChanged();
    void RemoteIPChanged();
    void RemotePortChanged();

    void LocalIPChanged();
    void LocalPortChanged();
    void ParityChanged();
    void StopBitsChanged();

    void DeviceIDChanged();
    void SoftwareVersionChanged();
    void HardwareVersionChanged();

    void ThemeIndexChanged();
    void LanguageIndexChanged();

private:
    explicit Configuration(QObject *parent = nullptr);

    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;
    static Configuration* _ptrConfiguration;

private:
    QString  m_baudRate;
    QString  m_dataBits;
    QString  m_parity;
    QString  m_stopBits;

    QString  m_localIp;
    QString  m_localPort;
    QString  m_remoteIp;
    QString  m_remotePort;

    QString  m_deviceID;
    QString  m_softwareVersion;
    QString  m_hardwareVersion;

    int  m_themeIndex;
    int  m_languageIndex;

    QSettings m_settings;


};

#endif // CONFIGURATION_H
