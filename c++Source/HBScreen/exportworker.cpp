#include "exportworker.h"

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

ExportWorker::ExportWorker(QObject *parent)
    : QObject{parent}
{}
