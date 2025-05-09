#include "network.h"

Network::Network(QObject *parent)
    : QObject{parent}
{}


int Network::GProtocol() const {
    return m_gProtocol;
}

void Network::setGProtocol(int value) {

    if (m_gProtocol != value) {
        m_gProtocol = value;
        emit GProtocolChanged();
    }
}

QString Network::GLocalIP() const {
    return m_gLocalIP;
}

void Network::setGLocalIP(const QString &value) {

    if (m_gLocalIP != value) {
        m_gLocalIP = value;
        emit GLocalIPChanged();
    }
}

QString Network::GLocalPort() const {
    return m_gLocalPort;
}

void Network::setGLocalPort(const QString &value) {

    if (m_gLocalPort != value) {
        m_gLocalPort = value;
        emit GLocalPortChanged();
    }
}

QString Network::GRemoteIP() const {
    return m_gRemoteIP;
}

void Network::setGRemoteIP(const QString &value) {

    if (m_gRemoteIP != value) {
        m_gRemoteIP = value;
        emit GRemoteIPChanged();
    }
}

QString Network::GRemotePort() const {
    return m_gRemotePort;
}

void Network::setGRemotePort(const QString &value) {

    if (m_gRemotePort != value) {
        m_gRemotePort = value;
        emit GRemotePortChanged();
    }
}

// Cloud
int Network::CProtocol() const {
    return m_cProtocol;
}

void Network::setCProtocol(int value) {

    if (m_cProtocol != value) {
        m_cProtocol = value;
        emit CProtocolChanged();
    }
}

QString Network::CLocalIP() const {
    return m_cLocalIP;
}

void Network::setCLocalIP(const QString &value) {

    if (m_cLocalIP != value) {
        m_cLocalIP = value;
        emit CLocalIPChanged();
    }
}

QString Network::CLocalPort() const {
    return m_cLocalPort;
}

void Network::setCLocalPort(const QString &value) {

    if (m_cLocalPort != value) {
        m_cLocalPort = value;
        emit CLocalPortChanged();
    }
}

QString Network::CRemoteIP() const {
    return m_cRemoteIP;
}

void Network::setCRemoteIP(const QString &value) {

    if (m_cRemoteIP != value) {
        m_cRemoteIP = value;
        emit CRemoteIPChanged();
    }
}

QString Network::CRemotePort() const {
    return m_cRemotePort;
}

void Network::setCRemotePort(const QString &value) {

    if (m_cRemotePort != value) {
        m_cRemotePort = value;
        emit CRemotePortChanged();
    }
}
