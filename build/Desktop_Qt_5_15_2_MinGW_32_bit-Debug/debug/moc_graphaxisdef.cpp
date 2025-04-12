/****************************************************************************
** Meta object code from reading C++ file 'graphaxisdef.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/graphaxisdef.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphaxisdef.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphAxisEnum_t {
    QByteArrayData data[15];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphAxisEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphAxisEnum_t qt_meta_stringdata_GraphAxisEnum = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GraphAxisEnum"
QT_MOC_LITERAL(1, 14, 14), // "GRAPHAXISINDEX"
QT_MOC_LITERAL(2, 29, 8), // "NONE_IDX"
QT_MOC_LITERAL(3, 38, 9), // "PHASE_IDX"
QT_MOC_LITERAL(4, 48, 10), // "ENERGY_IDX"
QT_MOC_LITERAL(5, 59, 8), // "FREQ_IDX"
QT_MOC_LITERAL(6, 68, 7), // "AMP_IDX"
QT_MOC_LITERAL(7, 76, 11), // "CURRENT_IDX"
QT_MOC_LITERAL(8, 88, 9), // "POWER_IDX"
QT_MOC_LITERAL(9, 98, 9), // "FORCE_IDX"
QT_MOC_LITERAL(10, 108, 12), // "VELOCITY_IDX"
QT_MOC_LITERAL(11, 121, 16), // "ABSOLUTEDIST_IDX"
QT_MOC_LITERAL(12, 138, 16), // "COLLAPSEDIST_IDX"
QT_MOC_LITERAL(13, 155, 8), // "TIME_IDX"
QT_MOC_LITERAL(14, 164, 9) // "TOTAL_IDX"

    },
    "GraphAxisEnum\0GRAPHAXISINDEX\0NONE_IDX\0"
    "PHASE_IDX\0ENERGY_IDX\0FREQ_IDX\0AMP_IDX\0"
    "CURRENT_IDX\0POWER_IDX\0FORCE_IDX\0"
    "VELOCITY_IDX\0ABSOLUTEDIST_IDX\0"
    "COLLAPSEDIST_IDX\0TIME_IDX\0TOTAL_IDX"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphAxisEnum[] = {

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
       1,    1, 0x0,   13,   19,

 // enum data: key, value
       2, uint(GraphAxisEnum::NONE_IDX),
       3, uint(GraphAxisEnum::PHASE_IDX),
       4, uint(GraphAxisEnum::ENERGY_IDX),
       5, uint(GraphAxisEnum::FREQ_IDX),
       6, uint(GraphAxisEnum::AMP_IDX),
       7, uint(GraphAxisEnum::CURRENT_IDX),
       8, uint(GraphAxisEnum::POWER_IDX),
       9, uint(GraphAxisEnum::FORCE_IDX),
      10, uint(GraphAxisEnum::VELOCITY_IDX),
      11, uint(GraphAxisEnum::ABSOLUTEDIST_IDX),
      12, uint(GraphAxisEnum::COLLAPSEDIST_IDX),
      13, uint(GraphAxisEnum::TIME_IDX),
      14, uint(GraphAxisEnum::TOTAL_IDX),

       0        // eod
};

void GraphAxisEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject GraphAxisEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GraphAxisEnum.data,
    qt_meta_data_GraphAxisEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphAxisEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphAxisEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphAxisEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GraphAxisEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
