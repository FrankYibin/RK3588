/****************************************************************************
** Meta object code from reading C++ file 'productionruninterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/productionruninterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'productionruninterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProductionRun_t {
    QByteArrayData data[19];
    char stringdata0[364];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProductionRun_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProductionRun_t qt_meta_stringdata_ProductionRun = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ProductionRun"
QT_MOC_LITERAL(1, 14, 24), // "OnActiveRecipeNumChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 25), // "OnActiveRecipeNameChanged"
QT_MOC_LITERAL(4, 66, 23), // "OnRecipeWeldModeChanged"
QT_MOC_LITERAL(5, 90, 27), // "OnRecipeWeldModeUnitChanged"
QT_MOC_LITERAL(6, 118, 28), // "OnRecipeWeldModeValueChanged"
QT_MOC_LITERAL(7, 147, 23), // "OnTotalCycleTimeChanged"
QT_MOC_LITERAL(8, 171, 19), // "OnCycleCountChanged"
QT_MOC_LITERAL(9, 191, 23), // "OnPeakPowerRatioChanged"
QT_MOC_LITERAL(10, 215, 20), // "slotHeartbeatUpdated"
QT_MOC_LITERAL(11, 236, 15), // "ActiveRecipeNum"
QT_MOC_LITERAL(12, 252, 16), // "ActiveRecipeName"
QT_MOC_LITERAL(13, 269, 14), // "RecipeWeldMode"
QT_MOC_LITERAL(14, 284, 18), // "RecipeWeldModeUnit"
QT_MOC_LITERAL(15, 303, 19), // "RecipeWeldModeValue"
QT_MOC_LITERAL(16, 323, 14), // "TotalCycleTime"
QT_MOC_LITERAL(17, 338, 10), // "CycleCount"
QT_MOC_LITERAL(18, 349, 14) // "PeakPowerRatio"

    },
    "ProductionRun\0OnActiveRecipeNumChanged\0"
    "\0OnActiveRecipeNameChanged\0"
    "OnRecipeWeldModeChanged\0"
    "OnRecipeWeldModeUnitChanged\0"
    "OnRecipeWeldModeValueChanged\0"
    "OnTotalCycleTimeChanged\0OnCycleCountChanged\0"
    "OnPeakPowerRatioChanged\0slotHeartbeatUpdated\0"
    "ActiveRecipeNum\0ActiveRecipeName\0"
    "RecipeWeldMode\0RecipeWeldModeUnit\0"
    "RecipeWeldModeValue\0TotalCycleTime\0"
    "CycleCount\0PeakPowerRatio"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProductionRun[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       8,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    0,   63,    2, 0x06 /* Public */,
       7,    0,   64,    2, 0x06 /* Public */,
       8,    0,   65,    2, 0x06 /* Public */,
       9,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::VoidStar,    2,

 // properties: name, type, flags
      11, QMetaType::Int, 0x00495003,
      12, QMetaType::QString, 0x00495003,
      13, QMetaType::Int, 0x00495003,
      14, QMetaType::QString, 0x00495003,
      15, QMetaType::QString, 0x00495003,
      16, QMetaType::QString, 0x00495003,
      17, QMetaType::QString, 0x00495003,
      18, QMetaType::Float, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,

       0        // eod
};

void ProductionRun::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProductionRun *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnActiveRecipeNumChanged(); break;
        case 1: _t->OnActiveRecipeNameChanged(); break;
        case 2: _t->OnRecipeWeldModeChanged(); break;
        case 3: _t->OnRecipeWeldModeUnitChanged(); break;
        case 4: _t->OnRecipeWeldModeValueChanged(); break;
        case 5: _t->OnTotalCycleTimeChanged(); break;
        case 6: _t->OnCycleCountChanged(); break;
        case 7: _t->OnPeakPowerRatioChanged(); break;
        case 8: _t->slotHeartbeatUpdated((*reinterpret_cast< void*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnActiveRecipeNumChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnActiveRecipeNameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnRecipeWeldModeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnRecipeWeldModeUnitChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnRecipeWeldModeValueChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnTotalCycleTimeChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnCycleCountChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ProductionRun::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductionRun::OnPeakPowerRatioChanged)) {
                *result = 7;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ProductionRun *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getActiveRecipeNum(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getActiveRecipeName(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->getRecipeWeldMode(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getRecipeWeldModeUnit(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->getRecipeWeldModeValue(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->getTotalCycleTime(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->getCycleCount(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getPeakPowerRatio(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ProductionRun *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->updateActiveRecipeNum(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->updateActiveRecipeName(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->updateRecipeWeldMode(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->updateRecipeWeldModeUnit(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->updateRecipeWeldModeValue(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->updateTotalCycleTime(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->updateCycleCount(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->updatePeakPowerRatio(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ProductionRun::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_ProductionRun.data,
    qt_meta_data_ProductionRun,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProductionRun::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProductionRun::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProductionRun.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ProductionRun::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ProductionRun::OnActiveRecipeNumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ProductionRun::OnActiveRecipeNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ProductionRun::OnRecipeWeldModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ProductionRun::OnRecipeWeldModeUnitChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ProductionRun::OnRecipeWeldModeValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ProductionRun::OnTotalCycleTimeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ProductionRun::OnCycleCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ProductionRun::OnPeakPowerRatioChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
