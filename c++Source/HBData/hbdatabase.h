#ifndef HBDATABASE_H
#define HBDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "c++Source/HBDefine.h"

class HBDatabase : public QObject
{
    Q_OBJECT
public:
    static HBDatabase& getInstance();
    HBDatabase(const HBDatabase&) = delete;
    HBDatabase& operator=(const HBDatabase&) = delete;


    _Measurements_data queryMeasurementById(int id);
    //wellnum
    _Measurements_data queryWellDataByWellnum(QString wellnum);

    _USER_DATA queryUsertById(int id);


   //wellparameter
    void loadDataFromDatabase();
    bool loadWellParameter(_WellParameter &param);
    Q_INVOKABLE bool updateWellParameterFromInstance();
    bool updateWellParameter(const _WellParameter &param);

    //test
    bool testUpdate();


signals:

private:
    explicit HBDatabase(QObject *parent = nullptr);
    ~HBDatabase();

private:
    void init();  // 初始化数据库连
    void closeTransaction();
    QSqlDatabase m_database;
};

#endif // HBDATABASE_H
