#include "waveform.h"
#include <QDebug>

Waveform::Waveform()
{
    perspective = false;

    read_setting();
    tipe_data = 1;
    tipe_sb_y_accel = 1;
    tipe_sb_y_velo = 1;
    tipe_sb_y_disp = 1;
    waveform_ms = (int)((setting.fft_lines * 1000) / setting.f_stop);
    waveform_points = 2.56 * (setting.fft_lines);
    persen_tampil = 1.0;
    poin_tampil = waveform_points;

    auto_y = 1;
    y_conv = 1;

    tipe_sumbu_x = 1;
    marker_fasa_state = 0;

    data_waveform = new float[BESAR_DATA_RECIP]();

    ft1 = new QFont("/usr/share/fonts/truetype/msttcorefonts/Verdana.ttf");
    ft1->setPixelSize(12);

}

Waveform::~Waveform()
{
    delete[] data_waveform;
}

void Waveform::read_setting()
{
    QString pth = "setting.ini";
    //qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    setting.fase_enabled = settings.value("fase_enable").toInt();

    setting.f_start         = settings.value("f_start").toInt();
    setting.f_stop          = settings.value("f_stop").toInt();
    setting.fft_lines_index = settings.value("lines_index").toInt();
    setting.fft_lines       = settings.value("lines").toInt();
}

void Waveform::get_waveform_param(int points, int lenght)
{
    waveform_points = points;
    waveform_ms = lenght;
    poin_tampil = persen_tampil * waveform_points;
}

void Waveform::get_data_waveform(float  *data_view, int points, int length)
{
    waveform_points = points;
    waveform_ms = length;
    poin_tampil = persen_tampil * waveform_points;
    memcpy(data_waveform, data_view, BESAR_DATA_RECIP);
}

void Waveform::reset_data()
{
    for (int y = 0; y<( BESAR_DATA_RECIP); y++)
        data_waveform[y] = 0.00;
}

void Waveform::paintGL()
{
    glClearColor(1.0f, 1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.3f, 1.3f, -1.5f, 1.5f, -1.0f, 20.0f);
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

    if(marker_fasa_state == 1)
        draw_marker_fasa();
    drawData();

    drawSatY((-1*y_max), y_max, 4);
    drawSatX(5);

    glFlush();
}

void Waveform::resizeGL(int w, int h)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Waveform::drawData()
{
    //qDebug() << "jml data wave = " << waveform_points;
    float rms =  (rmsf_ku(data_waveform, waveform_points));

    sprintf(val_rms, "rms = %.4f", rms);
    glColor3f(0.0f, 0.0f, 0.0f);
    ft1->setPixelSize(10);

    renderText(-0.2f, 1.1f, 0.0f, val_rms, *ft1);

    data_max = data_waveform[0];
    for(x = 0; x < waveform_points; x++)
    {
        if(data_waveform[x] > data_max)
        {
            data_max = data_waveform[x] ;
        }
    }
    data_min = data_waveform[0];
    for(x = 0; x < waveform_points; x++)
    {
        if(data_waveform[x]  < data_min)
        {
            data_min = data_waveform[x] ;
        }
    }
    range_val = data_max - data_min;

    sprintf(ptop, "P to P = %.4f", (data_max - data_min)*1);
    glColor3f(0.0f, 0.0f, 0.0f);
    ft1->setPixelSize(10);

    renderText(0.4f, 1.1f, 0.0f, ptop, *ft1);

    //gambar grafik

    glLineWidth(1.3);

    glBegin(GL_LINE_STRIP);
    x_val = -1.0;


    if(auto_y == 0)
    {
        for(x = 0; x < poin_tampil; x++)
        {
            glColor3f(0.0f, 0.39f, 0.0f);

            data_plot=data_waveform[x]*y_conv;

            if (data_plot>=1.0f)
            {
                data_plot=1.0f;
            }
            else if (data_plot<=-1.0f)
            {
                data_plot=-1.0f;
            }

            glVertex2f(x_val, data_plot);

            x_val = x_val + (2.0 / poin_tampil);
        }
    }

    if(auto_y == 1)
    {
        for(x = 0; x < poin_tampil; x++)
        {
            glColor3f(0.0f, 0.39f, 0.0f);

            glVertex2f(x_val, ((data_waveform[x] -  data_min)/range_val)*2.0f - 1.0f);
            x_val = x_val + (2.0 / poin_tampil);
        }
    }

    glEnd();

    glLineWidth(1);
}

void Waveform::draw_marker_fasa()
{

    y_kursor_max =0.0;
    idx_data_kursor_max =0;

    for(x = 0; x < waveform_points; x++)
    {
        if(data_waveform[x] > y_kursor_max)
        {
            y_kursor_max = data_waveform[x];
            idx_data_kursor_max = x;
        }
    }

    x_kursor_max = (idx_data_kursor_max*2.0f/(waveform_points)) - 1.0f;

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(x_kursor_max, -1.0f);
    glVertex2f(x_kursor_max, 1.0f);
    glEnd();

    sprintf(val_kursor, "fasa = %d deg",  idx_data_kursor_max * 360 / waveform_points);
    glColor3f(0.0f, 0.0f, 0.0f);
    ft1->setPixelSize(10);

    renderText(-0.8f, 1.1f, 0.0f, val_kursor, *ft1);
}

