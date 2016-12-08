/****************************************************************************
** Meta object code from reading C++ file 'kanalview.h'
**
** Created: Thu Aug 29 16:21:55 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kanalview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kanalview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_kanalView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   11,   10,   10, 0x08,
      31,   10,   10,   10, 0x08,
      41,   10,   10,   10, 0x08,
      64,   10,   10,   10, 0x08,
      86,   10,   10,   10, 0x08,
     109,   10,   10,   10, 0x08,
     131,   10,   10,   10, 0x08,
     153,   10,   10,   10, 0x08,
     175,   10,   10,   10, 0x08,
     192,   10,   10,   10, 0x08,
     208,   10,   10,   10, 0x08,
     229,   10,   10,   10, 0x08,
     250,   10,   10,   10, 0x08,
     272,   10,   10,   10, 0x08,
     291,  286,   10,   10, 0x08,
     323,  286,   10,   10, 0x08,
     358,  286,   10,   10, 0x08,
     393,  286,   10,   10, 0x08,
     427,  286,   10,   10, 0x08,
     461,  286,   10,   10, 0x08,
     495,  286,   10,   10, 0x08,
     531,  286,   10,   10, 0x08,
     567,  286,   10,   10, 0x08,
     597,  286,   10,   10, 0x08,
     634,  286,   10,   10, 0x08,
     669,  286,   10,   10, 0x08,
     703,  286,   10,   10, 0x08,
     738,   10,   10,   10, 0x0a,
     758,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_kanalView[] = {
    "kanalView\0\0pos\0popMenu(QPoint)\0tim_wtf()\0"
    "view_copy_image_wave()\0view_copy_data_wave()\0"
    "view_copy_image_spek()\0view_copy_data_spek()\0"
    "view_copy_image_wtf()\0marker_state_change()\0"
    "marker_free_on()\0marker_max_on()\0"
    "marker_harmonic_on()\0marker_fasa_change()\0"
    "auto_scale_Y_change()\0proses_view()\0"
    "arg1\0on_cb_window_activated(QString)\0"
    "on_cb_data_tipe_activated(QString)\0"
    "on_cb_sat_accel_activated(QString)\0"
    "on_cb_sat_velo_activated(QString)\0"
    "on_cb_sat_disp_activated(QString)\0"
    "on_cb_averages_activated(QString)\0"
    "on_cb_sat_x_wave_activated(QString)\0"
    "on_cb_sat_x_spek_activated(QString)\0"
    "on_cb_ymax_activated(QString)\0"
    "on_cb_wave_length_activated(QString)\0"
    "on_cb_ymax_spek_activated(QString)\0"
    "on_cb_wtf_intv_activated(QString)\0"
    "on_cb_spek_tipe_activated(QString)\0"
    "start_proses_view()\0stop_proses_view()\0"
};

const QMetaObject kanalView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_kanalView,
      qt_meta_data_kanalView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &kanalView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *kanalView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *kanalView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_kanalView))
        return static_cast<void*>(const_cast< kanalView*>(this));
    return QWidget::qt_metacast(_clname);
}

int kanalView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: popMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: tim_wtf(); break;
        case 2: view_copy_image_wave(); break;
        case 3: view_copy_data_wave(); break;
        case 4: view_copy_image_spek(); break;
        case 5: view_copy_data_spek(); break;
        case 6: view_copy_image_wtf(); break;
        case 7: marker_state_change(); break;
        case 8: marker_free_on(); break;
        case 9: marker_max_on(); break;
        case 10: marker_harmonic_on(); break;
        case 11: marker_fasa_change(); break;
        case 12: auto_scale_Y_change(); break;
        case 13: proses_view(); break;
        case 14: on_cb_window_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: on_cb_data_tipe_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: on_cb_sat_accel_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: on_cb_sat_velo_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: on_cb_sat_disp_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: on_cb_averages_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: on_cb_sat_x_wave_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: on_cb_sat_x_spek_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: on_cb_ymax_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: on_cb_wave_length_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: on_cb_ymax_spek_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: on_cb_wtf_intv_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: on_cb_spek_tipe_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: start_proses_view(); break;
        case 28: stop_proses_view(); break;
        default: ;
        }
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
