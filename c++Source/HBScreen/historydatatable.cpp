#include "historydatatable.h"
#include "c++Source/HBData/hbdatabase.h"
#include <QDebug>

HistoryDataTable::HistoryDataTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    loadFromDatabase();
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
    case DepthRole: return item.depth / 100.0;
    case VelocityRole: return item.velocity / 100.0;
    case VelocityUnitRole: return item.velocityUnit;
    case TensionsRole: return item.tensions / 100.0;
    case TensionIncreamentRole: return item.tensionIncrement / 100.0;
    case TensionUnitRole: return item.tensionUnit;
    case MaxTensionRole: return item.maxTension / 100.0;
    case HarnessTensionRole: return item.harnessTension / 100.0;
    case SafetyTensionRole: return item.safetyTension / 100.0;
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

//void HistoryDataTable::resetModel()
//{
//    beginResetModel();
//    m_dataList.clear();

//    for (int i = 0; i < 15; ++i) {
//        m_dataList.append({
//            i,
//            "陕30H-3",
//            "2025-4-80",
//            "射孔",
//            "1",
//            100,
//            100,
//            "m/min",
//            50,
//            1,
//            "kg",
//            255,
//            101,
//            100,
//            "无"
//        });
//    }

//    endResetModel();
//}


void HistoryDataTable::loadFromDatabase()
{
    beginResetModel();
      m_dataList = HBDatabase::getInstance().loadHistoryData();
      if (m_dataList.isEmpty()) {
          qDebug() << "HistoryDataTable: 数据库中没有历史数据或加载失败";
      }
      endResetModel();
}
