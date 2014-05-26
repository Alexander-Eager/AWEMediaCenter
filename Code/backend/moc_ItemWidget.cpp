/****************************************************************************
** Meta object code from reading C++ file 'ItemWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/widgets/ItemWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ItemWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI__ItemWidget_t {
    QByteArrayData data[14];
    char stringdata[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UI__ItemWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UI__ItemWidget_t qt_meta_stringdata_UI__ItemWidget = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 11),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 11),
QT_MOC_LITERAL(4, 40, 4),
QT_MOC_LITERAL(5, 45, 13),
QT_MOC_LITERAL(6, 59, 19),
QT_MOC_LITERAL(7, 79, 8),
QT_MOC_LITERAL(8, 88, 8),
QT_MOC_LITERAL(9, 97, 7),
QT_MOC_LITERAL(10, 105, 13),
QT_MOC_LITERAL(11, 119, 9),
QT_MOC_LITERAL(12, 129, 11),
QT_MOC_LITERAL(13, 141, 15)
    },
    "UI::ItemWidget\0highlighted\0\0ItemWidget*\0"
    "item\0unhighlighted\0highlightingChanged\0"
    "newState\0selected\0clicked\0doubleClicked\0"
    "highlight\0unhighlight\0setHighlighting\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI__ItemWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06,
       1,    1,   80,    2, 0x06,
       5,    0,   83,    2, 0x06,
       5,    1,   84,    2, 0x06,
       6,    1,   87,    2, 0x06,
       6,    2,   90,    2, 0x06,
       8,    0,   95,    2, 0x06,
       8,    1,   96,    2, 0x06,
       9,    0,   99,    2, 0x06,
      10,    0,  100,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      11,    0,  101,    2, 0x0a,
      12,    0,  102,    2, 0x0a,
      13,    1,  103,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    7,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,

       0        // eod
};

void UI::ItemWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ItemWidget *_t = static_cast<ItemWidget *>(_o);
        switch (_id) {
        case 0: _t->highlighted(); break;
        case 1: _t->highlighted((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 2: _t->unhighlighted(); break;
        case 3: _t->unhighlighted((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 4: _t->highlightingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->highlightingChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< ItemWidget*(*)>(_a[2]))); break;
        case 6: _t->selected(); break;
        case 7: _t->selected((*reinterpret_cast< ItemWidget*(*)>(_a[1]))); break;
        case 8: _t->clicked(); break;
        case 9: _t->doubleClicked(); break;
        case 10: _t->highlight(); break;
        case 11: _t->unhighlight(); break;
        case 12: _t->setHighlighting((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
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
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ItemWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::highlighted)) {
                *result = 0;
            }
        }
        {
            typedef void (ItemWidget::*_t)(ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::highlighted)) {
                *result = 1;
            }
        }
        {
            typedef void (ItemWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::unhighlighted)) {
                *result = 2;
            }
        }
        {
            typedef void (ItemWidget::*_t)(ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::unhighlighted)) {
                *result = 3;
            }
        }
        {
            typedef void (ItemWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::highlightingChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (ItemWidget::*_t)(bool , ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::highlightingChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (ItemWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::selected)) {
                *result = 6;
            }
        }
        {
            typedef void (ItemWidget::*_t)(ItemWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::selected)) {
                *result = 7;
            }
        }
        {
            typedef void (ItemWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::clicked)) {
                *result = 8;
            }
        }
        {
            typedef void (ItemWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemWidget::doubleClicked)) {
                *result = 9;
            }
        }
    }
}

const QMetaObject UI::ItemWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UI__ItemWidget.data,
      qt_meta_data_UI__ItemWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *UI::ItemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::ItemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UI__ItemWidget.stringdata))
        return static_cast<void*>(const_cast< ItemWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int UI::ItemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void UI::ItemWidget::highlighted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UI::ItemWidget::highlighted(ItemWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UI::ItemWidget::unhighlighted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void UI::ItemWidget::unhighlighted(ItemWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UI::ItemWidget::highlightingChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UI::ItemWidget::highlightingChanged(bool _t1, ItemWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void UI::ItemWidget::selected()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void UI::ItemWidget::selected(ItemWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void UI::ItemWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void UI::ItemWidget::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
