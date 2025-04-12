#include "rs232.h"

RS232* RS232::s_RS232 = nullptr;

RS232 *RS232::getInstance()
{
    if(!s_RS232){
        s_RS232 = new RS232();
    }
    return s_RS232;

}

RS232::RS232(QObject *parent)
    : QAbstractListModel{parent}
{
    loadTestData();
}



int RS232::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}


QVariant RS232::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= m_data.count())
        return QVariant();

    const _GroundSerial &item = m_data.at(index.row());

    switch (role) {
    case PortRole:
        return item.Port;
    case BaudRateRole:
        return item.BaudRate;
    case DataBitRole:
        return item.DataBit;
    case ProtocolRole:
        return item.SerialType;
    default:
        return QVariant();;
    }

}

QHash<int, QByteArray> RS232::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PortRole] = "port";
    roles[BaudRateRole] = "baudRate";
    roles[DataBitRole] = "dataBit";
    roles[ProtocolRole] = "serialType";
    return roles;

}

void RS232::setSerial(int index, int port,int baudRate, int dataBit, int serialType)
{
    if(index < 0 || index >= m_data.size())
        return;

    _GroundSerial &item = m_data[index];
    item.Port = port;        // 更新串口号
    item.BaudRate = baudRate;
    item.DataBit = dataBit;
    item.SerialType = serialType;

    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex);

}

void RS232::loadTestData()
{
    m_data.clear();
    // m_data.append({1, 9600, 8, 0});
    // m_data.append({2, 115200, 8, 1});
    // m_data.append({3, 38400, 7, 0});
    beginResetModel();
    endResetModel();

}

