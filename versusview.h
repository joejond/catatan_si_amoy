#ifndef VERSUSVIEW_H
#define VERSUSVIEW_H

#include <QWidget>

#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QActionGroup>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

#include <QImage>

#include <math.h>

#include "waveformvs.h"

#include "libku/dsp/integrasi.h"
#include "libku/windowing/buat_filter.h"
#include "libku/dsp/window_filter.h"

#include <QSettings>
#include "lain.h"

#include "alokasi.h"

extern struct t_setting setting;

namespace Ui {
class VersusView;
}

class VersusView : public QWidget
{
    Q_OBJECT
    
public:
    explicit VersusView(QWidget *parent = 0);
    ~VersusView();

    void get_data_kanal1(float *data, int jml, int ms_data);
    void get_data_kanal2(float *data, int jml, int ms_data);
    void get_data_kanal3(float *data, int jml, int ms_data);
    void get_data_kanal4(float *data, int jml, int ms_data);
    
private:
    Ui::VersusView *ui;

    float *data_view1;
    float *data_view2;
    float *data_view3;
    float *data_view4;

    int kanal1_view_state;
    int kanal2_view_state;
    int kanal3_view_state;
    int kanal4_view_state;

    int jml_data_waveform;

    int i, x;

    int proses_state;
    int tipe_data;

    WaveformVS *wavevs;

    int tipe_spek;
    int tipe_accel;
    int tipe_velo;
    int tipe_disp;

    int jml_last_masuk;
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

    int marker_state;
    int marker_fasa_state;
    int auto_scale_Y_state;
    int marker_type;

    QAction *marker_on;
    QAction *marker_fasa_on;
    QAction *auto_scale_y;

    int timer_ms;
    QTimer *timer_proses;

    void read_setting();
    void hitung_param_view();
    void create_contextMenu();
    void update_setting();

    float acc_sens1;
    float acc_sens2;
    float acc_sens3;
    float acc_sens4;
    float conv;

    void remove_dc(float * data_kanal, int jml);
    void highpass_filter(float *data_kanal, int jml);
    void integral_wf(float *in, float *out, int jum, float s_rate);

    int window_type;
    float *window_coef;
    float faktor_filter;
    doubledd *filter_hp;
    int len_highpass;
    double *temp_filter;

    int ms_delay;
    int poin_delay_adc;
    int poin_delay_system;
    float *geser_delay1;
    float *geser_delay2;
    float *geser_delay3;
    float *geser_delay4;
    float *geser_system1;
    float *geser_system2;
    float *geser_system3;
    float *geser_system4;

public slots:
    void start_proses_view();
    void stop_proses_view();

private slots:
    //slot buat context menu
    void popMenu(const QPoint &pos);

    void view_copy_image_wave();
    void view_copy_data_wave();

    void auto_scale_Y_change();

    void proses_view();

    void on_check_kanal1_clicked();
    void on_check_kanal2_clicked();
    void on_check_kanal3_clicked();
    void on_check_kanal4_clicked();
    void on_cb_data_tipe_activated(const QString &arg1);
    void on_cb_sat_accel_activated(const QString &arg1);
    void on_cb_sat_velo_activated(const QString &arg1);
    void on_cb_sat_disp_activated(const QString &arg1);
    void on_cb_ymax_activated(const QString &arg1);
    void on_cb_sat_x_wave_activated(const QString &arg1);
    void on_cb_wave_length_activated(const QString &arg1);
    void on_cb_window_activated(const QString &arg1);
};

#endif // VERSUSVIEW_H
