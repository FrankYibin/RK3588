#include "hbdatabase.h"
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include "c++Source/HBDefine.h"
#include "c++Source/HBScreen/wellparameter.h"
#include "c++Source/HBScreen/depthsetting.h"
#include "c++Source/HBScreen/depthsafe.h"
#include "c++Source/HBScreen/hbhome.h"
#include "c++Source/HBScreen/tensionsafety.h"
#include "c++Source/HBScreen/tensiometer.h"
#include "c++Source/HBScreen/tensionsetting.h"
#include <QVariant>


HBDatabase::HBDatabase(QObject *parent)
    : QObject{parent}
{
    init();
    //    loadDataFromDatabase();

}

HBDatabase::~HBDatabase()
{

    closeTransaction();
}

void HBDatabase::init()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/DVTT.db";
    qDebug() << "DB Path: " << dbPath;
    m_database.setDatabaseName(dbPath);

    if (!m_database.open())
    {
        qDebug() << "Database Open Fail ";
        qDebug() << m_database.lastError();
    }

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


HBDatabase &HBDatabase::getInstance()
{
    static HBDatabase instance; // 局部静态，线程安全单例
    return instance;
}

bool HBDatabase::loadWellParameter(_WellParameter &param)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM wellparameter LIMIT 1");

    if (!query.exec()) {
        qDebug() << "Load failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No data found in wellparameter table";
        return false;
    }

    param.id = query.value("id").toInt();
    param.wellNumber = query.value("wellNumber").toString();
    param.areaBlock = query.value("areaBlock").toString();
    param.wellType = query.value("wellType").toInt();
    param.wellDepth = query.value("wellDepth").toString();
    param.harnessWeight = query.value("harnessWeight").toString();
    param.sensorWeight = query.value("sensorWeight").toString();
    param.harnessType = query.value("harnessType").toInt();
    param.harnessForce = query.value("harnessForce").toString();
    param.tensionUnit = query.value("tensionUnit").toInt();
    param.workType = query.value("workType").toInt();
    param.userName = query.value("userName").toString();
    param.operatorType = query.value("operatorType").toString();

    WellParameter* wp = WellParameter::GetInstance();
    wp->setWellNumber(param.wellNumber);
    wp->setAreaBlock(param.areaBlock);
    wp->setWellType(param.wellType);
    wp->setDepthWell(param.wellDepth);
    wp->setWeightEachKilometerCable(param.harnessWeight);
    wp->setWeightInstrumentString(param.sensorWeight);
    wp->setCableSpec(param.harnessType);
    wp->setBreakingForceCable(param.harnessForce);
    wp->setTonnageTensionStick(param.tensionUnit);
    wp->setWorkType(param.workType);
    wp->setUserName(param.userName);
    wp->setOperatorType(param.operatorType);

    return true;
}

void HBDatabase::loadDataFromDatabase()
{
    _WellParameter param;
    bool ok = HBDatabase::getInstance().loadWellParameter(param);
    if (ok) {

        qDebug() << "Loaded data:";
        qDebug() << "Updating record id:" << param.id;
        qDebug() << "WellNumber:" << param.wellNumber;
        qDebug() << "AreaBlock:" << param.areaBlock;

    } else {
        qDebug() << "Failed to load data from database";
    }

    _DepthSet deptParam;
    bool success = HBDatabase::getInstance().loadDepthSet(deptParam);
    if (success) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    _DepthSafe dsParam;
    bool ds_ok = HBDatabase::getInstance().loadDepthSafe(dsParam);
    if (ds_ok) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    _TensionSafe tsParam;
    bool tsp_ok = HBDatabase::getInstance().loadTensionSafe(tsParam);
    if (tsp_ok) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    _TensionSet setParam;
    bool set_ok = HBDatabase::getInstance().loadTensionSet(setParam);
    if (set_ok) {
        qDebug() << "DepthSet loaded successfully!";
    } else {
        qDebug() << "Failed to load DepthSet from DB.";
    }

    UnitSettings setUint;

    bool set_Unit = HBDatabase::getInstance().getUnitSettings(setUint);
    if (set_Unit) {
        qDebug() << "set_Unit loaded successfully!";
    } else {
        qDebug() << "Failed to load set_Unit from DB.";
    }
}

