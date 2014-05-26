/****************************************************************************
** Meta object code from reading C++ file 'MediaItemWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/widgets/items/MediaItemWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaItemWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI__MediaItemWidget_t {
    QByteArrayData data[11];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UI__MediaItemWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UI__MediaItemWidget_t qt_meta_stringdata_UI__MediaItemWidget = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 12),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 15),
QT_MOC_LITERAL(4, 50, 4),
QT_MOC_LITERAL(5, 55, 14),
QT_MOC_LITERAL(6, 70, 20),
QT_MOC_LITERAL(7, 91, 19),
QT_MOC_LITERAL(8, 111, 5),
QT_MOC_LITERAL(9, 117, 19),
QT_MOC_LITERAL(10, 137, 4)
    },
    "UI::MediaItemWidget\0setMediaItem\0\0"
    "AWE::MediaItem*\0item\0respondToClick\0"
    "respondToDoubleClick\0respondToIconChange\0"
    "index\0respondToNameChange\0name\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI__MediaItemWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a,
       5,    0,   42,    2, 0x08,
       6,    0,   43,    2, 0x08,
       7,    1,   44,    2, 0x08,
       9,    1,   47,    2, 0x08,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void UI::MediaItemWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MediaItemWidget *_t = static_cast<MediaItemWidget *>(_o);
        switch (_id) {
        case 0: _t->setMediaItem((*reinterpret_cast< AWE::MediaItem*(*)>(_a[1]))); break;
        case 1: _t->respondToClick(); break;
        case 2: _t->respondToDoubleClick(); break;
        case 3: _t->respondToIconChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->respondToNameChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AWE::MediaItem* >(); break;
            }
            break;
        }
    }
}

const QMetaObject UI::MediaItemWidget::staticMetaObject = {
    { &ItemWidget::staticMetaObject, qt_meta_stringdata_UI__MediaItemWidget.data,
      qt_meta_data_UI__MediaItemWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *UI::MediaItemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::MediaItemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UI__MediaItemWidget.stringdata))
        return static_cast<void*>(const_cast< MediaItemWidget*>(this));
    return ItemWidget::qt_metacast(_clname);
}

int UI::MediaItemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ItemWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
