/****************************************************************************
** Meta object code from reading C++ file 'GraphAxisDefineHB.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/HBGraph/GraphAxisDefineHB.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphAxisDefineHB.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HBGraphAxisEnum_t {
    QByteArrayData data[9];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HBGraphAxisEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HBGraphAxisEnum_t qt_meta_stringdata_HBGraphAxisEnum = {
    {
QT_MOC_LITERAL(0, 0, 15), // "HBGraphAxisEnum"
QT_MOC_LITERAL(1, 16, 16), // "HBGRAPHAXISINDEX"
QT_MOC_LITERAL(2, 33, 8), // "NONE_IDX"
QT_MOC_LITERAL(3, 42, 9), // "DEPTH_IDX"
QT_MOC_LITERAL(4, 52, 12), // "VELOCITY_IDX"
QT_MOC_LITERAL(5, 65, 12), // "TENSIONS_IDX"
QT_MOC_LITERAL(6, 78, 21), // "TENSION_INCREMENT_IDX"
QT_MOC_LITERAL(7, 100, 8), // "TIME_IDX"
QT_MOC_LITERAL(8, 109, 9) // "TOTAL_IDX"

    },
    "HBGraphAxisEnum\0HBGRAPHAXISINDEX\0"
    "NONE_IDX\0DEPTH_IDX\0VELOCITY_IDX\0"
    "TENSIONS_IDX\0TENSION_INCREMENT_IDX\0"
    "TIME_IDX\0TOTAL_IDX"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HBGraphAxisEnum[] = {

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
       1,    1, 0x0,    7,   19,

 // enum data: key, value
       2, uint(HBGraphAxisEnum::NONE_IDX),
       3, uint(HBGraphAxisEnum::DEPTH_IDX),
       4, uint(HBGraphAxisEnum::VELOCITY_IDX),
       5, uint(HBGraphAxisEnum::TENSIONS_IDX),
       6, uint(HBGraphAxisEnum::TENSION_INCREMENT_IDX),
       7, uint(HBGraphAxisEnum::TIME_IDX),
       8, uint(HBGraphAxisEnum::TOTAL_IDX),

       0        // eod
};

void HBGraphAxisEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject HBGraphAxisEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HBGraphAxisEnum.data,
    qt_meta_data_HBGraphAxisEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HBGraphAxisEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HBGraphAxisEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HBGraphAxisEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HBGraphAxisEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
