#include "historyoperationmodel.h"

HistoryOperationModel::HistoryOperationModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int HistoryOperationModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_rows.size();
}

QVariant HistoryOperationModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid() || idx.row() >= m_rows.size())
        return {};

    const Row &r = m_rows.at(idx.row());
    switch (role) {
    case IndexRole:       return r.index;
    case WellNumberRole:  return r.wellNumber;
    case OperateTypeRole: return r.operateType;
    case OperaterRole:    return r.operater;
    case DateRole:        return r.date.toString("yyyy-MM-dd HH:mm");
    case DescriptionRole: return r.description;
    default:              return {};
    }
}

QHash<int, QByteArray> HistoryOperationModel::roleNames() const
{
    return {
        {IndexRole,       "Index"},
        {WellNumberRole,  "WellNumber"},
        {OperateTypeRole, "OperateType"},
        {OperaterRole,    "Operater"},
        {DateRole,        "Date"},
        {DescriptionRole, "Description"}
    };
}

void HistoryOperationModel::clear()
{
    if (m_rows.isEmpty())
        return;
    beginResetModel();
    m_rows.clear();
    endResetModel();
}

void HistoryOperationModel::reset(const QList<Row> &rows)
{
    beginResetModel();
    m_rows = rows;
    endResetModel();
}