void Waveform::drawBatas()
{
    //sumbu x, y, z

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( -1.0f, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f( 1.0f, 1.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glEnd();

    // garis box batas

    glColor3f(1.0f, 1.0f, 1.0f);

    glLineStipple(2, 0xAAAA);
    glEnable (GL_LINE_STIPPLE);

    glBegin (GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

void Waveform::drawGrid()
{
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);

    glLineStipple(2, 0xAAAA);
    glEnable (GL_LINE_STIPPLE);

    for(int x = 1; x < 5; x++)
    {
        glBegin (GL_LINES);
        glVertex2f((2.0f/5)*x-1.0f, -1.0f);
        glVertex2f((2.0f/5)*x-1.0f, 1.0f);
        glEnd();
    }

    for(int y = 1; y < 4; y++)
    {
        glBegin (GL_LINES);
        glVertex2f(-1.0f, (2.0f/4)*y-1.0f);
        glVertex2f(1.0f, (2.0f/4)*y-1.0f );
        glEnd();
    }

    glDisable(GL_LINE_STIPPLE);
}

void Waveform::drawSatX(int step)
{
    ft1->setPixelSize(10);
    intv_x = 0;

    x_pos = -1.05f;
    x_intv = 2.0f/step;

    if(tipe_sumbu_x == 1)
    {
        intv_x =  (waveform_ms * poin_tampil)/ (waveform_points * step);
        renderText(0, -1.3f, 0, "(ms)", *ft1, 2000);
    }
    else if(tipe_sumbu_x == 2)
    {
        intv_x = 360 / step;
        renderText(0, -1.3f, 0, "(deg)", *ft1, 2000);
    }
    else if(tipe_sumbu_x == 3)
    {
        intv_x = (float)poin_tampil / (float)step;
        renderText(0, -1.3f, 0, "(points)", *ft1, 2000);
    }

    float min_val = 0;
    glColor3f(0.0f, 0.0f, 0.0f);
    for(int x = 0; x < (step+1); x++)
    {
        sprintf(val, "%.0f", min_val);
        renderText(x_pos, -1.2f, 0, val, *ft1, 2000);
        x_pos = x_pos + x_intv;
        min_val = min_val + intv_x;
    }
}

void Waveform::update_y_scale()
{
        y_conv = 1/y_max;
}

void Waveform::drawSatY(float min_val, float max_val, int step)
{
    interv = 0;
    range = max_val - min_val;

    y_pos = -1.04f;
    y_intv = 2.0f/step;

    if(tipe_data == 1)
    {
        if(tipe_sb_y_accel == 1)
        {
            renderText(-1.17f, 0.2f, 0, "(G)", *ft1, 2000);
        }
        else if(tipe_sb_y_accel == 2)
        {
            renderText(-1.17f, 0.2f, 0, "(mm/s2)", *ft1, 2000);
        }
    }

    if(tipe_data == 2)
    {
        if(tipe_sb_y_velo == 1)
        {
            renderText(-1.17f, 0.2f, 0, "(mm/s)", *ft1, 2000);
        }
        else if(tipe_sb_y_velo == 2)
        {
            renderText(-1.17f, 0.2f, 0, "(IPS)", *ft1, 2000);
        }
    }

    if(tipe_data == 3)
    {
        if(tipe_sb_y_disp == 1)
        {
            renderText(-1.17f, 0.2f, 0, "(mm)", *ft1, 2000);
        }
        else if(tipe_sb_y_disp == 2)
        {
            renderText(-1.17f, 0.2f, 0, "(micron)", *ft1, 2000);
        }
        else if(tipe_sb_y_disp == 3)
        {
            renderText(-1.17f, 0.2f, 0, "(mils)", *ft1, 2000);
        }
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    if(auto_y == 0)
    {
        interv = range / step;
        for(int x = 0; x < (step+1); x++)
        {
            if((min_val) <= 1 || (min_val) >= -1)
                snprintf(val, sizeof(val), "%.4f", min_val );
            if((min_val) > 1 || (min_val ) < -1)
                snprintf(val, sizeof(val), "%.0f", min_val );
            renderText(-1.22f, y_pos, 0, val, *ft1, 2000);
            y_pos = y_pos + y_intv;
            min_val = min_val + interv;
        }
    }
    else if(auto_y == 1)
    {
        interv = range_val / 4;
        min_val = data_min;
        for(int x = 0; x < 5; x++)
        {
            if((min_val) <= 1 || (min_val ) >= -1)
                snprintf(val, sizeof(val), "%.4f", min_val );
            if((min_val) > 1 || (min_val) < -1)
                snprintf(val, sizeof(val), "%.0f", min_val );
            renderText(-1.22f, y_pos, 0, val, *ft1, 2000);
            y_pos = y_pos + y_intv;
            min_val = min_val + interv;
        }
    }
}

void Waveform::copy_image()
{
    QImage image = this->grabFrameBuffer();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(QPixmap::fromImage(image));
}

void Waveform::copy_data()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString str;
    QString datakanal;

    for(int x = 0; x < waveform_points; x++)
    {
        str = str + datakanal.setNum(x);
        str = str + "\t";
    }
    str = str + "\n";
    for(int x = 0; x < waveform_points; x++)
    {
        str = str + datakanal.setNum(data_waveform[x]);
        str = str + "\t";
    }
    str = str + "\n";

    clipboard->setText(str);
}
