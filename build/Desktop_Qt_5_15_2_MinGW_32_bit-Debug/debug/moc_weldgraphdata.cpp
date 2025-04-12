/****************************************************************************
** Meta object code from reading C++ file 'weldgraphdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/weldgraphdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weldgraphdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WeldGraphData_t {
    QByteArrayData data[15];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WeldGraphData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WeldGraphData_t qt_meta_stringdata_WeldGraphData = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WeldGraphData"
QT_MOC_LITERAL(1, 14, 13), // "appendSamples"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "QAbstractSeries*"
QT_MOC_LITERAL(4, 46, 8), // "a_series"
QT_MOC_LITERAL(5, 55, 6), // "a_type"
QT_MOC_LITERAL(6, 62, 20), // "setAxisMinParameters"
QT_MOC_LITERAL(7, 83, 13), // "QList<qreal>&"
QT_MOC_LITERAL(8, 97, 9), // "a_axisVal"
QT_MOC_LITERAL(9, 107, 20), // "setAxisMaxParameters"
QT_MOC_LITERAL(10, 128, 20), // "getAxisMinParameters"
QT_MOC_LITERAL(11, 149, 12), // "QList<qreal>"
QT_MOC_LITERAL(12, 162, 20), // "getAxisMaxParameters"
QT_MOC_LITERAL(13, 183, 10), // "clearGraph"
QT_MOC_LITERAL(14, 194, 20) // "generateRandomNumber"

    },
    "WeldGraphData\0appendSamples\0\0"
    "QAbstractSeries*\0a_series\0a_type\0"
    "setAxisMinParameters\0QList<qreal>&\0"
    "a_axisVal\0setAxisMaxParameters\0"
    "getAxisMinParameters\0QList<qreal>\0"
    "getAxisMaxParameters\0clearGraph\0"
    "generateRandomNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeldGraphData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x02 /* Public */,
       6,    1,   54,    2, 0x02 /* Public */,
       9,    1,   57,    2, 0x02 /* Public */,
      10,    0,   60,    2, 0x02 /* Public */,
      12,    0,   61,    2, 0x02 /* Public */,
      13,    0,   62,    2, 0x02 /* Public */,
      14,    0,   63,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 3, QMetaType::UChar,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    0x80000000 | 11,
    0x80000000 | 11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WeldGraphData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WeldGraphData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->appendSamples((*reinterpret_cast< QAbstractSeries*(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->setAxisMinParameters((*reinterpret_cast< QList<qreal>(*)>(_a[1]))); break;
        case 2: _t->setAxisMaxParameters((*reinterpret_cast< QList<qreal>(*)>(_a[1]))); break;
        case 3: { QList<qreal> _r = _t->getAxisMinParameters();
            if (_a[0]) *reinterpret_cast< QList<qreal>*>(_a[0]) = std::move(_r); }  break;
        case 4: { QList<qreal> _r = _t->getAxisMaxParameters();
            if (_a[0]) *reinterpret_cast< QList<qreal>*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->clearGraph(); break;
        case 6: _t->generateRandomNumber(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSeries* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WeldGraphData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WeldGraphData.data,
    qt_meta_data_WeldGraphData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WeldGraphData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeldGraphData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WeldGraphData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WeldGraphData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
