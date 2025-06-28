#include "hbdatabase.h"
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include "c++Source/HBDefine.h"
#include "c++Source/HBScreen/depthsetting.h"
#include "c++Source/HBScreen/depthsiman.h"
#include "c++Source/HBScreen/hbhome.h"
#include "c++Source/HBScreen/tensionsafety.h"
#include "c++Source/HBScreen/tensionsetting.h"
#include "c++Source/HBScreen/wellparameter.h"
#include "c++Source/HBScreen/usermanagermodel.h"
#include <QVariant>
#include <QDir>
#include <QFile>

HBDatabase::HBDatabase(QObject *parent)
    : QObject{parent}
{
    init();
}

HBDatabase::~HBDatabase()
{

    closeTransaction();
}

void HBDatabase::init()
{
    QDir execDir(QCoreApplication::applicationDirPath());
    QString dbPath = execDir.filePath("DVTT.db");

    if (!QFile::exists(dbPath)) {
        QString srcPath = execDir.absoluteFilePath("../DVTT.db");
        if (QFile::exists(srcPath)) {
            qDebug() << "Copying DVTT.db from" << srcPath << "to" << dbPath;
            if (!QFile::copy(srcPath, dbPath)) {
                qWarning() << "Failed to copy database file from" << srcPath << "to" << dbPath;
                return;
            }
        } else {
            qWarning() << "Source database file not found at" << srcPath;
            return;
        }
    }

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbPath);

    if (!m_database.open()) {
        qWarning() << "Database open failed:" << m_database.lastError();
        return;
    }

    qDebug() << "Database opened successfully at" << dbPath;

}

bool HBDatabase::beginTransaction()
{
    if (!m_database.transaction()) {
        qDebug() << "Failed to start transaction:" << m_database.lastError();
        return false;
    }
    return true;
}

bool HBDatabase::commitTransaction()
{
    if (!m_database.commit()) {
        qDebug() << "Failed to commit transaction:" << m_database.lastError();
        return false;
    }
    return true;
}

void HBDatabase::closeTransaction()
{
    if (m_database.isOpen()) {
        m_database.close();
        qDebug() << "Database closed successfully";
    }

}

QList<HistoryOperationModel::Row> HBDatabase::loadOperationData(const QDateTime &start, const QDateTime &end)
{
    QList<HistoryOperationModel::Row> list;

    if (!m_database.isOpen()) {
        qWarning() << "DB not open";
        return list;
    }

    static const char *sql =
        "SELECT well_number, work_type, username, datetime, operate "
        "FROM operating_data "
        "WHERE datetime(datetime) BETWEEN datetime(:start) AND datetime(:end) "
        "ORDER BY datetime(datetime) ASC";

    QSqlQuery q(m_database);
    if (!q.prepare(sql)) {
        qWarning() << q.lastError();
        return list;
    }

    q.bindValue(":start", start.toString("yyyy-MM-dd HH:mm:ss"));
    q.bindValue(":end",   end.toString("yyyy-MM-dd HH:mm:ss"));

    if (!q.exec()) {
        qWarning() << q.lastError();
        return list;
    }

    int idx = 0;
    while (q.next()) {
        HistoryOperationModel::Row r;
        r.index       = ++idx;
        r.wellNumber  = q.value("well_number").toString();
        r.operateType = q.value("work_type").toString();
        r.operater    = q.value("username").toString();
        r.date        = QDateTime::fromString(
            q.value("datetime").toString(),
            "yyyy-MM-dd HH:mm:ss");
        r.description = q.value("operate").toString();
        list.append(r);
    }
    return list;

}

QList<HistoryOperationModel::Row> HBDatabase::loadAllOperationData()
{
    QList<HistoryOperationModel::Row> list;

    if (!m_database.isOpen()) {
        qWarning() << "DB not open";
        return list;
    }

    QSqlQuery q(m_database);
    QString sql = R"(
        SELECT well_number, work_type, username, datetime, operate
        FROM operating_data
        ORDER BY datetime(datetime) ASC
    )";

    if (!q.exec(sql)) {
        qWarning() << q.lastError();
        return list;
    }

    int idx = 0;
    while (q.next()) {
        HistoryOperationModel::Row r;
        r.index       = ++idx;
        r.wellNumber  = q.value("well_number").toString();
        r.operateType = q.value("work_type").toString();
        r.operater    = q.value("username").toString();
        r.date        = QDateTime::fromString(
            q.value("datetime").toString(),
            "yyyy-MM-dd HH:mm:ss");
        r.description = q.value("operate").toString();
        list.append(r);
    }
    return list;

}

