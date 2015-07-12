/****************************************************************************
** Meta object code from reading C++ file 'cmytablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cmytablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmytablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CMyTableWidget_t {
    QByteArrayData data[19];
    char stringdata[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMyTableWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMyTableWidget_t qt_meta_stringdata_CMyTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CMyTableWidget"
QT_MOC_LITERAL(1, 15, 18), // "SignalStartNewGame"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "nRow"
QT_MOC_LITERAL(4, 40, 16), // "SignalStopScript"
QT_MOC_LITERAL(5, 57, 17), // "SignalStartScript"
QT_MOC_LITERAL(6, 75, 16), // "SignalSendAddAcc"
QT_MOC_LITERAL(7, 92, 6), // "strAcc"
QT_MOC_LITERAL(8, 99, 6), // "strPsw"
QT_MOC_LITERAL(9, 106, 7), // "strArea"
QT_MOC_LITERAL(10, 114, 9), // "strServer"
QT_MOC_LITERAL(11, 124, 9), // "strScript"
QT_MOC_LITERAL(12, 134, 14), // "SlotAddAccount"
QT_MOC_LITERAL(13, 149, 13), // "SlotStartGame"
QT_MOC_LITERAL(14, 163, 17), // "SlotChangeAccount"
QT_MOC_LITERAL(15, 181, 14), // "SlotStopScript"
QT_MOC_LITERAL(16, 196, 15), // "SlotStartScript"
QT_MOC_LITERAL(17, 212, 13), // "SlotChangeAcc"
QT_MOC_LITERAL(18, 226, 10) // "SlotAddAcc"

    },
    "CMyTableWidget\0SignalStartNewGame\0\0"
    "nRow\0SignalStopScript\0SignalStartScript\0"
    "SignalSendAddAcc\0strAcc\0strPsw\0strArea\0"
    "strServer\0strScript\0SlotAddAccount\0"
    "SlotStartGame\0SlotChangeAccount\0"
    "SlotStopScript\0SlotStartScript\0"
    "SlotChangeAcc\0SlotAddAcc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMyTableWidget[] = {

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
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       5,    1,   75,    2, 0x06 /* Public */,
       6,    5,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,
      17,    5,   94,    2, 0x08 /* Private */,
      18,    5,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,   10,   11,

       0        // eod
};

void CMyTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CMyTableWidget *_t = static_cast<CMyTableWidget *>(_o);
        switch (_id) {
        case 0: _t->SignalStartNewGame((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->SignalStopScript((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->SignalStartScript((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->SignalSendAddAcc((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 4: _t->SlotAddAccount(); break;
        case 5: _t->SlotStartGame(); break;
        case 6: _t->SlotChangeAccount(); break;
        case 7: _t->SlotStopScript(); break;
        case 8: _t->SlotStartScript(); break;
        case 9: _t->SlotChangeAcc((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 10: _t->SlotAddAcc((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CMyTableWidget::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CMyTableWidget::SignalStartNewGame)) {
                *result = 0;
            }
        }
        {
            typedef void (CMyTableWidget::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CMyTableWidget::SignalStopScript)) {
                *result = 1;
            }
        }
        {
            typedef void (CMyTableWidget::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CMyTableWidget::SignalStartScript)) {
                *result = 2;
            }
        }
        {
            typedef void (CMyTableWidget::*_t)(const QString & , const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CMyTableWidget::SignalSendAddAcc)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject CMyTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_CMyTableWidget.data,
      qt_meta_data_CMyTableWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CMyTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMyTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CMyTableWidget.stringdata))
        return static_cast<void*>(const_cast< CMyTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int CMyTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
void CMyTableWidget::SignalStartNewGame(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CMyTableWidget::SignalStopScript(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CMyTableWidget::SignalStartScript(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CMyTableWidget::SignalSendAddAcc(const QString & _t1, const QString & _t2, const QString & _t3, const QString & _t4, const QString & _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
