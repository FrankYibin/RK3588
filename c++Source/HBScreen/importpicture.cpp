#include "importpicture.h"
#include "wellparameter.h"
#include <QProcess>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

bool ImportPicture::parseJson(const QString message, QMap<QString, QString> *_list)
{
    bool bResult = false;
    if(_list == nullptr)
        return bResult;

    // 从混合消息中提取JSON部分
    QString jsonString;
    QStringList lines = message.split('\n');
    
    for (const QString &line : lines) {
        QString trimmedLine = line.trimmed();
        // 移除可能的回车符
        trimmedLine = trimmedLine.remove('\r');
        
        // 查找以{开头且包含"success"的行（JSON数据）
        if (trimmedLine.startsWith("{") && trimmedLine.contains("\"success\"")) {
            jsonString = trimmedLine;
            qDebug() << "提取到JSON:" << jsonString;
            break;
        }
    }
    
    // 如果没有找到JSON，尝试直接解析原始消息
    if (jsonString.isEmpty()) {
        jsonString = message;
        qDebug() << "未找到JSON行，使用原始消息:" << jsonString;
    }

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &jsonError);
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
        qDebug() << "尝试解析的内容:" << jsonString;
    }
    return bResult;
}

bool ImportPicture::processData(QMap<QString, QString> *_list)
{
    if(_list == nullptr)
        return false;
    if(_list->size() == 0)
        return false;
    QMap<QString, QString>::iterator iter = _list->find("井别");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setWellOfficalType(iter.value());
    }
    iter = _list->find("井号");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setWellNumber(iter.value());
    }
    iter = _list->find("井型");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setWellModel(iter.value());
    }
    iter = _list->find("垂直段长度");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setVerticalLength(iter.value());
    }
    iter = _list->find("完钻井深");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setCompleteWellDepth(iter.value());
    }
    iter = _list->find("水平段长度");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setHorizontalLength(iter.value());
    }
    iter = _list->find("生产套管下深");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setProductionCasingDepth(iter.value());
    }
    iter = _list->find("表层套管下深");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setSurfaceCasingDepth(iter.value());
    }
    iter = _list->find("设计井深");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setDesignWellDepth(iter.value());
    }
    iter = _list->find("造斜点");
    if(iter != _list->end())
    {
        if(iter.value().isEmpty() == false)
            WellParameter::GetInstance()->setKickOffPoint(iter.value());
    }   
    return true;
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
    // ./OcrAi /run/media/sda4/602224575.jpg
    QString program = "./OcrAi";  // 修正程序名：QcrAi -> OcrAi
    
    // 设置工作目录
    process.setWorkingDirectory("/opt/MeteringDisplay/bin");
    
    QStringList arguments;
    QString strFile = m_USBDirectory + "/" + m_PictureFile;
    qDebug() << "OCR处理文件: " << strFile;
    qDebug() << "工作目录: " << process.workingDirectory();
    qDebug() << "程序路径: " << program;
    arguments.append(strFile);

    process.start(program, arguments);
    
    if (!process.waitForStarted(5000)) {
        qDebug() << "程序启动失败，错误: " << process.errorString();
        return;
    }

    process.waitForFinished(60000);

    QString output = process.readAllStandardOutput();
    qDebug() << output;
    QString error = process.readAllStandardError();
    qDebug() << error;

    // output = R"({"code":200,"data":{"井别":"","井号":"华H108-2井","井型":"","垂直段长度":"","完钻井深":"3775.00","水平段长度":"1577.00","生产套管下深":"3773.73","表层套管下深":"237.76t","设计井深":"","造斜点":"525.00"},"message":"success","success":true})";

    if(!output.isEmpty())
    {
        m_WellInfoList.clear();
        bResult = parseJson(output, &m_WellInfoList);
        bResult = processData(&m_WellInfoList);
        importFinished(bResult, error);
    }
}
