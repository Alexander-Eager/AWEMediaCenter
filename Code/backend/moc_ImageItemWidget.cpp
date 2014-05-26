/****************************************************************************
** Meta object code from reading C++ file 'ImageItemWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/widgets/ImageItemWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageItemWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI__ImageItemWidget_t {
    QByteArrayData data[8];
    char stringdata[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UI__ImageItemWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UI__ImageItemWidget_t qt_meta_stringdata_UI__ImageItemWidget = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 8),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 4),
QT_MOC_LITERAL(4, 35, 4),
QT_MOC_LITERAL(5, 40, 5),
QT_MOC_LITERAL(6, 46, 8),
QT_MOC_LITERAL(7, 55, 5)
    },
    "UI::ImageItemWidget\0setImage\0\0QDir\0"
    "file\0image\0setIndex\0index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI__ImageItemWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a,
       1,    1,   32,    2, 0x0a,
       6,    1,   35,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QPixmap,    5,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void UI::ImageItemWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageItemWidget *_t = static_cast<ImageItemWidget *>(_o);
        switch (_id) {
        case 0: _t->setImage((*reinterpret_cast< QDir(*)>(_a[1]))); break;
        case 1: _t->setImage((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: _t->setIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject UI::ImageItemWidget::staticMetaObject = {
    { &ItemWidget::staticMetaObject, qt_meta_stringdata_UI__ImageItemWidget.data,
      qt_meta_data_UI__ImageItemWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *UI::ImageItemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::ImageItemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UI__ImageItemWidget.stringdata))
        return static_cast<void*>(const_cast< ImageItemWidget*>(this));
    return ItemWidget::qt_metacast(_clname);
}

int UI::ImageItemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ItemWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
