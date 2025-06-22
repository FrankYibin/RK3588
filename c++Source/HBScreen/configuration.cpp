#include "configuration.h"
#include <QCoreApplication>

Configuration* Configuration::_ptrConfiguration = nullptr;

Configuration::Configuration(QObject *parent)
    : QObject(parent), m_settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat)
{
    m_settings.setIniCodec("UTF-8");

    m_baudRate = m_settings.value("RS232/BaudRate", "9600").toString();
    m_settings.setValue("RS232/BaudRate", m_baudRate);
    m_dataBits = m_settings.value("RS232/DataBits", "8").toString();
    m_settings.setValue("RS232/DataBits", m_dataBits);
    m_parity = m_settings.value("RS232/Parity", "None").toString();
    m_settings.setValue("RS232/Parity", m_parity);
    m_stopBits = m_settings.value("RS232/StopBits", "1").toString();
    m_settings.setValue("RS232/StopBits", m_stopBits);

    m_localIp = m_settings.value("Network/LocalIP", "192.168.1.1").toString();
    m_settings.setValue("Network/LocalIP", m_localIp);
    m_localPort = m_settings.value("Network/LocalPort", "8000").toString();
    m_settings.setValue("Network/LocalPort", m_localPort);
    m_remoteIp = m_settings.value("Network/RemoteIP", "192.168.1.2").toString();
    m_settings.setValue("Network/RemoteIP", m_remoteIp);
    m_remotePort = m_settings.value("Network/RemotePort", "8001").toString();
    m_settings.setValue("Network/RemotePort", m_remotePort);

    m_deviceID = m_settings.value("Version/DeviceID", "18229001939").toString();
    m_settings.setValue("Version/DeviceID", m_deviceID);
    m_softwareVersion = m_settings.value("Version/SoftwareVersion", "20250618").toString();
    m_settings.setValue("Version/SoftwareVersion", m_softwareVersion);
    m_hardwareVersion = m_settings.value("Version/HardwareVersion", "20250318").toString();
    m_settings.setValue("Version/HardwareVersion", m_hardwareVersion);

    m_themeIndex = m_settings.value("Theme/ThemeIndex", 0).toInt();
    m_settings.setValue("Theme/ThemeIndex", m_themeIndex);
    m_languageIndex = m_settings.value("Language/LanguageIndex",0).toInt();
    m_settings.setValue("Language/LanguageIndex", m_languageIndex);
}

Configuration *Configuration::GetInstance()
{
    if (!_ptrConfiguration) {
        _ptrConfiguration = new Configuration();
    }
    return _ptrConfiguration;
}

// RS232
QString Configuration::BaudRate() const {

    return m_baudRate;
}
void Configuration::setBaudRate(const QString baudRate) {
    if (baudRate != m_baudRate) {
        m_baudRate = baudRate;
        m_settings.setValue("RS232/BaudRate", baudRate);
        emit BaudRateChanged();
    }
}

QString Configuration::DataBits() const {

    return m_dataBits;
}
void Configuration::setDataBits(const QString dataBits) {
    if (dataBits != m_dataBits) {
        m_dataBits = dataBits;
        m_settings.setValue("RS232/DataBits", dataBits);
        emit DataBitsChanged();
    }
}

QString Configuration::Parity() const {

    return m_parity;
}
void Configuration::setParity(const QString parity) {

    if (parity != m_parity) {
        m_parity = parity;
        m_settings.setValue("RS232/Parity", parity);
        emit ParityChanged();
    }
}

QString Configuration::StopBits() const {

    return m_stopBits;
}
void Configuration::setStopBits(const QString stopBits) {
    if (stopBits != m_stopBits) {
        m_stopBits = stopBits;
        m_settings.setValue("RS232/StopBits", stopBits);
        emit StopBitsChanged();
    }
}

// Network Getters/Setters
QString Configuration::LocalIP() const {

    return m_localIp;
}
void Configuration::setLocalIP(const QString ip) {
    if (ip != m_localIp) {
        m_localIp = ip;
        m_settings.setValue("Network/LocalIP", ip);
        emit LocalIPChanged();
    }
}

QString Configuration::LocalPort() const {

    return m_localPort;
}
void Configuration::setLocalPort(const QString port) {

    if (port != m_localPort) {
        m_localPort = port;
        m_settings.setValue("Network/LocalPort", port);
        emit LocalPortChanged();
    }
}

QString Configuration::RemoteIP() const {

    return m_remoteIp;
}
void Configuration::setRemoteIP(const QString ip) {

    if (ip != m_remoteIp) {
        m_remoteIp = ip;
        m_settings.setValue("Network/RemoteIP", ip);
        emit RemoteIPChanged();
    }
}

QString Configuration::RemotePort() const {

    return m_remotePort;
}
void Configuration::setRemotePort(const QString port) {
    if (port != m_remotePort) {
        m_remotePort = port;
        m_settings.setValue("Network/RemotePort", port);
        emit RemotePortChanged();
    }
}

// Version Getters/Setters
QString Configuration::DeviceID() const {

    return m_deviceID;
}
void Configuration::setDeviceID(const QString id) {

    if (id != m_deviceID) {
        m_deviceID = id;
        m_settings.setValue("Version/DeviceID", id);
        emit DeviceIDChanged();
    }
}

QString Configuration::SoftwareVersion() const {

    return m_softwareVersion;
}

void Configuration::setSoftwareVersion(const QString version) {

    if (version != m_softwareVersion) {
        m_softwareVersion = version;
        m_settings.setValue("Version/SoftwareVersion", version);
        emit SoftwareVersionChanged();
    }
}

QString Configuration::HardwareVersion() const {

    return m_hardwareVersion;
}
void Configuration::setHardwareVersion(const QString version) {

    if (version != m_hardwareVersion) {
        m_hardwareVersion = version;
        m_settings.setValue("Version/HardwareVersion", version);
        emit HardwareVersionChanged();
    }
}

int Configuration::ThemeIndex() const
{
    return m_themeIndex;
}

void Configuration::setThemeIndex(int themeIndex)
{
    if (themeIndex != m_themeIndex) {
        m_themeIndex = themeIndex;
        m_settings.setValue("Theme/ThemeIndex", themeIndex);
        emit ThemeIndexChanged();
    }
}

int Configuration::LanguageIndex() const
{
    return m_languageIndex;
}

void Configuration::setLanguageIndex(int languageIndex)
{
    if (languageIndex != m_languageIndex) {
        m_languageIndex = languageIndex;
        m_settings.setValue("Language/LanguageIndex", languageIndex);
        emit LanguageIndexChanged();
    }
}

