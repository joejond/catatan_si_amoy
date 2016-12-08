#include "waterfall.h"
#include <QDebug>

WaterFall::WaterFall()
{
    perspective = true;

    for(x = 0; x < 20; x++)
    {
        data_wtf[x] = new float[BESAR_DATA_RECIP]();
    }

    data_spektrum = new float[BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        data_spektrum[x] = 0.00;

    window_coef = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<( BESAR_DATA_RECIP); x++)
        window_coef[x] = 0.00;

    hasil_windowing  = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<( BESAR_DATA_RECIP); x++)
        hasil_windowing[x] = 0.00;

    fft_re_out = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<( BESAR_DATA_RECIP); x++)
        fft_re_out[x] = 0.00;

    fft_im_out = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<( BESAR_DATA_RECIP); x++)
        fft_im_out[x] = 0.00;

    fft_magt = new float[BESAR_DATA_RECIP]();
    for (x = 0; x<( BESAR_DATA_RECIP); x++)
        fft_magt[x] = 0.00;

    jml_points = 100;

    connect(&tm_wtf, SIGNAL(timeout()), this, SLOT(updateGL()));
}

WaterFall::~WaterFall()
{
    delete[] data_spektrum;
    delete[] window_coef;
    delete[] hasil_windowing;
    delete[] fft_re_out;
    delete[] fft_im_out;
    delete[] fft_magt;

    for(x = 0; x < 20; x++)
    {
        delete[] data_wtf[x];
    }
}

void WaterFall::update_y_scale()
{
    float conv =  4 * 1/y_max;

    if(tipe_data == 1)
    {
        if(tipe_sb_y_accel == 1)
        {
            y_conv = conv;
        }
        else if(tipe_sb_y_accel == 2)
        {
            y_conv = conv * 1000;
        }
    }

    if(tipe_data == 2)
    {
        if(tipe_sb_y_velo == 1)
        {
            y_conv = conv / acc_sens / 1000 * 60;
        }
        else if(tipe_sb_y_velo == 2)
        {
            y_conv = conv / acc_sens / 1000 * 60 / 2.54;
        }
    }

    if(tipe_data == 3)
    {
        if(tipe_sb_y_disp == 1)
        {
            y_conv = conv / acc_sens / 1000 * 60 * 60;
        }
        else if(tipe_sb_y_disp == 2)
        {
            y_conv = conv / acc_sens * 60 * 60;
        }
        else if(tipe_sb_y_disp == 3)
        {
            y_conv = conv / acc_sens / 1000 * 60 * 60 / 25.4;
        }
    }
}

void WaterFall::get_spektrum_param(int points, float fstop)
{
    spektrum_points = points;
    jml_points = spektrum_points / 2.56;
    f_stop = fstop;
}

void WaterFall::get_data_spektrum(float  *data_view)
{
    memcpy(data_spektrum, data_view, BESAR_DATA_RECIP);
}

void WaterFall::reset_data()
{

}

void WaterFall::hitung_coef_window()
{
    if(tipe_window == 1)
    {
        buat_hanning(window_coef, spektrum_points);
    }
    if(tipe_window == 2)
    {
        buat_rectangular(window_coef, spektrum_points);
    }
    if(tipe_window == 3)
    {
        buat_blackman(window_coef, spektrum_points);
    }
    if(tipe_window == 4)
    {
        buat_hamming(window_coef, spektrum_points);
    }
}

void WaterFall::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (perspective)
        gluPerspective(15.0f, 1.4f *((float)(this->width()) / (float)(this->height())), 1.0f, 500.0f);
    else
        glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 20.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
                0.0f, 0.0f, 5.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f
                );

    glRotatef( 15, 1.0f, 0.0f, 0.0f );
    glTranslatef(-0.0f, -0.0f, -0.0f);

    for(int x = 0; x < 20; x++)
    {
        for(int a = 0; a < jml_points; a++)
        {
            if(x > 0)
                data_wtf[x][a] = data_wtf[x-1][a];
        }
    }
    drawBatas();
    drawData();
    glFlush();
}

void WaterFall::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w*1.1f, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void WaterFall::update_wtf(float *mag, int point)
{
    jml_points = point;
    x = 19;
    for(int n = 0; n < 20; n++)
    {
        if(x > 0)
        {
            memcpy(data_wtf[x], data_wtf[x-1], BESAR_DATA_RECIP);
        }
        if(x == 0)
        {
            memcpy(data_wtf[0], mag, BESAR_DATA_RECIP);
        }
        x = x - 1;
    }
}

void WaterFall::drawData()
{
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

    for(int n = 0; n < 20; n++)
    {
        glBegin(GL_LINE_STRIP);
        float x_val = -1.0f;

        for(int x = 0; x < jml_points; x++)
        {
            if(data_wtf[n][x] < 0.1f)
                glColor3f(0.0f, 1.0f, 0.0f);
            else if(data_wtf[n][x] >= 0.1f && data_wtf[n][x] < 0.3f)
                glColor3f(1.0f, 1.0f, 0.0f);
            else if(data_wtf[n][x] >= 0.3f)
                glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(x_val, (data_wtf[n][x])*10, n*0.075f);
            x_val = x_val + (2.0f/jml_points);
        }
        glEnd();
    }
}

void WaterFall::drawBatas()
{
    char *p = "25.47Hz";
    glPushMatrix();
    glTranslatef(0, 0, 1.05f);
    //glRasterPos3f(0, 0, 1.05f);

    glScalef(0.0003, 0.0003, 0.0003);
    glRotatef(90, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    //glRotatef(-90, 0, 0, 1);
    for (int d = 0; d <7;  d++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, p[d]);
    glPopMatrix();

    //sumbu x, y, z

    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f( 1.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f( -1.0f, 0.5f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f( -1.0f, 0.0f, 1.5f);
    glEnd();

    // garis box batas

    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

    glLineStipple(2, 0xAAAA);
    glEnable (GL_LINE_STIPPLE);

    glBegin (GL_LINES);
    glVertex3f(-1.0f, 0.0f, 1.5f);
    glVertex3f(1.0f, 0.0f, 1.5f);
    glEnd();

    glBegin (GL_LINES);
    glVertex3f(-1.0f, 0.5f, 0.0f);
    glVertex3f(1.0f, 0.5f, 0.0f);
    glEnd();

    glBegin (GL_LINES);
    glVertex3f(-1.0f, 0.5f, 0.0f);
    glVertex3f(-1.0f, 0.5f, 1.5f);
    glEnd();

    glBegin (GL_LINES);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 1.5f);
    glEnd();

    glBegin (GL_LINES);
    glVertex3f(-1.0f, 0.0f, 1.5f);
    glVertex3f(-1.0f, 0.5f, 1.5f);
    glEnd();

    glBegin (GL_LINES);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.5f, 0.0f);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

}

void WaterFall::copy_image()
{

}
