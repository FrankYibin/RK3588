/****************************************************************************
** Meta object code from reading C++ file 'recipedef.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/recipedef.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recipedef.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecipeEnum_t {
    QByteArrayData data[19];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecipeEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecipeEnum_t qt_meta_stringdata_RecipeEnum = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RecipeEnum"
QT_MOC_LITERAL(1, 11, 13), // "WELDMODEINDEX"
QT_MOC_LITERAL(2, 25, 8), // "NONE_IDX"
QT_MOC_LITERAL(3, 34, 8), // "TIME_IDX"
QT_MOC_LITERAL(4, 43, 10), // "ENERGY_IDX"
QT_MOC_LITERAL(5, 54, 13), // "PEAKPOWER_IDX"
QT_MOC_LITERAL(6, 68, 15), // "COLDISTANCE_IDX"
QT_MOC_LITERAL(7, 84, 15), // "ABSDISTANCE_IDX"
QT_MOC_LITERAL(8, 100, 10), // "GROUND_IDX"
QT_MOC_LITERAL(9, 111, 17), // "TOTALWELDMODE_IDX"
QT_MOC_LITERAL(10, 129, 13), // "RECIPEACTIONS"
QT_MOC_LITERAL(11, 143, 14), // "CREATE_NEW_IDX"
QT_MOC_LITERAL(12, 158, 18), // "PRODUCTION_RUN_IDX"
QT_MOC_LITERAL(13, 177, 8), // "EDIT_IDX"
QT_MOC_LITERAL(14, 186, 21), // "RESET_CYCLE_COUNT_IDX"
QT_MOC_LITERAL(15, 208, 17), // "SET_AS_ACTIVE_IDX"
QT_MOC_LITERAL(16, 226, 10), // "DELETE_IDX"
QT_MOC_LITERAL(17, 237, 8), // "COPY_IDX"
QT_MOC_LITERAL(18, 246, 15) // "INFORMATION_IDX"

    },
    "RecipeEnum\0WELDMODEINDEX\0NONE_IDX\0"
    "TIME_IDX\0ENERGY_IDX\0PEAKPOWER_IDX\0"
    "COLDISTANCE_IDX\0ABSDISTANCE_IDX\0"
    "GROUND_IDX\0TOTALWELDMODE_IDX\0RECIPEACTIONS\0"
    "CREATE_NEW_IDX\0PRODUCTION_RUN_IDX\0"
    "EDIT_IDX\0RESET_CYCLE_COUNT_IDX\0"
    "SET_AS_ACTIVE_IDX\0DELETE_IDX\0COPY_IDX\0"
    "INFORMATION_IDX"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecipeEnum[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    8,   24,
      10,   10, 0x0,    8,   40,

 // enum data: key, value
       2, uint(RecipeEnum::NONE_IDX),
       3, uint(RecipeEnum::TIME_IDX),
       4, uint(RecipeEnum::ENERGY_IDX),
       5, uint(RecipeEnum::PEAKPOWER_IDX),
       6, uint(RecipeEnum::COLDISTANCE_IDX),
       7, uint(RecipeEnum::ABSDISTANCE_IDX),
       8, uint(RecipeEnum::GROUND_IDX),
       9, uint(RecipeEnum::TOTALWELDMODE_IDX),
      11, uint(RecipeEnum::CREATE_NEW_IDX),
      12, uint(RecipeEnum::PRODUCTION_RUN_IDX),
      13, uint(RecipeEnum::EDIT_IDX),
      14, uint(RecipeEnum::RESET_CYCLE_COUNT_IDX),
      15, uint(RecipeEnum::SET_AS_ACTIVE_IDX),
      16, uint(RecipeEnum::DELETE_IDX),
      17, uint(RecipeEnum::COPY_IDX),
      18, uint(RecipeEnum::INFORMATION_IDX),

       0        // eod
};

void RecipeEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject RecipeEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RecipeEnum.data,
    qt_meta_data_RecipeEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecipeEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecipeEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecipeEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RecipeEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
