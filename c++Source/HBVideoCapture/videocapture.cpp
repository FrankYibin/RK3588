#include "videocapture.h"
#include <QPainter>
#include <QDir>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QProcess>
#include "c++Source/HBScreen/usermanagermodel.h"
VideoCapture* VideoCapture::_ptrVideoCapture = nullptr;
bool VideoCapture::ParseComparedLog(const QString &log)
{
    // 打印日志内容，便于调试
    qDebug() << "Log content:" << log;

    // 尝试用正则表达式提取JSON部分
    QRegularExpression jsonRegex(R"(\{[\s\S]*\})"); // 支持多行JSON
    QRegularExpressionMatch jsonMatch = jsonRegex.match(log);

    QString jsonString;
    if (jsonMatch.hasMatch()) {
        jsonString = jsonMatch.captured(0); // 提取匹配到的 JSON 部分
    } else {
        // 如果正则匹配不到，尝试手动提取
        int startIndex = log.indexOf('{');
        int endIndex = log.lastIndexOf('}');
        if (startIndex != -1 && endIndex != -1 && startIndex < endIndex) {
            jsonString = log.mid(startIndex, endIndex - startIndex + 1);
        }
    }

    // 检查是否成功提取JSON
    if (jsonString.isEmpty()) {
        qDebug() << "No JSON found in the log.";
        return false;
    }

    // 解析JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();

        // 提取errno, msg, result_num, face_token
        int errnoValue = jsonObj["errno"].toInt();
        QString msg = jsonObj["msg"].toString();
        QJsonObject data = jsonObj["data"].toObject();
        QString faceToken = data["face_token"].toString();
        int resultNum = data["result_num"].toInt();
        m_ComparedResult.Errno = errnoValue;
        m_ComparedResult.Msg = msg;
        m_ComparedResult.FaceToken = faceToken;
        m_ComparedResult.ComparedUserCount = resultNum;

        // 输出解析结果
        // qDebug() << QString("Errno: %1, Message: %2, Face Token: %3, Result Number: %4")
        //                 .arg(errnoValue)
        //                 .arg(msg)
        //                 .arg(faceToken)
        //                 .arg(resultNum);

        // 提取results数组
        QJsonArray results = data["result"].toArray();
        // qDebug() << "Results:";
        for (const QJsonValue &value : results) {
            QJsonObject resultObj = value.toObject();
            QString groupId = resultObj["group_id"].toString();
            double score = resultObj["score"].toDouble();
            QString userId = resultObj["user_id"].toString();

            qDebug() << QString("  Group ID: %1, Score: %2, User ID: %3")
                            .arg(groupId)
                            .arg(score)
                            .arg(userId);
            m_ComparedResult.GroupID = groupId;
            m_ComparedResult.Score = score;
            m_ComparedResult.UserID = userId;
        }
    }
    else
    {
        qDebug() << "Failed to parse JSON.";
        return false;
    }
    return true;
}

