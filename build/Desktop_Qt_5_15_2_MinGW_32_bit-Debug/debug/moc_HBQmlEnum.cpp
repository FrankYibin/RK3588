/****************************************************************************
** Meta object code from reading C++ file 'HBQmlEnum.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/HBQmlEnum.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HBQmlEnum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HQmlEnum_t {
    QByteArrayData data[7];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HQmlEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HQmlEnum_t qt_meta_stringdata_HQmlEnum = {
    {
QT_MOC_LITERAL(0, 0, 8), // "HQmlEnum"
QT_MOC_LITERAL(1, 9, 12), // "RS232_COLUMN"
QT_MOC_LITERAL(2, 22, 10), // "RS232_port"
QT_MOC_LITERAL(3, 33, 15), // "RS232_baud_rate"
QT_MOC_LITERAL(4, 49, 14), // "RS232_data_bit"
QT_MOC_LITERAL(5, 64, 16), // "RS232_parity_bit"
QT_MOC_LITERAL(6, 81, 14) // "RS232_protocol"

    },
    "HQmlEnum\0RS232_COLUMN\0RS232_port\0"
    "RS232_baud_rate\0RS232_data_bit\0"
    "RS232_parity_bit\0RS232_protocol"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HQmlEnum[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    5,   19,

 // enum data: key, value
       2, uint(HQmlEnum::RS232_port),
       3, uint(HQmlEnum::RS232_baud_rate),
       4, uint(HQmlEnum::RS232_data_bit),
       5, uint(HQmlEnum::RS232_parity_bit),
       6, uint(HQmlEnum::RS232_protocol),

       0        // eod
};

void HQmlEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject HQmlEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HQmlEnum.data,
    qt_meta_data_HQmlEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HQmlEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HQmlEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HQmlEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HQmlEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
