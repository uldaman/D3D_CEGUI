/****************************************************************************
** Meta object code from reading C++ file 'qtserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTServer_t {
    QByteArrayData data[14];
    char stringdata[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTServer_t qt_meta_stringdata_QTServer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QTServer"
QT_MOC_LITERAL(1, 9, 15), // "SlotMessageRead"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "SlotClientClosed"
QT_MOC_LITERAL(4, 43, 14), // "SlotNewConnect"
QT_MOC_LITERAL(5, 58, 14), // "SlotAddAccount"
QT_MOC_LITERAL(6, 73, 13), // "SlotOptionSet"
QT_MOC_LITERAL(7, 87, 16), // "SlotStartNewGame"
QT_MOC_LITERAL(8, 104, 6), // "strAcc"
QT_MOC_LITERAL(9, 111, 6), // "strPsw"
QT_MOC_LITERAL(10, 118, 7), // "strArea"
QT_MOC_LITERAL(11, 126, 9), // "strServer"
QT_MOC_LITERAL(12, 136, 16), // "SlotInitGamePath"
QT_MOC_LITERAL(13, 153, 10) // "SlotAddAcc"

    },
    "QTServer\0SlotMessageRead\0\0SlotClientClosed\0"
    "SlotNewConnect\0SlotAddAccount\0"
    "SlotOptionSet\0SlotStartNewGame\0strAcc\0"
    "strPsw\0strArea\0strServer\0SlotInitGamePath\0"
    "SlotAddAcc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    4,   59,    2, 0x08 /* Private */,
      12,    0,   68,    2, 0x08 /* Private */,
      13,    4,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,   11,

       0        // eod
};

void QTServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTServer *_t = static_cast<QTServer *>(_o);
        switch (_id) {
        case 0: _t->SlotMessageRead(); break;
        case 1: _t->SlotClientClosed(); break;
        case 2: _t->SlotNewConnect(); break;
        case 3: _t->SlotAddAccount(); break;
        case 4: _t->SlotOptionSet(); break;
        case 5: _t->SlotStartNewGame((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 6: _t->SlotInitGamePath(); break;
        case 7: _t->SlotAddAcc((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject QTServer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QTServer.data,
      qt_meta_data_QTServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QTServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QTServer.stringdata))
        return static_cast<void*>(const_cast< QTServer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QTServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
