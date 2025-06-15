#ifndef HISTORYOPERATIONMODEL_H
#define HISTORYOPERATIONMODEL_H
#include <QAbstractListModel>
#include <QList>
#include <QDateTime>

class HistoryOperationModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        IndexRole = Qt::UserRole + 1,
        WellNumberRole,
        OperateTypeRole,
        OperaterRole,
        DateRole,
        DescriptionRole
    };
    Q_ENUM(Roles)

    explicit HistoryOperationModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    struct Row {
        int index;
        QString wellNumber;
        QString operateType;
        QString operater;
        QDateTime date;
        QString description;
    };

    Q_INVOKABLE void clear();
    Q_INVOKABLE void reset(const QList<Row> &rows);

    Q_INVOKABLE void setRange(const QString &startIso,
                              const QString &endIso);

    Q_INVOKABLE void loadAll();


signals:

private:


    QList<Row> m_rows;
};

#endif // HISTORYOPERATIONMODEL_H
