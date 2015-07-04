/****************************************************************************
** Meta object code from reading C++ file 'ceguiinject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ceguiinject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ceguiinject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CeguiInject_t {
    QByteArrayData data[8];
    char stringdata[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CeguiInject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CeguiInject_t qt_meta_stringdata_CeguiInject = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CeguiInject"
QT_MOC_LITERAL(1, 12, 7), // "runGame"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "selectPath"
QT_MOC_LITERAL(4, 32, 10), // "installDll"
QT_MOC_LITERAL(5, 43, 7), // "OpenVip"
QT_MOC_LITERAL(6, 51, 10), // "receiveVip"
QT_MOC_LITERAL(7, 62, 7) // "strCard"

    },
    "CeguiInject\0runGame\0\0selectPath\0"
    "installDll\0OpenVip\0receiveVip\0strCard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CeguiInject[] = {

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
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    1,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void CeguiInject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CeguiInject *_t = static_cast<CeguiInject *>(_o);
        switch (_id) {
        case 0: _t->runGame(); break;
        case 1: _t->selectPath(); break;
        case 2: _t->installDll(); break;
        case 3: _t->OpenVip(); break;
        case 4: _t->receiveVip((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CeguiInject::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CeguiInject.data,
      qt_meta_data_CeguiInject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CeguiInject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CeguiInject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CeguiInject.stringdata))
        return static_cast<void*>(const_cast< CeguiInject*>(this));
    return QWidget::qt_metacast(_clname);
}

int CeguiInject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