bool HBDatabase::updateWellParameter(const _WellParameter &param)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
                  UPDATE wellparameter SET
                  wellNumber = :wellNumber,
                  areaBlock = :areaBlock,
                  wellType = :wellType,
                  wellDepth = :wellDepth,
                  harnessWeight = :harnessWeight,
                  sensorWeight = :sensorWeight,
                  harnessType = :harnessType,
                  harnessForce = :harnessForce,
                  tensionUnit = :tensionUnit,
                  workType = :workType,
                  userName = :userName,
                  operatorType = :operatorType
                  WHERE id = :id
                  )");

    query.bindValue(":wellNumber", param.wellNumber);
    query.bindValue(":areaBlock", param.areaBlock);
    query.bindValue(":wellType", param.wellType);
    query.bindValue(":wellDepth", param.wellDepth);
    query.bindValue(":harnessWeight", param.harnessWeight);
    query.bindValue(":sensorWeight", param.sensorWeight);
    query.bindValue(":harnessType", param.harnessType);
    query.bindValue(":harnessForce", param.harnessForce);
    query.bindValue(":tensionUnit", param.tensionUnit);
    query.bindValue(":workType", param.workType);
    query.bindValue(":userName", param.userName);
    query.bindValue(":operatorType", param.operatorType);
    query.bindValue(":id", param.id);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "Update successful";
    return true;
}

bool HBDatabase::updateWellParameterFromInstance()
{
    WellParameter* wp = WellParameter::GetInstance();
    _WellParameter param;
    param.id = 1;
    param.wellNumber = wp->WellNumber();
    param.areaBlock = wp->AreaBlock();
    param.wellType = wp->WellType();
    param.wellDepth = wp->DepthWell();
    param.harnessWeight = wp->WeightEachKilometerCable();
    param.sensorWeight = wp->WeightInstrumentString();
    param.harnessType = wp->CableSpec();
    param.harnessForce = wp->BreakingForceCable();
    param.tensionUnit = wp->TonnageTensionStick();
    param.workType = wp->WorkType();
    param.userName = wp->UserName();
    param.operatorType = wp->OperatorType();

    qDebug() << "Updating record id:" << param.id;
    qDebug() << "wellNumber:" << param.wellNumber;
    qDebug() << "areaBlock:" << param.areaBlock;
    qDebug() << "wellType:" << param.wellType;
    qDebug() << "wellDepth:" << param.wellDepth;
    qDebug() << "harnessWeight:" << param.harnessWeight;
    qDebug() << "sensorWeight:" << param.sensorWeight;
    qDebug() << "harnessType:" << param.harnessType;
    qDebug() << "harnessForce:" << param.harnessForce;
    qDebug() << "tensionUnit:" << param.tensionUnit;
    qDebug() << "workType:" << param.workType;
    qDebug() << "userName:" << param.userName;
    qDebug() << "operatorType:" << param.operatorType;

    return updateWellParameter(param);
}

