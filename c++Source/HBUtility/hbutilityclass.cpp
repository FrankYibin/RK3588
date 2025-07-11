﻿#include "hbutilityclass.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
HBUtilityClass* HBUtilityClass::_ptrInstance = nullptr;
void HBUtilityClass::SetTextData(DATA_FORMAT index, int data, float factor, QString formater)
{
    txtData[index].Data = data;
    txtData[index].Factor = factor;
    txtData[index].Format = formater;
}

void HBUtilityClass::InitTextData()
{
    SetTextData(HEX2METER,          0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2FEET,           0, static_cast<float>(0.01 * 3.28),             QString("%.2f"));
    SetTextData(HEX2METER_PER_HOUR, 0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2FEET_PER_HOUR,  0, static_cast<float>(0.01 * 3.28),             QString("%.2f"));
    SetTextData(HEX2METER_PER_MIN,  0, static_cast<float>(0.01/60),                 QString("%.2f"));
    SetTextData(HEX2FEET_PER_MIN,   0, static_cast<float>(0.01 * 3.28 / 60),        QString("%.2f"));
    SetTextData(HEX2POUND,          0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2KILOGRAM,       0, static_cast<float>(0.01 * 0.454),            QString("%.2f"));
    SetTextData(HEX2KILONEWTON,     0, static_cast<float>(0.01 * 0.004448230531),   QString("%.2f"));
    SetTextData(HEX2PULSE,          0, static_cast<float>(1.0),                     QString("%d"));
    SetTextData(HEX2K_VALUE,        0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2AMPERE,         0, static_cast<float>(1.0),                     QString("%d"));
    SetTextData(HEX2VOLTAGE,        0, static_cast<float>(0.001),                   QString("%.3f"));
    SetTextData(HEX2PERCENT,        0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2TONAGE,         0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2FACTOR,         0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2SECOND,         0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2DEGREE,         0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2INTEGER,        0, static_cast<float>(1.0),                     QString("%d"));
    SetTextData(HEX2DECIMAL,        0, static_cast<float>(0.01),                    QString("%.2f"));
}

QString HBUtilityClass::FormatedDataToString(const DATA_FORMAT index, const int data)
{
    QString tmpStr;
    if(txtData[index].Format.contains("d") == true)
        tmpStr.sprintf(txtData[index].Format.toStdString().c_str(), data);
    else
        tmpStr.sprintf(txtData[index].Format.toStdString().c_str(), static_cast<double>(data * txtData[index].Factor));
    return tmpStr;
}

int HBUtilityClass::StringToFormatedData(const DATA_FORMAT index, const QString strData)
{
    QString tmpStr = strData.trimmed();
    if(tmpStr.isEmpty() == true)
        return -1;
    QByteArray tmpArray = tmpStr.toLatin1();
    const char *s = tmpArray.data();
    int i = 0;
    while(((*s >= '0') && (*s <= '9')) || (*s == '.') || (*s == '-'))
    {
        s++;
        i++;
    }
    tmpStr.remove(i, tmpStr.size() -1);
    double tmpValue = tmpStr.toDouble();
    const double d_factor = 1.0 / txtData[index].Factor;
    return static_cast<int>(tmpValue * d_factor);
}

HBUtilityClass* HBUtilityClass::GetInstance()
{
    if(_ptrInstance == nullptr)
    {
        _ptrInstance = new HBUtilityClass();
    }
    return _ptrInstance;
}

HBUtilityClass::HBUtilityClass()
{
    InitTextData();
}

bool HBUtilityClass::ListJsonToString(QList<int>* _SourceList, QString &DestString)
{
    QJsonObject json;
    if(_SourceList == nullptr)
        return false;
    for(int i = 0; i < _SourceList->size(); i++)
        json.insert(QString::number(i,10),  QString::number(_SourceList->at(i), 10));
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool HBUtilityClass::StringJsonToList(QString SourceString, QList<int> *_DestList)
{
    bool bResult = false;
    if(_DestList == nullptr)
        return false;
    QByteArray byte_array = SourceString.toLatin1();
    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_document.isObject())
        {
            QJsonObject obj = parse_document.object();
            if(_DestList->isEmpty() == false)
                _DestList->clear();
            QJsonObject::const_iterator tmp;
            for (int i = 0; i < obj.count();i++)
            {
                tmp = obj.constFind(QString("%1").arg(i));
                if(tmp != obj.constEnd())
                    _DestList->append(tmp.value().toVariant().toInt());
            }
            bResult = true;

        }
    }
    return bResult;
}