bool VideoCapture::ParseUserListLog(const QString &log)
{
    // 打印日志内容，便于调试
    qDebug() << "Log content:" << log;

    // 尝试用正则表达式提取JSON部分
    QRegularExpression jsonRegex(R"(\{[\s\S]*\})"); // 支持多行JSON
    QRegularExpressionMatch jsonMatch = jsonRegex.match(log);

    QString jsonString;
    if (jsonMatch.hasMatch()) {
        jsonString = jsonMatch.captured(0); // 提取匹配到的 JSON 部分
    } else {
        // 如果正则匹配不到，尝试手动提取
        int startIndex = log.indexOf('{');
        int endIndex = log.lastIndexOf('}');
        if (startIndex != -1 && endIndex != -1 && startIndex < endIndex) {
            jsonString = log.mid(startIndex, endIndex - startIndex + 1);
        }
    }

    // 检查是否成功提取JSON
    if (jsonString.isEmpty()) {
        qDebug() << "No JSON found in the log.";
        return false;
    }

    // 解析JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();

        // 提取errno, msg, result_num, face_token
        int errnoValue = jsonObj["errno"].toInt();
        QString msg = jsonObj["msg"].toString();
        QJsonObject data = jsonObj["data"].toObject();
        QString faceToken = data["face_token"].toString();
        int resultNum = data["result_num"].toInt();
        m_ComparedResult.Errno = errnoValue;
        m_ComparedResult.Msg = msg;
        m_ComparedResult.FaceToken = faceToken;
        m_ComparedResult.ComparedUserCount = resultNum;

        // 输出解析结果
        // qDebug() << QString("Errno: %1, Message: %2, Face Token: %3, Result Number: %4")
        //                 .arg(errnoValue)
        //                 .arg(msg)
        //                 .arg(faceToken)
        //                 .arg(resultNum);

        // 提取results数组
        QJsonArray results = data["user_id_list"].toArray();
        // qDebug() << "Results:";
        for (const QJsonValue &value : results) {
            QJsonObject resultObj = value.toObject();
            QString userId = resultObj["user_id"].toString();
            m_UserIDList.append(userId);
        }
    }
    else
    {
        qDebug() << "Failed to parse JSON.";
        return false;
    }
    return true;
}

void VideoCapture::RunCommand(const QString cmd, const QStringList arguments)
{
    QString str = "CMD: ";
    str += cmd + " ";
    for(int i = 0; i < arguments.size(); i++)
    {
        str += arguments[i] + " ";
    }
    qDebug() << str;
}

VideoCapture *VideoCapture::GetInstance()
{
    if(_ptrVideoCapture == nullptr)
        _ptrVideoCapture = new VideoCapture();
    return _ptrVideoCapture;
}

bool VideoCapture::detectFaceImage()
{
#ifdef RK3588
    // 创建 QProcess 对象
    QProcess process;

    // 设置要执行的命令
    QString program = "./faceTest.sh"; // 你可以替换为其他 Linux 命令
    QStringList arguments; // 这里可以添加命令参数，例如 "-l" 或其他
    arguments.append("-compare");
    arguments.append("/opt/MeteringDisplay/bin/image/tmpImage.jpg");

    RunCommand(program, arguments);

    // 启动进程
    process.start(program, arguments);

    // 等待进程结束
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty()) {
        if(ParseComparedLog(output) == true)
        {
            // 输出解析结果
            qDebug() << QString("Errno: %1, Message: %2, Face Token: %3, User Count: %4, GroupID: %5, UserID: %6, Score: %7")
                            .arg(m_ComparedResult.Errno)
                            .arg(m_ComparedResult.Msg)
                            .arg(m_ComparedResult.FaceToken)
                            .arg(m_ComparedResult.ComparedUserCount)
                            .arg(m_ComparedResult.GroupID)
                            .arg(m_ComparedResult.UserID)
                            .arg(m_ComparedResult.Score);
        }
        else
            return false;

    }
    else
        return false;
    if (!error.isEmpty()) {
        qDebug() << "Command Error:" << error;
        return false;
    }
    if((m_ComparedResult.Errno == 0) && (m_ComparedResult.Score > 80))
    {
        QString userId = m_ComparedResult.UserID;
        if(UserManagerModel::GetInstance().ValidateUser(userId) == false)
            return false;
    }
    else
        return false;
#endif
    return true;
}