bool HBDatabase::insertOperationLog(const QString operateText)
{
    if (!m_database.isOpen()) {
        qWarning() << "Database not open";
        return false;
    }

    QString username = UserManagerModel::GetInstance().CurrentUser();
    QString datetime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    QSqlQuery query(m_database);
    query.prepare(R"(
        INSERT INTO operating_data (username, datetime, operate)
        VALUES (?, ?, ?)
    )");
    query.addBindValue(username);
    query.addBindValue(datetime);
    query.addBindValue(operateText);

    if (!query.exec()) {
        qWarning() << "insertOperationLog insert fail:" << query.lastError().text();
        return false;
    }

    return true;
}

HBDatabase &HBDatabase::GetInstance()
{
    static HBDatabase instance;
    return instance;
}

void HBDatabase::loadDataFromDatabase()
{
    _DepthSet deptParam;
    bool success = HBDatabase::GetInstance().loadDepthSet(deptParam);
    if (success) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    _DepthSafe dsParam;
    bool ds_ok = HBDatabase::GetInstance().loadDepthSafe(dsParam);
    if (ds_ok) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    _TensionSafe tsParam;
    bool tsp_ok = HBDatabase::GetInstance().loadTensionSafe(tsParam);
    if (tsp_ok) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    _TensionSet setParam;
    bool set_ok = HBDatabase::GetInstance().loadTensionSet(setParam);
    if (set_ok) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    UnitSettings setUint;

    bool set_Unit = HBDatabase::GetInstance().getUnitSettings(setUint);
    if (set_Unit) {
        qDebug() << "set_Unit loaded successfully!";
    } else {
        qDebug() << "Failed to load set_Unit from DB.";
    }
}

bool HBDatabase::loadDepthSet(_DepthSet &param)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM depthset LIMIT 1");

    if (!query.exec()) {
        qDebug() << "Load failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No data found in depthset table";
        return false;
    }

    param.id = query.value("id").toInt();
    param.targetLayerDepth = query.value("targetLayerDepth").toInt();
    param.depthOrientation = query.value("depthOrientation").toInt();
    param.meterDepth = query.value("meterDepth").toInt();
    param.depthCalculateType = query.value("depthCalculateType").toInt();
    param.codeOption = query.value("codeOption").toInt();
    param.pulse = query.value("pulse").toInt();

    DepthSetting* ds = DepthSetting::GetInstance();
    HBHome* hs = HBHome::GetInstance();

    ds->setDepthTargetLayer(param.targetLayerDepth);
    ds->setDepthOrientation(param.depthOrientation);
    ds->setDepthSurfaceCover(param.meterDepth);
    ds->setDepthEncoder(param.depthCalculateType);
    hs->setPulseCount(param.pulse);

    return true;
}

bool HBDatabase::updateDepthSet(const _DepthSet &param)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE depthset SET
            targetLayerDepth = :targetLayerDepth,
            depthOrientation = :depthOrientation,
            meterDepth = :meterDepth,
            depthCalculateType = :depthCalculateType,
            codeOption = :codeOption,
            pulse = :pulse
        WHERE id = :id
    )");

    query.bindValue(":targetLayerDepth", param.targetLayerDepth);
    query.bindValue(":depthOrientation", param.depthOrientation);
    query.bindValue(":meterDepth", param.meterDepth);
    query.bindValue(":depthCalculateType", param.depthCalculateType);
    query.bindValue(":codeOption", param.codeOption);
    query.bindValue(":pulse", param.pulse);
    query.bindValue(":id", param.id);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "DepthSet update successful";
    return true;
}

bool HBDatabase::updateDepthSetFromInstance()
{
    DepthSetting* ds = DepthSetting::GetInstance();
    HBHome* hs = HBHome::GetInstance();

    _DepthSet param;
    param.id = 1;
    param.targetLayerDepth = ds->DepthTargetLayer();
    param.depthOrientation = ds->DepthOrientation();
    param.meterDepth = ds->DepthSurfaceCover();
    param.depthCalculateType = ds->DepthEncoder();
    // param.codeOption = ds->CodeOption();
    param.pulse = hs->PulseCount();

    return updateDepthSet(param);
}

