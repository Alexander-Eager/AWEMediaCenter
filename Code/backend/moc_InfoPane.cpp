/****************************************************************************
** Meta object code from reading C++ file 'InfoPane.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/pane/InfoPane.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InfoPane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI__InfoPane_t {
    QByteArrayData data[24];
    char stringdata[354];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UI__InfoPane_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UI__InfoPane_t qt_meta_stringdata_UI__InfoPane = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 15),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 15),
QT_MOC_LITERAL(4, 46, 4),
QT_MOC_LITERAL(5, 51, 24),
QT_MOC_LITERAL(6, 76, 6),
QT_MOC_LITERAL(7, 83, 18),
QT_MOC_LITERAL(8, 102, 25),
QT_MOC_LITERAL(9, 128, 7),
QT_MOC_LITERAL(10, 136, 17),
QT_MOC_LITERAL(11, 154, 12),
QT_MOC_LITERAL(12, 167, 6),
QT_MOC_LITERAL(13, 174, 24),
QT_MOC_LITERAL(14, 199, 15),
QT_MOC_LITERAL(15, 215, 4),
QT_MOC_LITERAL(16, 220, 28),
QT_MOC_LITERAL(17, 249, 7),
QT_MOC_LITERAL(18, 257, 5),
QT_MOC_LITERAL(19, 263, 7),
QT_MOC_LITERAL(20, 271, 19),
QT_MOC_LITERAL(21, 291, 19),
QT_MOC_LITERAL(22, 311, 19),
QT_MOC_LITERAL(23, 331, 21)
    },
    "UI::InfoPane\0wantsToOpenFile\0\0"
    "AWE::MediaFile*\0file\0AWE::MediaPlayerHandler*\0"
    "player\0wantsToOpenService\0"
    "AWE::MediaServiceHandler*\0service\0"
    "wantsToOpenFolder\0AWE::Folder*\0folder\0"
    "wantsToScrapeForMetadata\0AWE::MediaItem*\0"
    "item\0AWE::MetadataScraperHandler*\0"
    "scraper\0flags\0setItem\0respondToPlayButton\0"
    "respondToOpenButton\0respondToFolderOpen\0"
    "respondToScrapeButton\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI__InfoPane[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06,
       7,    1,   64,    2, 0x06,
      10,    1,   67,    2, 0x06,
      13,    3,   70,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      19,    1,   77,    2, 0x0a,
      20,    0,   80,    2, 0x08,
      21,    0,   81,    2, 0x08,
      22,    0,   82,    2, 0x08,
      23,    0,   83,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16, QMetaType::Int,   15,   17,   18,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UI::InfoPane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InfoPane *_t = static_cast<InfoPane *>(_o);
        switch (_id) {
        case 0: _t->wantsToOpenFile((*reinterpret_cast< AWE::MediaFile*(*)>(_a[1])),(*reinterpret_cast< AWE::MediaPlayerHandler*(*)>(_a[2]))); break;
        case 1: _t->wantsToOpenService((*reinterpret_cast< AWE::MediaServiceHandler*(*)>(_a[1]))); break;
        case 2: _t->wantsToOpenFolder((*reinterpret_cast< AWE::Folder*(*)>(_a[1]))); break;
        case 3: _t->wantsToScrapeForMetadata((*reinterpret_cast< AWE::MediaItem*(*)>(_a[1])),(*reinterpret_cast< AWE::MetadataScraperHandler*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->setItem((*reinterpret_cast< AWE::MediaItem*(*)>(_a[1]))); break;
        case 5: _t->respondToPlayButton(); break;
        case 6: _t->respondToOpenButton(); break;
        case 7: _t->respondToFolderOpen(); break;
        case 8: _t->respondToScrapeButton(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AWE::MediaPlayerHandler* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AWE::MediaServiceHandler* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AWE::Folder* >(); break;
            }
            break;
        case 3:
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
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AWE::MediaItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (InfoPane::*_t)(AWE::MediaFile * , AWE::MediaPlayerHandler * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InfoPane::wantsToOpenFile)) {
                *result = 0;
            }
        }
        {
            typedef void (InfoPane::*_t)(AWE::MediaServiceHandler * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InfoPane::wantsToOpenService)) {
                *result = 1;
            }
        }
        {
            typedef void (InfoPane::*_t)(AWE::Folder * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InfoPane::wantsToOpenFolder)) {
                *result = 2;
            }
        }
        {
            typedef void (InfoPane::*_t)(AWE::MediaItem * , AWE::MetadataScraperHandler * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InfoPane::wantsToScrapeForMetadata)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject UI::InfoPane::staticMetaObject = {
    { &Pane::staticMetaObject, qt_meta_stringdata_UI__InfoPane.data,
      qt_meta_data_UI__InfoPane,  qt_static_metacall, 0, 0}
};


const QMetaObject *UI::InfoPane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::InfoPane::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UI__InfoPane.stringdata))
        return static_cast<void*>(const_cast< InfoPane*>(this));
    return Pane::qt_metacast(_clname);
}

int UI::InfoPane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Pane::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void UI::InfoPane::wantsToOpenFile(AWE::MediaFile * _t1, AWE::MediaPlayerHandler * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UI::InfoPane::wantsToOpenService(AWE::MediaServiceHandler * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UI::InfoPane::wantsToOpenFolder(AWE::Folder * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UI::InfoPane::wantsToScrapeForMetadata(AWE::MediaItem * _t1, AWE::MetadataScraperHandler * _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
