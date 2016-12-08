/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Aug 29 16:21:54 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      31,   11,   11,   11, 0x05,
      49,   11,   11,   11, 0x05,
      69,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      88,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     176,   11,   11,   11, 0x08,
     211,   11,   11,   11, 0x08,
     247,   11,   11,   11, 0x08,
     257,   11,   11,   11, 0x08,
     270,   11,   11,   11, 0x08,
     296,   11,   11,   11, 0x08,
     311,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,
     361,   11,   11,   11, 0x08,
     386,   11,   11,   11, 0x08,
     411,   11,   11,   11, 0x08,
     441,   11,   11,   11, 0x08,
     470,   11,   11,   11, 0x0a,
     480,   11,   11,   11, 0x0a,
     495,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0kanal_view_start()\0"
    "kanal_view_stop()\0versus_view_start()\0"
    "versus_view_stop()\0"
    "on_actionMode_Simulasi_triggered()\0"
    "on_actionStart_triggered()\0"
    "on_actionStop_triggered()\0"
    "on_actionSetting_Motor_triggered()\0"
    "on_actionModul_Akuisisi_triggered()\0"
    "ada_udp()\0tim_update()\0on_actionExit_triggered()\0"
    "decode_kanal()\0on_actionCH1_triggered()\0"
    "on_actionCH2_triggered()\0"
    "on_actionCH3_triggered()\0"
    "on_actionCH4_triggered()\0"
    "on_actionDatabase_triggered()\0"
    "on_actionCOMPARE_triggered()\0open_db()\0"
    "start_simpan()\0load_db()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: kanal_view_start(); break;
        case 1: kanal_view_stop(); break;
        case 2: versus_view_start(); break;
        case 3: versus_view_stop(); break;
        case 4: on_actionMode_Simulasi_triggered(); break;
        case 5: on_actionStart_triggered(); break;
        case 6: on_actionStop_triggered(); break;
        case 7: on_actionSetting_Motor_triggered(); break;
        case 8: on_actionModul_Akuisisi_triggered(); break;
        case 9: ada_udp(); break;
        case 10: tim_update(); break;
        case 11: on_actionExit_triggered(); break;
        case 12: decode_kanal(); break;
        case 13: on_actionCH1_triggered(); break;
        case 14: on_actionCH2_triggered(); break;
        case 15: on_actionCH3_triggered(); break;
        case 16: on_actionCH4_triggered(); break;
        case 17: on_actionDatabase_triggered(); break;
        case 18: on_actionCOMPARE_triggered(); break;
        case 19: open_db(); break;
        case 20: start_simpan(); break;
        case 21: load_db(); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::kanal_view_start()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::kanal_view_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::versus_view_start()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::versus_view_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
