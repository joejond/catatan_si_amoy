#ifndef WATERFALL_H
#define WATERFALL_H

#include <QGLWidget>
#include <GL/glut.h>
#include <QTimer>

#include "libku/windowing/windowkan.h"
#include "libku/windowing/buat_filter.h"
#include <math.h>
#include "libku/fft/fourier.h"

#include "alokasi.h"

class WaterFall : public QGLWidget
{
public:
    WaterFall();
    ~WaterFall();

protected:
    void paintGL();
    virtual void resizeGL(int w, int h);

private:
    void drawBatas();
    void drawData();

    float set_max;
    bool perspective;
    float *data_wtf[20];

    float *data_spektrum;
    float *window_coef;
    float *hasil_windowing;
    float *fft_re_out;
    float *fft_im_out;
    float *fft_magt;
    float *avrg[4];

    int x;

    int spektrum_points;
    int jml_points;
    float f_stop;

public:
    QTimer tm_wtf;

    void update_wtf(float *mag, int point);
    void copy_image();

    void update_y_scale();
    void reset_data();
    void get_spektrum_param(int points, float fstop);
    void get_data_spektrum(float  *data_view);
    void hitung_coef_window();

    int tipe_window;
    int tipe_data;
    int tipe_sb_y_accel;
    int tipe_sb_y_velo;
    int tipe_sb_y_disp;
    float y_max;
    float y_conv;
    float acc_sens;

};

#endif // WATERFALL_H
