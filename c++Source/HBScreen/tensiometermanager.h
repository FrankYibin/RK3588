#ifndef TENSIOMETERMANAGER_H
#define TENSIOMETERMANAGER_H

#include <QAbstractListModel>
#include <QList>
#include "c++Source/HBData/hbdatabase.h"
#include "tensiometer.h"


class TensiometerManager : public QAbstractListModel {
    Q_OBJECT

    // Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum TensiometerRoles {
        NumberRole = Qt::UserRole + 1,
        TypeRole,
        RangeRole,
        SignalRole,
        IndexRole,
        ScaledRole,
    };
    static TensiometerManager* GetInstance();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addTensiometer();
    Q_INVOKABLE void removeTensiometer(const int index);
    Q_INVOKABLE void syncTensiometer(const int index);

    Q_INVOKABLE void setTensionmeterNumber(int index);


protected:
    explicit TensiometerManager(QObject *parent = nullptr);
signals:

public slots:
    void UpdateTensiometer(const int index, const QString scale);
private:
    static TensiometerManager* _ptrTensiometerManager;
    static QList<Tensiometer::TENSIONMETER> m_TensiometerList;
    HBDatabase* m_db;


};

#endif // TENSIOMETERMANAGER_H