bool HBDatabase::loadDepthSafe(_DepthSafe &param)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM depthsafe LIMIT 1");

    if (!query.exec()) {
        qDebug() << "Load failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No data found in depthsafe table";
        return false;
    }

    param.id = query.value("id").toInt();
    param.depthPreset = query.value("depthPreset").toInt();
    param.wellWarnig = query.value("wellWarnig").toInt();
    param.brake = query.value("brake").toInt();
    param.velocityLimit = query.value("velocityLimit").toInt();
    param.depthWarning = query.value("depthWarning").toInt();
    param.totalDepth = query.value("totalDepth").toInt();
    param.depthBrake = query.value("depthBrake").toInt();


    DepthSiMan* ds = DepthSiMan::GetInstance();

    // ds->setDepthPreset(param.depthPreset);
    // ds->setWellWarnig(param.wellWarnig);
    // ds->setBrake(param.brake);
    ds->setVelocitySiman(param.velocityLimit);
    // ds->setDepthWarning(param.depthWarning);
    // ds->setTotalDepth(param.totalDepth);
    // ds->setDepthBrake(param.depthBrake);

    return true;
}

bool HBDatabase::updateDepthSafe(const _DepthSafe &param)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE depthsafe SET
            depthPreset = :depthPreset,
            wellWarnig = :wellWarnig,
            brake = :brake,
            velocityLimit = :velocityLimit,
            depthWarning = :depthWarning,
            totalDepth = :totalDepth,
            depthBrake = :depthBrake,
            depthVelocityLimit = :depthVelocityLimit
        WHERE id = :id
    )");

    query.bindValue(":depthPreset", param.depthPreset);
    query.bindValue(":wellWarnig", param.wellWarnig);
    query.bindValue(":brake", param.brake);
    query.bindValue(":velocityLimit", param.velocityLimit);
    query.bindValue(":depthWarning", param.depthWarning);
    query.bindValue(":totalDepth", param.totalDepth);
    query.bindValue(":depthBrake", param.depthBrake);
    query.bindValue(":id", param.id);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "DepthSafe update successful";
    return true;
}

bool HBDatabase::updateDepthSafeFromInstance()
{
    DepthSiMan* ds = DepthSiMan::GetInstance();

    _DepthSafe param;
    param.id = 1;
    // param.depthPreset = ds->DepthPreset();
    // param.wellWarnig = ds->WellWarnig();
    // param.brake = ds->Brake();
    param.velocityLimit = ds->VelocitySiman();
    // param.depthWarning = ds->DepthWarning();
    // param.totalDepth = ds->TotalDepth();
    // param.depthBrake = ds->DepthBrake();

    return updateDepthSafe(param);
}

bool HBDatabase::loadTensionSafe(_TensionSafe &param)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM tensionsafe LIMIT 1");

    if (!query.exec()) {
        qDebug() << "Load failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No data found in tensionsafe table";
        return false;
    }

    param.id = query.value("id").toInt();
    param.wellType = query.value("wellType").toString();
    param.maxTension = query.value("maxTension").toInt();
    param.weakForce = query.value("weakForce").toString();
    param.tensionSafeFactor = query.value("tensionSafeFactor").toString();

    TensionSafety* ts = TensionSafety::GetInstance();
    HBHome* hs = HBHome::GetInstance();

    hs->setTensionLimited(param.maxTension);
    ts->setBreakingForceWeakness(param.weakForce);
    ts->setTensionSafetyCoefficient(param.tensionSafeFactor);

    return true;
}

bool HBDatabase::updateTensionSafe(const _TensionSafe &param)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE tensionsafe SET
            wellType = :wellType,
            maxTension = :maxTension,
            weakForce = :weakForce,
            tensionSafeFactor = :tensionSafeFactor
        WHERE id = :id
    )");

    query.bindValue(":wellType", param.wellType);
    query.bindValue(":maxTension", param.maxTension);
    query.bindValue(":weakForce", param.weakForce);
    query.bindValue(":tensionSafeFactor", param.tensionSafeFactor);
    query.bindValue(":id", param.id);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "TensionSafe update successful";
    return true;
}

bool HBDatabase::updateTensionSafeFromInstance()
{
    TensionSafety* ts = TensionSafety::GetInstance();
    HBHome* hs = HBHome::GetInstance();

    _TensionSafe param;
    param.id = 1;
    // param.wellType = ts->WellType();
    param.maxTension = hs->TensionLimited();
    param.weakForce = ts->BreakingForceWeakness();
    param.tensionSafeFactor = ts->TensionSafetyCoefficient();

    return updateTensionSafe(param);
}

