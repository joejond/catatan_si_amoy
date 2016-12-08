#ifndef WAVEFORMVS_H
#define WAVEFORMVS_H

#include <QGLWidget>
#include <GL/glut.h>

#include <QPixmap>
#include <QClipboard>
#include <QApplication>

#include "alokasi.h"

#include "libku/dsp/itung_rms.h"

#include <QSettings>
#include "lain.h"

extern struct t_setting setting;

class WaveformVS : public QGLWidget
{
public:
    WaveformVS();
    ~WaveformVS();

protected:
    virtual void resizeGL(int w, int h);
    void paintGL();

private:
    void read_setting();
    void drawBatas();
    void drawData(float *data_tampil, int kanal_id, int waveform_points, int poin_tampil);
    void drawGrid();

    void drawSatX(int step);
    void drawSatY(float min_val, float max_val, int step);

    void draw_marker_fasa();


    int x;

    int idx_max;
    int idx_min;
    float data_max;
    float data_min;

    bool perspective;
    float *data_waveform1;
    float *data_waveform2;
    float *data_waveform3;
    float *data_waveform4;

    char val_kursor[30];
    char val[30];
    char val_rms[30];
    char ptop[30];
    float interv;
    float intv_x;
    float interv_data;
    float x_val;

    float range;
    float range_val;
    float int_val;

    float x_pos;
    float x_intv;

    float y_kursor_max;
    int idx_data_kursor_max;
    float x_kursor_max;

    float y_pos;
    float y_intv;

    QFont *ft1;

public:
    void get_waveform_param(int points, int lenght);
    void get_data_waveform1(float  *data_view, int points, int length);
    void get_data_waveform2(float  *data_view, int points, int length);
    void get_data_waveform3(float  *data_view, int points, int length);
    void get_data_waveform4(float  *data_view, int points, int length);
    void reset_data();
    void update_y_scale();
    int tipe_data;
    int tipe_sumbu_x;
    int tipe_sb_y_accel;
    int tipe_sb_y_velo;
    int tipe_sb_y_disp;
    int fasa_enable;
    int marker_fasa_state;
    float acc_sens;

    int waveform_ms;
    int poin_tampil;
    int waveform_points;

    int waveform_points1;
    int waveform_points2;
    int waveform_points3;
    int waveform_points4;
    int waveform_ms1;
    int waveform_ms2;
    int waveform_ms3;
    int waveform_ms4;
    int poin_tampil1;
    int poin_tampil2;
    int poin_tampil3;
    int poin_tampil4;
    float persen_tampil;

    int wave1_state;
    int wave2_state;
    int wave3_state;
    int wave4_state;

    int color_state;
    int auto_y;

    float y_max;
    float y_conv;

    void copy_image();
    void copy_data();
};

#endif // WAVEFORMVS_H