//bool HBDatabase::testUpdate()
//{
//    QSqlQuery query(m_database);
//    query.prepare("UPDATE wellparameter SET wellNumber = 'Test123' WHERE id = 1");
//    if (!query.exec()) {
//        qDebug() << "Test update failed:" << query.lastError();
//        return false;
//    }
//    qDebug() << "Test update successful, rows affected:" << query.numRowsAffected();
//    return true;
//}

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
    param.depthVelocityLimit = query.value("depthVelocityLimit").toInt();


    DepthSafe* ds = DepthSafe::getInstance();

    ds->setDepthPreset(param.depthPreset);
    ds->setWellWarnig(param.wellWarnig);
    ds->setBrake(param.brake);
    ds->setVelocityLimit(param.velocityLimit);
    ds->setDepthWarning(param.depthWarning);
    ds->setTotalDepth(param.totalDepth);
    ds->setDepthBrake(param.depthBrake);
    ds->setDepthVelocityLimit(param.depthVelocityLimit);

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
    query.bindValue(":depthVelocityLimit", param.depthVelocityLimit);
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
    DepthSafe* ds = DepthSafe::getInstance();

    _DepthSafe param;
    param.id = 1;
    param.depthPreset = ds->DepthPreset();
    param.wellWarnig = ds->WellWarnig();
    param.brake = ds->Brake();
    param.velocityLimit = ds->VelocityLimit();
    param.depthWarning = ds->DepthWarning();
    param.totalDepth = ds->TotalDepth();
    param.depthBrake = ds->DepthBrake();
    param.depthVelocityLimit = ds->DepthVelocityLimit();

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
bool HBDatabase::insertTensiometerData(TensiometerData &data)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare(R"(
        INSERT INTO tensiometer (tensiometerNumber, tensiometerType, tensiometerRange, tensiometerSignal)
        VALUES (:tensiometerNumber, :tensiometerType, :tensiometerRange, :tensiometerSignal)
    )");

    query.bindValue(":tensiometerNumber", data.tensiometerNumber);
    query.bindValue(":tensiometerType", data.tensiometerType);
    query.bindValue(":tensiometerRange", data.tensiometerRange);
    query.bindValue(":tensiometerSignal", data.tensiometerSignal);

    if (!query.exec()) {
        qDebug() << "Insert tensiometer data failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    data.id = query.lastInsertId().toInt();

    if (!commitTransaction())
        return false;

    qDebug() << "Insert tensiometer data successful, id:" << data.id;
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
bool HBDatabase::deleteTensiometerData(int id)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!beginTransaction())
        return false;

    QSqlQuery query(m_database);
    query.prepare("DELETE FROM tensiometer WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Delete tensiometer data failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No tensiometer data deleted (id not found):" << id;
    }

    if (!commitTransaction())
        return false;

    qDebug() << "Delete tensiometer data successful";
    return true;
}

// 加载全部数据
bool HBDatabase::loadAllTensiometerData(QList<TensiometerData> &list)
{
    list.clear();

    QSqlQuery query(m_database);
    if (!query.exec("SELECT * FROM tensiometer")) {
        qDebug() << "Load all tensiometer data failed:" << query.lastError();
        return false;
    }

    while (query.next()) {
        TensiometerData data;
        data.id = query.value("id").toInt();
        data.tensiometerNumber = query.value("tensiometerNumber").toString();
        data.tensiometerType = query.value("tensiometerType").toInt();
        data.tensiometerRange = query.value("tensiometerRange").toInt();
        data.tensiometerSignal = query.value("tensiometerSignal").toInt();
        list.append(data);
    }

    qDebug() << "Loaded" << list.size() << "tensiometer records.";
    return true;
}


bool HBDatabase::loadScalesForTensiometerNumber(const QString &tensioNumber,QList<ScaleData> &outRecords)

