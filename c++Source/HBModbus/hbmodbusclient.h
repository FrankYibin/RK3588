#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>

class HBModbusClient : public QObject
{
    Q_OBJECT
public:
    explicit HBModbusClient(QObject *parent = nullptr);

signals:
};

#endif // HBMODBUSCLIENT_H
