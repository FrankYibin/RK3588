#include "hbdatabase.h"
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>

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
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/DVTT.db";
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

_USER_DATA HBDatabase::queryUsertById(int id){


    _USER_DATA data;
    QSqlQuery query;

    query.prepare("SELECT * FROM user WHERE id = :id");
    query.bindValue(":id", id);
    // QString sql = QString("SELECT * FROM %1 WHERE id = %2").arg("user").arg(id);
    // query.prepare(sql);

    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        qDebug() << "Query executed: " << query.lastQuery();
        return data; // 返回空结构体
    }


    if (query.next()) {
        data.id = query.value("id").toInt();
        data.username = query.value("username").toString();
        data.password = query.value("password").toInt();

    }else{
        qDebug() << "No data found for ID:" << id;
    }
    return data;

}

_Measurements_data HBDatabase::queryMeasurementById(int id)
{

    _Measurements_data data;  // 创建一个结构体实例来存储查询结果
    QSqlQuery query;

    QString sql = QString("SELECT * FROM %1 WHERE id = %2").arg("measurements").arg(id);
    query.prepare(sql);

    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        qDebug() << "Query executed: " << query.lastQuery();
        return data; // 返回空结构体
    }

    // 获取查询结果的字段名
    QSqlRecord record = query.record();
    int fieldCount = record.count();

    qDebug() << "Field count: " << fieldCount;

    // 输出字段名
    for (int i = 0; i < fieldCount; ++i) {
        qDebug() << "Field " << i << ": " << record.fieldName(i);
    }

    if (query.next()) {

        data.id = query.value("id").toInt();
        data.wellnum = query.value("wellnum").toString();
        data.depth = query.value("depth").toDouble();
        data.speed = query.value("speed").toDouble();
        data.target_depth = query.value("target_depth").toDouble();
        data.surface_depth = query.value("surface_depth").toDouble();
        data.pulse_count = query.value("pulse_count").toDouble();
        data.depth_dir = query.value("depth_dir").toDouble();
        data.depth_calcu = query.value("depth_calcu").toDouble();
        data.coder_cho = query.value("coder_cho").toDouble();
        data.coder1_depth = query.value("coder1_depth").toDouble();
        data.coder2_depth = query.value("coder2_depth").toDouble();
        data.coder3_depth = query.value("coder3_depth").toDouble();
        data.coder_error = query.value("coder_error").toDouble();
        data.depth_countdown = query.value("depth_countdown").toDouble();
        data.cumulative_depth = query.value("cumulative_depth").toDouble();
        data.tension = query.value("tension").toDouble();
        data.tension_increment = query.value("tension_increment").toDouble();
        data.K_value = query.value("K_value").toDouble();
        data.tensioner_status = query.value("tensioner_status").toDouble();
        data.tension_meter_bat = query.value("tension_meter_bat").toDouble();
        data.tensioner_num = query.value("tensioner_num").toDouble();
        data.scale_end_num = query.value("scale_end_num").toDouble();
        data.end_scale = query.value("end_scale").toDouble();
        data.end_tension = query.value("end_tension").toDouble();
        data.end_nums = query.value("end_nums").toDouble();
        data.calibrate_or = query.value("calibrate_or").toDouble();
        data.limit_tension = query.value("limit_tension").toDouble();
        data.limit_tension_increment = query.value("limit_tension_increment").toDouble();
        data.limit_speed = query.value("limit_speed").toDouble();
        data.head_tension = query.value("head_tension").toDouble();
        data.cv_status = query.value("cv_status").toDouble();
        data.cv_let = query.value("cv_let").toDouble();
        data.cv_speed = query.value("cv_speed").toDouble();
        data.pump_down_current = query.value("pump_down_current").toDouble();
        data.pump_up_current = query.value("pump_up_current").toDouble();
        data.motor_current = query.value("motor_current").toDouble();
        data.invalid_reservation = query.value("invalid_reservation").toDouble();
        data.volt = query.value("volt").toDouble();
        data.tension_channel = query.value("tension_channel").toDouble();
        data.pump_speed_potentiometer = query.value("pump_speed_potentiometer").toDouble();
        data.speed_trimmer_potentiometer = query.value("speed_trimmer_potentiometer").toDouble();
        data.tension_bar_m = query.value("tension_bar_m").toDouble();
        data.cable_specification = query.value("cable_specification").toDouble();
        data.well_depth = query.value("well_depth").toDouble();
        data.well_deviation = query.value("well_deviation").toDouble();
        data.work_type = query.value("work_type").toDouble();
        data.cable_breaking_f = query.value("cable_breaking_f").toDouble();
        data.weak_pull_f = query.value("weak_pull_f").toDouble();
        data.m_per_km = query.value("m_per_km").toDouble();
        data.instruments_m = query.value("instruments_m").toDouble();
        data.safe_tension_paras = query.value("safe_tension_paras").toDouble();
        data.now_safe_tension = query.value("now_safe_tension").toDouble();
        data.now_limit_tension = query.value("now_limit_tension").toDouble();
        data.cable_tension_changing = query.value("cable_tension_changing").toDouble();
        data.safe_stop_time = query.value("safe_stop_time").toDouble();
        data.depth_tension_status = query.value("depth_tension_status").toDouble();
        data.timestamp = query.value("timestamp").toString();
        data.current_user = query.value("current_user").toString();
        data.speed_unit = query.value("speed_unit").toString();
        data.tension_unit = query.value("tension_unit").toString();
    } else {
        qDebug() << "No data found for ID:" << id;
    }

    return data;
}

