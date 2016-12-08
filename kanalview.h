#ifndef KANALVIEW_H
#define KANALVIEW_H

#include <QWidget>

#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QActionGroup>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

#include <math.h>
#include "waveform.h"
#include "polar.h"
#include "spektrum.h"
#include "waterfall.h"

#include "libku/dsp/integrasi.h"
#include "libku/dsp/window_filter.h"

#include <QSettings>
#include "lain.h"

#include "alokasi.h"


extern struct t_setting setting;

namespace Ui {
class kanalView;
}

class kanalView : public QWidget
{
    Q_OBJECT

public:
    explicit kanalView(QWidget *parent = 0);
    ~kanalView();

    int kanal_id;

private:
    Ui::kanalView *ui;

    int i, x;

    int proses_state;
    int tipe_data;
    int tipe_accel;
    int tipe_velo;
    int tipe_disp;

    Waveform *wave;
    Spektrum *spektrum;
    WaterFall *wtf;
    Polar *polar;

    int tipe_spek;

    int jml_last_masuk;
    int jml_data_waveform;
    //int jml_paket_kecil;
    int index_buffer;
    //int paket_min;
    int waveform_ms;
    float *data_integrasi1;
    float *data_integrasi2;

    // context menu
    QMenu *menuPop;

    QMenu *SubMenuCopy;
    QAction *menuCopyImageWave;
    QAction *menuCopyDataWave;
    QAction *menuCopyImageSpek;
    QAction *menuCopyDataSpek;
    QAction *menuCopyImageWtf;

    int marker_state;
    int marker_fasa_state;
    int auto_scale_Y_state;
    int marker_type;

    QAction *marker_on;
    QMenu *Sub_marker_type;
    QAction *marker_free;
    QAction *marker_max;
    QAction *marker_harmonic;
    QAction *marker_fasa_on;
    QAction *auto_scale_y;

    int timer_ms;
    int wtf_ms;
    QTimer *timer_proses;
    QTimer *timer_wtf;

    void read_setting();
    void hitung_param_view();
    void create_contextMenu();
    void update_setting();

    void remove_dc(float * data_kanal, int jml);
    void highpass_filter(float *data_kanal, int jml);
    void integral_wf(float *in, float *out, int jum, float s_rate);

    int window_type;
    float *window_coef;
    doubledd *filter_hp;
    int len_highpass;
    float faktor_filter;

    int ms_delay;
    int poin_delay_adc;
    int poin_delay_system;
    float *geser_delay;
    float *geser_system;

    float acc_sens;
    float conv;

public:
    void get_data_kanal(float *data, int jml, int ms_data);

    float *data_view;
    float *buffer;
    double *temp_filter;
    int last_index_dibaca;

    void reset_data();
    int color_state;

private slots:
    //slot buat context menu
    void popMenu(const QPoint &pos);

    void tim_wtf();

    void view_copy_image_wave();
    void view_copy_data_wave();
    void view_copy_image_spek();
    void view_copy_data_spek();
    void view_copy_image_wtf();

    void marker_state_change();
    void marker_free_on();
    void marker_max_on();
    void marker_harmonic_on();

    void marker_fasa_change();

    void auto_scale_Y_change();


    void proses_view();

    void on_cb_window_activated(const QString &arg1);
    void on_cb_data_tipe_activated(const QString &arg1);
    void on_cb_sat_accel_activated(const QString &arg1);
    void on_cb_sat_velo_activated(const QString &arg1);
    void on_cb_sat_disp_activated(const QString &arg1);
    void on_cb_averages_activated(const QString &arg1);
    void on_cb_sat_x_wave_activated(const QString &arg1);
    void on_cb_sat_x_spek_activated(const QString &arg1);
    void on_cb_ymax_activated(const QString &arg1);
    void on_cb_wave_length_activated(const QString &arg1);
    void on_cb_ymax_spek_activated(const QString &arg1);
    void on_cb_wtf_intv_activated(const QString &arg1);
    void on_cb_spek_tipe_activated(const QString &arg1);

public slots:
    void start_proses_view();
    void stop_proses_view();

};

#endif // KANALVIEW_H