bool VideoCapture::generateFaceEigenValue(QString userId)
{
#ifdef RK3588
    // 创建 QProcess 对象
    QProcess process;

    // 设置要执行的命令
    QString program = "./faceTest.sh"; // 你可以替换为其他 Linux 命令
    QStringList arguments; // 这里可以添加命令参数，例如 "-l" 或其他
    arguments.append("-record");
    arguments.append("HB");
    arguments.append(userId);
    arguments.append("/opt/MeteringDisplay/bin/image/tmpImage.jpg");
    RunCommand(program, arguments);

    // 启动进程
    process.start(program, arguments);

    // 等待进程结束
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty()) {
        if(ParseComparedLog(output) == true)
        {
            // 输出解析结果
            qDebug() << QString("Errno: %1, Message: %2, Face Token: %3, User Count: %4, GroupID: %5, UserID: %6, Score: %7")
                            .arg(m_ComparedResult.Errno)
                            .arg(m_ComparedResult.Msg)
                            .arg(m_ComparedResult.FaceToken)
                            .arg(m_ComparedResult.ComparedUserCount)
                            .arg(m_ComparedResult.GroupID)
                            .arg(m_ComparedResult.UserID)
                            .arg(m_ComparedResult.Score);
        }
        else
            return false;
    }
    else
        return false;
    if (!error.isEmpty()) {
        qDebug() << "Command Error:" << error;
        return false;
    }
    if(m_ComparedResult.Errno != 0)
    {
        return false;
    }
#endif
    return true;
}

bool VideoCapture::deleteFaceRecord(QString userId)
{
#ifdef RK3588
    // 创建 QProcess 对象
    QProcess process;

    // 设置要执行的命令
    QString program = "./faceTest.sh"; // 你可以替换为其他 Linux 命令
    QStringList arguments; // 这里可以添加命令参数，例如 "-l" 或其他
    arguments.append("-delete");
    arguments.append("HB");
    arguments.append(userId);
    RunCommand(program, arguments);

    // 启动进程
    process.start(program, arguments);

    // 等待进程结束
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty()) {
        if(ParseComparedLog(output) == true)
        {
            // 输出解析结果
            qDebug() << QString("Errno: %1, Message: %2, Face Token: %3, User Count: %4, GroupID: %5, UserID: %6, Score: %7")
                            .arg(m_ComparedResult.Errno)
                            .arg(m_ComparedResult.Msg)
                            .arg(m_ComparedResult.FaceToken)
                            .arg(m_ComparedResult.ComparedUserCount)
                            .arg(m_ComparedResult.GroupID)
                            .arg(m_ComparedResult.UserID)
                            .arg(m_ComparedResult.Score);

        }
    }
    if (!error.isEmpty()) {
        qDebug() << "Command Error:" << error;
    }
#endif
    return false;
}

bool VideoCapture::getUsersList()
{
#ifdef RK3588
    QProcess process;
    // 设置要执行的命令
    QString program = "./faceTest.sh"; // 你可以替换为其他 Linux 命令
    QStringList arguments; // 这里可以添加命令参数，例如 "-l" 或其他
    arguments.append("-get");
    arguments.append("userlist");
    arguments.append("HB");
    RunCommand(program, arguments);

    // 启动进程
    process.start(program, arguments);
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty()) {
        if(ParseUserListLog(output) == true)
        {
            // 输出解析结果
            for(int i = 0; i < m_UserIDList.size(); i++)
            {
                QString strUserID = m_UserIDList[i];
                if(strUserID.contains("_") == true)
                {
                    qDebug() << "the User iD will be deleted" << m_UserIDList[i];
                    deleteFaceRecord(strUserID);
                }
                qDebug() << i << ": " << m_UserIDList[i];
            }
        }
    }
    if (!error.isEmpty()) {
        qDebug() << "Command Error:" << error;
    }
#endif
    return false;
}

QString VideoCapture::getImageDirectory()
{
    return m_ImagePath;
}

VideoCapture::VideoCapture(QQuickItem *parent)
    : QObject(parent)
{
    QString str = QDir::currentPath();
    QDir dir(str);
    if(!dir.exists("image"))
    {
        if(dir.mkdir("image"))
        {
            qDebug() << "image has been created";
        }
        else
        {
            qDebug() << "No way to create image folder";
        }
    }
    else
        qDebug() << "image folde is exist in current path";
    m_ImagePath = str + "/image";
    getUsersList();
}
