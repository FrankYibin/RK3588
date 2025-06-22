#include "usermanagermodel.h"
#include "c++Source/HBData/hbdatabase.h"
#include <QDebug>
QString UserManagerModel::UserLevel[4] = {"超级用户", "操作员", "普通用户", "访客"}; //Must align with QML definition
UserManagerModel::UserManagerModel(QObject *parent)
    : QAbstractTableModel{parent}
{

    m_rowIndex = -1;
    m_userName = "";
    m_groupIndex = 5;
    m_nickName = "";
    m_password = "";

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
    case GroupNameRole: return user.groupIndex;
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

bool UserManagerModel::updateUser(const int row, const QString username, const QString password,const int groupindex, const QString nickname)
{
    if (row < 0 || row >= m_users.size())
        return false;

    const QString &oldUserName = m_users[row].userName;
    bool success = HBDatabase::GetInstance().UpdateUser(oldUserName, username, password, groupindex, nickname);
    if (!success) {
        qWarning() << "Failed to update user in database:" << oldUserName;
        return false;
    }
    m_users[row].userName = username;
    m_users[row].groupIndex = groupindex;
    m_users[row].nickName = nickname;
    return true;
}

bool UserManagerModel::getUser(int row)
{
    QString username, password, nickname;
    int groupindex;
    username = m_users[row].userName;
    bool success = HBDatabase::GetInstance().QueryUser(username, password, groupindex, nickname);
    if(success == true)
    {
        setUserName(username);
        setPassword(password);
        setGroupIndex(groupindex);
        setNickName(nickname);
        setRowIndex(row);
    }
    return true;
}

bool UserManagerModel::resetUser()
{
    setRowIndex(-1);
    setUserName("");
    setPassword("");
    setGroupIndex(3);
    setNickName("");
    return true;
}

bool UserManagerModel::syncUserList()
{

}

bool UserManagerModel::addNewUser(const QString username, const QString password, const int groupindex, const QString nickname)
{
    if(!HBDatabase::GetInstance().InsertUser(username, password, groupindex, nickname))
        return false;
    return true;
}

bool UserManagerModel::validateUser(const QString username, const QString password)
{
    int groupId = -1;
    if(HBDatabase::GetInstance().QueryUser(username, password, groupId) == true)
    {
        setCurrentUser(username);
        switch(groupId)
        {
        case SUPER_USER:
            setCurrentGroup(UserLevel[SUPER_USER]);
            break;
        case OPERATOR_USER:
            setCurrentGroup(UserLevel[OPERATOR_USER]);
            break;
        case NORMAL_USER:
            setCurrentGroup(UserLevel[NORMAL_USER]);
            break;
        case VISITOR_USER:
            setCurrentGroup(UserLevel[VISITOR_USER]);
            break;
        default:
            setCurrentGroup(tr("ADMIN"));
            break;
        }
        return true;
    }
    return false;
}

void UserManagerModel::loadFromDatabase()
{
    beginResetModel();
    m_users = HBDatabase::GetInstance().LoadAllUsers();
    endResetModel();
}

void UserManagerModel::setRowIndex(int rowIndex)
{
    if (m_rowIndex != rowIndex) {
        m_rowIndex = rowIndex;
        emit RowIndexChanged(rowIndex);
    }
}
int UserManagerModel::RowIndex() const
{
    return m_rowIndex;
}
void UserManagerModel::setUserName(const QString &userName)
{
    if (m_userName != userName) {
        m_userName = userName;
        emit UserNameChanged(userName);
    }
}
QString UserManagerModel::UserName() const
{
    return m_userName;
}
void UserManagerModel::setGroupIndex(const int &groupIndex)
{
    if (m_groupIndex != groupIndex) {
        m_groupIndex = groupIndex;
        emit GroupIndexChanged(groupIndex);
    }
}
int UserManagerModel::GroupIndex() const
{
    return m_groupIndex;
}
void UserManagerModel::setNickName(const QString &nickName)
{
    if (m_nickName != nickName) {
        m_nickName = nickName;
        emit NickNameChanged(nickName);
    }
}
QString UserManagerModel::NickName() const
{
    return m_nickName;
}
void UserManagerModel::setPassword(const QString &password)
{
    if (m_password != password) {
        m_password = password;
        emit PasswordChanged(password);
    }
}
QString UserManagerModel::Password() const
{
    return m_password;
}

void UserManagerModel::setCurrentUser(const QString &currentUser)
{
    if (m_currentUser != currentUser) {
        m_currentUser = currentUser;
        emit CurrentUserChanged(currentUser);
    }
}
QString UserManagerModel::CurrentUser() const
{
    return m_currentUser;
}
void UserManagerModel::setCurrentGroup(const QString &currentGroup)
{
    if (m_currentGroup != currentGroup) {
        m_currentGroup = currentGroup;
        emit CurrentGroupChanged(currentGroup);
    }
}
QString UserManagerModel::CurrentGroup() const
{
    return m_currentGroup;
}
