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
    char stringdata[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTServer_t qt_meta_stringdata_QTServer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QTServer"
QT_MOC_LITERAL(1, 9, 12), // "message_read"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "client_closed"
QT_MOC_LITERAL(4, 37, 11), // "new_connect"
QT_MOC_LITERAL(5, 49, 10), // "AddAccount"
QT_MOC_LITERAL(6, 60, 9), // "OptionSet"
QT_MOC_LITERAL(7, 70, 12), // "startNewGame"
QT_MOC_LITERAL(8, 83, 12), // "initGamePath"
QT_MOC_LITERAL(9, 96, 6), // "addAcc"
QT_MOC_LITERAL(10, 103, 6), // "strAcc"
QT_MOC_LITERAL(11, 110, 6), // "strPsw"
QT_MOC_LITERAL(12, 117, 7), // "strArea"
QT_MOC_LITERAL(13, 125, 9) // "strServer"

    },
    "QTServer\0message_read\0\0client_closed\0"
    "new_connect\0AddAccount\0OptionSet\0"
    "startNewGame\0initGamePath\0addAcc\0"
    "strAcc\0strPsw\0strArea\0strServer"
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
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    4,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   11,   12,   13,

       0        // eod
};

void QTServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTServer *_t = static_cast<QTServer *>(_o);
        switch (_id) {
        case 0: _t->message_read(); break;
        case 1: _t->client_closed(); break;
        case 2: _t->new_connect(); break;
        case 3: _t->AddAccount(); break;
        case 4: _t->OptionSet(); break;
        case 5: _t->startNewGame(); break;
        case 6: _t->initGamePath(); break;
        case 7: _t->addAcc((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
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
