#include "exportworker.h"
#include <QDir>
bool ExportWorker::GetTargetDirectory(const QString localDirectory, QString &targetDirectory)
{
    QString tmpStr = localDirectory;
    QStringList tmpList = tmpStr.split("/");
    if(tmpList.size() == 0)
        return false;
    tmpStr = tmpList.at(tmpList.size() - 1);
    tmpList.clear();
    tmpList = tmpStr.split(".");
    if(tmpList.size() == 0)
        return false;
    targetDirectory = tmpList.at(0);
    return true;
}

bool ExportWorker::DeleteLocalCSVFiles()
{
    bool bResult = true;
    QDir dir("/opt/MeteringDisplay/bin/");

    // 设置文件名过滤器
    QStringList filters;
    filters << "*.csv";
    dir.setNameFilters(filters);

    // 获取匹配的文件列表
    QFileInfoList fileList = dir.entryInfoList(QDir::Files);

    if (fileList.isEmpty()) {
        qDebug() << "No CSV files found to delete";
        return true; // 没有文件也算成功
    }

    // 删除每个文件
    foreach (const QFileInfo &fileInfo, fileList) {
        if (!QFile::remove(fileInfo.absoluteFilePath())) {
            qDebug() << "Failed to delete:" << fileInfo.absoluteFilePath();
            bResult = false;
        } else {
            qDebug() << "Deleted:" << fileInfo.absoluteFilePath();
        }
    }
    return bResult;
}

ExportWorker::ExportWorker(QObject *parent)
    : QObject{parent}
{}
