#ifndef USERMANAGERMODEL_H
#define USERMANAGERMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "c++Source/HBDefine.h"


class UserManagerModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int RowIndex READ RowIndex WRITE setRowIndex NOTIFY RowIndexChanged FINAL)
    Q_PROPERTY(QString UserName READ UserName WRITE setUserName NOTIFY UserNameChanged FINAL)
    Q_PROPERTY(int GroupIndex READ GroupIndex WRITE setGroupIndex NOTIFY GroupIndexChanged FINAL)
    Q_PROPERTY(QString NickName READ NickName WRITE setNickName NOTIFY NickNameChanged FINAL)
    Q_PROPERTY(QString Password READ Password WRITE setPassword NOTIFY PasswordChanged FINAL)
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
    Q_INVOKABLE bool updateUser(const int row, const QString username, const QString password, const int groupindex, const QString nickname);
    Q_INVOKABLE bool addNewUser(const QString username, const QString password, const int groupindex, const QString nickname);
    Q_INVOKABLE bool validateUser(const QString username, const QString password);
    Q_INVOKABLE bool getUser(int row);
    Q_INVOKABLE bool resetUser();
    Q_INVOKABLE void loadFromDatabase();

    void setRowIndex(int rowIndex);
    int RowIndex() const;
    void setUserName(const QString &userName);
    QString UserName() const;
    void setGroupIndex(const int &groupIndex);
    int GroupIndex() const;
    void setNickName(const QString &nickName);
    QString NickName() const;
    void setPassword(const QString &password);
    QString Password() const;   
    
private:
    explicit UserManagerModel(QObject *parent = nullptr);
    UserManagerModel(const UserManagerModel&) = delete;
    UserManagerModel& operator=(const UserManagerModel&) = delete;
signals:
    void RowIndexChanged(int rowIndex);
    void UserNameChanged(const QString &userName);
    void GroupIndexChanged(const int &groupIndex);
    void NickNameChanged(const QString &nickName);
    void PasswordChanged(const QString &password);

private:
    QVector<UserInfo> m_users;
    int m_rowIndex;
    QString m_userName;
    int m_groupIndex;
    QString m_nickName; 
    QString m_password;
};

#endif // USERMANAGERMODEL_H
