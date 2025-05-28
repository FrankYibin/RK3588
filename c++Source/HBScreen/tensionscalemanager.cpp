#include "tensionscalemanager.h"
#include "c++Source/HBScreen/tensiometer.h"

TensionScaleManager::TensionScaleManager(QObject *parent)
    : QAbstractListModel(parent)
{
    resetModel();
}

int TensionScaleManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_scales.count();
}

QVariant TensionScaleManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const TensionScaleData &scale = m_scales.at(index.row());

    switch (role) {
    case CheckedRole:
        return scale.checked;
    case IndexRole:
        return scale.index;
    case ScaleValueRole:{

        int row = index.row();
        Tensiometer* t = Tensiometer::getInstance();

        switch (row) {
        case 1: return t->Scale1();
        case 2: return t->Scale2();
        case 3: return t->Scale3();
        case 4: return t->Scale4();
        case 5: return t->Scale5();
        default: return scale.scaleValue;
        }
    }
    case TensionValueRole:
        return scale.tensionValue;
    default:
        return QVariant();
    }
}

void TensionScaleManager::resetModel()
{
    beginResetModel();
    m_scales.clear();

    m_scales.append({true, 1, 10,10 });
    m_scales.append({true, 2, 20, 10});
    m_scales.append({false, 3, 30, 15});
    m_scales.append({false, 4, 40, 20});
    m_scales.append({false, 5, 50, 25});

    endResetModel();
}

void TensionScaleManager::updateTensionValue(int index, double newTensionValue)
{
    if (index >= 0 && index < m_scales.size()) {
        m_scales[index].tensionValue = newTensionValue;
        emit dataChanged(this->index(index), this->index(index), {TensionValueRole});
    }
}

int TensionScaleManager::getCheckedCount() const
{
    int count = 0;
    for (const TensionScaleData &scale : m_scales) {
        if (scale.checked) {
            ++count;
        }
    }
    return count;
}

QHash<int, QByteArray> TensionScaleManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CheckedRole] = "Checked";
    roles[IndexRole] = "Index";
    roles[ScaleValueRole] = "ScaleValue";
    roles[TensionValueRole] = "TensionValue";
    return roles;
}
