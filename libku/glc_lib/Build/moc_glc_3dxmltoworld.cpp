/****************************************************************************
** Meta object code from reading C++ file 'glc_3dxmltoworld.h'
**
** Created: Mon Feb 25 13:38:13 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../io/glc_3dxmltoworld.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glc_3dxmltoworld.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLC_3dxmlToWorld[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GLC_3dxmlToWorld[] = {
    "GLC_3dxmlToWorld\0\0currentQuantum(int)\0"
};

void GLC_3dxmlToWorld::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLC_3dxmlToWorld *_t = static_cast<GLC_3dxmlToWorld *>(_o);
        switch (_id) {
        case 0: _t->currentQuantum((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GLC_3dxmlToWorld::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GLC_3dxmlToWorld::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GLC_3dxmlToWorld,
      qt_meta_data_GLC_3dxmlToWorld, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLC_3dxmlToWorld::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLC_3dxmlToWorld::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLC_3dxmlToWorld::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLC_3dxmlToWorld))
        return static_cast<void*>(const_cast< GLC_3dxmlToWorld*>(this));
    return QObject::qt_metacast(_clname);
}

int GLC_3dxmlToWorld::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void GLC_3dxmlToWorld::currentQuantum(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
