/****************************************************************************
** Meta object code from reading C++ file 'motorcontrol.h'
**
** Created: Thu Aug 29 12:14:26 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "motorcontrol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'motorcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MotorControl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x08,
      36,   13,   13,   13, 0x08,
      58,   50,   13,   13, 0x08,
      92,   13,   13,   13, 0x08,
     117,   13,   13,   13, 0x08,
     143,   13,   13,   13, 0x08,
     171,   13,   13,   13, 0x08,
     203,  198,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MotorControl[] = {
    "MotorControl\0\0j\0set_serialport(int)\0"
    "ResetStatus()\0checked\0"
    "on_chk_motor_enable_clicked(bool)\0"
    "on_rb_motor_fw_clicked()\0"
    "on_rb_motor_rev_clicked()\0"
    "on_pb_motor_start_clicked()\0"
    "on_pb_motor_stop_clicked()\0arg1\0"
    "on_comboBox_activated(QString)\0"
};

const QMetaObject MotorControl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MotorControl,
      qt_meta_data_MotorControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MotorControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MotorControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MotorControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MotorControl))
        return static_cast<void*>(const_cast< MotorControl*>(this));
    return QWidget::qt_metacast(_clname);
}

int MotorControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: set_serialport((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: ResetStatus(); break;
        case 2: on_chk_motor_enable_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_rb_motor_fw_clicked(); break;
        case 4: on_rb_motor_rev_clicked(); break;
        case 5: on_pb_motor_start_clicked(); break;
        case 6: on_pb_motor_stop_clicked(); break;
        case 7: on_comboBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
