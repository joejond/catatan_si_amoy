/****************************************************************************
** Meta object code from reading C++ file 'modulsetting.h'
**
** Created: Thu Aug 29 12:14:25 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modulsetting.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulsetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModulSetting[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      52,   47,   13,   13, 0x08,
      93,   47,   13,   13, 0x08,
     134,   47,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ModulSetting[] = {
    "ModulSetting\0\0on_pb_update_set_modul_clicked()\0"
    "arg1\0on_cb_lines_currentIndexChanged(QString)\0"
    "on_cb_fstop_currentIndexChanged(QString)\0"
    "on_cb_fstart_activated(QString)\0"
};

const QMetaObject ModulSetting::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModulSetting,
      qt_meta_data_ModulSetting, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModulSetting::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModulSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModulSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModulSetting))
        return static_cast<void*>(const_cast< ModulSetting*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModulSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pb_update_set_modul_clicked(); break;
        case 1: on_cb_lines_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: on_cb_fstop_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: on_cb_fstart_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
