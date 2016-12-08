#include "polar.h"
#include <math.h>
#include <QDebug>

Polar::Polar()
{
    tipe_data = 1;
    tipe_sb_accel = 1;
    tipe_sb_velo = 1;
    tipe_sb_disp = 1;
    polar_points = 256;
    polar_ms = 100;

    auto_y = 1;
    y_max = 100;
    y_conv = 0;


    data_polar = new float[BESAR_DATA_RECIP]();

    ft1 = new QFont("/usr/share/fonts/truetype/msttcorefonts/Verdana.ttf");
    ft1->setPixelSize(12);
}

Polar::~Polar()
{
    delete[] data_polar;
}

void Polar::paintGL()
{
    glClearColor(1.0f, 1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.3f, 1.3f, -1.3f, 1.3f, -1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
                0.0f, 0.0f, 20.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f
                );

    glTranslatef(-0.0f, -0.0f, -0.0f);

    drawBatas();
    drawGrid();
    drawData();
    glFlush();
}

void Polar::resizeGL(int w, int h)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport((w - h)/2, 0, h, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Polar::get_polar_param(int points, int lenght)
{
    polar_points = points;
}

void Polar::get_data_polar(float *data_view, int points)
{
    polar_points = points;
    memcpy(data_polar, data_view, BESAR_DATA_RECIP);
}

void Polar::reset_data()
{
    for (int y = 0; y<( BESAR_DATA_RECIP); y++)
        data_polar[y] = 0.00;
}

void Polar::update_scale()
{

}

void Polar::drawData()
{

    data_max = data_polar[0];
    for(x = 0; x < polar_points; x++)
    {
        if(data_polar[x] > data_max)
        {
            data_max = data_polar[x] ;
            max_idx = x;
        }
    }
    data_min = data_polar[0];
    for(x = 0; x < polar_points; x++)
    {
        if(data_polar[x]  < data_min)
        {
            data_min = data_polar[x] ;
        }
    }
    range_val = data_max - data_min;

    //gambar grafik

    glBegin(GL_LINE_LOOP);
    x_val = 0;

    for(x = 0; x < polar_points; x++)
    {
        glColor3f(0.0f, 0.39f, 0.0f);

        x_polar = ((data_polar[x] -  data_min)/range_val) * cosf(x_val);
        y_polar = ((data_polar[x] -  data_min)/range_val) * sinf(x_val);

        glVertex2f(x_polar, y_polar);
        x_val = x_val + (2 * M_PI / polar_points);
    }

    glEnd();

    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 0.0f, 0.0f);
    x_val = (2 * M_PI / polar_points) * max_idx;
    x_polar = ((data_polar[max_idx] -  data_min)/range_val) * cosf(x_val);
    y_polar = ((data_polar[max_idx] -  data_min)/range_val) * sinf(x_val);

    glVertex2f(0, 0);
    glVertex2f(x_polar, y_polar);


    glEnd();



}

void Polar::drawBatas()
{


    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();
}

void Polar::drawGrid()
{
    glColor3f(0.0f, 0.0f, 0.0f);

    glLineStipple(2, 0xAAAA);
    glEnable (GL_LINE_STIPPLE);

    glBegin(GL_LINE_LOOP);
    for(int i =0; i <= 300; i++){
    double angle = 2 * M_PI * i / 300;
    double x = cos(angle);
    double y = sin(angle);
    glVertex2d(x,y);
    }
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    renderText(1.02f, -0.03f, 0, "0", *ft1, 2000);
    renderText(-0.05f, 1.05f, 0, "90", *ft1, 2000);
    renderText(-1.25f, -0.03f, 0, "180", *ft1, 2000);
    renderText(-0.1f, -1.15f, 0, "270", *ft1, 2000);
}

void Polar::copy_data()
{

}

void Polar::copy_image()
{

}
