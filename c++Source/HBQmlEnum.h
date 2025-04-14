#ifndef HBQMLENUM_H
#define HBQMLENUM_H

#include <QObject>

class HQmlEnum: public QObject
{
    Q_OBJECT
public:

    enum RS232_COLUMN
    {
        RS232_port = 0,
        RS232_baud_rate,
        RS232_data_bit,
        RS232_parity_bit,
        RS232_protocol,
    };
    Q_ENUM(RS232_COLUMN)




public:
    explicit HQmlEnum(QObject *parent = nullptr){}

signals:


};

#endif // HBQMLENUM_H
