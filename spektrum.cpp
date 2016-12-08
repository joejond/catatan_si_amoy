#include "spektrum.h"

Spektrum::Spektrum()
{
    perspective = false;

    read_setting();

    y_max = 0;
    y_conv = 0;

    auto_y = 1;
    tipe_window = 1;
    tipe_data = 1;
    tipe_sumbu_x = 1;
    tipe_sb_y_accel = 1;
    tipe_sb_y_velo = 1;
    tipe_sb_y_disp = 1;
    spektrum_points =  2.56 * (setting.fft_lines);
    tampilkan_points = setting.fft_lines;

    num_avrg = 4;

    marker_state = 0;
    marker_type = 1;
    idx_data_kursor = 0;
    x_kursor = -1.0f;
    y_kursor = -1.0f;
    x_kursor_max = -1.0f;
    y_kursor_max = -1.0f;

    data_spektrum = new float[BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        data_spektrum[x] = 0.00;

    window_coef = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        window_coef[x] = 0.00;

    hasil_windowing  = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        hasil_windowing[x] = 0.00;

    fft_re_out = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        fft_re_out[x] = 0.00;

    fft_im_out = new float[ BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        fft_im_out[x] = 0.00;

    fft_magt = new float[BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        fft_magt[x] = 0.00;

    int y = 0;
    for(x = 0; x < 4; x++)
    {
        avrg[x] = new float[BESAR_DATA_RECIP]();
        for (y = 0; y<(BESAR_DATA_RECIP); y++)
            avrg[x][y] = 0.00;
    }

    hasil_avrg = new float[BESAR_DATA_RECIP]();
    for (x = 0; x<(BESAR_DATA_RECIP); x++)
        hasil_avrg[x] = 0.00;

    ft1 = new QFont("/usr/share/fonts/truetype/tlwg/Bold.ttf");
    ft1->setPixelSize(14);
}

Spektrum::~Spektrum()
{
    delete[] data_spektrum;
    delete[] window_coef;
    delete[] hasil_windowing;
    delete[] fft_re_out;
    delete[] fft_im_out;
    delete[] fft_magt;
    delete[] hasil_avrg;
    for(x = 0; x < 4; x++)
    {
        delete[] avrg[x];
    }
}

void Spektrum::read_setting()
{
    QString pth = "setting.ini";
    QSettings settings(pth, QSettings::IniFormat);

    setting.f_start         = settings.value("f_start").toInt();
    setting.f_stop          = settings.value("f_stop").toInt();
    setting.fft_lines_index = settings.value("lines_index").toInt();
    setting.fft_lines       = settings.value("lines").toInt();
}

void Spektrum::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
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

    drawSatY(0.0, y_max, 4);
    drawSatX(0.0, tampilkan_points, 5);
    drawData();
    if(marker_state == 1)
        drawKursor();
    glFlush();
}

void Spektrum::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Spektrum::drawKursor()
{
    if(marker_type == 1)
    {
        if(auto_y == 0)
            y_kursor =  ((hasil_avrg[idx_data_kursor]*y_conv)-1.0);
        if(auto_y == 1)
            y_kursor = ((hasil_avrg[idx_data_kursor] / data_max) * 2.0f)-1.0f;

        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex3f((x_kursor - 0.02f), y_kursor, 0.0f);
        glVertex3f( (x_kursor + 0.02f), y_kursor, 0.0f);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(x_kursor, (y_kursor - 0.05f), 0.0f);
        glVertex3f(x_kursor, (y_kursor + 0.05f), 0.0f);
        glEnd();

        sprintf(val_kursor, "(%.0f, %.4f)",  idx_data_kursor*x_factor, (hasil_avrg[idx_data_kursor]*y_conv*y_max/2));
        glColor3f(0.0f, 0.0f, 1.0f);
        ft1->setPixelSize(10);

        renderText(x_kursor+0.02f, y_kursor+0.02f, 0.0f, val_kursor, *ft1);
    }

    if(marker_type == 2)
    {
        y_kursor_max =0.0;
        idx_data_kursor_max =0;

        for(x = 0; x < tampilkan_points; x++)
        {
            if(hasil_avrg[x] > y_kursor_max)
            {
                y_kursor_max = hasil_avrg[x];
                idx_data_kursor_max=x;
            }
        }

        x_kursor_max = (idx_data_kursor_max*2.0f/(tampilkan_points)) - 1.0f;
        if(auto_y == 0)
            y_kursor_max =  ((hasil_avrg[idx_data_kursor_max]*y_conv)-1.0);
        if(auto_y == 1)
            y_kursor_max = ((hasil_avrg[idx_data_kursor_max] / data_max) * 2.0f)-1.0f;

        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex3f((x_kursor_max - 0.02f), y_kursor_max, 0.0f);
        glVertex3f( (x_kursor_max + 0.02f), y_kursor_max, 0.0f);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(x_kursor_max, (y_kursor_max - 0.05f), 0.0f);
        glVertex3f(x_kursor_max, (y_kursor_max + 0.05f), 0.0f);
        glEnd();

        sprintf(val_kursor, "(%.0f, %.4f)",  idx_data_kursor_max*x_factor, (hasil_avrg[idx_data_kursor_max]*y_conv*y_max/2));
        glColor3f(0.0f, 0.0f, 1.0f);
        ft1->setPixelSize(10);

        renderText(x_kursor_max+0.02f, y_kursor_max+0.02f, 0.0f, val_kursor, *ft1);
    }

    if(marker_type == 3)
    {
        int idx_har;
        float step_x = (2.0f)/(tampilkan_points-1);
        for(int n = 0; n < 5; n++)
        {
            idx_har = idx_data_kursor  + n * idx_data_kursor;
            y_kursor =  ((hasil_avrg[idx_har]*y_conv)-1.0);

            x_kursor_harmonic = x_kursor + (idx_har * step_x);

            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_LINES);
            glVertex3f((x_kursor_harmonic - 0.02f), y_kursor, 0.0f);
            glVertex3f((x_kursor_harmonic + 0.02f), y_kursor, 0.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(x_kursor_harmonic, (y_kursor - 0.05f), 0.0f);
            glVertex3f(x_kursor_harmonic, (y_kursor + 0.05f), 0.0f);
            glEnd();

            sprintf(val_kursor, "(%.0f, %.4f)",  idx_har*x_factor, (hasil_avrg[idx_har]*y_conv*y_max/2));
            glColor3f(0.0f, 0.0f, 1.0f);
            ft1->setPixelSize(10);

            renderText(x_kursor_harmonic+0.02f, y_kursor+0.02f, 0.0f, val_kursor, *ft1);
        }
    }
}

void Spektrum::get_spektrum_param()
{
    read_setting();
    spektrum_points =  2.56 * (setting.fft_lines);
    tampilkan_points = setting.fft_lines;
}

void Spektrum::reset_data()
{
    for (int y = 0; y<( BESAR_DATA_RECIP); y++)
        data_spektrum[y] = 0.00;
}


void Spektrum::get_data_spektrum(float  *data_view)
{
    memcpy(data_spektrum, data_view, BESAR_DATA_RECIP);
}

void Spektrum::update_y_scale()
{
    y_conv =  4 * 1/y_max;
}

void Spektrum::hitung_coef_window()
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

void Spektrum::drawData()
{

    hitung_coef_window();

    // proses FFT
    windowkan(data_spektrum, hasil_windowing, window_coef, spektrum_points);

    memset( fft_re_out, 0, spektrum_points);
    memset( fft_im_out, 0, spektrum_points);

    fft_float( spektrum_points, 0, hasil_windowing, 0, fft_re_out, fft_im_out);

    for (int i=0; i< spektrum_points; i++)
    {
        fft_magt[i] = sqrt( (fft_re_out[i] * fft_re_out[i]) + ( fft_im_out[i] * fft_im_out[i]));
        fft_magt[i] = fft_magt[i] / spektrum_points;
    }

    fft_magt[0] = 0.0; //????????

    memcpy(avrg[3], avrg[2], BESAR_DATA_RECIP);
    memcpy(avrg[2], avrg[1], BESAR_DATA_RECIP);
    memcpy(avrg[1], avrg[0], BESAR_DATA_RECIP);
    memcpy(avrg[0], fft_magt, BESAR_DATA_RECIP);

    if(num_avrg > 1)
    {
        for(x = 0; x < num_avrg; x++)
        {
            for(int n = 0; n < spektrum_points; n++)
            {
                hasil_avrg[n] = hasil_avrg[n] + avrg[x][n];
            }
        }
        for(int n = 0; n < spektrum_points; n++)
        {
            hasil_avrg[n] = hasil_avrg[n] / num_avrg;
        }
    }

    if(num_avrg == 1)
    {
        for(int n = 0; n < spektrum_points; n++)
        {
            hasil_avrg[n] = avrg[0][n];
        }
    }

    // proses menggambar

    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    float x_val = -1.0f;

    data_max = hasil_avrg[0];
    for(x = 0; x < spektrum_points; x++)
    {
        if(hasil_avrg[x] > data_max)
        {
            data_max = hasil_avrg[x] ;
        }
    }

    if(auto_y == 0)
    {
        for(int x = 0; x < tampilkan_points; x++)
        {
            data_plot = (hasil_avrg[x]*y_conv)-1.0f;

            //buat memotong grafik bila melewati batas atas bidang gambar

            if (data_plot>=1.0f)
            {
                data_plot=1.0f;
            }

            if(hasil_avrg[x]*y_conv < 0.1f)
                glColor3f(0.0f, 0.39f, 0.0f);
            else if(hasil_avrg[x]*y_conv >= 0.1f && hasil_avrg[x]*y_conv < 0.3f)
                glColor3f(1.0f, 0.84f, 0.0f);
            else if(hasil_avrg[x]*y_conv >= 0.3f)
                glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(x_val, data_plot);
            x_val = x_val + (2.0f)/(tampilkan_points);
        }
    }
    else if(auto_y == 1)
    {
        for(int x = 0; x < tampilkan_points; x++)
        {
            if(hasil_avrg[x]*y_conv < 0.1f)
                glColor3f(0.0f, 0.39f, 0.0f);
            else if(hasil_avrg[x]*y_conv >= 0.1f && hasil_avrg[x]*y_conv < 0.3f)
                glColor3f(1.0f, 0.84f, 0.0f);
            else if(hasil_avrg[x]*y_conv >= 0.3f)
                glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(x_val, ((hasil_avrg[x] / data_max) * 2.0f)-1.0f);
            x_val = x_val + (2.0f)/tampilkan_points;
        }
    }
    glEnd();
}

void Spektrum::drawBatas()
{
    //sumbu x, y, z

    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( -1.0f, 1.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, 1.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();
}

void Spektrum::drawGrid()
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

void Spektrum::drawSatX(float min_val, float max_val, int step)
{
    ft1->setPixelSize(10);

    range = max_val - min_val;
    int_val = range / step;

    x_pos = -1.05f;
    x_intv = 2.0f/step;

    if(tipe_sumbu_x == 1)
    {
        interv = setting.f_stop / step;
        renderText(0, -1.3f, 0, "(Hz)", *ft1, 2000);
        x_factor = (float)(setting.f_stop) / (float)(tampilkan_points);
    }
    else if(tipe_sumbu_x == 2)
    {
        interv = setting.f_stop * 60 / step;
        renderText(0, -1.3f, 0, "(cpm)", *ft1, 2000);
        x_factor = setting.f_stop * 60 / tampilkan_points;
    }
    else if(tipe_sumbu_x == 3)
    {
        interv = int_val;
        renderText(0, -1.3f, 0, "(points)", *ft1, 2000);
        x_factor = 1.0;
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    for(int x = 0; x < (step+1); x++)
    {
        sprintf(val, "%.0f", min_val);
        renderText(x_pos, -1.2f, 0, val, *ft1, 2000);
        x_pos = x_pos + x_intv;
        min_val = min_val + interv;
    }
}

void Spektrum::drawSatY(float min_val, float max_val, int step)
{
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
        int_val = (max_val - min_val) / (float)step;
        for(int x = 0; x < (step+1); x++)
        {
            if((min_val) <= 1)
                snprintf(val, sizeof(val), "%.4f", min_val);
            if((min_val) > 1)
                snprintf(val, sizeof(val), "%.0f", min_val );
            renderText(-1.22f, y_pos, 0, val, *ft1, 2000);
            y_pos = y_pos + y_intv;
            min_val = min_val + int_val;
        }
    }
    else if(auto_y == 1)
    {
        interv = data_max / 2;
        for(int x = 0; x < 5; x++)
        {
            if((min_val) <= 1)
                snprintf(val, sizeof(val), "%.4f", min_val);
            if((min_val) > 1)
                snprintf(val, sizeof(val), "%.0f", min_val );
            renderText(-1.22f, y_pos, 0, val, *ft1, 2000);
            y_pos = y_pos + y_intv;
            min_val = min_val + interv;
        }
    }
}

void Spektrum::keyPressEvent ( QKeyEvent * e)
{
    if(marker_type == 1 || marker_type == 3)
    {
        switch( e->key() )
        {
        case Qt::Key_Left:
        {
            x_kursor = x_kursor-(2.0f)/(tampilkan_points-1);
            idx_data_kursor=idx_data_kursor-1;
            y_kursor=((hasil_avrg[idx_data_kursor]*y_conv)-1.0);
        }
            break;

        case Qt::Key_Right:
        {
            x_kursor = x_kursor+(2.0f)/(tampilkan_points-1);
            idx_data_kursor=idx_data_kursor+1;
            y_kursor=((hasil_avrg[idx_data_kursor]*y_conv)-1.0);
        }
            break;
        }
        update();
    }
}

void Spektrum::mousePressEvent(QMouseEvent * event)
{
    if(marker_type == 1)
    {
        setFocusPolicy(Qt::StrongFocus);
        this->setFocus();

        float x_mouse = event->x() ;
        float y_mouse = event->y() ;
        float w = this->width();
        float h = this->height();

        float x_gl = x_mouse - w/2;
        float y_gl = h/2 - y_mouse;

        float x_chart = x_gl*2*1.3f/w;
        float y_chart = y_gl*2*1.5f/h;

        float x_val = -1.0f;
        idx_data_kursor = 0;

        for(int x = 0; x < tampilkan_points; x++)
        {
            if(x_chart > x_val)
            {
                x_val = x_val + (2.0f)/(tampilkan_points-1);
            }
            else
            {
                x_chart = x_val;
                idx_data_kursor = x;
                break;
            }
        }

        y_chart =  ((hasil_avrg[idx_data_kursor]*y_conv)-1.0);

        x_kursor = x_chart;
        y_kursor = y_chart;
        update();
    }
}

void Spektrum::copy_image()
{
    QImage image = this->grabFrameBuffer();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(QPixmap::fromImage(image));
}

void Spektrum::copy_data()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString str;
    QString datakanal;

    for(int x = 0; x < tampilkan_points; x++)
    {
        str = str + datakanal.setNum(x);
        str = str + "\t";
    }
    str = str + "\n";
    for(int x = 0; x < tampilkan_points; x++)
    {
        str = str + datakanal.setNum(hasil_avrg[x]);
        str = str + "\t";
    }
    str = str + "\n";

    clipboard->setText(str);
}
