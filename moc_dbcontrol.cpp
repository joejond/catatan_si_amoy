/****************************************************************************
** Meta object code from reading C++ file 'dbcontrol.h'
**
** Created: Thu Aug 29 12:14:25 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dbcontrol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DbControl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      32,   10,   10,   10, 0x05,
      44,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      59,   10,   10,   10, 0x08,
      89,   83,   10,   10, 0x08,
     122,   10,   10,   10, 0x08,
     146,   10,   10,   10, 0x08,
     170,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DbControl[] = {
    "DbControl\0\0buka_db_mainwindow()\0"
    "simpan_db()\0load_from_db()\0"
    "on_pb_open_db_clicked()\0index\0"
    "on_table_db_clicked(QModelIndex)\0"
    "on_pb_save_db_clicked()\0on_pb_load_db_clicked()\0"
    "on_pb_delete_record_clicked()\0"
};

const QMetaObject DbControl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DbControl,
      qt_meta_data_DbControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DbControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DbControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DbControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DbControl))
        return static_cast<void*>(const_cast< DbControl*>(this));
    return QWidget::qt_metacast(_clname);
}

int DbControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: buka_db_mainwindow(); break;
        case 1: simpan_db(); break;
        case 2: load_from_db(); break;
        case 3: on_pb_open_db_clicked(); break;
        case 4: on_table_db_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: on_pb_save_db_clicked(); break;
        case 6: on_pb_load_db_clicked(); break;
        case 7: on_pb_delete_record_clicked(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DbControl::buka_db_mainwindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DbControl::simpan_db()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void DbControl::load_from_db()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
