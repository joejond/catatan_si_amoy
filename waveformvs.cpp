#include "waveformvs.h"
#include <QDebug>

WaveformVS::WaveformVS()
{
    perspective = false;

    read_setting();
    tipe_data = 1;
    tipe_sb_y_accel = 1;
    tipe_sb_y_velo = 1;
    tipe_sb_y_disp = 1;
    waveform_ms1 = (int)((setting.fft_lines * 1000) / setting.f_stop);
    waveform_ms2 = (int)((setting.fft_lines * 1000) / setting.f_stop);
    waveform_ms3 = (int)((setting.fft_lines * 1000) / setting.f_stop);
    waveform_ms4 = (int)((setting.fft_lines * 1000) / setting.f_stop);
    waveform_points1 = 2.56 * (setting.fft_lines);
    waveform_points2 = 2.56 * (setting.fft_lines);
    waveform_points3 = 2.56 * (setting.fft_lines);
    waveform_points4 = 2.56 * (setting.fft_lines);
    persen_tampil = 1.0;
    poin_tampil1 = waveform_points1;
    poin_tampil2 = waveform_points2;
    poin_tampil3 = waveform_points3;
    poin_tampil4 = waveform_points4;

    auto_y = 1;
    y_max = 100;
    y_conv = 0;

    tipe_sumbu_x = 1;
    marker_fasa_state = 0;

    wave1_state = 0;
    wave2_state = 0;
    wave3_state = 0;
    wave4_state = 0;

    data_waveform1 = new float[BESAR_DATA_RECIP]();
    data_waveform2 = new float[BESAR_DATA_RECIP]();
    data_waveform3 = new float[BESAR_DATA_RECIP]();
    data_waveform4 = new float[BESAR_DATA_RECIP]();

    ft1 = new QFont("/usr/share/fonts/truetype/msttcorefonts/Verdana.ttf");
    ft1->setPixelSize(12);

}

WaveformVS::~WaveformVS()
{
    delete[] data_waveform1;
    delete[] data_waveform2;
    delete[] data_waveform3;
    delete[] data_waveform4;
}

void WaveformVS::read_setting()
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

void WaveformVS::get_waveform_param(int points, int lenght)
{
    waveform_points1 = points;
    waveform_points2 = points;
    waveform_points3 = points;
    waveform_points4 = points;
    waveform_ms1 = lenght;
    waveform_ms2 = lenght;
    waveform_ms3 = lenght;
    waveform_ms4 = lenght;
    poin_tampil1 = persen_tampil * waveform_points1;
    poin_tampil2 = persen_tampil * waveform_points2;
    poin_tampil3 = persen_tampil * waveform_points3;
    poin_tampil4 = persen_tampil * waveform_points4;
}

void WaveformVS::get_data_waveform1(float  *data_view, int points, int length)
{
    waveform_points1 = points;
    waveform_ms1 = length;
    poin_tampil1 = persen_tampil * waveform_points1;
    memcpy(data_waveform1, data_view, BESAR_DATA_RECIP);
}

void WaveformVS::get_data_waveform2(float  *data_view, int points, int length)
{
    waveform_points2 = points;
    waveform_ms2 = length;
    poin_tampil2 = persen_tampil * waveform_points2;
    memcpy(data_waveform2, data_view, BESAR_DATA_RECIP);
}

void WaveformVS::get_data_waveform3(float  *data_view, int points, int length)
{
    waveform_points3 = points;
    waveform_ms3 = length;
    poin_tampil3 = persen_tampil * waveform_points3;
    memcpy(data_waveform3, data_view, BESAR_DATA_RECIP);
}

void WaveformVS::get_data_waveform4(float  *data_view, int points, int length)
{
    waveform_points4 = points;
    waveform_ms4 = length;
    poin_tampil4 = persen_tampil * waveform_points4;
    memcpy(data_waveform4, data_view, BESAR_DATA_RECIP);
}

void WaveformVS::reset_data()
{
    for (int y = 0; y<( BESAR_DATA_RECIP); y++)
        data_waveform1[y] = 0.00;
}

void WaveformVS::paintGL()
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
    drawSatY((-1*y_max), y_max, 4);
    drawSatX(4);
    if(marker_fasa_state == 1)
        draw_marker_fasa();
    if(wave1_state == 1)
        drawData(data_waveform1, 1, waveform_points1, poin_tampil1);
    if(wave2_state == 1)
        drawData(data_waveform2, 2, waveform_points2, poin_tampil2);
    if(wave3_state == 1)
        drawData(data_waveform3, 3, waveform_points3, poin_tampil3);
    if(wave4_state == 1)
        drawData(data_waveform4, 4, waveform_points4, poin_tampil4);
    glFlush();
}

