/****************************************************************************
** Meta object code from reading C++ file 'SetupDialog.h'
**
** Created: Tue Jul 31 11:13:11 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SetupDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SetupDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SetupDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      41,   31,   12,   12, 0x0a,
      77,   68,   12,   12, 0x0a,
     100,   68,   12,   12, 0x0a,
     130,   68,   12,   12, 0x0a,
     160,   68,   12,   12, 0x0a,
     191,   68,   12,   12, 0x0a,
     222,   12,   12,   12, 0x0a,
     227,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SetupDialog[] = {
    "SetupDialog\0\0selectDirectory()\0directory\0"
    "directorySelected(QString)\0newValue\0"
    "movieWidthChanged(int)\0"
    "movieFieldHMarginChanged(int)\0"
    "movieFieldVMarginChanged(int)\0"
    "movieFieldHPaddingChanged(int)\0"
    "movieFieldVPaddingChanged(int)\0ok()\0"
    "okAndRun()\0"
};

void SetupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SetupDialog *_t = static_cast<SetupDialog *>(_o);
        switch (_id) {
        case 0: _t->selectDirectory(); break;
        case 1: _t->directorySelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->movieWidthChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->movieFieldHMarginChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->movieFieldVMarginChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->movieFieldHPaddingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->movieFieldVPaddingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->ok(); break;
        case 8: _t->okAndRun(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SetupDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SetupDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetupDialog,
      qt_meta_data_SetupDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SetupDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SetupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SetupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetupDialog))
        return static_cast<void*>(const_cast< SetupDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
