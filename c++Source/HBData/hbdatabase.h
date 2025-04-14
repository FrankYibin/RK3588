#ifndef HBDATABASE_H
#define HBDATABASE_H

#include <QObject>

class HBDatabase : public QObject
{
    Q_OBJECT
public:
    explicit HBDatabase(QObject *parent = nullptr);

signals:
};

#endif // HBDATABASE_H
