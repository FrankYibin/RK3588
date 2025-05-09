#ifndef DEPTH_H
#define DEPTH_H

#include <QObject>

class Depth : public QObject
{
    Q_OBJECT
public:
    explicit Depth(QObject *parent = nullptr);

signals:
};

#endif // DEPTH_H
