/****************************************************************************
** Meta object code from reading C++ file 'MediaPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "player/MediaPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AWE__MediaPlayer_t {
    QByteArrayData data[8];
    char stringdata[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AWE__MediaPlayer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AWE__MediaPlayer_t qt_meta_stringdata_AWE__MediaPlayer = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 6),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 10),
QT_MOC_LITERAL(4, 36, 4),
QT_MOC_LITERAL(5, 41, 14),
QT_MOC_LITERAL(6, 56, 4),
QT_MOC_LITERAL(7, 61, 5)
    },
    "AWE::MediaPlayer\0closed\0\0MediaFile*\0"
    "file\0startedPlaying\0play\0close\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AWE__MediaPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06,
       1,    1,   50,    2, 0x06,
       5,    0,   53,    2, 0x06,
       5,    1,   54,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    1,   57,    2, 0x0a,
       7,    0,   60,    2, 0x0a,
       7,    1,   61,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 3,    4,
    QMetaType::Bool,
    QMetaType::Bool, 0x80000000 | 3,    4,

       0        // eod
};

void AWE::MediaPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MediaPlayer *_t = static_cast<MediaPlayer *>(_o);
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
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MediaPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayer::closed)) {
                *result = 0;
            }
        }
        {
            typedef void (MediaPlayer::*_t)(MediaFile * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayer::closed)) {
                *result = 1;
            }
        }
        {
            typedef void (MediaPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayer::startedPlaying)) {
                *result = 2;
            }
        }
        {
            typedef void (MediaPlayer::*_t)(MediaFile * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MediaPlayer::startedPlaying)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject AWE::MediaPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AWE__MediaPlayer.data,
      qt_meta_data_AWE__MediaPlayer,  qt_static_metacall, 0, 0}
};


const QMetaObject *AWE::MediaPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AWE::MediaPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AWE__MediaPlayer.stringdata))
        return static_cast<void*>(const_cast< MediaPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int AWE::MediaPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void AWE::MediaPlayer::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AWE::MediaPlayer::closed(MediaFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AWE::MediaPlayer::startedPlaying()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void AWE::MediaPlayer::startedPlaying(MediaFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
