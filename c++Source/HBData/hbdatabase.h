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


    //Depthset

    bool loadDepthSet(_DepthSet &param);
    bool updateDepthSet(const _DepthSet &param);
    Q_INVOKABLE bool updateDepthSetFromInstance();

    //DepthSafe
    bool loadDepthSafe(_DepthSafe &param);
    bool updateDepthSafe(const _DepthSafe &param);
    Q_INVOKABLE bool updateDepthSafeFromInstance();


    //tensionsafe
    bool loadTensionSafe(_TensionSafe &param);
    bool updateTensionSafe(const _TensionSafe &param);
    Q_INVOKABLE bool updateTensionSafeFromInstance();

    //tensionset
    bool loadTensionSet(_TensionSet &param);
    bool updateTensionSet(const _TensionSet &param);
    bool updateTensionSetFromInstance();


    //tensiometer
    // 加载单条 Tensiometer 数据
    bool loadTensiometerData(int id, TensiometerData &data);

    // 插入新的 Tensiometer 数据（返回新 id）
    bool insertTensiometerData(TensiometerData &data);

    // 更新现有 Tensiometer 数据
    bool updateTensiometerData(const TensiometerData &data);

    // 删除 Tensiometer 数据
    bool deleteTensiometerData(int id);

    // 加载所有 Tensiometer 数据（用于列表展示）
    bool loadAllTensiometerData(QList<TensiometerData> &list);



    // 加载某台张力计的所有刻度点
    bool loadScalesForTensiometer(int tensioId,QList<ScaleData> &outRecords);


    // 插入默认的 5 条刻度点（在 addTensiometer 后调用）
    bool insertDefaultScales(int tensioId);


    bool updateTensionScale(int scaleId, int rawValue);


    bool deleteScalesByTensiometerId(int tensioId);





    ///加载历史数据
    QList<HistoryData> loadHistoryData();

    bool insertHistoryData(const ModbusData& modbusData);

    void closeTransaction();


    //test
    bool testUpdate();


signals:

private:
    explicit HBDatabase(QObject *parent = nullptr);
    ~HBDatabase();

private:
    void init();  // 初始化数据库连


    bool isDatabaseReady() const;
    bool beginTransaction();
    bool commitTransaction();

private:
    QSqlDatabase m_database;
};

#endif // HBDATABASE_H
