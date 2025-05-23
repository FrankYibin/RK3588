﻿#include "hbdatabase.h"
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include "c++Source/HBDefine.h"
#include "c++Source/HBScreen/wellparameter.h"
#include "c++Source/HBScreen/depth.h"
#include "c++Source/HBScreen/depthsafe.h"
#include "c++Source/HBScreen/hbhome.h"
#include  "c++Source/HBScreen/tensionsafe.h"
#include "c++Source/HBScreen/tensiometer.h"
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

    WellParameter* wp = WellParameter::getInstance();
    wp->setWellNumber(param.wellNumber);
    wp->setAreaBlock(param.areaBlock);
    wp->setWellType(param.wellType);
    wp->setWellDepth(param.wellDepth);
    wp->setHarnessWeight(param.harnessWeight);
    wp->setSensorWeight(param.sensorWeight);
    wp->setHarnessType(param.harnessType);
    wp->setHarnessForce(param.harnessForce);
    wp->setTensionUnit(param.tensionUnit);
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
    WellParameter* wp = WellParameter::getInstance();
    _WellParameter param;
    param.id = 1;
    param.wellNumber = wp->WellNumber();
    param.areaBlock = wp->AreaBlock();
    param.wellType = wp->WellType();
    param.wellDepth = wp->WellDepth();
    param.harnessWeight = wp->HarnessWeight();
    param.sensorWeight = wp->SensorWeight();
    param.harnessType = wp->HarnessType();
    param.harnessForce = wp->HarnessForce();
    param.tensionUnit = wp->TensionUnit();
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

    Depth* ds = Depth::getInstance();
    HBHome* hs = HBHome::getInstance();

    ds->setTargetLayerDepth(param.targetLayerDepth);
    ds->setDepthOrientation(param.depthOrientation);
    ds->setMeterDepth(param.meterDepth);
    ds->setDepthCalculateType(param.depthCalculateType);
    ds->setCodeOption(param.codeOption);
    hs->setPulse(param.pulse);

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
    Depth* ds = Depth::getInstance();
    HBHome* hs = HBHome::getInstance();

    _DepthSet param;
    param.id = 1;
    param.targetLayerDepth = ds->TargetLayerDepth();
    param.depthOrientation = ds->DepthOrientation();
    param.meterDepth = ds->MeterDepth();
    param.depthCalculateType = ds->DepthCalculateType();
    param.codeOption = ds->CodeOption();
    param.pulse = hs->Pulse();

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

    TensionSafe* ts = TensionSafe::getInstance();
    HBHome* hs = HBHome::getInstance();
    ts->setWellType(param.wellType);
    hs->setMaxTension(param.maxTension);
    ts->setWeakForce(param.weakForce);
    ts->setTensionSafeFactor(param.tensionSafeFactor);

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
    TensionSafe* ts = TensionSafe::getInstance();
    HBHome* hs = HBHome::getInstance();

    _TensionSafe param;
    param.id = 1;
    param.wellType = ts->WellType();
    param.maxTension = hs->MaxTension();
    param.weakForce = ts->WeakForce();
    param.tensionSafeFactor = ts->TensionSafeFactor();

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

    Tensiometer* ts = Tensiometer::getInstance();
    HBHome* hs = HBHome::getInstance();
    hs->setKValue(param.kValue);
    ts->setTensionUnits(param.tensionUnit);

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
    Tensiometer* ts = Tensiometer::getInstance();
    HBHome* hs = HBHome::getInstance();

    _TensionSet param;
    param.id = 1;
    param.kValue = hs->KValue();
    param.tensionUnit = ts->TensionUnits();

    return updateTensionSet(param);
}


////

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "hbdatabase.h"

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