void WaveformVS::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void WaveformVS::drawData(float * data_tampil, int kanal_id, int waveform_points, int poin_tampil)
{
    float rms =  (rmsf_ku(data_tampil, waveform_points));

    data_max = data_tampil[0];
    for(x = 0; x < waveform_points; x++)
    {
        if(data_tampil[x] > data_max)
        {
            data_max = data_tampil[x] ;
        }
    }
    data_min = data_waveform1[0];
    for(x = 0; x < waveform_points; x++)
    {
        if(data_tampil[x]  < data_min)
        {
            data_min = data_tampil[x] ;
        }
    }
    range_val = data_max - data_min;

    glColor3f(0.0f, 0.0f, 0.0f);
    ft1->setPixelSize(10);

    if(kanal_id == 1)
    {
        sprintf(val_rms, "rms (1) = %.4f", rms*1);
        renderText(-0.2f, 1.4f, 0.0f, val_rms, *ft1);

        sprintf(ptop, "P to P (1) = %.4f", (data_max - data_min)*1);
        renderText(0.4f, 1.4f, 0.0f, ptop, *ft1);
    }
    if(kanal_id == 2)
    {
        sprintf(val_rms, "rms (2) = %.4f", rms*1);
        renderText(-0.2f, 1.3f, 0.0f, val_rms, *ft1);

        sprintf(ptop, "P to P (2) = %.4f", (data_max - data_min)*1);
        renderText(0.4f, 1.3f, 0.0f, ptop, *ft1);
    }
    if(kanal_id == 3)
    {
        sprintf(val_rms, "rms (3) = %.4f", rms*1);
        renderText(-0.2f, 1.2f, 0.0f, val_rms, *ft1);

        sprintf(ptop, "P to P (3) = %.4f", (data_max - data_min)*1);
        renderText(0.4f, 1.2f, 0.0f, ptop, *ft1);
    }
    if(kanal_id == 4)
    {
        sprintf(val_rms, "rms (4) = %.4f", rms*1);
        renderText(-0.2f, 1.1f, 0.0f, val_rms, *ft1);

        sprintf(ptop, "P to P (4) = %.4f", (data_max - data_min)*1);
        renderText(0.4f, 1.1f, 0.0f, ptop, *ft1);
    }

    //gambar grafik

    glBegin(GL_LINE_STRIP);
    x_val = -1.0;

    if(kanal_id == 1)
        glColor3f(1.0f, 0.39f, 0.0f);
    if(kanal_id == 2)
        glColor3f(0.0f, 1.0f, 0.3f);
    if(kanal_id == 3)
        glColor3f(0.0f, 0.39f, 1.0f);
    if(kanal_id == 4)
        glColor3f(1.0f, 0.0f, 1.0f);

    if(auto_y == 0)
    {
        for(x = 0; x < poin_tampil; x++)
        {
            glVertex2f(x_val, (data_tampil[x])*y_conv);
            x_val = x_val + (2.0 / poin_tampil);
        }
    }

    if(auto_y == 1)
    {
        for(x = 0; x < poin_tampil; x++)
        {
            glVertex2f(x_val, ((data_tampil[x] -  data_min)/range_val)*2.0f - 1.0f);
            x_val = x_val + (2.0 / poin_tampil);
        }
    }

    glEnd();
}

void WaveformVS::draw_marker_fasa()
{
//    y_kursor_max =0.0;
//    idx_data_kursor_max =0;

//    for(x = 0; x < waveform_points; x++)
//    {
//        if(data_waveform1[x] > y_kursor_max)
//        {
//            y_kursor_max = data_waveform1[x];
//            idx_data_kursor_max = x;
//        }
//    }

//    x_kursor_max = (idx_data_kursor_max*2.0f/(waveform_points)) - 1.0f;

//    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//    glBegin(GL_LINES);
//    glVertex2f(x_kursor_max, -1.0f);
//    glVertex2f(x_kursor_max, 1.0f);
//    glEnd();


//    sprintf(val_kursor, "fasa = %d deg",  idx_data_kursor_max * 360 / waveform_points);
//    glColor3f(0.0f, 0.0f, 0.0f);
//    ft1->setPixelSize(10);

//    renderText(-0.8f, 1.1f, 0.0f, val_kursor, *ft1);

}

