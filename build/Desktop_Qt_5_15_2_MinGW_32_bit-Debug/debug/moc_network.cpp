/****************************************************************************
** Meta object code from reading C++ file 'network.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/HBScreen/network.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Network_t {
    QByteArrayData data[22];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Network_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Network_t qt_meta_stringdata_Network = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Network"
QT_MOC_LITERAL(1, 8, 16), // "GProtocolChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "GLocalIPChanged"
QT_MOC_LITERAL(4, 42, 17), // "GLocalPortChanged"
QT_MOC_LITERAL(5, 60, 16), // "GRemoteIPChanged"
QT_MOC_LITERAL(6, 77, 18), // "GRemotePortChanged"
QT_MOC_LITERAL(7, 96, 16), // "CProtocolChanged"
QT_MOC_LITERAL(8, 113, 15), // "CLocalIPChanged"
QT_MOC_LITERAL(9, 129, 17), // "CLocalPortChanged"
QT_MOC_LITERAL(10, 147, 16), // "CRemoteIPChanged"
QT_MOC_LITERAL(11, 164, 18), // "CRemotePortChanged"
QT_MOC_LITERAL(12, 183, 9), // "GProtocol"
QT_MOC_LITERAL(13, 193, 8), // "GLocalIP"
QT_MOC_LITERAL(14, 202, 10), // "GLocalPort"
QT_MOC_LITERAL(15, 213, 9), // "GRemoteIP"
QT_MOC_LITERAL(16, 223, 11), // "GRemotePort"
QT_MOC_LITERAL(17, 235, 9), // "CProtocol"
QT_MOC_LITERAL(18, 245, 8), // "CLocalIP"
QT_MOC_LITERAL(19, 254, 10), // "CLocalPort"
QT_MOC_LITERAL(20, 265, 9), // "CRemoteIP"
QT_MOC_LITERAL(21, 275, 11) // "CRemotePort"

    },
    "Network\0GProtocolChanged\0\0GLocalIPChanged\0"
    "GLocalPortChanged\0GRemoteIPChanged\0"
    "GRemotePortChanged\0CProtocolChanged\0"
    "CLocalIPChanged\0CLocalPortChanged\0"
    "CRemoteIPChanged\0CRemotePortChanged\0"
    "GProtocol\0GLocalIP\0GLocalPort\0GRemoteIP\0"
    "GRemotePort\0CProtocol\0CLocalIP\0"
    "CLocalPort\0CRemoteIP\0CRemotePort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Network[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
      10,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,
       7,    0,   69,    2, 0x06 /* Public */,
       8,    0,   70,    2, 0x06 /* Public */,
       9,    0,   71,    2, 0x06 /* Public */,
      10,    0,   72,    2, 0x06 /* Public */,
      11,    0,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::Int, 0x00495103,
      13, QMetaType::QString, 0x00495103,
      14, QMetaType::QString, 0x00495103,
      15, QMetaType::QString, 0x00495103,
      16, QMetaType::QString, 0x00495103,
      17, QMetaType::Int, 0x00495103,
      18, QMetaType::QString, 0x00495103,
      19, QMetaType::QString, 0x00495103,
      20, QMetaType::QString, 0x00495103,
      21, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,

       0        // eod
};

void Network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Network *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GProtocolChanged(); break;
        case 1: _t->GLocalIPChanged(); break;
        case 2: _t->GLocalPortChanged(); break;
        case 3: _t->GRemoteIPChanged(); break;
        case 4: _t->GRemotePortChanged(); break;
        case 5: _t->CProtocolChanged(); break;
        case 6: _t->CLocalIPChanged(); break;
        case 7: _t->CLocalPortChanged(); break;
        case 8: _t->CRemoteIPChanged(); break;
        case 9: _t->CRemotePortChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::GProtocolChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::GLocalIPChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::GLocalPortChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::GRemoteIPChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::GRemotePortChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::CProtocolChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::CLocalIPChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::CLocalPortChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::CRemoteIPChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::CRemotePortChanged)) {
                *result = 9;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Network *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->GProtocol(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->GLocalIP(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->GLocalPort(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->GRemoteIP(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->GRemotePort(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->CProtocol(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->CLocalIP(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->CLocalPort(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->CRemoteIP(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->CRemotePort(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Network *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setGProtocol(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setGLocalIP(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setGLocalPort(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setGRemoteIP(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setGRemotePort(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setCProtocol(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setCLocalIP(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setCLocalPort(*reinterpret_cast< QString*>(_v)); break;
        case 8: _t->setCRemoteIP(*reinterpret_cast< QString*>(_v)); break;
        case 9: _t->setCRemotePort(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Network::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Network.data,
    qt_meta_data_Network,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Network.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Network::GProtocolChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Network::GLocalIPChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Network::GLocalPortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Network::GRemoteIPChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Network::GRemotePortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Network::CProtocolChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Network::CLocalIPChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Network::CLocalPortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Network::CRemoteIPChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Network::CRemotePortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
