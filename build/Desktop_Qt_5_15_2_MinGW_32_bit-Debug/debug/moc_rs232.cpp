/****************************************************************************
** Meta object code from reading C++ file 'rs232.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/HBScreen/rs232.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rs232.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RS232_t {
    QByteArrayData data[18];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RS232_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RS232_t qt_meta_stringdata_RS232 = {
    {
QT_MOC_LITERAL(0, 0, 5), // "RS232"
QT_MOC_LITERAL(1, 6, 17), // "SerialPortChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "BaudRateChanged"
QT_MOC_LITERAL(4, 41, 15), // "DataBitsChanged"
QT_MOC_LITERAL(5, 57, 17), // "SerialTypeChanged"
QT_MOC_LITERAL(6, 75, 10), // "SerialPort"
QT_MOC_LITERAL(7, 86, 13), // "setSerialPort"
QT_MOC_LITERAL(8, 100, 4), // "port"
QT_MOC_LITERAL(9, 105, 8), // "BaudRate"
QT_MOC_LITERAL(10, 114, 11), // "setBaudRate"
QT_MOC_LITERAL(11, 126, 4), // "baud"
QT_MOC_LITERAL(12, 131, 8), // "DataBits"
QT_MOC_LITERAL(13, 140, 11), // "setDataBits"
QT_MOC_LITERAL(14, 152, 4), // "bits"
QT_MOC_LITERAL(15, 157, 10), // "SerialType"
QT_MOC_LITERAL(16, 168, 13), // "setSerialType"
QT_MOC_LITERAL(17, 182, 4) // "type"

    },
    "RS232\0SerialPortChanged\0\0BaudRateChanged\0"
    "DataBitsChanged\0SerialTypeChanged\0"
    "SerialPort\0setSerialPort\0port\0BaudRate\0"
    "setBaudRate\0baud\0DataBits\0setDataBits\0"
    "bits\0SerialType\0setSerialType\0type"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RS232[] = {

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
      15,    0,   90,    2, 0x02 /* Public */,
      16,    1,   91,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   17,

 // properties: name, type, flags
       6, QMetaType::Int, 0x00495103,
       9, QMetaType::Int, 0x00495103,
      12, QMetaType::Int, 0x00495103,
      15, QMetaType::Int, 0x00495903,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void RS232::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RS232 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SerialPortChanged(); break;
        case 1: _t->BaudRateChanged(); break;
        case 2: _t->DataBitsChanged(); break;
        case 3: _t->SerialTypeChanged(); break;
        case 4: { int _r = _t->SerialPort();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setSerialPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { int _r = _t->BaudRate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setBaudRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: { int _r = _t->DataBits();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setDataBits((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: { int _r = _t->SerialType();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->setSerialType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RS232::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RS232::SerialPortChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RS232::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RS232::BaudRateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RS232::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RS232::DataBitsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RS232::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RS232::SerialTypeChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<RS232 *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->SerialPort(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->BaudRate(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->DataBits(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->SerialType(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<RS232 *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSerialPort(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setBaudRate(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setDataBits(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setSerialType(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject RS232::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RS232.data,
    qt_meta_data_RS232,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RS232::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RS232::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RS232.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RS232::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void RS232::SerialPortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RS232::BaudRateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void RS232::DataBitsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void RS232::SerialTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
