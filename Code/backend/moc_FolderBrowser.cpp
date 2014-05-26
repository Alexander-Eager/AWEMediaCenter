/****************************************************************************
** Meta object code from reading C++ file 'FolderBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/contents/FolderBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FolderBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI__FolderBrowser_t {
    QByteArrayData data[15];
    char stringdata[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UI__FolderBrowser_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UI__FolderBrowser_t qt_meta_stringdata_UI__FolderBrowser = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 8),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 15),
QT_MOC_LITERAL(4, 44, 4),
QT_MOC_LITERAL(5, 49, 15),
QT_MOC_LITERAL(6, 65, 15),
QT_MOC_LITERAL(7, 81, 4),
QT_MOC_LITERAL(8, 86, 18),
QT_MOC_LITERAL(9, 105, 5),
QT_MOC_LITERAL(10, 111, 17),
QT_MOC_LITERAL(11, 129, 20),
QT_MOC_LITERAL(12, 150, 28),
QT_MOC_LITERAL(13, 179, 7),
QT_MOC_LITERAL(14, 187, 5)
    },
    "UI::FolderBrowser\0openItem\0\0AWE::MediaItem*\0"
    "item\0moveUpOneFolder\0setTitleBarText\0"
    "text\0setBackgroundImage\0image\0"
    "scrapeForMetadata\0AWE::MetadataHolder*\0"
    "AWE::MetadataScraperHandler*\0scraper\0"
    "flags\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI__FolderBrowser[] = {

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
       5,    0,   42,    2, 0x0a,
       6,    1,   43,    2, 0x0a,
       8,    1,   46,    2, 0x0a,
      10,    3,   49,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QPixmap,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 12, QMetaType::Int,    4,   13,   14,

       0        // eod
};

void UI::FolderBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FolderBrowser *_t = static_cast<FolderBrowser *>(_o);
        switch (_id) {
        case 0: _t->openItem((*reinterpret_cast< AWE::MediaItem*(*)>(_a[1]))); break;
        case 1: _t->moveUpOneFolder(); break;
        case 2: _t->setTitleBarText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setBackgroundImage((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 4: _t->scrapeForMetadata((*reinterpret_cast< AWE::MetadataHolder*(*)>(_a[1])),(*reinterpret_cast< AWE::MetadataScraperHandler*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
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
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AWE::MetadataHolder* >(); break;
            }
            break;
        }
    }
}

const QMetaObject UI::FolderBrowser::staticMetaObject = {
    { &WindowContents::staticMetaObject, qt_meta_stringdata_UI__FolderBrowser.data,
      qt_meta_data_UI__FolderBrowser,  qt_static_metacall, 0, 0}
};


const QMetaObject *UI::FolderBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::FolderBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UI__FolderBrowser.stringdata))
        return static_cast<void*>(const_cast< FolderBrowser*>(this));
    return WindowContents::qt_metacast(_clname);
}

int UI::FolderBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WindowContents::qt_metacall(_c, _id, _a);
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