bool HBUtilityClass::ListJsonToString(QList<TensionScaleManager::SCALE_RAW_DATA> *_SourceList, QString &DestString)
{
    QJsonObject json;
    if(_SourceList == nullptr)
        return false;
    for(int i = 0; i < _SourceList->size(); i++)
    {
        QJsonObject item;
        item.insert("ScaleValue", _SourceList->at(i).ScaleRaw);
        item.insert("TensionValue", _SourceList->at(i).TensionRaw);
        json.insert(QString::number(i,10), item);
    }
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool HBUtilityClass::StringJsonToList(QString SourceString, QList<TensionScaleManager::SCALE_RAW_DATA> *_DestList)
{
    bool bResult = false;
    if(_DestList == nullptr)
        return false;
    QByteArray byte_array = SourceString.toLatin1();
    QJsonParseError json_error;
    TensionScaleManager::SCALE_RAW_DATA scale;
    QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_document.isObject())
        {
            QJsonObject obj = parse_document.object();
            if(_DestList->isEmpty() == false)
                _DestList->clear();
            QJsonObject::const_iterator tmp;
            for (int i = 0; i < obj.count();i++)
            {
                tmp = obj.constFind(QString::number(i));
                if(tmp != obj.constEnd())
                {
                    QJsonObject item = tmp.value().toObject();
                    scale.ScaleRaw = item.value("ScaleValue").toInt();
                    scale.TensionRaw = item.value("TensionValue").toInt();
                    _DestList->append(scale);
                }
            }
            bResult = true;
        }
    }
    return bResult;
}

void HBUtilityClass::CalculateLargest(qreal &a_axisVal, qreal a_val)
{
    if(a_axisVal < a_val)
        a_axisVal = a_val;
}

void HBUtilityClass::CalculateSmallest(qreal &a_axisVal, qreal a_val)
{
    if(a_axisVal > a_val)
        a_axisVal = a_val;
}

void HBUtilityClass::TestFaceDetection()
{
    // 创建 QProcess 对象
    QProcess process;

    // 设置要执行的命令
    QString program = "./faceTest.sh"; // 你可以替换为其他 Linux 命令
    QStringList arguments; // 这里可以添加命令参数，例如 "-l" 或其他
    arguments.append("-compare");
    arguments.append("/opt/face_offline_sdk/images/1.jpg");

    // 启动进程
    process.start(program, arguments);

    // 等待进程结束
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty()) {
        qDebug() << "Command Output 1111111111111111111:" << output;
    }
    if (!error.isEmpty()) {
        qDebug() << "Command Error:" << error;
    }
}

bool HBUtilityClass::SetSystemClock(QString strDateTime)
{
    QString cmd = QString("date -s %1%2%3").arg('"').arg(strDateTime).arg('"');

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QStringList cmdlist;
    process.start("bash", cmdlist);
    if(!process.waitForStarted())
    {
        qDebug() << "Failed to start process";
        return false;
    }

    qDebug() << "Cmd: " << cmd;
    process.write(cmd.toUtf8());
    process.waitForBytesWritten();

    process.closeWriteChannel();
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty()) {
        qDebug() << "DateTime Setting Output:" << output;
        return true;
    }
    if (!error.isEmpty()) {
        qDebug() << "Command Error:" << error;
        return false;
    }
    return true;
}

bool HBUtilityClass::SyncHardwareRTC()
{
    QString cmd = "hwclock -w -f /dev/rtc0\n";

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QStringList cmdlist;
    process.start("bash", cmdlist);
    if(!process.waitForStarted())
    {
        qDebug() << "Failed to start process";
        return false;
    }

    process.write(cmd.toUtf8());
    process.waitForBytesWritten();

    process.closeWriteChannel();
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty()) {
        qDebug() << "Hardware Clock Sync Output:" << output;
        return true;
    }
    if (!error.isEmpty()) {
        qDebug() << "Command Error:" << error;
        return false;
    }
    return true;
}

QSettings& HBUtilityClass::settings()
{
    static QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    return settings;
}


