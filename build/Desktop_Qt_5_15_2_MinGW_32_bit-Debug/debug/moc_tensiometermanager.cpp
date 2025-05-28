/****************************************************************************
** Meta object code from reading C++ file 'tensiometermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/HBScreen/tensiometermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tensiometermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TensiometerManager_t {
    QByteArrayData data[15];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TensiometerManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TensiometerManager_t qt_meta_stringdata_TensiometerManager = {
    {
QT_MOC_LITERAL(0, 0, 18), // "TensiometerManager"
QT_MOC_LITERAL(1, 19, 12), // "countChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "rowCount"
QT_MOC_LITERAL(4, 42, 11), // "QModelIndex"
QT_MOC_LITERAL(5, 54, 6), // "parent"
QT_MOC_LITERAL(6, 61, 14), // "addTensiometer"
QT_MOC_LITERAL(7, 76, 6), // "number"
QT_MOC_LITERAL(8, 83, 4), // "type"
QT_MOC_LITERAL(9, 88, 5), // "range"
QT_MOC_LITERAL(10, 94, 6), // "signal"
QT_MOC_LITERAL(11, 101, 17), // "removeTensiometer"
QT_MOC_LITERAL(12, 119, 5), // "index"
QT_MOC_LITERAL(13, 125, 5), // "clear"
QT_MOC_LITERAL(14, 131, 17) // "updateTensiometer"

    },
    "TensiometerManager\0countChanged\0\0"
    "rowCount\0QModelIndex\0parent\0addTensiometer\0"
    "number\0type\0range\0signal\0removeTensiometer\0"
    "index\0clear\0updateTensiometer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TensiometerManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   50,    2, 0x02 /* Public */,
       3,    0,   53,    2, 0x22 /* Public | MethodCloned */,
       6,    4,   54,    2, 0x02 /* Public */,
      11,    1,   63,    2, 0x02 /* Public */,
      13,    0,   66,    2, 0x02 /* Public */,
      14,    5,   67,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 4,    5,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,    7,    8,    9,   10,

       0        // eod
};

void TensiometerManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TensiometerManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->countChanged(); break;
        case 1: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->addTensiometer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->removeTensiometer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->clear(); break;
        case 6: _t->updateTensiometer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TensiometerManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TensiometerManager::countChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TensiometerManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_TensiometerManager.data,
    qt_meta_data_TensiometerManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TensiometerManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TensiometerManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TensiometerManager.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int TensiometerManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TensiometerManager::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