bool HBDatabase::loadTensionSet(_TensionSet &param)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM tensionset LIMIT 1");

    if (!query.exec()) {
        qDebug() << "Load failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No data found in tensionset table";
        return false;
    }

    param.id = query.value("id").toInt();
    param.kValue = query.value("kValue").toInt();
    param.tensionUnit = query.value("tensionUnit").toInt();

    Tensiometer* ts = Tensiometer::GetInstance();
    HBHome* hs = HBHome::GetInstance();
    // hs->setKValue(param.kValue);
    // ts->setTensionUnits(param.tensionUnit);

    return true;
}

bool HBDatabase::updateTensionSet(const _TensionSet &param)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE tensionset SET
            kValue = :kValue,
            tensionUnit = :tensionUnit
        WHERE id = :id
    )");

    query.bindValue(":kValue", param.kValue);
    query.bindValue(":tensionUnit", param.tensionUnit);
    query.bindValue(":id", param.id);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "TensionSet update successful";
    return true;
}

bool HBDatabase::updateTensionSetFromInstance()
{
    TensionSetting* ts = TensionSetting::GetInstance();
    HBHome* hs = HBHome::GetInstance();

    _TensionSet param;
    param.id = 1;
    param.kValue = hs->KValue();
    param.tensionUnit = ts->TensionUnit();

    return updateTensionSet(param);
}

// 加载单条数据
bool HBDatabase::loadTensiometerData(int id, TensiometerData &data)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM tensiometer WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Load tensiometer data failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No tensiometer data found for id:" << id;
        return false;
    }

    data.id = query.value("id").toInt();
    data.tensiometerNumber = query.value("tensiometerNumber").toString();
    data.tensiometerType = query.value("tensiometerType").toInt();
    data.tensiometerRange = query.value("tensiometerRange").toInt();
    data.tensiometerSignal = query.value("tensiometerSignal").toInt();

    return true;
}

// 插入新数据（自动生成 ID）
bool HBDatabase::InsertNewTensiometer(Tensiometer::TENSIONMETER &meter)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
        INSERT INTO tensiometer (Number, Type, Range, Signal, Scale)
        VALUES (:Number, :Type, :Range, :Signal, :Scale)
    )");

    query.bindValue(":Number",  meter.Number);
    query.bindValue(":Type",    meter.Encoder);
    query.bindValue(":Range",   meter.Range);
    query.bindValue(":Signal",  meter.Analog);
    query.bindValue(":Scale",   meter.Scale);

    if (!query.exec()) {
        qDebug() << "Insert tensiometer data failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    int id = query.lastInsertId().toInt();
    if (!commitTransaction())
        return false;
    qDebug() << "Insert tensiometer data successful, id:" << id;
    return true;
}

// 更新数据
bool HBDatabase::updateTensiometerData(const TensiometerData &data)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE tensiometer SET
            tensiometerNumber = :tensiometerNumber,
            tensiometerType = :tensiometerType,
            tensiometerRange = :tensiometerRange,
            tensiometerSignal = :tensiometerSignal
        WHERE id = :id
    )");

    query.bindValue(":tensiometerNumber", data.tensiometerNumber);
    query.bindValue(":tensiometerType", data.tensiometerType);
    query.bindValue(":tensiometerRange", data.tensiometerRange);
    query.bindValue(":tensiometerSignal", data.tensiometerSignal);
    query.bindValue(":id", data.id);

    if (!query.exec()) {
        qDebug() << "Update tensiometer data failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No tensiometer data updated (id not found):" << data.id;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "Update tensiometer data successful";
    return true;
}

// 删除数据
bool HBDatabase::deleteTensiometerData(int number)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare("DELETE FROM tensiometer WHERE Number = :Number");
    query.bindValue(":Number", number);

    if (!query.exec()) {
        qDebug() << "Delete tensiometer data failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No tensiometer data deleted (meter not found): " << number;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "Delete tensiometer data successful";
    return true;
}

// 加载全部数据
bool HBDatabase::LoadTensiometerTable(QList<Tensiometer::TENSIONMETER> &list)
{
    list.clear();
    QSqlQuery query(m_database);
    if (!query.exec("SELECT * FROM tensiometer")) {
        qDebug() << "Load all tensiometer data failed:" << query.lastError();
        return false;
    }

    while (query.next()) {
        Tensiometer::TENSIONMETER data;
        data.Number = query.value("Number").toInt();
        data.Encoder = query.value("Type").toInt();
        data.Range = query.value("Range").toInt();
        data.Analog = query.value("Signal").toInt();
        data.Scale = query.value("Scale").toString();
        list.append(data);
    }

    qDebug() << "Loaded" << list.size() << "tensiometer records.";
    return true;
}

