/****************************************************************************
** Meta object code from reading C++ file 'systemTypeDef.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/systemTypeDef.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemTypeDef.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SystemTypeDef_t {
    QByteArrayData data[5];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemTypeDef_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemTypeDef_t qt_meta_stringdata_SystemTypeDef = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SystemTypeDef"
QT_MOC_LITERAL(1, 14, 10), // "SYSTEMTYPE"
QT_MOC_LITERAL(2, 25, 7), // "ALLTYPE"
QT_MOC_LITERAL(3, 33, 6), // "GSX_E1"
QT_MOC_LITERAL(4, 40, 11) // "GSX_P1_BASE"

    },
    "SystemTypeDef\0SYSTEMTYPE\0ALLTYPE\0"
    "GSX_E1\0GSX_P1_BASE"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemTypeDef[] = {

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
       1,    1, 0x0,    3,   19,

 // enum data: key, value
       2, uint(SystemTypeDef::ALLTYPE),
       3, uint(SystemTypeDef::GSX_E1),
       4, uint(SystemTypeDef::GSX_P1_BASE),

       0        // eod
};

void SystemTypeDef::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SystemTypeDef::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SystemTypeDef.data,
    qt_meta_data_SystemTypeDef,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SystemTypeDef::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemTypeDef::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SystemTypeDef.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SystemTypeDef::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