{
    QSqlQuery q(m_database);
    q.prepare(R"SQL(
              SELECT id, point_index, scale_value, tension_value, selected
              FROM tension_scale
              WHERE tensiometer_number = ?
              ORDER BY point_index
              )SQL");
    q.addBindValue(tensioNumber);
    if (!q.exec()) {
        qWarning() << "Failed to load scales for tensiometer_number" << tensioNumber
                   << ":" << q.lastError().text();
        return false;
    }
    outRecords.clear();
    while (q.next()) {
        ScaleData data;
        data.id = q.value(0).toInt();
        data.pointIndex = q.value(1).toInt();
        data.rawScaleValue = q.value(2).toDouble();
        data.rawTensionValue = q.value(3).toDouble();
        data.selected = q.value(4).toInt();
        outRecords.append(data);

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

bool HBDatabase::updateTensionValue(const QString &tensioNumber, int index, double scaleValue, double tensionValue, bool selected)
{

    QSqlQuery query;
    query.prepare(R"(
        UPDATE tension_scale
        SET scale_value = :scale,
            tension_value = :tension,
            selected = :selected
        WHERE tensiometer_number = :num AND point_index = :idx
    )");

    query.bindValue(":scale", scaleValue);
    query.bindValue(":tension", tensionValue);
    query.bindValue(":selected", selected ? 1 : 0);
    query.bindValue(":num", tensioNumber);
    query.bindValue(":idx", index);

    bool success = query.exec();
    if (!success) {
        qWarning() << " Failed to update tension value in DB:"
                   << query.lastError().text()
                   << "\nQuery:" << query.lastQuery();
    } else {
        qDebug() << " Updated tension successfully:"
                 << "Tensio#" << tensioNumber << "Index:" << index
                 << "Scale:" << scaleValue << "Tension:" << tensionValue << "Selected:" << selected;
    }

    return query.exec();


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
        if (fullDate.length() >= 7) {
            item.date = fullDate.left(10);
        } else {
            item.date = "";
        }
        item.operateType = query.value("operateType").toString();
        item.operater = query.value("operater").toString();
        item.depth = query.value("depth").toInt();
        item.velocity = query.value("velocity").toInt();
        item.velocityUnit = query.value("velocityUnit").toString();
        item.tensions = query.value("tensions").toInt();
        item.tensionIncrement = query.value("tensionIncrement").toInt();
        item.tensionUnit = query.value("tensionUnit").toString();
        item.maxTension = query.value("maxTension").toInt();
        item.harnessTension = query.value("harnessTension").toInt();
        item.safetyTension = query.value("safetyTension").toInt();
        item.exception = query.value("exception").toString();

        dataList.append(item);
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
                  "VALUES (:wellNumber, CURRENT_DATE, :operateType, :operater, :depth, :velocity, "
                  ":velocityUnit, :tensions,:tensionIncrement,:tensionUnit, :maxTension, :harnessTension, :safetyTension, :exception)";
    query.prepare(sql);


    query.bindValue(":wellNumber", modbusData.wellNumber);
    query.bindValue(":operateType", modbusData.operateType);
    query.bindValue(":operater", modbusData.operater);
    query.bindValue(":depth", modbusData.depth);
    query.bindValue(":velocity", modbusData.velocity);
    query.bindValue(":velocityUnit", "m/min");
    query.bindValue(":tensions", modbusData.tensions);
    query.bindValue(":tensionIncrement", modbusData.tensionIncrement);
    query.bindValue(":tensionUnit", "kg");
    query.bindValue(":maxTension", modbusData.maxTension);
    query.bindValue(":harnessTension", modbusData.harnessTension);
    query.bindValue(":safetyTension", modbusData.safetyTension);
    query.bindValue(":exception", "无");

    // 执行插入
    if (!query.exec()) {
        qDebug() << "Failed to insert data:" << query.lastError();
        return false;
    }

    qDebug() << "Data inserted successfully!";
    return true;
}

QVector<QPointF> HBDatabase::loadGraphPoints(const QString& fieldName)
{
    QVector<QPointF> points;

    if (!m_database.isOpen()) {
        qDebug() << "Database is not open!";
        return points;
    }

    QSqlQuery query(m_database);
    QString sql = QString("SELECT date, %1 FROM history_table ORDER BY date ASC").arg(fieldName);

    if (!query.exec(sql)) {
        qDebug() << "Failed to load graph data:" << query.lastError();
        return points;
    }

    while (query.next()) {

        qreal x = query.value(0).toDouble();
        QVariant value = query.value(1);

        if (value.isValid() && value.canConvert<double>()) {
            qreal y = value.toDouble();
            points.append(QPointF(x, y));
        } else {
            qWarning() << "Invalid data at row:" << query.at();
        }
    }

    return points;
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
