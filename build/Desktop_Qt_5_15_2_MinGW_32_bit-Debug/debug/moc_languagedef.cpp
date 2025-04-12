/****************************************************************************
** Meta object code from reading C++ file 'languagedef.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../c++Source/languagedef.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'languagedef.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LanguageEnum_t {
    QByteArrayData data[15];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LanguageEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LanguageEnum_t qt_meta_stringdata_LanguageEnum = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LanguageEnum"
QT_MOC_LITERAL(1, 13, 13), // "LANGUAGEINDEX"
QT_MOC_LITERAL(2, 27, 8), // "NONE_IDX"
QT_MOC_LITERAL(3, 36, 11), // "ENGLISH_IDX"
QT_MOC_LITERAL(4, 48, 10), // "FRENCH_IDX"
QT_MOC_LITERAL(5, 59, 10), // "GERMAN_IDX"
QT_MOC_LITERAL(6, 70, 11), // "SPANISH_IDX"
QT_MOC_LITERAL(7, 82, 10), // "KOREAN_IDX"
QT_MOC_LITERAL(8, 93, 21), // "SIMPLIFIEDCHINESE_IDX"
QT_MOC_LITERAL(9, 115, 11), // "ITALIAN_IDX"
QT_MOC_LITERAL(10, 127, 12), // "JAPANESE_IDX"
QT_MOC_LITERAL(11, 140, 10), // "DANISH_IDX"
QT_MOC_LITERAL(12, 151, 13), // "SLOVAKIAN_IDX"
QT_MOC_LITERAL(13, 165, 10), // "POLISH_IDX"
QT_MOC_LITERAL(14, 176, 9) // "TOTAL_IDX"

    },
    "LanguageEnum\0LANGUAGEINDEX\0NONE_IDX\0"
    "ENGLISH_IDX\0FRENCH_IDX\0GERMAN_IDX\0"
    "SPANISH_IDX\0KOREAN_IDX\0SIMPLIFIEDCHINESE_IDX\0"
    "ITALIAN_IDX\0JAPANESE_IDX\0DANISH_IDX\0"
    "SLOVAKIAN_IDX\0POLISH_IDX\0TOTAL_IDX"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LanguageEnum[] = {

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
       1,    1, 0x0,   13,   19,

 // enum data: key, value
       2, uint(LanguageEnum::NONE_IDX),
       3, uint(LanguageEnum::ENGLISH_IDX),
       4, uint(LanguageEnum::FRENCH_IDX),
       5, uint(LanguageEnum::GERMAN_IDX),
       6, uint(LanguageEnum::SPANISH_IDX),
       7, uint(LanguageEnum::KOREAN_IDX),
       8, uint(LanguageEnum::SIMPLIFIEDCHINESE_IDX),
       9, uint(LanguageEnum::ITALIAN_IDX),
      10, uint(LanguageEnum::JAPANESE_IDX),
      11, uint(LanguageEnum::DANISH_IDX),
      12, uint(LanguageEnum::SLOVAKIAN_IDX),
      13, uint(LanguageEnum::POLISH_IDX),
      14, uint(LanguageEnum::TOTAL_IDX),

       0        // eod
};

void LanguageEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LanguageEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LanguageEnum.data,
    qt_meta_data_LanguageEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LanguageEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LanguageEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LanguageEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LanguageEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
