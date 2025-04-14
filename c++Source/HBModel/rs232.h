#ifndef RS232_H
#define RS232_H


#include <QAbstractListModel>
#include "c++Source/HBDefine.h"

class RS232 : public QAbstractListModel
{
    Q_OBJECT

public:

    enum Roles {
        PortRole = Qt::UserRole + 1,
        BaudRateRole,
        DataBitRole,
        ProtocolRole
    };

    static RS232 *getInstance();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setSerial(int index, int port, int baudRate, int dataBit, int serialType);

    //test
    Q_INVOKABLE void loadTestData();

private:
    explicit RS232(QObject *parent = nullptr);

    static RS232* s_RS232;

    QList<_GroundSerial> m_data;
};

#endif // RS232_H
