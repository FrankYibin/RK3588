/****************************************************************************
** Meta object code from reading C++ file 'logindef.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/logindef.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logindef.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoginIndexEnum_t {
    QByteArrayData data[6];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginIndexEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginIndexEnum_t qt_meta_stringdata_LoginIndexEnum = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LoginIndexEnum"
QT_MOC_LITERAL(1, 15, 10), // "LOGININDEX"
QT_MOC_LITERAL(2, 26, 14), // "EMPTY_PASSCODE"
QT_MOC_LITERAL(3, 41, 21), // "MULTIPLE_FAILED_LOGIN"
QT_MOC_LITERAL(4, 63, 10), // "LOGIN_FAIL"
QT_MOC_LITERAL(5, 74, 7) // "SUCCESS"

    },
    "LoginIndexEnum\0LOGININDEX\0EMPTY_PASSCODE\0"
    "MULTIPLE_FAILED_LOGIN\0LOGIN_FAIL\0"
    "SUCCESS"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginIndexEnum[] = {

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
       1,    1, 0x0,    4,   19,

 // enum data: key, value
       2, uint(LoginIndexEnum::EMPTY_PASSCODE),
       3, uint(LoginIndexEnum::MULTIPLE_FAILED_LOGIN),
       4, uint(LoginIndexEnum::LOGIN_FAIL),
       5, uint(LoginIndexEnum::SUCCESS),

       0        // eod
};

void LoginIndexEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LoginIndexEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LoginIndexEnum.data,
    qt_meta_data_LoginIndexEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LoginIndexEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginIndexEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoginIndexEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LoginIndexEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
