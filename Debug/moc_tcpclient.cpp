/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../core/port/tcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CTcpClient_t {
    QByteArrayData data[18];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CTcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CTcpClient_t qt_meta_stringdata_CTcpClient = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CTcpClient"
QT_MOC_LITERAL(1, 11, 12), // "sigDataReady"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "sigWrite"
QT_MOC_LITERAL(4, 34, 11), // "const char*"
QT_MOC_LITERAL(5, 46, 9), // "sigSetCOM"
QT_MOC_LITERAL(6, 56, 8), // "sigClose"
QT_MOC_LITERAL(7, 65, 8), // "sigClear"
QT_MOC_LITERAL(8, 74, 13), // "slotDataReady"
QT_MOC_LITERAL(9, 88, 9), // "slotWrite"
QT_MOC_LITERAL(10, 98, 3), // "pch"
QT_MOC_LITERAL(11, 102, 10), // "slotSetCOM"
QT_MOC_LITERAL(12, 113, 6), // "strCOM"
QT_MOC_LITERAL(13, 120, 5), // "iPort"
QT_MOC_LITERAL(14, 126, 9), // "slotClose"
QT_MOC_LITERAL(15, 136, 9), // "slotClear"
QT_MOC_LITERAL(16, 146, 12), // "displayError"
QT_MOC_LITERAL(17, 159, 28) // "QAbstractSocket::SocketError"

    },
    "CTcpClient\0sigDataReady\0\0sigWrite\0"
    "const char*\0sigSetCOM\0sigClose\0sigClear\0"
    "slotDataReady\0slotWrite\0pch\0slotSetCOM\0"
    "strCOM\0iPort\0slotClose\0slotClear\0"
    "displayError\0QAbstractSocket::SocketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    2,   72,    2, 0x06 /* Public */,
       5,    2,   77,    2, 0x06 /* Public */,
       6,    0,   82,    2, 0x06 /* Public */,
       7,    0,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   84,    2, 0x08 /* Private */,
       9,    2,   85,    2, 0x08 /* Private */,
      11,    2,   90,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,
      15,    0,   96,    2, 0x08 /* Private */,
      16,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::LongLong,   10,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,    2,

       0        // eod
};

void CTcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CTcpClient *_t = static_cast<CTcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigDataReady((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->sigWrite((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->sigSetCOM((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->sigClose(); break;
        case 4: _t->sigClear(); break;
        case 5: _t->slotDataReady(); break;
        case 6: _t->slotWrite((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->slotSetCOM((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 8: _t->slotClose(); break;
        case 9: _t->slotClear(); break;
        case 10: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CTcpClient::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CTcpClient::sigDataReady)) {
                *result = 0;
            }
        }
        {
            typedef void (CTcpClient::*_t)(const char * , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CTcpClient::sigWrite)) {
                *result = 1;
            }
        }
        {
            typedef void (CTcpClient::*_t)(const QString , const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CTcpClient::sigSetCOM)) {
                *result = 2;
            }
        }
        {
            typedef void (CTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CTcpClient::sigClose)) {
                *result = 3;
            }
        }
        {
            typedef void (CTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CTcpClient::sigClear)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject CTcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CTcpClient.data,
      qt_meta_data_CTcpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CTcpClient.stringdata0))
        return static_cast<void*>(const_cast< CTcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int CTcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void CTcpClient::sigDataReady(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CTcpClient::sigWrite(const char * _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CTcpClient::sigSetCOM(const QString _t1, const int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CTcpClient::sigClose()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void CTcpClient::sigClear()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
