#include "csvexportworker.h"
CSVExportWorker::CSVExportWorker(const QStringList &localfiles, const QString USBDirectory)
{
    m_LocalFiles.clear();
    m_LocalFiles = localfiles;
    m_USBDirectory = USBDirectory;
}

void CSVExportWorker::exportToFile()
{
    bool bResult = true;
    QString message;
    QString localAppDirectory, targetDirectory;
    if(m_LocalFiles.size() == 0)
        bResult = false;
    else
    {
        for(int i = 0; i < m_LocalFiles.size(); i++)
        {
            localAppDirectory = m_LocalFiles.at(i);
            bResult = QFile::exists(localAppDirectory);
            if(bResult == false)
                break;
            QString tmpStr = m_LocalFiles.at(i);
            bResult = GetTargetDirectory(tmpStr, targetDirectory);
            if(bResult == false)
                break;
            targetDirectory += ".csv";
            if(!QFile::copy(localAppDirectory, m_USBDirectory + "/" + targetDirectory))
            {
                message = "Failed to copy " + localAppDirectory + " to " + m_USBDirectory + "/" + targetDirectory;
                bResult = false;
                break;
            }
            emit exportPrograss(i, m_LocalFiles.size());
        }
    }
    if(bResult == true)
        message = "Successed to copy " + localAppDirectory + " to " + m_USBDirectory + "/" + targetDirectory;
    emit exportFinished(bResult, message);
}

