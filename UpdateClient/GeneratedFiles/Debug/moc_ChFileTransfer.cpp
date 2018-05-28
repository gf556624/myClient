/****************************************************************************
** Meta object code from reading C++ file 'ChFileTransfer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ChFileTransfer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChFileTransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChFileTransfer_t {
    QByteArrayData data[11];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChFileTransfer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChFileTransfer_t qt_meta_stringdata_ChFileTransfer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ChFileTransfer"
QT_MOC_LITERAL(1, 15, 17), // "sigUpdateProgress"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "bytes"
QT_MOC_LITERAL(4, 40, 10), // "sigMaxSize"
QT_MOC_LITERAL(5, 51, 7), // "maxSize"
QT_MOC_LITERAL(6, 59, 6), // "sigMsg"
QT_MOC_LITERAL(7, 66, 6), // "strMsg"
QT_MOC_LITERAL(8, 73, 12), // "sigConnected"
QT_MOC_LITERAL(9, 86, 18), // "slotUpdateProgress"
QT_MOC_LITERAL(10, 105, 16) // "slotDisconnected"

    },
    "ChFileTransfer\0sigUpdateProgress\0\0"
    "bytes\0sigMaxSize\0maxSize\0sigMsg\0strMsg\0"
    "sigConnected\0slotUpdateProgress\0"
    "slotDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChFileTransfer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       8,    0,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   54,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void,

       0        // eod
};

void ChFileTransfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChFileTransfer *_t = static_cast<ChFileTransfer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigUpdateProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: _t->sigMaxSize((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: _t->sigMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->sigConnected(); break;
        case 4: _t->slotUpdateProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->slotDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChFileTransfer::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChFileTransfer::sigUpdateProgress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ChFileTransfer::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChFileTransfer::sigMaxSize)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ChFileTransfer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChFileTransfer::sigMsg)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ChFileTransfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChFileTransfer::sigConnected)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ChFileTransfer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ChFileTransfer.data,
      qt_meta_data_ChFileTransfer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ChFileTransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChFileTransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ChFileTransfer.stringdata0))
        return static_cast<void*>(const_cast< ChFileTransfer*>(this));
    return QObject::qt_metacast(_clname);
}

int ChFileTransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ChFileTransfer::sigUpdateProgress(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChFileTransfer::sigMaxSize(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChFileTransfer::sigMsg(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChFileTransfer::sigConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
