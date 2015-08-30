/****************************************************************************
** Meta object code from reading C++ file 'udpsend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../soccerBotSoftware/udpsend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpsend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UdpSend_t {
    QByteArrayData data[6];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpSend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpSend_t qt_meta_stringdata_UdpSend = {
    {
QT_MOC_LITERAL(0, 0, 7), // "UdpSend"
QT_MOC_LITERAL(1, 8, 8), // "sendVals"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 4), // "data"
QT_MOC_LITERAL(4, 23, 12), // "QHostAddress"
QT_MOC_LITERAL(5, 36, 4) // "host"

    },
    "UdpSend\0sendVals\0\0data\0QHostAddress\0"
    "host"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpSend[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

       0        // eod
};

void UdpSend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UdpSend *_t = static_cast<UdpSend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendVals((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject UdpSend::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpSend.data,
      qt_meta_data_UdpSend,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UdpSend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpSend::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UdpSend.stringdata0))
        return static_cast<void*>(const_cast< UdpSend*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpSend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
