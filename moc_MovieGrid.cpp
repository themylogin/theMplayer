/****************************************************************************
** Meta object code from reading C++ file 'MovieGrid.h'
**
** Created: Tue Jul 31 11:13:12 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MovieGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MovieGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MovieGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x0a,
      41,   34,   10,   10, 0x0a,
      56,   10,   10,   10, 0x0a,
      72,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MovieGrid[] = {
    "MovieGrid\0\0movie\0addMovie(Movie*)\0"
    "socket\0lircEvent(int)\0scrollForward()\0"
    "scrollBackward()\0"
};

void MovieGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MovieGrid *_t = static_cast<MovieGrid *>(_o);
        switch (_id) {
        case 0: _t->addMovie((*reinterpret_cast< Movie*(*)>(_a[1]))); break;
        case 1: _t->lircEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->scrollForward(); break;
        case 3: _t->scrollBackward(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MovieGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MovieGrid::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MovieGrid,
      qt_meta_data_MovieGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MovieGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MovieGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MovieGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MovieGrid))
        return static_cast<void*>(const_cast< MovieGrid*>(this));
    if (!strcmp(_clname, "AbstractMovieGrid"))
        return static_cast< AbstractMovieGrid*>(const_cast< MovieGrid*>(this));
    return QWidget::qt_metacast(_clname);
}

int MovieGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
