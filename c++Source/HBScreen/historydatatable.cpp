#include "historydatatable.h"
#include "c++Source/HBData/hbdatabase.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QStorageInfo>
#include <qcoreapplication.h>
#include <QProcess>
#include "c++Source/HBScreen/usermanagermodel.h"
HistoryDataTable* HistoryDataTable::_ptrHistoryDataTable = nullptr;
HistoryDataTable::HistoryDataTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    QString ConvertExcelPath    = QCoreApplication::applicationDirPath() + "/ConvertExcel.py";
    QString ConvertPDFPath      = QCoreApplication::applicationDirPath() + "/ConvertPDF.py";
    QString SimsunPath          = QCoreApplication::applicationDirPath() + "/simsun.ttc";
    if(!QFile::exists(ConvertExcelPath))
    {
        if(!QFile::copy(":/misc/ConvertExcel.py", ConvertExcelPath))
        {
            qWarning() << "Failed to copy ConvertExcel.py from resources to" << ConvertExcelPath;
            return;
        }
    }
    if(!QFile::exists(ConvertPDFPath))
    {
        if(!QFile::copy(":/misc/ConvertPDF.py", ConvertPDFPath))
        {
            qWarning() << "Failed to copy ConvertPDF.py from resource to" << ConvertPDFPath;
        }
    }
}

HistoryDataTable *HistoryDataTable::GetInstance()
{
    if (!_ptrHistoryDataTable)
    {
        _ptrHistoryDataTable = new HistoryDataTable();
    }
    return _ptrHistoryDataTable;
}

int HistoryDataTable::rowCount(const QModelIndex &) const
{
    return m_dataList.count();
}

int HistoryDataTable::columnCount(const QModelIndex &) const
{
    return 1; // Not used for QML TableView when using roles
}

QVariant HistoryDataTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_dataList.size())
        return QVariant();

    const HistoryData &item = m_dataList.at(index.row());

    switch (role) {
    case IndexRole: return  index.row();
    case WellNumberRole: return item.wellNumber;
    case DateRole: return item.date;
    case OperateTypeRole: return item.operateType;
    case OperaterRole: return item.operater;
    case DepthRole: return item.depth;
    case VelocityRole: return item.velocity ;
    case VelocityUnitRole: return item.velocityUnit;
    case TensionsRole: return item.tensions ;
    case TensionIncreamentRole: return item.tensionIncrement ;
    case TensionUnitRole: return item.tensionUnit;
    case MaxTensionRole: return item.maxTension ;
    case HarnessTensionRole: return item.harnessTension ;
    case SafetyTensionRole: return item.safetyTension ;
    case ExceptionRole: return item.exception;
    default: return QVariant();
    }
}

QHash<int, QByteArray> HistoryDataTable::roleNames() const
{
    return {
        { IndexRole, "Index" },
        { WellNumberRole, "WellNumber" },
        { DateRole, "Date" },
        { OperateTypeRole, "OperateType" },
        { OperaterRole, "Operater" },
        { DepthRole, "Depth" },
        { VelocityRole, "Velocity" },
        { VelocityUnitRole, "VelocityUnit" },
        { TensionsRole, "Tensions" },
        { TensionIncreamentRole, "TensionIncreament" },
        { TensionUnitRole, "TensionUnit" },
        { MaxTensionRole, "MaxTension" },
        { HarnessTensionRole, "HarnessTension" },
        { SafetyTensionRole, "SafetyTension" },
        { ExceptionRole, "Exception" },
    };
}

void HistoryDataTable::setRange(const QString &startIso, const QString &endIso)
{
    QDateTime s = QDateTime::fromString(startIso, Qt::ISODate);
    QDateTime e = QDateTime::fromString(endIso,   Qt::ISODate);
    if (!s.isValid() || !e.isValid()) {
        qWarning() << "HistoryDataTable: invalid time strings";
        return;
    }
    if (s == m_start && e == m_end)
        return;

    m_start = s;
    m_end   = e;

    loadFromDatabase(m_start, m_end,UserManagerModel::GetInstance().CurrentUser(),false);

}


void HistoryDataTable::loadFromDatabase(const QDateTime start, const QDateTime end,const QString currentUser, bool includeExceptionsOnly)
{
    beginResetModel();
    m_dataList = HBDatabase::GetInstance().loadHistoryData(start, end,currentUser,includeExceptionsOnly);
    endResetModel();
}


