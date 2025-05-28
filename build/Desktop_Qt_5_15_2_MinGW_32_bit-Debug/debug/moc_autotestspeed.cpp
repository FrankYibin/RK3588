/****************************************************************************
** Meta object code from reading C++ file 'autotestspeed.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/HBScreen/autotestspeed.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autotestspeed.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AutoTestSpeed_t {
    QByteArrayData data[16];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutoTestSpeed_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutoTestSpeed_t qt_meta_stringdata_AutoTestSpeed = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AutoTestSpeed"
QT_MOC_LITERAL(1, 14, 16), // "DirectionChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "SpeedValueChanged"
QT_MOC_LITERAL(4, 50, 21), // "DepthCountDownChanged"
QT_MOC_LITERAL(5, 72, 19), // "DepthCurrentChanged"
QT_MOC_LITERAL(6, 92, 9), // "Direction"
QT_MOC_LITERAL(7, 102, 12), // "setDirection"
QT_MOC_LITERAL(8, 115, 12), // "newDirection"
QT_MOC_LITERAL(9, 128, 10), // "SpeedValue"
QT_MOC_LITERAL(10, 139, 13), // "setSpeedValue"
QT_MOC_LITERAL(11, 153, 13), // "newSpeedValue"
QT_MOC_LITERAL(12, 167, 14), // "DepthCountDown"
QT_MOC_LITERAL(13, 182, 17), // "setDepthCountDown"
QT_MOC_LITERAL(14, 200, 12), // "DepthCurrent"
QT_MOC_LITERAL(15, 213, 15) // "setDepthCurrent"

    },
    "AutoTestSpeed\0DirectionChanged\0\0"
    "SpeedValueChanged\0DepthCountDownChanged\0"
    "DepthCurrentChanged\0Direction\0"
    "setDirection\0newDirection\0SpeedValue\0"
    "setSpeedValue\0newSpeedValue\0DepthCountDown\0"
    "setDepthCountDown\0DepthCurrent\0"
    "setDepthCurrent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutoTestSpeed[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       4,   94, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   78,    2, 0x02 /* Public */,
       7,    1,   79,    2, 0x02 /* Public */,
       9,    0,   82,    2, 0x02 /* Public */,
      10,    1,   83,    2, 0x02 /* Public */,
      12,    0,   86,    2, 0x02 /* Public */,
      13,    1,   87,    2, 0x02 /* Public */,
      14,    0,   90,    2, 0x02 /* Public */,
      15,    1,   91,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   11,

 // properties: name, type, flags
       6, QMetaType::Int, 0x00495103,
       9, QMetaType::Int, 0x00495103,
      12, QMetaType::Int, 0x00495103,
      14, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void AutoTestSpeed::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AutoTestSpeed *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DirectionChanged(); break;
        case 1: _t->SpeedValueChanged(); break;
        case 2: _t->DepthCountDownChanged(); break;
        case 3: _t->DepthCurrentChanged(); break;
        case 4: { int _r = _t->Direction();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { int _r = _t->SpeedValue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setSpeedValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: { int _r = _t->DepthCountDown();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setDepthCountDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: { int _r = _t->DepthCurrent();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->setDepthCurrent((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AutoTestSpeed::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoTestSpeed::DirectionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AutoTestSpeed::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoTestSpeed::SpeedValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AutoTestSpeed::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoTestSpeed::DepthCountDownChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AutoTestSpeed::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoTestSpeed::DepthCurrentChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AutoTestSpeed *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->Direction(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->SpeedValue(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->DepthCountDown(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->DepthCurrent(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AutoTestSpeed *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDirection(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setSpeedValue(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setDepthCountDown(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setDepthCurrent(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AutoTestSpeed::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AutoTestSpeed.data,
    qt_meta_data_AutoTestSpeed,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AutoTestSpeed::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutoTestSpeed::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AutoTestSpeed.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AutoTestSpeed::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AutoTestSpeed::DirectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AutoTestSpeed::SpeedValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AutoTestSpeed::DepthCountDownChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AutoTestSpeed::DepthCurrentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