bool HBDatabase::LoadScales(const int tensioNumber, QString& scale)
{
    QSqlQuery q(m_database);
    q.prepare(R"SQL(
              SELECT Scale
              FROM tensiometer
              WHERE Number = ?
              )SQL");
    q.addBindValue(tensioNumber);
    if (!q.exec()) {
        qWarning() << "Failed to load scales for tensiometer_number" << tensioNumber
                   << ":" << q.lastError().text();
        return false;
    }
    while (q.next()) {
        scale = q.value(0).toString();
    }
    return true;
}

bool HBDatabase::deleteScalesByTensiometerId(int tensioId)
{
    QSqlQuery q(m_database);
    q.prepare(R"SQL(
              DELETE FROM tension_scale
              WHERE tensiometer_id = ?
              )SQL");
    q.addBindValue(tensioId);
    if (!q.exec()) {
        qWarning() << "Failed to delete scales for tensioId" << tensioId
                   << ":" << q.lastError().text();
        return false;
    }
    return true;
}

//// 插入默认的 5 条刻度点
bool HBDatabase::insertDefaultScales(QString &tensiometerNumber)
{
    QSqlQuery q(m_database);
    q.prepare(R"SQL(
              INSERT INTO tension_scale
              (tensiometer_number, point_index, scale_value, tension_value)
              VALUES (?, ?, ?, ?)
              )SQL");
    for (int i = 1; i <= 5; ++i) {
        q.bindValue(0, tensiometerNumber);
        q.bindValue(1, i);
        q.bindValue(2, i * 100);   // 默认刻度值 ×100 存储
        q.bindValue(3, 0);         // 默认张力值 0
        if (!q.exec()) {
            qWarning() << "Failed to insert default scale for tensiometer_number" << tensiometerNumber
                       << "point" << i << ":" << q.lastError().text();
            return false;
        }
    }

    return true;
}

////  更新某条刻度的张力值
bool HBDatabase::updateTensionScale(int scaleId, int rawValue)
{
    QSqlQuery q(m_database);
    q.prepare(R"SQL(
              UPDATE tension_scale
              SET tension_value = ?
              WHERE id = ?
              )SQL");
    q.addBindValue(rawValue);
    q.addBindValue(scaleId);
    if (!q.exec()) {
        qWarning() << "Failed to update tension_scale id" << scaleId
                   << ":" << q.lastError().text();
        return false;
    }
    return true;
}

bool HBDatabase::updateScaleJson(const int tensiometerNumber, const QString scaleJson)
{

    QSqlQuery query;
    query.prepare(R"(UPDATE tensiometer SET Scale = :scale WHERE Number = :num)");
    query.bindValue(":scale", scaleJson);
    query.bindValue(":num", tensiometerNumber);


    bool success = query.exec();
    if (!success) {
        qWarning() << " Failed to update scale value in DB:"
                   << query.lastError().text()
                   << "\nQuery:" << query.lastQuery();
    }
    return success;
}

// 删除某台张力计的所有刻度点
bool HBDatabase::deleteScalesByTensiometerId( const QString &tensioNumber)
{
    QSqlQuery q(m_database);
    q.prepare(R"SQL(
              DELETE FROM tension_scale
              WHERE tensiometer_number  = ?
              )SQL");
    q.addBindValue(tensioNumber);
    if (!q.exec()) {
        qWarning() << "Failed to delete scales for tensioNumber" << tensioNumber
                   << ":" << q.lastError().text();
        return false;
    }
    return true;
}

