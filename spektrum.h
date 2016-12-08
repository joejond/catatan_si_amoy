#ifndef SPEKTRUM_H
#define SPEKTRUM_H

#include <QObject>

#include <QGLWidget>
#include <GL/glut.h>
#include <QTimer>

#include <QPixmap>
#include <QClipboard>
#include <QApplication>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include "alokasi.h"

#include "libku/windowing/windowkan.h"
#include "libku/windowing/buat_filter.h"
#include <math.h>
#include "libku/fft/fourier.h"

#include <QSettings>
#include "lain.h"

extern struct t_setting setting;

class Spektrum : public QGLWidget
{
    Q_OBJECT
public:
    Spektrum();
    ~Spektrum();

protected:
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    QFont *ft1;

private:
    void read_setting();
    void drawBatas();
    void drawGrid();
    void drawData();
    void drawSatY(float min_val, float max_val, int step);
    void drawSatX(float min_val, float max_val, int step);
    void drawKursor();

    int x;

    bool perspective;
    float x_kursor;
    float x_kursor_harmonic;
    float y_kursor;
    float x_kursor_max;
    float y_kursor_max;
    int idx_data_kursor;
    int idx_data_kursor_max;
    int spektrum_points;

    float *data_spektrum;
    float *window_coef;
    float *hasil_windowing;
    float *fft_re_out;
    float *fft_im_out;
    float *fft_magt;
    float *avrg[4];

    float data_plot;

    char val[10];
    char val_kursor[20];
    float nilai_y;
    float interv;
    float interv_y;

    float range;
    float int_val;

    float x_pos;
    float x_intv;

    float y_pos;
    float y_intv;

public:
    int tipe_window;
    int tipe_data;
    int tipe_sumbu_x;
    int tipe_sb_y_accel;
    int tipe_sb_y_velo;
    int tipe_sb_y_disp;
    int tampilkan_points;
    int num_avrg;

    float *hasil_avrg;

    int marker_state;
    int marker_type;
    float x_factor;
    float data_max;
    float range_val;

    void update_y_scale();
    void get_spektrum_param();
    void get_data_spektrum(float  *data_view);
    void hitung_coef_window();
    float y_max;
    float y_conv;
    float acc_sens;
    int auto_y;

    void reset_data();

protected:
    virtual void keyPressEvent ( QKeyEvent * e );
    virtual void mousePressEvent(QMouseEvent * event);

public:
    double rms;

public:
    void copy_image();
    void copy_data();

};

#endif // SPEKTRUM_H
