/****************************************************************************
** Meta object code from reading C++ file 'upgradesoftwaredef.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/upgradesoftwaredef.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'upgradesoftwaredef.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UpgradeSoftwareEnum_t {
    QByteArrayData data[5];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpgradeSoftwareEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpgradeSoftwareEnum_t qt_meta_stringdata_UpgradeSoftwareEnum = {
    {
QT_MOC_LITERAL(0, 0, 19), // "UpgradeSoftwareEnum"
QT_MOC_LITERAL(1, 20, 12), // "UPGRADEINDEX"
QT_MOC_LITERAL(2, 33, 8), // "NONE_IDX"
QT_MOC_LITERAL(3, 42, 19), // "WELDER_SOFTWARE_IDX"
QT_MOC_LITERAL(4, 62, 25) // "UICONTROLLER_SOFTWARE_IDX"

    },
    "UpgradeSoftwareEnum\0UPGRADEINDEX\0"
    "NONE_IDX\0WELDER_SOFTWARE_IDX\0"
    "UICONTROLLER_SOFTWARE_IDX"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpgradeSoftwareEnum[] = {

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
       2, uint(UpgradeSoftwareEnum::NONE_IDX),
       3, uint(UpgradeSoftwareEnum::WELDER_SOFTWARE_IDX),
       4, uint(UpgradeSoftwareEnum::UICONTROLLER_SOFTWARE_IDX),

       0        // eod
};

void UpgradeSoftwareEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject UpgradeSoftwareEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_UpgradeSoftwareEnum.data,
    qt_meta_data_UpgradeSoftwareEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UpgradeSoftwareEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpgradeSoftwareEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UpgradeSoftwareEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UpgradeSoftwareEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
