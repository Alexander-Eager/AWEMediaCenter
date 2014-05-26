/****************************************************************************
** Meta object code from reading C++ file 'MediaPlayerHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "player/MediaPlayerHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaPlayerHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AWE__MediaPlayerHandler_t {
    QByteArrayData data[10];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AWE__MediaPlayerHandler_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AWE__MediaPlayerHandler_t qt_meta_stringdata_AWE__MediaPlayerHandler = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 6),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 10),
QT_MOC_LITERAL(4, 43, 4),
QT_MOC_LITERAL(5, 48, 14),
QT_MOC_LITERAL(6, 63, 4),
QT_MOC_LITERAL(7, 68, 5),
QT_MOC_LITERAL(8, 74, 15),
QT_MOC_LITERAL(9, 90, 16)
    },
    "AWE::MediaPlayerHandler\0closed\0\0"
    "MediaFile*\0file\0startedPlaying\0play\0"
    "close\0respondToClosed\0respondToPlaying\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AWE__MediaPlayerHandler[] = {

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
       1,    0,   69,    2, 0x06,
       1,    1,   70,    2, 0x06,
       5,    0,   73,    2, 0x06,
       5,    1,   74,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    1,   77,    2, 0x0a,
       7,    0,   80,    2, 0x0a,
       7,    1,   81,    2, 0x0a,
       8,    0,   84,    2, 0x08,
       8,    1,   85,    2, 0x08,
       9,    0,   88,    2, 0x08,
       9,    1,   89,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 3,    4,
    QMetaType::Bool,
    QMetaType::Bool, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void AWE::MediaPlayerHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MediaPlayerHandler *_t = static_cast<MediaPlayerHandler *>(_o);
        switch (_id) {
        case 0: _t->closed(); break;
        case 1: _t->closed((*reinterpret_cast< MediaFile*(*)>(_a[1]))); break;
        case 2: _t->startedPlaying(); break;
        case 3: _t->startedPlaying((*reinterpret_cast< MediaFile*(*)>(_a[1]))); break;
        case 4: { bool _r = _t->play((*reinterpret_cast< MediaFile*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->close();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->close((*reinterpret_cast< MediaFile*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->respondToClosed(); break;
        case 8: _t->respondToClosed((*reinterpret_cast< MediaFile*(*)>(_a[1]))); break;
        case 9: _t->respondToPlaying(); break;
        case 10: _t->respondToPlaying((*reinterpret_cast< MediaFile*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MediaPlayerHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayerHandler::closed)) {
                *result = 0;
            }
        }
        {
            typedef void (MediaPlayerHandler::*_t)(MediaFile * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayerHandler::closed)) {
                *result = 1;
            }
        }
        {
            typedef void (MediaPlayerHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayerHandler::startedPlaying)) {
                *result = 2;
            }
        }
        {
            typedef void (MediaPlayerHandler::*_t)(MediaFile * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayerHandler::startedPlaying)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject AWE::MediaPlayerHandler::staticMetaObject = {
    { &MetadataHolder::staticMetaObject, qt_meta_stringdata_AWE__MediaPlayerHandler.data,
      qt_meta_data_AWE__MediaPlayerHandler,  qt_static_metacall, 0, 0}
};


const QMetaObject *AWE::MediaPlayerHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AWE::MediaPlayerHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AWE__MediaPlayerHandler.stringdata))
        return static_cast<void*>(const_cast< MediaPlayerHandler*>(this));
    return MetadataHolder::qt_metacast(_clname);
}

int AWE::MediaPlayerHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MetadataHolder::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void AWE::MediaPlayerHandler::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AWE::MediaPlayerHandler::closed(MediaFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AWE::MediaPlayerHandler::startedPlaying()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void AWE::MediaPlayerHandler::startedPlaying(MediaFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
