/****************************************************************************
** Meta object code from reading C++ file 'languageconfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/languageconfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'languageconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LanguageConfig_t {
    QByteArrayData data[11];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LanguageConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LanguageConfig_t qt_meta_stringdata_LanguageConfig = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LanguageConfig"
QT_MOC_LITERAL(1, 15, 28), // "signalCurrentLanguageChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 21), // "getLanguageStringList"
QT_MOC_LITERAL(4, 67, 11), // "screenIndex"
QT_MOC_LITERAL(5, 79, 10), // "sourceList"
QT_MOC_LITERAL(6, 90, 19), // "getLanguageMenuName"
QT_MOC_LITERAL(7, 110, 10), // "sourceName"
QT_MOC_LITERAL(8, 121, 24), // "getLanguageModelInstance"
QT_MOC_LITERAL(9, 146, 14), // "LanguageModel*"
QT_MOC_LITERAL(10, 161, 15) // "CurrentLanguage"

    },
    "LanguageConfig\0signalCurrentLanguageChanged\0"
    "\0getLanguageStringList\0screenIndex\0"
    "sourceList\0getLanguageMenuName\0"
    "sourceName\0getLanguageModelInstance\0"
    "LanguageModel*\0CurrentLanguage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LanguageConfig[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   46, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    2,   35,    2, 0x02 /* Public */,
       6,    2,   40,    2, 0x02 /* Public */,
       8,    0,   45,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::QStringList, QMetaType::Int, QMetaType::QStringList,    4,    5,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,    4,    7,
    0x80000000 | 9,

 // properties: name, type, flags
      10, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void LanguageConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LanguageConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalCurrentLanguageChanged(); break;
        case 1: { QStringList _r = _t->getLanguageStringList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->getLanguageMenuName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { LanguageModel* _r = _t->getLanguageModelInstance();
            if (_a[0]) *reinterpret_cast< LanguageModel**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LanguageConfig::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LanguageConfig::signalCurrentLanguageChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LanguageConfig *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getCurrentLanguage(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<LanguageConfig *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCurrentLanguage(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject LanguageConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LanguageConfig.data,
    qt_meta_data_LanguageConfig,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LanguageConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LanguageConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LanguageConfig.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LanguageConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void LanguageConfig::signalCurrentLanguageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