bool HistoryDataTable::isAvailaleDiskUSB()
{
    bool bResult = false;
    m_USBDirectory.clear();
#ifdef RK3588
    // 导出到CSV文件
    QString filePath = "";
    QString strPath = "";
    filePath.clear();
    strPath.clear();
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes())
    {
        if(storage.isReady())
        {
            qDebug() << "Found USB Drive:";
            strPath = storage.rootPath();
            qDebug() << "Path:" << storage.rootPath();
            qDebug() << "File System Type: " << storage.fileSystemType();
            qDebug() << "Total Size: " << storage.bytesTotal() / (1024 * 1024) << "MB";
            qDebug() << "Available Size: " << storage.bytesAvailable() / (1024 * 1024) << "MB";
            qDebug() << "-------------------------";
            if(strPath.contains("/run/media/"))
            {
                if(strPath.contains("/run/media/mmcblk") == false)
                {
                    m_USBDirectory = strPath;
                    bResult = true;
                    break;
                }
                else
                    m_USBDirectory.clear();
            }
            else
                m_USBDirectory.clear();
        }
    }
#endif
    return bResult;
}

bool HistoryDataTable:: exportData(int fileType)
{
    bool bResult = false;

    if(m_USBDirectory.isEmpty() == true)
        return false;
    QList<QStringList> rows;
    QStringList headers = {"井号", "时间", "工种", "操作员", "深度", "速度","速度单位","张力","张力增量","张力单位","最大张力",
                           "缆头张力", "安全张力",
                           "异常数据标识"   };

    for(int i=0;i<m_dataList.count();i++)
    {
        QStringList value= {
            m_dataList[i].wellNumber,
            m_dataList[i].date,
            m_dataList[i].operateType,
            m_dataList[i].operater,
            m_dataList[i].depth,
            m_dataList[i].velocity,
            m_dataList[i].velocityUnit,
            m_dataList[i].tensions,
            m_dataList[i].tensionIncrement,
            m_dataList[i].tensionUnit,
            m_dataList[i].maxTension,
            m_dataList[i].harnessTension,
            m_dataList[i].safetyTension,
            m_dataList[i].exception,
        };
        rows.append(value);
    }
    QString localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.csv";
    switch(fileType)
    {
    case CSV_FILE:
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.csv";
        break;
    case TXT_FILE:
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.txt";
        break;
    case PDF_FILE:
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.csv";
        break;
    case XLSX_FILE:
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.csv";
        break;
    default:
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.csv";
        break;
    }

    bResult = ExportToCSV(localAppDirectory, headers, rows);
    if(bResult == false)
        return bResult;
    bResult = QFile::exists(localAppDirectory);
    if(bResult == false)
        return bResult;


    switch(fileType)
    {
    case CSV_FILE:
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.csv";
        break;
    case TXT_FILE:
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.txt";
        break;
    case PDF_FILE:
        ExportToPDF();
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.pdf";
        break;
    case XLSX_FILE:
        ExportToXLSX();
        localAppDirectory = QCoreApplication::applicationDirPath()+ "/output.xlsx";
        break;
    default:
        break;
    }
    bResult = QFile::exists(localAppDirectory);
    if(bResult == false)
        return bResult;
    if(!QFile::copy(localAppDirectory, m_USBDirectory))
    {
        qWarning() << "Failed to copy " << localAppDirectory << " to " << m_USBDirectory;
        bResult = false;
    }
    return bResult;
}


bool HistoryDataTable:: ExportToCSV(const QString& filePath, const QStringList& headers, const QList<QStringList>& data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件：" << filePath;
        return false;
    }

    QTextStream out(&file);

    // 写入表头
    out << headers.join(",") << "\n";

    // 写入数据
    for (const auto& row : data) {
        out << row.join(",") << "\n";
    }

    file.close();
    qDebug() << "数据已成功导出到：" << filePath;
    return true;
}

bool HistoryDataTable::ExportToPDF()
{
    bool bResult = false;
    // 创建 QProcess 对象
    QProcess process;

    // 设置要执行的命令
    QString program = "python"; // 你可以替换为其他 Linux 命令
    QStringList arguments; // 这里可以添加命令参数，例如 "-l" 或其他
    arguments.append("ConvertPDF.py");

    // 启动进程
    process.start(program, arguments);

    // 等待进程结束
    process.waitForFinished();

    // 获取命令输出
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    // 输出结果
    if (!output.isEmpty())
        bResult = true;
    return bResult;
}

bool HistoryDataTable::ExportToXLSX()
{

}
