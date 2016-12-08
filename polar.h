#ifndef POLAR_H
#define POLAR_H

#include <QGLWidget>

#include <QPixmap>
#include <QClipboard>
#include <QApplication>

#include "alokasi.h"

#include "libku/dsp/itung_rms.h"

class Polar : public QGLWidget
{
public:
    Polar();
    ~Polar();

    void get_polar_param(int points, int lenght);
    void get_data_polar(float  *data_view, int points);
    void reset_data();
    void update_scale();
    int tipe_data;
    int tipe_sb_accel;
    int tipe_sb_velo;
    int tipe_sb_disp;
    int fasa_enable;
    int marker_fasa_state;
    float acc_sens;

    int color_state;
    int auto_y;

    float y_max;
    float y_conv;

    void copy_image();
    void copy_data();

protected:
    virtual void resizeGL(int w, int h);
    void paintGL();

private:
    int polar_points;
    int polar_ms;
    int x;
    int max_idx;

    int idx_max;
    int idx_min;
    float data_max;
    float data_min;
    float x_val;
    float range_val;
    float x_polar;
    float y_polar;

    float *data_polar;

    void drawBatas();
    void drawData();
    void drawGrid();

    QFont *ft1;
    
signals:
    
public slots:
    
};

#endif // POLAR_H
