#ifndef TENSIONSCALEMANAGER_H
#define TENSIONSCALEMANAGER_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QString>
#include "c++Source/HBDefine.h"

class TensionScaleManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TensionScaleManager(QObject *parent = nullptr);

    enum TensionScaleRoles {
        CheckedRole = Qt::UserRole + 1,
        IndexRole,
        ScaleValueRole,
        TensionValueRole
    };
public:

    // Reimplement rowCount and data to provide the data to QML
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // A function to reset the model with default data
    Q_INVOKABLE void resetModel();

    // A function to modify a tension value
    Q_INVOKABLE void updateTensionValue(int index, double newTensionValue);

    // A function to get the total number of checked scales
    Q_INVOKABLE int getCheckedCount() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<TensionScaleData> m_scales;  // 存储刻度点数据
};

#endif // TENSIONSCALEMANAGER_H