QList<HistoryData> HBDatabase::loadHistoryData()
{
    QList<HistoryData> dataList;

    if (!m_database.isOpen()) {
        qDebug() << "Database is not open!";
        return dataList;
    }

    QSqlQuery query(m_database);

    QString sql = "SELECT wellNumber, date, operateType, operater, depth, velocity, velocityUnit, "
                  "tensions, tensionIncrement, tensionUnit, maxTension, harnessTension, safetyTension, exception "
                  "FROM history_table";

    if (!query.exec(sql)) {
        qDebug() << "Failed to load history data:" << query.lastError();
        return dataList;
    }

    while (query.next()) {
        HistoryData item;
        item.wellNumber = query.value("wellNumber").toString();
        //        item.date = query.value("date").toString();
        QString fullDate = query.value("date").toString();
        item.operateType = query.value("operateType").toString();
        item.operater = query.value("operater").toString();
        item.depth = query.value("depth").toString();
        item.velocity = query.value("velocity").toString();
        item.velocityUnit = query.value("velocityUnit").toString();
        item.tensions = query.value("tensions").toString();
        item.tensionIncrement = query.value("tensionIncrement").toString();
        item.tensionUnit = query.value("tensionUnit").toString();
        item.maxTension = query.value("maxTension").toString();
        item.harnessTension = query.value("harnessTension").toString();
        item.safetyTension = query.value("safetyTension").toString();
        item.exception = query.value("exception").toString();

        dataList.append(item);
    }

    return dataList;
}

QList<HistoryData> HBDatabase::loadHistoryData(const QDateTime &start, const QDateTime &end)
{
    QList<HistoryData> dataList;

    if (!m_database.isOpen()) {
        qWarning() << "HBDatabase::loadHistoryData - database not open";
        return dataList;
    }

    const char* sql =
        "SELECT wellNumber, date, operateType, operater, depth, velocity, "
        "velocityUnit, tensions, tensionIncrement, tensionUnit, maxTension, "
        "harnessTension, safetyTension, exception "
        "FROM history_table "
        "WHERE datetime(date) BETWEEN datetime(:start) AND datetime(:end) "
        "ORDER BY datetime(date) ASC";    //DESC

    QSqlQuery query(m_database);

    if (!query.prepare(sql)) {
        qWarning() << "HBDatabase::loadHistoryData - prepare failed:"
                   << query.lastError();
        return dataList;
    }

    query.bindValue(":start", start.toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":end",   end.toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        qWarning() << "HBDatabase::loadHistoryData - exec failed:"
                   << query.lastError();
        return dataList;
    }


    while (query.next()) {
        HistoryData item;
        item.wellNumber         = query.value("wellNumber").toString();

        item.date               = query.value("date").toString();
        item.operateType        = query.value("operateType").toString();
        item.operater           = query.value("operater").toString();
        item.depth              = query.value("depth").toString();
        item.velocity           = query.value("velocity").toString();
        item.velocityUnit       = query.value("velocityUnit").toString();
        item.tensions           = query.value("tensions").toString();
        item.tensionIncrement   = query.value("tensionIncrement").toString();
        item.tensionUnit        = query.value("tensionUnit").toString();
        item.maxTension         = query.value("maxTension").toString();
        item.harnessTension     = query.value("harnessTension").toString();
        item.safetyTension      = query.value("safetyTension").toString();
        item.exception          = query.value("exception").toString();

        dataList.push_front(item);
    }

    return dataList;

}

bool HBDatabase::insertHistoryData(const ModbusData& modbusData)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
    QSqlQuery query(m_database);
    QString sql = "INSERT INTO history_table (wellNumber, date, operateType, operater, depth, velocity, "
                  "velocityUnit, tensions,tensionIncrement, tensionUnit, maxTension, harnessTension, safetyTension, exception) "
                  "VALUES (:wellNumber, :date, :operateType, :operater, :depth, :velocity, "
                  ":velocityUnit, :tensions,:tensionIncrement,:tensionUnit, :maxTension, :harnessTension, :safetyTension, :exception)";
    query.prepare(sql);
    query.bindValue(":wellNumber", modbusData.wellNumber);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    query.bindValue(":date", timestamp);
    query.bindValue(":operateType", modbusData.operateType);
    query.bindValue(":operater", modbusData.operater);
    query.bindValue(":depth", modbusData.depth);
    query.bindValue(":velocity", modbusData.velocity);
    switch(DepthSetting::GetInstance()->VelocityUnit())
    {
    case DepthSetting::FT_PER_HOUR:
        query.bindValue(":velocityUnit", "ft/h");
        break;
    case DepthSetting::FT_PER_MIN:
        query.bindValue(":velocityUnit", "ft/min");
        break;
    case DepthSetting::M_PER_HOUR:
        query.bindValue(":velocityUnit", "m/h");
        break;
    case DepthSetting::M_PER_MIN:
        query.bindValue(":velocityUnit", "m/min");
        break;
    default:
        query.bindValue(":velocityUnit", "m/h");
        break;
    }
    query.bindValue(":tensions", modbusData.tensions);
    query.bindValue(":tensionIncrement", modbusData.tensionIncrement);
    switch(TensionSetting::GetInstance()->TensionUnit())
    {
    case TensionSetting::KG:
        query.bindValue(":tensionUnit", "kg");
        break;
    case TensionSetting::KN:
        query.bindValue(":tensionUnit", "kn");
        break;
    case TensionSetting::LB:
        query.bindValue(":tensionUnit", "lb");
        break;
    default:
        query.bindValue(":tensionUnit", "lb");
        break;
    }
    query.bindValue(":maxTension", modbusData.maxTension);
    query.bindValue(":harnessTension", modbusData.harnessTension);
    query.bindValue(":safetyTension", modbusData.safetyTension);
    query.bindValue(":exception", "无");

    // 执行插入
    if (!query.exec()) {
        qDebug() << "Failed to insert data:" << query.lastError();
        return false;
    }
    return true;
}

