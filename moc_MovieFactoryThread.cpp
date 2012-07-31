/****************************************************************************
** Meta object code from reading C++ file 'MovieFactoryThread.h'
**
** Created: Tue Jul 31 11:13:13 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MovieFactoryThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MovieFactoryThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MovieFactoryThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   41,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MovieFactoryThread[] = {
    "MovieFactoryThread\0\0movieCreated(Movie*)\0"
    "movie\0acceptMovie(Movie*)\0"
};

void MovieFactoryThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MovieFactoryThread *_t = static_cast<MovieFactoryThread *>(_o);
        switch (_id) {
        case 0: _t->movieCreated((*reinterpret_cast< Movie*(*)>(_a[1]))); break;
        case 1: _t->acceptMovie((*reinterpret_cast< Movie*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MovieFactoryThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MovieFactoryThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MovieFactoryThread,
      qt_meta_data_MovieFactoryThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MovieFactoryThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MovieFactoryThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MovieFactoryThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MovieFactoryThread))
        return static_cast<void*>(const_cast< MovieFactoryThread*>(this));
    return QThread::qt_metacast(_clname);
}

int MovieFactoryThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MovieFactoryThread::movieCreated(Movie * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
