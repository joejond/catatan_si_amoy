#ifndef WAVEFORM_H
#define WAVEFORM_H

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

class Waveform : public QGLWidget
{
public:
    Waveform();
    ~Waveform();

protected:
    virtual void resizeGL(int w, int h);
    void paintGL();

private:
    void read_setting();
    void drawBatas();
    void drawData();
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
    float *data_waveform;
    float data_plot;

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
    void get_data_waveform(float  *data_view, int points, int length);
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

    int waveform_points;
    int poin_tampil;
    int waveform_ms;
    float persen_tampil;

    int color_state;
    int auto_y;

    float y_max;
    float y_conv;

    void copy_image();
    void copy_data();
};

#endif // WAVEFORM_H
