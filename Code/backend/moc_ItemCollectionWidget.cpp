/****************************************************************************
** Meta object code from reading C++ file 'ItemCollectionWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/widgets/collection/ItemCollectionWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ItemCollectionWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI__ItemCollectionWidget_t {
    QByteArrayData data[16];
    char stringdata[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UI__ItemCollectionWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UI__ItemCollectionWidget_t qt_meta_stringdata_UI__ItemCollectionWidget = {
    {
QT_MOC_LITERAL(0, 0, 24),
QT_MOC_LITERAL(1, 25, 15),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 11),
QT_MOC_LITERAL(4, 54, 4),
QT_MOC_LITERAL(5, 59, 17),
QT_MOC_LITERAL(6, 77, 23),
QT_MOC_LITERAL(7, 101, 8),
QT_MOC_LITERAL(8, 110, 12),
QT_MOC_LITERAL(9, 123, 7),
QT_MOC_LITERAL(10, 131, 10),
QT_MOC_LITERAL(11, 142, 5),
QT_MOC_LITERAL(12, 148, 24),
QT_MOC_LITERAL(13, 173, 26),
QT_MOC_LITERAL(14, 200, 32),
QT_MOC_LITERAL(15, 233, 21)
    },
    "UI::ItemCollectionWidget\0itemHighlighted\0"
    "\0ItemWidget*\0item\0itemUnhighlighted\0"
    "itemHighlightingChanged\0newState\0"
    "itemSelected\0addItem\0removeItem\0clear\0"
    "respondToItemHighlighted\0"
    "respondToItemUnhighlighted\0"
    "respondToItemHighlightingChanged\0"
    "respondToItemSelected\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI__ItemCollectionWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06,
       5,    1,   72,    2, 0x06,
       6,    2,   75,    2, 0x06,
       8,    1,   80,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       9,    1,   83,    2, 0x0a,
      10,    1,   86,    2, 0x0a,
      11,    0,   89,    2, 0x0a,
      12,    1,   90,    2, 0x09,
      13,    1,   93,    2, 0x09,
      14,    2,   96,    2, 0x09,
      15,    1,  101,    2, 0x09,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void UI::ItemCollectionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ItemCollectionWidget *_t = static_cast<ItemCollectionWidget *>(_o);
        switch (_id) {
        case 0: _t->itemHighlighted((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 1: _t->itemUnhighlighted((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 2: _t->itemHighlightingChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< ItemWidget*(*)>(_a[2]))); break;
        case 3: _t->itemSelected((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 4: _t->addItem((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 5: _t->removeItem((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 6: _t->clear(); break;
        case 7: _t->respondToItemHighlighted((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 8: _t->respondToItemUnhighlighted((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 9: _t->respondToItemHighlightingChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< ItemWidget*(*)>(_a[2]))); break;
        case 10: _t->respondToItemSelected((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ItemWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ItemCollectionWidget::*_t)(ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemCollectionWidget::itemHighlighted)) {
                *result = 0;
            }
        }
        {
            typedef void (ItemCollectionWidget::*_t)(ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemCollectionWidget::itemUnhighlighted)) {
                *result = 1;
            }
        }
        {
            typedef void (ItemCollectionWidget::*_t)(bool , ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemCollectionWidget::itemHighlightingChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (ItemCollectionWidget::*_t)(ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemCollectionWidget::itemSelected)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject UI::ItemCollectionWidget::staticMetaObject = {
    { &TransparentScrollArea::staticMetaObject, qt_meta_stringdata_UI__ItemCollectionWidget.data,
      qt_meta_data_UI__ItemCollectionWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *UI::ItemCollectionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::ItemCollectionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UI__ItemCollectionWidget.stringdata))
        return static_cast<void*>(const_cast< ItemCollectionWidget*>(this));
    return TransparentScrollArea::qt_metacast(_clname);
}

int UI::ItemCollectionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TransparentScrollArea::qt_metacall(_c, _id, _a);
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
void UI::ItemCollectionWidget::itemHighlighted(ItemWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UI::ItemCollectionWidget::itemUnhighlighted(ItemWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UI::ItemCollectionWidget::itemHighlightingChanged(bool _t1, ItemWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UI::ItemCollectionWidget::itemSelected(ItemWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
