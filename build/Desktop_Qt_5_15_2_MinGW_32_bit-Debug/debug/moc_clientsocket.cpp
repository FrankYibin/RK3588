/****************************************************************************
** Meta object code from reading C++ file 'clientsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/clientsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_clientSocket_t {
    QByteArrayData data[18];
    char stringdata0[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_clientSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_clientSocket_t qt_meta_stringdata_clientSocket = {
    {
QT_MOC_LITERAL(0, 0, 12), // "clientSocket"
QT_MOC_LITERAL(1, 13, 24), // "signalMessageReadyToSend"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 24), // "signalSocketReadyToClose"
QT_MOC_LITERAL(4, 64, 22), // "signalErrorCodeChanged"
QT_MOC_LITERAL(5, 87, 23), // "signalAlarmCodeToNotify"
QT_MOC_LITERAL(6, 111, 9), // "alarmCode"
QT_MOC_LITERAL(7, 121, 22), // "signalHeartbeatUpdated"
QT_MOC_LITERAL(8, 144, 17), // "slotDataReceiving"
QT_MOC_LITERAL(9, 162, 21), // "slotSocketStateChange"
QT_MOC_LITERAL(10, 184, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(11, 213, 11), // "socketState"
QT_MOC_LITERAL(12, 225, 22), // "slotSocketDisconnected"
QT_MOC_LITERAL(13, 248, 20), // "slotSocketConnecting"
QT_MOC_LITERAL(14, 269, 15), // "slotDataSending"
QT_MOC_LITERAL(15, 285, 13), // "slotSslErrors"
QT_MOC_LITERAL(16, 299, 16), // "QList<QSslError>"
QT_MOC_LITERAL(17, 316, 6) // "errors"

    },
    "clientSocket\0signalMessageReadyToSend\0"
    "\0signalSocketReadyToClose\0"
    "signalErrorCodeChanged\0signalAlarmCodeToNotify\0"
    "alarmCode\0signalHeartbeatUpdated\0"
    "slotDataReceiving\0slotSocketStateChange\0"
    "QAbstractSocket::SocketState\0socketState\0"
    "slotSocketDisconnected\0slotSocketConnecting\0"
    "slotDataSending\0slotSslErrors\0"
    "QList<QSslError>\0errors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_clientSocket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    1,   72,    2, 0x06 /* Public */,
       7,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   78,    2, 0x08 /* Private */,
       9,    1,   79,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    1,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::VoidStar,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void clientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<clientSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMessageReadyToSend(); break;
        case 1: _t->signalSocketReadyToClose(); break;
        case 2: _t->signalErrorCodeChanged(); break;
        case 3: _t->signalAlarmCodeToNotify((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalHeartbeatUpdated((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 5: _t->slotDataReceiving(); break;
        case 6: _t->slotSocketStateChange((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 7: _t->slotSocketDisconnected(); break;
        case 8: _t->slotSocketConnecting(); break;
        case 9: _t->slotDataSending(); break;
        case 10: _t->slotSslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (clientSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientSocket::signalMessageReadyToSend)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (clientSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientSocket::signalSocketReadyToClose)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (clientSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientSocket::signalErrorCodeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (clientSocket::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientSocket::signalAlarmCodeToNotify)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (clientSocket::*)(void * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientSocket::signalHeartbeatUpdated)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject clientSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QSslSocket::staticMetaObject>(),
    qt_meta_stringdata_clientSocket.data,
    qt_meta_data_clientSocket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *clientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *clientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_clientSocket.stringdata0))
        return static_cast<void*>(this);
    return QSslSocket::qt_metacast(_clname);
}

int clientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSslSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void clientSocket::signalMessageReadyToSend()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void clientSocket::signalSocketReadyToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void clientSocket::signalErrorCodeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void clientSocket::signalAlarmCodeToNotify(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void clientSocket::signalHeartbeatUpdated(void * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
