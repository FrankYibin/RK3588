#ifndef DEPTHMETER_H
#define DEPTHMETER_H

#include <QObject>

class DepthMeter : public QObject
{
    Q_OBJECT
public:
    explicit DepthMeter(QObject *parent = nullptr);

signals:
};

#endif // DEPTHMETER_H
