#ifndef USERMANAGERMODEL_H
#define USERMANAGERMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "c++Source/HBDefine.h"


class UserManagerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    static UserManagerModel &GetInstance();

    enum Roles {
        IndexRole = Qt::UserRole + 1,
        UserNameRole,
        NickNameRole,
        GroupNameRole,
        CreateTimeRole,
        UserHandleRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool removeUser(int row);
    Q_INVOKABLE void updateUser(int row, const QString &username, const QString &password,const QString &groupname, const QString &nickname);
    Q_INVOKABLE bool addUser(const QString &username, const QString &password,const QString &groupname, const QString &nickname);

    void loadFromDatabase();

private:
    explicit UserManagerModel(QObject *parent = nullptr);
    UserManagerModel(const UserManagerModel&) = delete;
    UserManagerModel& operator=(const UserManagerModel&) = delete;


signals:

private:
    QVector<UserInfo> m_users;
};

#endif // USERMANAGERMODEL_H
