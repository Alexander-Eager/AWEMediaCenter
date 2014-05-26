/****************************************************************************
** Meta object code from reading C++ file 'MediaItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "items/MediaItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AWE__MediaItem_t {
    QByteArrayData data[9];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AWE__MediaItem_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AWE__MediaItem_t qt_meta_stringdata_AWE__MediaItem = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 8),
QT_MOC_LITERAL(2, 24, 8),
QT_MOC_LITERAL(3, 33, 8),
QT_MOC_LITERAL(4, 42, 6),
QT_MOC_LITERAL(5, 49, 9),
QT_MOC_LITERAL(6, 59, 6),
QT_MOC_LITERAL(7, 66, 4),
QT_MOC_LITERAL(8, 71, 7)
    },
    "AWE::MediaItem\0itemType\0ItemType\0"
    "isFolder\0isFile\0isService\0FOLDER\0FILE\0"
    "SERVICE\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AWE__MediaItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       1,   26, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x00085c09,
       3, QMetaType::Bool, 0x00085c01,
       4, QMetaType::Bool, 0x00085c01,
       5, QMetaType::Bool, 0x00085c01,

 // enums: name, flags, count, data
       2, 0x0,    3,   30,

 // enum data: key, value
       6, uint(AWE::MediaItem::FOLDER),
       7, uint(AWE::MediaItem::FILE),
       8, uint(AWE::MediaItem::SERVICE),

       0        // eod
};

void AWE::MediaItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject AWE::MediaItem::staticMetaObject = {
    { &MetadataHolder::staticMetaObject, qt_meta_stringdata_AWE__MediaItem.data,
      qt_meta_data_AWE__MediaItem,  qt_static_metacall, 0, 0}
};


const QMetaObject *AWE::MediaItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AWE::MediaItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AWE__MediaItem.stringdata))
        return static_cast<void*>(const_cast< MediaItem*>(this));
    return MetadataHolder::qt_metacast(_clname);
}

int AWE::MediaItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MetadataHolder::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< ItemType*>(_v) = getItemType(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isFolder(); break;
        case 2: *reinterpret_cast< bool*>(_v) = isFile(); break;
        case 3: *reinterpret_cast< bool*>(_v) = isService(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
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
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
