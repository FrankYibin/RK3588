#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>

class Network : public QObject
{
    Q_OBJECT

    //Ground Gauge

    //Ground Protocol
    Q_PROPERTY(int GProtocol READ GProtocol WRITE setGProtocol NOTIFY GProtocolChanged)

    //Ground Local IP
    Q_PROPERTY(QString GLocalIP READ GLocalIP WRITE setGLocalIP NOTIFY GLocalIPChanged)

    //Ground Local Port
    Q_PROPERTY(QString GLocalPort READ GLocalPort WRITE setGLocalPort NOTIFY GLocalPortChanged)

    //Ground Romote IP
    Q_PROPERTY(QString GRemoteIP READ GRemoteIP WRITE setGRemoteIP NOTIFY GRemoteIPChanged)

    //Ground Romote Port
    Q_PROPERTY(QString GRemotePort READ GRemotePort WRITE setGRemotePort NOTIFY GRemotePortChanged)



    //Cloud Protocol
    Q_PROPERTY(int CProtocol READ CProtocol WRITE setCProtocol NOTIFY CProtocolChanged)

    //Ground Local IP
    Q_PROPERTY(QString CLocalIP READ CLocalIP WRITE setCLocalIP NOTIFY CLocalIPChanged)

    //Ground Local Port
    Q_PROPERTY(QString CLocalPort READ CLocalPort WRITE setCLocalPort NOTIFY CLocalPortChanged)

    //Ground Romote IP
    Q_PROPERTY(QString CRemoteIP READ CRemoteIP WRITE setCRemoteIP NOTIFY CRemoteIPChanged)

    //Ground Local Port
    Q_PROPERTY(QString CRemotePort READ CRemotePort WRITE setCRemotePort NOTIFY CRemotePortChanged)

public:
    explicit Network(QObject *parent = nullptr);

    // 地面网络
    int GProtocol() const;
    void setGProtocol(int value);

    QString GLocalIP() const;
    void setGLocalIP(const QString &value);

    QString GLocalPort() const;
    void setGLocalPort(const QString &value);

    QString GRemoteIP() const;
    void setGRemoteIP(const QString &value);

    QString GRemotePort() const;
    void setGRemotePort(const QString &value);

    // 云端网络
    int CProtocol() const;
    void setCProtocol(int value);

    QString CLocalIP() const;
    void setCLocalIP(const QString &value);

    QString CLocalPort() const;
    void setCLocalPort(const QString &value);

    QString CRemoteIP() const;
    void setCRemoteIP(const QString &value);

    QString CRemotePort() const;
    void setCRemotePort(const QString &value);

signals:

    void GProtocolChanged();
    void GLocalIPChanged();
    void GLocalPortChanged();
    void GRemoteIPChanged();
    void GRemotePortChanged();

    void CProtocolChanged();
    void CLocalIPChanged();
    void CLocalPortChanged();
    void CRemoteIPChanged();
    void CRemotePortChanged();

private:

    int m_gProtocol;
    QString m_gLocalIP;
    QString m_gLocalPort;
    QString m_gRemoteIP;
    QString m_gRemotePort;

    int m_cProtocol;
    QString m_cLocalIP;
    QString m_cLocalPort;
    QString m_cRemoteIP;
    QString m_cRemotePort;


};
#endif // NETWORK_H
