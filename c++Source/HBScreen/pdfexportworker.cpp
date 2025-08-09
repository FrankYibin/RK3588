#include "pdfexportworker.h"

PDFExportWorker::PDFExportWorker(const QStringList &localfiles, const QString USBDirectory)
{
    m_LocalFiles.clear();
    m_LocalFiles = localfiles;
    m_USBDirectory = USBDirectory;
}

void PDFExportWorker::exportToFile()
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
            targetDirectory += ".pdf";
            ExportToPDF(localAppDirectory, m_USBDirectory + "/" + targetDirectory);
            // if(!QFile::copy(localAppDirectory, m_USBDirectory + "/" + targetDirectory))
            // {
            //     message = "Failed to copy " + localAppDirectory + " to " + m_USBDirectory + "/" + targetDirectory;
            //     bResult = false;
            //     break;
            // }
            emit exportPrograss(i, m_LocalFiles.size());
        }
    }
    if(bResult == true)
        message = "Successed to copy " + localAppDirectory + " to " + m_USBDirectory + "/" + targetDirectory;
    emit exportFinished(bResult, message);
}

bool PDFExportWorker::ExportToPDF(const QString localDirectory, const QString targetDirectory)
{
    bool bResult = false;
    // 创建 QProcess 对象
    QProcess process;

    // 设置要执行的命令
    QString program = "python"; // 你可以替换为其他 Linux 命令
    QStringList arguments; // 这里可以添加命令参数，例如 "-l" 或其他
    arguments.append("ConvertPDF.py");
    arguments.append(localDirectory);
    arguments.append("-o");
    arguments.append(targetDirectory);

    // 启动进程
    process.start(program, arguments);

    // 等待进程结束
    process.waitForFinished(100000);

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    qDebug() << output;
    QString error = process.readAllStandardError();
    qDebug() << error;

    // 输出结果
    if (!output.isEmpty())
        bResult = true;
    return bResult;
}
