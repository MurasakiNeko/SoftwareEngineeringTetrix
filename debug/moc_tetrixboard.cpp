/****************************************************************************
** Meta object code from reading C++ file 'tetrixboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tetrixboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tetrixboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TetrixBoard_t {
    QByteArrayData data[9];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TetrixBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TetrixBoard_t qt_meta_stringdata_TetrixBoard = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TetrixBoard"
QT_MOC_LITERAL(1, 12, 12), // "scoreChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "score"
QT_MOC_LITERAL(4, 32, 12), // "levelChanged"
QT_MOC_LITERAL(5, 45, 5), // "level"
QT_MOC_LITERAL(6, 51, 19), // "linesRemovedChanged"
QT_MOC_LITERAL(7, 71, 8), // "numLines"
QT_MOC_LITERAL(8, 80, 15) // "sendBoardAction"

    },
    "TetrixBoard\0scoreChanged\0\0score\0"
    "levelChanged\0level\0linesRemovedChanged\0"
    "numLines\0sendBoardAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TetrixBoard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,
       8,    3,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,

       0        // eod
};

void TetrixBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TetrixBoard *_t = static_cast<TetrixBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scoreChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->levelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->linesRemovedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sendBoardAction((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TetrixBoard::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TetrixBoard::scoreChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TetrixBoard::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TetrixBoard::levelChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TetrixBoard::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TetrixBoard::linesRemovedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TetrixBoard::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TetrixBoard::sendBoardAction)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TetrixBoard::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_TetrixBoard.data,
      qt_meta_data_TetrixBoard,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TetrixBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TetrixBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TetrixBoard.stringdata0))
        return static_cast<void*>(const_cast< TetrixBoard*>(this));
    return QFrame::qt_metacast(_clname);
}

int TetrixBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TetrixBoard::scoreChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TetrixBoard::levelChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TetrixBoard::linesRemovedChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TetrixBoard::sendBoardAction(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
