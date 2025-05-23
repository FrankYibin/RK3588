#ifndef TENSIOMETERMANAGER_H
#define TENSIOMETERMANAGER_H

#include <QAbstractListModel>
#include <QList>
#include "c++Source/HBDefine.h"
#include "c++Source/HBData/hbdatabase.h"


class TensiometerManager : public QAbstractListModel {
    Q_OBJECT
public:
    enum TensiometerRoles {
        NumberRole = Qt::UserRole + 1,
        TypeRole,
        RangeRole,
        SignalRole,
        IndexRole = Qt::UserRole + 100
    };

    explicit TensiometerManager(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addTensiometer(const QString &number, int type, int range, int signal);
    Q_INVOKABLE void removeTensiometer(int index);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void updateTensiometer(int index, const QString &number, int type, int range, int signal);

    const QList<TensiometerData>& items() const;

private:
    QList<TensiometerData> m_items;
    HBDatabase *m_db;
};

#endif // TENSIOMETERMANAGER_H
