#ifndef HISTORYDATATABLE_H
#define HISTORYDATATABLE_H

#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include "c++Source/HBDefine.h"
#include "exportworker.h"
// #include "csvexportworker.h"
// #include "textexportworker.h"
// #include "pdfexportworker.h"
// #include "excelexportworker.h"

class HistoryDataTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum WellRoles {
        IndexRole = Qt::UserRole + 1,
        WellNumberRole,
        DateRole,
        OperateTypeRole,
        OperaterRole,
        DepthRole,
        VelocityRole,
        VelocityUnitRole,
        TensionsRole,
        TensionIncreamentRole,
        TensionUnitRole,
        MaxTensionRole,
        HarnessTensionRole,
        SafetyTensionRole,
        ExceptionRole
    };

    enum FILE_TYPE
    {
        CSV_FILE = 0,
        TXT_FILE,
        PDF_FILE,
        XLSX_FILE
    };

    static HistoryDataTable* GetInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setRange(const QString& startIso, const QString& endIso);

//    Q_INVOKABLE void resetModel();

    Q_INVOKABLE void loadFromDatabase(const QDateTime start, const QDateTime end,const QString currentUser, bool includeExceptionsOnly);

    Q_INVOKABLE bool isAvailaleDiskUSB();
    Q_INVOKABLE bool exportData(int fileType);
public slots:

protected:
    explicit HistoryDataTable(QObject *parent = nullptr);

private:
    QList<HistoryData>  m_dataList;
    QDateTime           m_start;
    QDateTime           m_end;
    QString             m_USBDirectory;
    static constexpr int MAX_RECORDS_IN_ONE_FILE = 1000;
    static HistoryDataTable* _ptrHistoryDataTable;
private:
    bool ExportToCSV(const QString& filePath, const QStringList& headers, const QList<QStringList>& data);
private slots:
    void ExportToCSVAsync(QStringList &localfiles);
    void ExportToTextAsync(QStringList &localfiles);
    void ExportToPDFAsync(QStringList &localfiles);
    void ExportToExcelAsync(QStringList &localfiles);
private slots:
    void onExportFinished(bool success, const QString &message);
signals:
    void signalExportCompleted(bool success, const QString &message);
    void signalExportPrograss(int current, int total);
private:
    QThread *m_exportThread = nullptr;
    ExportWorker *m_exportWorker = nullptr;

};

#endif // HISTORYDATATABLE_H