bool HBDatabase::LoadGraphPoints(const QDateTime start, const QDateTime end,
                                 QList<QDateTime>& timePoints, QList<qreal>& depthPoints,
                                 QList<qreal>& velocityPoints, QList<qreal>& tensionPoints,
                                 QList<qreal>& tensionDeltaPoints)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
    timePoints.clear();
    depthPoints.clear();
    velocityPoints.clear();
    tensionPoints.clear();
    tensionDeltaPoints.clear();

    const char* sql =
        "SELECT date, depth, velocity, velocityUnit, tensions, tensionIncrement, tensionUnit "
        "FROM history_table "
        "WHERE (datetime(date) BETWEEN datetime(:start) AND datetime(:end)) AND velocityUnit = :velocityUnit "
        "AND tensionUnit = :tensionUnit "
        "ORDER BY datetime(date) ASC";

    QSqlQuery query(m_database);

    if (!query.prepare(sql)) {
        qWarning() << "HBDatabase::loadGraphData - prepare failed:"
                   << query.lastError();
        return false;
    }

    query.bindValue(":start", start.toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":end",   end.toString("yyyy-MM-dd HH:mm:ss"));
    switch(DepthSetting::GetInstance()->VelocityUnit())
    {
    case DepthSetting::M_PER_HOUR:
        query.bindValue(":velocityUnit", "m/h");
        break;
    case DepthSetting::M_PER_MIN:
        query.bindValue(":velocityUnit", "m/min");
        break;
    case DepthSetting::FT_PER_HOUR:
        query.bindValue(":velocityUnit", "ft/h");
        break;
    case DepthSetting::FT_PER_MIN:
        query.bindValue(":velocityUnit", "ft/min");
        break;
    default:
        query.bindValue(":velocityUnit", "m/h");
        break;
    }

    switch(TensionSetting::GetInstance()->TensionUnit())
    {
    case TensionSetting::LB:
        query.bindValue(":tensionUnit", "lb");
        break;
    case TensionSetting::KG:
        query.bindValue(":tensionUnit", "kg");
        break;
    case TensionSetting::KN:
        query.bindValue(":tensionUnit", "kn");
        break;
    default:
        query.bindValue(":tensionUnit", "lb");
        break;
    }

    if (!query.exec()) {
        qWarning() << "HBDatabase::loadGraphData - exec failed:"
                   << query.lastError();
        return false;
    }
    QString str = "";
    QDateTime date;
    QString depth = "";
    QString velocity = "";
    QString tension = "";
    QString tensionDelta = "";

    while (query.next())
    {
        str = query.value("date").toString();
        date = QDateTime::fromString(str, "yyyy-MM-dd HH:mm:ss");
        timePoints.append(date);
        depth       = query.value("depth").toString();
        velocity    = query.value("velocity").toString();
        str         = query.value("velocityUnit").toString();

        depthPoints.append(depth.toDouble());
        velocityPoints.append(velocity.toDouble());
        tension         = query.value("tensions").toString();
        tensionDelta    = query.value("tensionIncrement").toString();
        str             = query.value("tensionUnit").toString();

        tensionPoints.append(tension.toDouble());
        tensionDeltaPoints.append(tensionDelta.toDouble());
    }
    return true;
}

