#ifndef DEPTHSAFE_H
#define DEPTHSAFE_H

#include <QObject>

class DepthSafe : public QObject
{
    Q_OBJECT
public:
    explicit DepthSafe(QObject *parent = nullptr);

signals:
};

#endif // DEPTHSAFE_H
