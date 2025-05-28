/****************************************************************************
** Meta object code from reading C++ file 'hbdatabase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/HBData/hbdatabase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hbdatabase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HBDatabase_t {
    QByteArrayData data[6];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HBDatabase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HBDatabase_t qt_meta_stringdata_HBDatabase = {
    {
QT_MOC_LITERAL(0, 0, 10), // "HBDatabase"
QT_MOC_LITERAL(1, 11, 31), // "updateWellParameterFromInstance"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 26), // "updateDepthSetFromInstance"
QT_MOC_LITERAL(4, 71, 27), // "updateDepthSafeFromInstance"
QT_MOC_LITERAL(5, 99, 29) // "updateTensionSafeFromInstance"

    },
    "HBDatabase\0updateWellParameterFromInstance\0"
    "\0updateDepthSetFromInstance\0"
    "updateDepthSafeFromInstance\0"
    "updateTensionSafeFromInstance"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HBDatabase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x02 /* Public */,
       3,    0,   35,    2, 0x02 /* Public */,
       4,    0,   36,    2, 0x02 /* Public */,
       5,    0,   37,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,

       0        // eod
};

void HBDatabase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HBDatabase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->updateWellParameterFromInstance();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->updateDepthSetFromInstance();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->updateDepthSafeFromInstance();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->updateTensionSafeFromInstance();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HBDatabase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HBDatabase.data,
    qt_meta_data_HBDatabase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HBDatabase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HBDatabase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HBDatabase.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HBDatabase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
