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
    Q_PROPERTY(QString CreateTime READ CreateTime WRITE setCreateTime NOTIFY CreateTimeChanged FINAL)

    Q_PROPERTY(QString CurrentUser READ CurrentUser WRITE setCurrentUser NOTIFY CurrentUserChanged FINAL)
    Q_PROPERTY(QString CurrentGroup READ CurrentGroup WRITE setCurrentGroup NOTIFY CurrentGroupChanged FINAL)


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
    Q_INVOKABLE bool syncUserList();
    Q_INVOKABLE void loadFromDatabase();
    Q_INVOKABLE int  getOperateType() const;
    bool ValidateUser(const QString userId);

    bool validateFaceUser(const QString username);

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
    void setCreateTime(const QString &createTime);
    QString CreateTime() const;

    void setCurrentUser(const QString &currentUser);
    QString CurrentUser() const;

    void setCurrentGroup(const QString &currentGroup);
    QString CurrentGroup() const;
    
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
    void CreateTimeChanged(const QString &createTime);

    void CurrentUserChanged(const QString &currentUser);
    void CurrentGroupChanged(const QString &currentGroup);

private:
    enum USER_LEVEL
    {
        SUPER_USER = 0,
        OPERATOR_USER,
        NORMAL_USER,
        VISITOR_USER
    };
    enum OPERATE_TYPE
    {
        OPERATE_CREATE_NEW = 0,
        OPERATE_EDIT_EXIST
    };
    
    QVector<UserInfo> m_users;
    int m_rowIndex;
    QString m_userName;
    int m_groupIndex;
    QString m_nickName; 
    QString m_password;
    QString m_createTime;

    QString m_currentUser;
    QString m_currentGroup;
    static QString UserLevel[4];
    OPERATE_TYPE m_OperateType;
};

#endif // USERMANAGERMODEL_H