void WaveformVS::drawBatas()
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

void WaveformVS::drawGrid()
{
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);

    glLineStipple(2, 0xAAAA);
    glEnable (GL_LINE_STIPPLE);

    for(int x = 1; x < 8; x++)
    {
        glBegin (GL_LINES);
        glVertex2f((2.0f/8)*x-1.0f, -1.0f);
        glVertex2f((2.0f/8)*x-1.0f, 1.0f);
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

void WaveformVS::drawSatX(int step)
{
    waveform_ms = waveform_ms1;
    if(waveform_ms < waveform_ms2)
        waveform_ms = waveform_ms2;
    if(waveform_ms < waveform_ms3)
        waveform_ms = waveform_ms3;
    if(waveform_ms < waveform_ms4)
        waveform_ms = waveform_ms4;

    poin_tampil = poin_tampil1;
    if(poin_tampil < poin_tampil2)
        poin_tampil = poin_tampil2;
    if(poin_tampil < poin_tampil3)
        poin_tampil = poin_tampil3;
    if(poin_tampil < poin_tampil4)
        poin_tampil = poin_tampil4;

    waveform_points = waveform_points1;
    if(waveform_points < waveform_points2)
        waveform_points = waveform_points2;
    if(waveform_points < waveform_points3)
        waveform_points = waveform_points3;
    if(waveform_points < waveform_points4)
        waveform_points = waveform_points4;

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

void WaveformVS::update_y_scale()
{
    if(auto_y == 0)
    {
        //kalibrasi y = m x val + c  --->> m = 9566
        float conv = 1 * 1 / y_max;
        y_conv = conv;

    }
}

void WaveformVS::drawSatY(float min_val, float max_val, int step)
{
    interv = 0;
    range = max_val - min_val;
    int_val = range / step;

    y_pos = -1.04f;
    y_intv = 2.0f/step;

    if(tipe_data == 1)
    {
        if(tipe_sb_y_accel == 1)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(mV)", *ft1, 2000);
        }
        else if(tipe_sb_y_accel == 2)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(mm/s2)", *ft1, 2000);
        }
        else if(tipe_sb_y_accel == 3)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(G)", *ft1, 2000);
        }
    }

    if(tipe_data == 2)
    {
        if(tipe_sb_y_velo == 1)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(mm/s)", *ft1, 2000);
        }
        else if(tipe_sb_y_velo == 2)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(IPS)", *ft1, 2000);
        }
    }

    if(tipe_data == 3)
    {
        if(tipe_sb_y_disp == 1)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(mm)", *ft1, 2000);
        }
        else if(tipe_sb_y_disp == 2)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(micron)", *ft1, 2000);
        }
        else if(tipe_sb_y_disp == 3)
        {
            interv = int_val;
            renderText(-1.17f, 0.2f, 0, "(mils)", *ft1, 2000);
        }
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    if(auto_y == 0)
    {
        for(int x = 0; x < (step+1); x++)
        {
            if(min_val <= 1 || min_val >= -1)
                snprintf(val, sizeof(val), "%.4f", min_val);
            if(min_val > 1 || min_val < -1)
                snprintf(val, sizeof(val), "%.0f", min_val);
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
            if(min_val <= 1 || min_val >= -1)
                snprintf(val, sizeof(val), "%.4f", min_val);
            if(min_val > 1 || min_val < -1)
                snprintf(val, sizeof(val), "%.0f", min_val);
            renderText(-1.22f, y_pos, 0, val, *ft1, 2000);
            y_pos = y_pos + y_intv;
            min_val = min_val + interv;
        }
    }

}

void WaveformVS::copy_image()
{
    QImage image = this->grabFrameBuffer();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(QPixmap::fromImage(image));
}

void WaveformVS::copy_data()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString str;
    QString datakanal;

//    for(int x = 0; x < waveform_points; x++)
//    {
//        str = str + datakanal.setNum(x);
//        str = str + "\t";
//    }
//    str = str + "\n";
//    for(int x = 0; x < waveform_points; x++)
//    {
//        str = str + datakanal.setNum(data_waveform1[x]);
//        str = str + "\t";
//    }
//    str = str + "\n";

//    clipboard->setText(str);
}
