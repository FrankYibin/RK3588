#include "tensiometermanager.h"
#include "tensionscalemanager.h"
#include "c++Source/HBModbus/hbmodbusclient.h"
#include "c++Source/HBQmlEnum.h"
#include "c++Source/HBUtility/hbutilityclass.h"
#include <QDebug>
QList<Tensiometer::TENSIONMETER> TensiometerManager::m_TensiometerList;
TensiometerManager* TensiometerManager::_ptrTensiometerManager = nullptr;
TensiometerManager::TensiometerManager(QObject *parent)
    : QAbstractListModel(parent),
      m_db(&HBDatabase::GetInstance())
{
//    beginResetModel();
//    m_TensiometerList.clear();
//    if(m_db->LoadTensiometerTable(m_TensiometerList) == false)
//    {
//        qDebug() << "Failed to load tensiometer data from database.";
//    }
//    endResetModel();
    resetModel();
}


TensiometerManager *TensiometerManager::GetInstance()
{
    if (!_ptrTensiometerManager)
    {
        _ptrTensiometerManager = new TensiometerManager();
    }
    return _ptrTensiometerManager;
}

int TensiometerManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_TensiometerList.count();
}

QVariant TensiometerManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_TensiometerList.size())
        return QVariant();

    if (role == IndexRole)
        return index.row();

    Tensiometer::TENSIONMETER item = m_TensiometerList.at(index.row());

    switch (role)
    {
    case NumberRole:
        return item.Number;
    case TypeRole:
        return item.Encoder;
    case RangeRole:
        return item.Range;
    case SignalRole:
        return item.Analog;
    case ScaledRole:
        if(item.Scale.isEmpty() == true)
            return true;
        else
            return false;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TensiometerManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NumberRole]   = "SensorNumber";
    roles[TypeRole]     = "SensorType";
    roles[RangeRole]    = "SensorRange";
    roles[SignalRole]   = "AnalogRange";
    roles[IndexRole]    = "index";
    roles[ScaledRole]   = "Scaled";
    return roles;
}

void TensiometerManager::addTensiometer()
{
    Tensiometer::TENSIONMETER tensiometer;
    tensiometer.Number = Tensiometer::GetInstance()->TensiometerNumber().toInt();
    tensiometer.Encoder = Tensiometer::GetInstance()->TensiometerEncoder();
    tensiometer.Range = Tensiometer::GetInstance()->TensiometerRange();
    tensiometer.Analog = Tensiometer::GetInstance()->TensiometerAnalog();
    tensiometer.Scale = "";

    if(m_db->InsertNewTensiometer(tensiometer))
    {
        qDebug() << "Insert tensiometer data successful";
        beginInsertRows(QModelIndex(), m_TensiometerList.count(), m_TensiometerList.count());
        tensiometer.Scale.clear();
        m_TensiometerList.append(tensiometer);
        endInsertRows();
    }
    else
    {
        qDebug() << "Failed to insert tensiometer data.";
    }
}

void TensiometerManager::removeTensiometer(const int index)
{
    if (index < 0 || index >= m_TensiometerList.size())
    {
        qDebug() << "Invalid index for removal:" << index;
        return;
    }
    beginResetModel();
    int number = m_TensiometerList[index].Number;
    if (m_db->deleteTensiometerData(number))
    {
        m_TensiometerList.removeAt(index);
    }
    else
    {
        qDebug() << "Failed to delete tensiometer data with Number:" << number;
    }
    endResetModel();
}

void TensiometerManager::syncTensiometer(const int index)
{
    if (index < 0 || index >= m_TensiometerList.size())
    {
        qDebug() << "Invalid index for removal:" << index;
        return;
    }
    beginResetModel();
    QString strNumber = QString::number(m_TensiometerList[index].Number);
    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSIOMETER_NUM_H, strNumber);
    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSIOMETER_ANALOG, m_TensiometerList[index].Analog);
    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSIOMETER_ENCODER, m_TensiometerList[index].Encoder);
    if(m_TensiometerList[index].Scale.isEmpty() != true)
    {
        QList<TensionScaleManager::SCALE_RAW_DATA> list;
        if(HBUtilityClass::GetInstance()->StringJsonToList(m_TensiometerList[index].Scale, &list) == true)
        {
            for(int i = 0; i < list.size(); i++)
            {
                switch(i)
                {
                case 0:
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::SCALE_1_H, list[i].ScaleRaw);
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSION_1_H, list[i].TensionRaw);
                    break;
                case 1:
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::SCALE_2_H, list[i].ScaleRaw);
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSION_2_H, list[i].TensionRaw);
                    break;
                case 2:
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::SCALE_3_H, list[i].ScaleRaw);
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSION_3_H, list[i].TensionRaw);
                    break;
                case 3:
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::SCALE_4_H, list[i].ScaleRaw);
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSION_4_H, list[i].TensionRaw);
                    break;
                case 4:
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::SCALE_5_H, list[i].ScaleRaw);
                    HBModbusClient::GetInstance()->writeRegister(HQmlEnum::TENSION_5_H, list[i].TensionRaw);
                    break;
                default:
                    break;
                }
            }
            int size = list.size();
            if(size > 5)
                size = 5;
            HBModbusClient::GetInstance()->writeRegister(HQmlEnum::QUANTITY_OF_CALIBRATION, size);
        }
    }
    endResetModel();
}

void TensiometerManager::UpdateTensiometer(const int index, const QString scale)
{
    if (index < 0 || index >= m_TensiometerList.size())
        return;

    m_TensiometerList[index].Scale = scale;
    QModelIndex modelIndex = createIndex(index, 0);
    emit dataChanged(modelIndex, modelIndex, {ScaledRole});
}

void TensiometerManager::setTensionmeterNumber(int index)
{
    int meterNumber = -1;
    if (index < 0 || index >= m_TensiometerList.size())
        TensionScaleManager::GetInstance()->setTensiometerNumber("NA");
    else
    {
        TensionScaleManager::GetInstance()->SetTensiometerIndex(index);
        meterNumber = m_TensiometerList[index].Number;
        TensionScaleManager::GetInstance()->setTensiometerNumber(QString::number(meterNumber));
    }
}

int TensiometerManager::checkTensiometerNumber(QString TensiometerNumber)
{
    bool ok = false;
    int number = TensiometerNumber.toInt(&ok);
    if (!ok)
        return -1;

    for (int index = 0; index < m_TensiometerList.size(); ++index)
    {
        if (m_TensiometerList[index].Number == number)
            return index;
    }
    return -1;
}

void TensiometerManager::resetModel()
{
    beginResetModel();
    m_TensiometerList.clear();
    if (m_db->LoadTensiometerTable(m_TensiometerList) == false)
    {
        qDebug() << "Failed to reload tensiometer data from database.";
    }
    else
    {
        qDebug() << "Tensiometer data reloaded successfully.";
    }
    endResetModel();

}

// const QList<TensiometerData>& TensiometerManager::items() const
// {
//     return m_items;
// }