QVector<UserInfo> HBDatabase::LoadAllUsers()
{
    QVector<UserInfo> users;

    const char* sql = "SELECT username, nickname, groupindex, createtime FROM userinfo WHERE groupindex != :groupindex";
    QSqlQuery query(m_database);
    if (!query.prepare(sql)) {
        qWarning() << "users::loadallusers - prepare failed:"
                   << query.lastError();
        return users;
    }
    query.bindValue(":groupindex", static_cast<int>(-1)); //SuperUser
    if (!query.exec()) { // 关键：必须exec
        qWarning() << "users::loadallusers - exec failed:"
                   << query.lastError();
        return users;
    }
    while (query.next()) {
        UserInfo user;
        user.userName = query.value(0).toString();
        user.nickName = query.value(1).toString();
        user.groupIndex = query.value(2).toInt();
        user.createTime = query.value(3).toString().left(10);
        user.userHandleVisible = true;
        users.append(user);
    }
    return users;

}

bool HBDatabase::QueryUser(QString &username, QString &password, int &groupindex, QString &nickname)
{
    bool bResult = false;
    QSqlQuery query(m_database);
    query.prepare("SELECT username, groupindex, nickname, password, createtime FROM userinfo WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Query user data failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No user data found for username:" << username;
        return false;
    }

    username = query.value(0).toString();
    groupindex = query.value(1).toInt();
    nickname = query.value(2).toString();
    password = query.value(3).toString();
    bResult = true;
    return bResult;
}

bool HBDatabase::QueryUser(const QString username, const QString password, int& groupId)
{
    bool bResult = false;
    QSqlQuery query(m_database);
    query.prepare("SELECT username, password, groupindex, createtime FROM userinfo WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Query user data failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No user data found for username:" << username;
        return false;
    }
    else
    {
        groupId = query.value(2).toInt();
    }

    bResult = true;
    return bResult;
}

bool HBDatabase::QueryUser(const QString username, int &groupId)
{
    bool bResult = false;
    QSqlQuery query(m_database);
    query.prepare("SELECT username, password, groupindex, createtime FROM userinfo WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Query user data failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No user data found for username:" << username;
        return false;
    }
    else
    {
        groupId = query.value(2).toInt();
    }

    bResult = true;
    return bResult;
}

bool HBDatabase::InsertUser(const QString username, const QString password, const int groupindex, const QString nickname)
{
    QSqlQuery query;
    query.prepare("INSERT INTO userinfo (username,password,groupindex,nickname)"
                  "VALUES(:username, :password, :groupindex, :nickname)");

    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":groupindex", groupindex);
    query.bindValue(":nickname", nickname);

    if (!query.exec()) {
        qWarning() << "insert fial:" << query.lastError().text();
        return false;
    }

    return true;

}

bool HBDatabase::UpdateUser(const QString oldUserName, const QString newUserName, const QString password, const int groupindex, const QString nickname)
{
    QSqlQuery query;
    query.prepare("UPDATE userinfo SET username = :newUserName, password = :password, groupindex = :groupindex, nickname = :nickname WHERE username = :oldUserName");
    query.bindValue(":oldUserName", oldUserName);
    query.bindValue(":newUserName", newUserName);
    query.bindValue(":password", password);
    query.bindValue(":groupindex", groupindex);
    query.bindValue(":nickname", nickname);

    if (!query.exec()) {
        qWarning() << "Update user failed:" << query.lastError().text();
        return false;
    }

    return true;;
}

bool HBDatabase::deleteUserByName(const QString &username)
{
    QSqlQuery query;
    query.prepare("DELETE FROM userinfo WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qWarning() << "Delete user failed:" << query.lastError().text();
        return false;
    }
    return true;

}

bool HBDatabase::getUnitSettings(UnitSettings &settings) {

    QSqlQuery query("SELECT tension_unit, depth_unit FROM unit_settings WHERE id = 1");
    if (query.next()) {
        settings.tensionUnit = query.value(0).toInt();
        settings.depthUnit = query.value(1).toInt();

        TensionSetting *ts = TensionSetting::GetInstance();
        DepthSetting *ds = DepthSetting::GetInstance();

        if (ts) {
            ts->setTensionUnit(settings.tensionUnit);
            ds->setVelocityUnit(settings.depthUnit);
        }

        return true;
    }
    return false;
}

bool HBDatabase::updateTensionUnit(int tensionUnit) {
    QSqlQuery query;
    query.prepare("UPDATE unit_settings SET tension_unit = :unit WHERE id = 1");
    query.bindValue(":unit", tensionUnit);
    return query.exec();
}

bool HBDatabase::updateDepthUnit(int depthUnit) {
    QSqlQuery query;
    query.prepare("UPDATE unit_settings SET depth_unit = :unit WHERE id = 1");
    query.bindValue(":unit", depthUnit);
    return query.exec();
}
