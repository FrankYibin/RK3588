#include "TensiometerManager.h"
#include <QDebug>

TensiometerManager::TensiometerManager(QObject *parent)
    : QAbstractListModel(parent), m_db(&HBDatabase::getInstance())
{
    QList<TensiometerData> list;
    if (m_db->loadAllTensiometerData(list)) {
        beginResetModel();
        m_items = list;
        endResetModel();
    } else {
        qDebug() << "Failed to load tensiometer data from database.";
    }
}

int TensiometerManager::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant TensiometerManager::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
        return QVariant();

    if (role == IndexRole)
        return index.row() + 1;  // 1-based index

    const TensiometerData &item = m_items.at(index.row());

    switch (role) {
    case NumberRole:
        return item.tensiometerNumber;
    case TypeRole:
        return item.tensiometerType;
    case RangeRole:
        return item.tensiometerRange;
    case SignalRole:
        return item.tensiometerSignal;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TensiometerManager::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NumberRole] = "SensorNumber";
    roles[TypeRole] = "SensorType";
    roles[RangeRole] = "SensorRange";
    roles[SignalRole] = "AnalogRange";
    roles[IndexRole] = "index";
    return roles;
}

void TensiometerManager::addTensiometer(const QString &number, int type, int range, int signal) {
    TensiometerData data;
    data.id = 0;
    data.tensiometerNumber = number;
    data.tensiometerType = type;
    data.tensiometerRange = range;
    data.tensiometerSignal = signal;

    if (m_db->insertTensiometerData(data)) {
        beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
        m_items.append(data);
        endInsertRows();
    } else {
        qDebug() << "Failed to insert tensiometer data.";
    }
}

void TensiometerManager::removeTensiometer(int index) {
    if (index < 0 || index >= m_items.size())
        return;

    int id = m_items[index].id;
    if (m_db->deleteTensiometerData(id)) {
        beginRemoveRows(QModelIndex(), index, index);
        m_items.removeAt(index);
        endRemoveRows();
    } else {
        qDebug() << "Failed to delete tensiometer data with id:" << id;
    }
}

void TensiometerManager::clear() {
    beginResetModel();
    for (const TensiometerData &data : m_items) {
        m_db->deleteTensiometerData(data.id);
    }
    m_items.clear();
    endResetModel();
}

void TensiometerManager::updateTensiometer(int index, const QString &number, int type, int range, int signal) {
    if (index < 0 || index >= m_items.size())
        return;

    TensiometerData &data = m_items[index];
    data.tensiometerNumber = number;
    data.tensiometerType = type;
    data.tensiometerRange = range;
    data.tensiometerSignal = signal;

    if (m_db->updateTensiometerData(data)) {
        emit dataChanged(this->index(index), this->index(index));
    } else {
        qDebug() << "Failed to update tensiometer data at index:" << index;
    }
}

const QList<TensiometerData>& TensiometerManager::items() const {
    return m_items;
}
