#include "tensionscalemanager.h"
#include "c++Source/HBScreen/tensiometer.h"
#include "c++Source/HBData/hbdatabase.h"
#include <QDebug>

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
        Tensiometer* t = Tensiometer::GetInstance();

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

void TensionScaleManager::setTensiometerNumber(const QString &number)
{
    m_tensiometerNumber = number;
    resetModel();
}
void TensionScaleManager::resetModel()
{
    beginResetModel();
    m_scales.clear();

    // m_scales.append({true, 1, 10,10 });
    // m_scales.append({true, 2, 20, 10});
    // m_scales.append({false, 3, 30, 15});
    // m_scales.append({false, 4, 40, 20});
    // m_scales.append({false, 5, 50, 25});
    if (!m_tensiometerNumber.isEmpty()) {
        QList<ScaleData> scaleData;
        if (HBDatabase::getInstance().loadScalesForTensiometerNumber(m_tensiometerNumber, scaleData)) {
            for (const ScaleData &sd : scaleData) {
                m_scales.append({sd.selected != 0, sd.pointIndex, sd.rawScaleValue, sd.rawTensionValue});
            }
        }
    }
    endResetModel();
}

void TensionScaleManager::updateTensionValue(int index, double newTensionValue)
{
    if (index >= 0 && index < m_scales.size()) {
        m_scales[index].tensionValue = newTensionValue;
        emit dataChanged(this->index(index), this->index(index), {TensionValueRole});
    }
}

void TensionScaleManager::saveData()
{
    for (const TensionScaleData &scale : m_scales) {
        qDebug() << "Saving Index:" << scale.index
                 << "ScaleValue:" << scale.scaleValue
                 << "TensionValue:" << scale.tensionValue
                 << "Checked:" << scale.checked;

        HBDatabase::getInstance().updateTensionValue(
            m_tensiometerNumber,
            scale.index,
            scale.scaleValue,
            scale.tensionValue,
            scale.checked
            );
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
