#ifndef HBDATABASE_H
#define HBDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "c++Source/HBDefine.h"
#include "c++Source/HBScreen/tensiometer.h"
#include "c++Source/HBScreen/historyoperationmodel.h"

class HBDatabase : public QObject
{
    Q_OBJECT
public:
    static HBDatabase& GetInstance();
    HBDatabase(const HBDatabase&) = delete;
    HBDatabase& operator=(const HBDatabase&) = delete;

    //wellparameter
    void loadDataFromDatabase();

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
    bool InsertNewTensiometer(Tensiometer::TENSIONMETER &meter);

    // 更新现有 Tensiometer 数据
    bool updateTensiometerData(const TensiometerData &data);

    // 删除 Tensiometer 数据
    bool deleteTensiometerData(int id);

    // 加载所有 Tensiometer 数据（用于列表展示）
    bool LoadTensiometerTable(QList<Tensiometer::TENSIONMETER> &list);



    // 加载某台张力计的所有刻度点
    bool LoadScales(const int tensioNumber, QString& scale);

    bool deleteScalesByTensiometerId(int tensioId);



    // 插入默认的 5 条刻度点（在 addTensiometer 后调用）
    bool insertDefaultScales(QString &tensiometerNumber);


    bool updateTensionScale(int scaleId, int rawValue);

    bool updateScaleJson(const int tensiometerNumber, const QString scaleJson);


    bool deleteScalesByTensiometerId(const QString &tensioNumber);

    ///加载历史数据
    QList<HistoryData> loadHistoryData();

    QList<HistoryData> loadHistoryData(const QDateTime& start,
                                       const QDateTime& end);

    bool insertHistoryData(const ModbusData& modbusData);

    void closeTransaction();

    //historyoperate
    QList<HistoryOperationModel::Row>
    loadOperationData(const QDateTime &start, const QDateTime &end);
    QList<HistoryOperationModel::Row> loadAllOperationData();

    bool LoadGraphPoints(const QDateTime start, const QDateTime end, QList<QDateTime> &timePoints, QList<qreal> &depthPoints, QList<qreal> &velocityPoints, QList<qreal> &tensionPoints, QList<qreal> &tensionDeltaPoints);

    QVector<QPointF> historyPoints(const QString& fieldName,
                                   const QDateTime& start,
                                   const QDateTime& end) const;

    QVector<UserInfo> LoadAllUsers();
    bool QueryUser(QString& username, QString& password, int &groupindex, QString& nickname);
    bool QueryUser(const QString username, const QString password, int &groupId);
    bool InsertUser(const QString username, const QString password, const int groupindex, const QString nickname);
    bool UpdateUser(const QString oldUserName, const QString newUserName, const QString password, const int groupindex, const QString nickname);

    bool deleteUserByName(const QString &username);

    //
    bool getUnitSettings(UnitSettings &settings);
    Q_INVOKABLE bool updateTensionUnit(int tensionUnit);

    Q_INVOKABLE bool updateDepthUnit(int depthUnit);
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
