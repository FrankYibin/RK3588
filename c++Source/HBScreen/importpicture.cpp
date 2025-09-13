#include "importpicture.h"
#include <QProcess>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

bool ImportPicture::parseJson(const QString message, QMap<QString, QString> *_list)
{
    bool bResult = false;
    if(_list == nullptr)
        return bResult;

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &jsonError);
    if (jsonError.error == QJsonParseError::NoError && doc.isObject()) {
        QJsonObject obj = doc.object();

        // 判断是否有 "data" 字段和 "success" 字段
        if (!obj.contains("data") || !obj.contains("success")) {
            qDebug() << "JSON缺少data或success字段";
            return false;
        }
        // 判断 success 字段是否为 true
        if (!obj.value("success").toBool()) {
            qDebug() << "success字段为false";
            return false;
        }

        QJsonObject dataObj = obj.value("data").toObject();
        QVariantMap dataMap = dataObj.toVariantMap();
        for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
            _list->insert(it.key(), it.value().toString());
        }
        for (auto it = _list->begin(); it != _list->end(); ++it) {
            qDebug() << it.key() << ":" << it.value();
        }
        bResult = true;
    } else {
        qDebug() << "JSON parse error:" << jsonError.errorString();
    }
    return bResult;
}

ImportPicture::ImportPicture(QObject *parent)
    : QObject{parent}
{}

ImportPicture::ImportPicture(QString pictureFile, QString directory)
{
    m_PictureFile = pictureFile;
    m_USBDirectory = directory;
}

void ImportPicture::importToFile()
{
    bool bResult = false;
    QProcess process;
    QString program = "./QcrAi";

    qDebug() << "Directory: " << m_USBDirectory;
    qDebug() << "pictureFile: " << m_PictureFile;

    QStringList arguments;
    arguments.append(m_USBDirectory + "/" + m_PictureFile);

    process.start(program, arguments);

    process.waitForFinished(30000);

    QString output = process.readAllStandardOutput();
    qDebug() << output;
    QString error = process.readAllStandardError();
    qDebug() << error;

    output = R"({"code":200,"data":{"井别":"","井号":"华H108-2井","井型":"","垂直段长度":"","完钻井深":"3775.00","水平段长度":"1577.00","生产套管下深":"3773.73","表层套管下深":"237.76t","设计井深":"","造斜点":"525.00"},"message":"success","success":true})";

    if(!output.isEmpty())
    {
        m_WellInfoList.clear();
        bResult = parseJson(output, &m_WellInfoList);
        importFinished(bResult, error);
    }
}
