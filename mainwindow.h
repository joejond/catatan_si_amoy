#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QClipboard>
#include <QTimer>
#include <QWaitCondition>
#include <QPainter>
#include <QFrame>
#include <QSettings>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QToolBar>
#include <QSlider>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMdiSubWindow>
#include <stdio.h>

#include <QtDebug>

#include "stdio.h"
#include "stdlib.h"
#include "lain.h"

#include "math.h"
#include "float.h"

#include "modulsetting.h"
#include "signalgeneratorset.h"
#include "dbcontrol.h"
#include "motorcontrol.h"

//#include "db_utils.h"
#include "simpanthread.h"

#include "libku/fft/fourier.h"
#include "libku/dsp/integrasi.h"

#include "kanalview.h"
#include "versusview.h"

#include "alokasi.h"

struct tt_req {
        char head[10];			// getdata, ressend
        int  state;             // SUDAH_KONEK, SELESAI, ULANG
        int  urutan;			// urutan paket data
        //int  tipe_data;			// 10 : kanal_A1, 11 : kanal_B1,
        int  pos_data;
        int  total;				// total paket
        int  last_kanal;
        int  jum_sample;		/* jumlah sampel pressure */
        int  jum_paket;			/* tadinya jum_paket_p */
        int  kanal;				/* ditambahkan 6 sept 2012, nomer kanal sedang dikirim, mulai 1 */
        int  urut_kanal;        /* memudahkan manipulasi array */
        int  lost_paket;
        int  fase_enabled;
        int  flag;				/* 1 master, 2 slave */
        int  bat_level;			/* mulai 2 Des 2012 */
        int  arus_charge;
        int  buck_level;
        int	 	sampling_rate;		// real sampling rate modul
        float 	pecahan_waveform;	// pecahan waveform
        unsigned char buf[1024];
};

struct t_data_mobar {
    float data_P[ BESAR_DATA_RECIP ];
    float data_V[ BESAR_DATA_RECIP ];
    float data_deg[ BESAR_DATA_RECIP ]; /* dalam micro second */
    int  jum_P;
    int  jum_V;
    int  jum_deg;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionMode_Simulasi_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionSetting_Motor_triggered();
    void on_actionModul_Akuisisi_triggered();

    void ada_udp(void);
    void tim_update(void);

    void on_actionExit_triggered();

    void decode_kanal();

    void on_actionCH1_triggered();
    void on_actionCH2_triggered();
    void on_actionCH3_triggered();
    void on_actionCH4_triggered();

    void on_actionDatabase_triggered();

    void on_actionCOMPARE_triggered();

private:

    void read_setting();
    void write_setting();

private:
    Ui::MainWindow *ui;

    float *data_kanal[ LOGGER_KANAL ];

    int hit;

    int modul_state;

    QUdpSocket *udpSocket;

    QString host1;
    int port1;

    int count_udp_kirim;
    int valid_flag;
    int nomer_kirim;

    struct tt_req  req_g;   /* req global */
    struct tt_req  ulang_g;

    int paket_hilang[ 1000 ];
    int sedang_hilang;
    int jum_hilang;
    int count_gagal;
    int batas_gagal;
    int jum_kanal_aktif;

    int jum_buf;

    QTimer *tim;
    QTimer *tim_plot;

    int pos_big_dibaca;
    int tim_count;
    int tim_ulang;
    int ms_refresh;

    QString last_file_open;

    int belum_show;
    int count_udp;

    double *bandpass_koef;
    int M_bandpass;
    int count_data_big;


    //kanal view
    bool kanal_view_state[4];
    kanalView *kanal_view[4];

    //versus view
    bool versus_view_state;
    VersusView *versus_view;

    //modul setting
    bool set_modul_state;
    ModulSetting *set_modul;

    //signal generator setting
    bool set_siggen_state;
    SignalGeneratorSet *set_siggen;

    //motor control
    bool set_motor_state;
    MotorControl *set_motor;

    //database control
    bool db_ctl_state;
    DbControl *db_ctl;

    QSqlDatabase db;
    QSqlQuery query_w;

signals:
    void kanal_view_start();
    void kanal_view_stop();
    void versus_view_start();
    void versus_view_stop();

public slots:
    void open_db();
    void start_simpan();
    void load_db();
};

#endif // MAINWINDOW_H
