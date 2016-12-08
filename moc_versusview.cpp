/****************************************************************************
** Meta object code from reading C++ file 'versusview.h'
**
** Created: Thu Aug 29 16:21:56 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "versusview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'versusview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VersusView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      32,   11,   11,   11, 0x0a,
      55,   51,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      94,   11,   11,   11, 0x08,
     116,   11,   11,   11, 0x08,
     138,   11,   11,   11, 0x08,
     152,   11,   11,   11, 0x08,
     178,   11,   11,   11, 0x08,
     204,   11,   11,   11, 0x08,
     230,   11,   11,   11, 0x08,
     261,  256,   11,   11, 0x08,
     296,  256,   11,   11, 0x08,
     331,  256,   11,   11, 0x08,
     365,  256,   11,   11, 0x08,
     399,  256,   11,   11, 0x08,
     429,  256,   11,   11, 0x08,
     465,  256,   11,   11, 0x08,
     502,  256,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VersusView[] = {
    "VersusView\0\0start_proses_view()\0"
    "stop_proses_view()\0pos\0popMenu(QPoint)\0"
    "view_copy_image_wave()\0view_copy_data_wave()\0"
    "auto_scale_Y_change()\0proses_view()\0"
    "on_check_kanal1_clicked()\0"
    "on_check_kanal2_clicked()\0"
    "on_check_kanal3_clicked()\0"
    "on_check_kanal4_clicked()\0arg1\0"
    "on_cb_data_tipe_activated(QString)\0"
    "on_cb_sat_accel_activated(QString)\0"
    "on_cb_sat_velo_activated(QString)\0"
    "on_cb_sat_disp_activated(QString)\0"
    "on_cb_ymax_activated(QString)\0"
    "on_cb_sat_x_wave_activated(QString)\0"
    "on_cb_wave_length_activated(QString)\0"
    "on_cb_window_activated(QString)\0"
};

const QMetaObject VersusView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VersusView,
      qt_meta_data_VersusView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VersusView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VersusView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VersusView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VersusView))
        return static_cast<void*>(const_cast< VersusView*>(this));
    return QWidget::qt_metacast(_clname);
}

int VersusView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start_proses_view(); break;
        case 1: stop_proses_view(); break;
        case 2: popMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: view_copy_image_wave(); break;
        case 4: view_copy_data_wave(); break;
        case 5: auto_scale_Y_change(); break;
        case 6: proses_view(); break;
        case 7: on_check_kanal1_clicked(); break;
        case 8: on_check_kanal2_clicked(); break;
        case 9: on_check_kanal3_clicked(); break;
        case 10: on_check_kanal4_clicked(); break;
        case 11: on_cb_data_tipe_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: on_cb_sat_accel_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: on_cb_sat_velo_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: on_cb_sat_disp_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: on_cb_ymax_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: on_cb_sat_x_wave_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: on_cb_wave_length_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: on_cb_window_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
