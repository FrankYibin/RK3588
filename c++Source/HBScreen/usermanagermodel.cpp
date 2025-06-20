#include "usermanagermodel.h"
#include "c++Source/HBData/hbdatabase.h"
#include <QDebug>

UserManagerModel::UserManagerModel(QObject *parent)
    : QAbstractTableModel{parent}
{

    loadFromDatabase();
}

UserManagerModel &UserManagerModel::GetInstance()
{
    static UserManagerModel model;
    return model;
}

int UserManagerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_users.size();

}

int UserManagerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return roleNames().size();

}

QVariant UserManagerModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() < 0 || index.row() >= m_users.size())
        return QVariant();

    const UserInfo &user = m_users[index.row()];

    switch(role){
    case IndexRole: return index.row();
    case UserNameRole: return user.userName;
    case NickNameRole: return user.nickName;
    case GroupNameRole: return user.groupName;
    case CreateTimeRole: return user.createTime;
    case UserHandleRole: return user.userHandleVisible;
    default: return QVariant();
    }

}

QHash<int, QByteArray> UserManagerModel::roleNames() const
{
    return {
            {IndexRole, "Index"},
            {UserNameRole, "UserName"},
            {NickNameRole, "NickName"},
            {GroupNameRole, "GroupName"},
            {CreateTimeRole, "CreateTime"},
            {UserHandleRole, "UserHandle"},
            };

}


bool UserManagerModel::removeUser(int row)
{
    if(row < 0 || row >= m_users.size())
        return false;

    QString userName = m_users[row].userName;

    if(!HBDatabase::GetInstance().deleteUserByName(userName)){
        return false;
    }

    beginRemoveRows(QModelIndex(),row,row);
    m_users.removeAt(row);
    endRemoveRows();

    return true;
}

void UserManagerModel::updateUser(int row, const QString &username, const QString &password,const QString &groupname, const QString &nickname)
{
    if (row < 0 || row >= m_users.size())
        return;

    const QString &oldUserName = m_users[row].userName;
    bool success = HBDatabase::GetInstance().updateUser(oldUserName, username, password, groupname, nickname);
    if (!success) {
        qWarning() << "Failed to update user in database:" << oldUserName;
        return;
    }
    m_users[row].userName = username;
    m_users[row].groupName = groupname;
    m_users[row].nickName = nickname;

    emit dataChanged(index(row, 0), index(row, columnCount() - 1));


}

bool UserManagerModel::addUser(const QString &username, const QString &password, const QString &groupname, const QString &nickname)
{
    if(!HBDatabase::GetInstance().insertUser(username,password,groupname,nickname)){
        qWarning() << "add user fail ";
        return false;
    }

    loadFromDatabase();
    return true;

}

void UserManagerModel::loadFromDatabase() {
    beginResetModel();
    m_users = HBDatabase::GetInstance().loadAllUsers();
    endResetModel();
}
