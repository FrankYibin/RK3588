#ifndef HBDATABASE_H
#define HBDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "c++Source/HBDefine.h"

class HBDatabase : public QObject
{
    Q_OBJECT
public:
    explicit HBDatabase(QObject *parent = nullptr);
    ~HBDatabase();

    _Measurements_data queryMeasurementById(int id);
    //wellnum
    _Measurements_data queryWellDataByWellnum(QString wellnum);

    _USER_DATA queryUsertById(int id);

signals:

private:
    void init();  // 初始化数据库连
    void closeTransaction();
    QSqlDatabase m_database;
};

#endif // HBDATABASE_H