_Measurements_data HBDatabase::queryWellDataByWellnum(QString wellnum)
{
    _Measurements_data data;  // 创建一个结构体实例来存储查询结果
    QSqlQuery query;

    // 准备 SQL 查询语句，查询指定 ID 的数据
    query.prepare("SELECT * FROM measurements WHERE wellnum = :wellnum");
    query.bindValue(":wellnum", wellnum);

    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        return data; // 返回空结构体
    }


    if (query.next()) {
        data.id = query.value("id").toInt();
        data.wellnum = query.value("wellnum").toString();
        data.depth = query.value("depth").toDouble();
        data.speed = query.value("speed").toDouble();
        data.target_depth = query.value("target_depth").toDouble();
        data.surface_depth = query.value("surface_depth").toDouble();
        data.pulse_count = query.value("pulse_count").toDouble();
        data.depth_dir = query.value("depth_dir").toDouble();
        data.depth_calcu = query.value("depth_calcu").toDouble();
        data.coder_cho = query.value("coder_cho").toDouble();
        data.coder1_depth = query.value("coder1_depth").toDouble();
        data.coder2_depth = query.value("coder2_depth").toDouble();
        data.coder3_depth = query.value("coder3_depth").toDouble();
        data.coder_error = query.value("coder_error").toDouble();
        data.depth_countdown = query.value("depth_countdown").toDouble();
        data.cumulative_depth = query.value("cumulative_depth").toDouble();
        data.tension = query.value("tension").toDouble();
        data.tension_increment = query.value("tension_increment").toDouble();
        data.K_value = query.value("K_value").toDouble();
        data.tensioner_status = query.value("tensioner_status").toDouble();
        data.tension_meter_bat = query.value("tension_meter_bat").toDouble();
        data.tensioner_num = query.value("tensioner_num").toDouble();
        data.scale_end_num = query.value("scale_end_num").toDouble();
        data.end_scale = query.value("end_scale").toDouble();
        data.end_tension = query.value("end_tension").toDouble();
        data.end_nums = query.value("end_nums").toDouble();
        data.calibrate_or = query.value("calibrate_or").toDouble();
        data.limit_tension = query.value("limit_tension").toDouble();
        data.limit_tension_increment = query.value("limit_tension_increment").toDouble();
        data.limit_speed = query.value("limit_speed").toDouble();
        data.head_tension = query.value("head_tension").toDouble();
        data.cv_status = query.value("cv_status").toDouble();
        data.cv_let = query.value("cv_let").toDouble();
        data.cv_speed = query.value("cv_speed").toDouble();
        data.pump_down_current = query.value("pump_down_current").toDouble();
        data.pump_up_current = query.value("pump_up_current").toDouble();
        data.motor_current = query.value("motor_current").toDouble();
        data.invalid_reservation = query.value("invalid_reservation").toDouble();
        data.volt = query.value("volt").toDouble();
        data.tension_channel = query.value("tension_channel").toDouble();
        data.pump_speed_potentiometer = query.value("pump_speed_potentiometer").toDouble();
        data.speed_trimmer_potentiometer = query.value("speed_trimmer_potentiometer").toDouble();
        data.tension_bar_m = query.value("tension_bar_m").toDouble();
        data.cable_specification = query.value("cable_specification").toDouble();
        data.well_depth = query.value("well_depth").toDouble();
        data.well_deviation = query.value("well_deviation").toDouble();
        data.work_type = query.value("work_type").toDouble();
        data.cable_breaking_f = query.value("cable_breaking_f").toDouble();
        data.weak_pull_f = query.value("weak_pull_f").toDouble();
        data.m_per_km = query.value("m_per_km").toDouble();
        data.instruments_m = query.value("instruments_m").toDouble();
        data.safe_tension_paras = query.value("safe_tension_paras").toDouble();
        data.now_safe_tension = query.value("now_safe_tension").toDouble();
        data.now_limit_tension = query.value("now_limit_tension").toDouble();
        data.cable_tension_changing = query.value("cable_tension_changing").toDouble();
        data.safe_stop_time = query.value("safe_stop_time").toDouble();
        data.depth_tension_status = query.value("depth_tension_status").toDouble();
        data.timestamp = query.value("timestamp").toString();
        data.current_user = query.value("current_user").toString();
        data.speed_unit = query.value("speed_unit").toString();
        data.tension_unit = query.value("tension_unit").toString();
    } else {
        qDebug() << "No data found for wellnum:" << wellnum;
    }
    return data;

}
