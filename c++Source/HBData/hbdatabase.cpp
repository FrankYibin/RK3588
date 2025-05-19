#include "hbdatabase.h"
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include "c++Source/HBDefine.h"
#include "c++Source/HBScreen/wellparameter.h"
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
}

bool HBDatabase::updateWellParameter(const _WellParameter &param)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    if (!m_database.transaction()) {
        qDebug() << "Failed to start transaction:" << m_database.lastError();
        return false;
    }

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

    query.bindValue(":wellNumber", param.wellNumber,QSql::In);
    query.bindValue(":areaBlock", param.areaBlock,QSql::In);
    query.bindValue(":wellType", param.wellType,QSql::In);
    query.bindValue(":wellDepth", param.wellDepth,QSql::In);
    query.bindValue(":harnessWeight", param.harnessWeight,QSql::In);
    query.bindValue(":sensorWeight", param.sensorWeight,QSql::In);
    query.bindValue(":harnessType", param.harnessType,QSql::In);
    query.bindValue(":harnessForce", param.harnessForce,QSql::In);
    query.bindValue(":tensionUnit", param.tensionUnit,QSql::In);
    query.bindValue(":workType", param.workType,QSql::In);
    query.bindValue(":userName", param.userName,QSql::In);
    query.bindValue(":operatorType", param.operatorType,QSql::In);
    query.bindValue(":id", param.id,QSql::In);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError();
        m_database.rollback();
        return false;
    }

    m_database.commit();
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
