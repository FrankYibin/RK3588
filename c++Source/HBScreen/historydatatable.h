#ifndef HISTORYDATATABLE_H
#define HISTORYDATATABLE_H

#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include "c++Source/HBDefine.h"

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

    static HistoryDataTable* GetInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setRange(const QString& startIso, const QString& endIso);

//    Q_INVOKABLE void resetModel();

    void loadFromDatabase();

    Q_INVOKABLE void loadFromDatabase(const QDateTime& start, const QDateTime& end);

    Q_INVOKABLE bool isAvailaleDiskUSB();
    Q_INVOKABLE bool exportData();
public slots:

protected:
    explicit HistoryDataTable(QObject *parent = nullptr);

private:
    QList<HistoryData>  m_dataList;
    QDateTime           m_start;
    QDateTime           m_end;
    QString             m_USBDirectory;
    static HistoryDataTable* _ptrHistoryDataTable;
private:
    bool ExportToCSV(const QString& filePath, const QStringList& headers, const QList<QStringList>& data);
};

#endif // HISTORYDATATABLE_H
