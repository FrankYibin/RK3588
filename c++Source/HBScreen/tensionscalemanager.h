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


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;


    Q_INVOKABLE void resetModel();


    Q_INVOKABLE void updateTensionValue(int index, double newTensionValue);


    Q_INVOKABLE int getCheckedCount() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<TensionScaleData> m_scales;  // 存储刻度点数据
};

#endif // TENSIONSCALEMANAGER_H
