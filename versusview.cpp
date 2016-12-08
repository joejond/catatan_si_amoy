#include "versusview.h"
#include "ui_versusview.h"

VersusView::VersusView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VersusView)
{
    ui->setupUi(this);

    read_setting();
    tipe_spek = 1;
    tipe_data = 1;
    tipe_accel = 1;
    tipe_velo = 1;
    tipe_disp = 1;

    jml_last_masuk = 0;
    index_buffer = 0;
    marker_fasa_state = 0;
    auto_scale_Y_state = 1;

    window_type = 1;

    marker_state = 0;
    marker_type = 1;

    proses_state = 0;

    waveform_ms = (int)((setting.fft_lines * 1000) / setting.f_stop);
    jml_data_waveform = 2.56 * (setting.fft_lines);

    data_view1 = new float[BESAR_DATA_RECIP]();
    data_view2 = new float[BESAR_DATA_RECIP]();
    data_view3 = new float[BESAR_DATA_RECIP]();
    data_view4 = new float[BESAR_DATA_RECIP]();

    geser_delay1 = new float[BESAR_DATA_RECIP]();
    geser_delay2 = new float[BESAR_DATA_RECIP]();
    geser_delay3 = new float[BESAR_DATA_RECIP]();
    geser_delay4 = new float[BESAR_DATA_RECIP]();

    geser_system1 = new float[BESAR_DATA_RECIP]();
    geser_system2 = new float[BESAR_DATA_RECIP]();
    geser_system3 = new float[BESAR_DATA_RECIP]();
    geser_system4 = new float[BESAR_DATA_RECIP]();

    window_coef = new float[BESAR_DATA_RECIP]();
    temp_filter = new double[BESAR_DATA_RECIP]();

    data_integrasi1 = new float[BESAR_DATA_RECIP]();
    data_integrasi2 = new float[BESAR_DATA_RECIP]();

    wavevs = new WaveformVS;
    wavevs->y_max = 0.01;

    ui->vl_wave->addWidget(wavevs);

    create_contextMenu();

    timer_proses = new QTimer();
    connect(timer_proses, SIGNAL(timeout()), this, SLOT(proses_view()));

    ui->cb_sat_accel->setEnabled(true);
    ui->cb_sat_velo->setEnabled(false);
    ui->cb_sat_disp->setEnabled(false);

}

VersusView::~VersusView()
{
    delete[] data_view1;
    delete[] data_view2;
    delete[] data_view3;
    delete[] data_view4;

    delete[] geser_delay1;
    delete[] geser_delay2;
    delete[] geser_delay3;
    delete[] geser_delay4;

    delete[] geser_system1;
    delete[] geser_system2;
    delete[] geser_system3;
    delete[] geser_system4;

    delete[] data_integrasi1;
    delete[] data_integrasi2;

    delete[] window_coef;
    delete[] temp_filter;

    delete ui;
}

void VersusView::hitung_param_view()
{    
    if(setting.fase_enabled == 0)
        faktor_filter = 1.5;
    if(setting.fase_enabled == 1)
        faktor_filter = 1;

    wavevs->get_waveform_param(jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

    wavevs->update_y_scale();
    wavevs->update();
}

void VersusView::start_proses_view()
{
    read_setting();
    update_setting();

    acc_sens1 = setting.acc_sencitivity1;
    acc_sens2 = setting.acc_sencitivity2;
    acc_sens3 = setting.acc_sencitivity3;
    acc_sens4 = setting.acc_sencitivity4;

    // global view parameters
    waveform_ms = (int)((setting.fft_lines * 1000) / setting.f_stop);
    jml_data_waveform = 2.56 * (setting.fft_lines);

    //delay adc
    ms_delay = (int)(39000/(setting.f_stop * 2.56));

    for(i = 0; i < (BESAR_DATA_RECIP); i++)
    {
        data_view1[i] = 0.0;
        data_view2[i] = 0.0;
        data_view3[i] = 0.0;
        data_view4[i] = 0.0;
    }

    if(window_type == 1)
        buat_hanning( window_coef, jml_data_waveform);
    if(window_type == 2)
        buat_blackman( window_coef, jml_data_waveform);
    if(window_type == 3)
        buat_rectangular( window_coef, jml_data_waveform);
    if(window_type == 4)
        buat_hamming( window_coef, jml_data_waveform);
    siapkan_filter( (setting.f_stop * 2.56), setting.f_start, setting.f_stop, BAND_PASS);

    len_highpass = 121; // 251
    filter_hp = create1TransSinc( len_highpass, ((double)(setting.f_start) * 1.0), ((double)(setting.f_stop) * 2.56 * 1.0), HIGH_PASS);


    hitung_param_view();
    jml_last_masuk = 0;
    if(proses_state == 0)
    {
        int ms_proses = setting.fft_lines * 1000 / setting.f_stop;

        qDebug()  << "ms_proses" << ms_proses;
        timer_proses->start(ms_proses / 2);
        qDebug() << "view diproses";
    }
    else if(proses_state == 1)
    {
        qDebug() << "sudah jalan proses view";
    }
    proses_state = 1;
    wavevs->fasa_enable = setting.fase_enabled;

    wavevs->reset_data();
    wavevs->update();

    if(setting.fase_enabled == 0)
    {
        wavevs->tipe_sumbu_x = 1;
        ui->cb_sat_x_wave->setCurrentIndex(0);
        ui->cb_wave_length->setEnabled(true);
    }
    else if(setting.fase_enabled == 1)
    {
        wavevs->tipe_sumbu_x = 2;
        ui->cb_sat_x_wave->setCurrentIndex(1);
        ui->cb_wave_length->setCurrentIndex(5);
        ui->cb_wave_length->setDisabled(true);
    }
}

void VersusView::stop_proses_view()
{
    qDebug() << "view proses stop";
    timer_proses->stop();
    proses_state = 0;
}

void VersusView::read_setting()
{
    QString pth = "setting.ini";
    //qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    sprintf(setting.kanal_use, "%s", settings.value("kanal_use").toString().toAscii().data());
    setting.kanal_1 = settings.value("kanal_1").toInt();
    setting.kanal_2 = settings.value("kanal_2").toInt();
    setting.kanal_3 = settings.value("kanal_3").toInt();
    setting.kanal_4 = settings.value("kanal_4").toInt();

    setting.fase_enabled = settings.value("fase_enable").toInt();

    setting.view_lines1 = settings.value("view_lines1").toInt();
    setting.view_lines2 = settings.value("view_lines2").toInt();
    setting.view_lines3 = settings.value("view_lines3").toInt();
    setting.view_lines4 = settings.value("view_lines4").toInt();

    setting.acc_sencitivity1 = settings.value("acc_sencitivity1").toFloat();
    setting.acc_sencitivity2 = settings.value("acc_sencitivity2").toFloat();
    setting.acc_sencitivity3 = settings.value("acc_sencitivity3").toFloat();
    setting.acc_sencitivity4 = settings.value("acc_sencitivity4").toFloat();

    setting.client_status = settings.value("client_status").toInt();

    setting.unit_acc = settings.value("Unit_acc").toInt();
    setting.unit_velo = settings.value("Unit_velo").toInt();
    setting.unit_disp = settings.value("Unit_disp").toInt();
    setting.unit_frek = settings.value("Unit_frek").toInt();

    setting.window          = settings.value("window").toInt();
    setting.PP              = settings.value("PP").toInt();
    setting.lebar_waveform  = settings.value("lebar_waveform").toInt();
    setting.waveform_x      = settings.value("waveform_x").toInt();
    setting.waveform_y      = settings.value("waveform_y").toInt();

    setting.chart_mode      = settings.value("chart_mode").toInt();

    setting.f_start = settings.value("f_start").toInt();
    setting.f_stop = settings.value("f_stop").toInt();

    // baca setting simulasi
    setting.mode_simulasi   = settings.value("mode_simulasi").toInt();
    setting.tipe_sinyal    = settings.value("tipe_sinyal").toInt();

}

void VersusView::get_data_kanal1(float *data, int jml,  int ms_data)
{
    memcpy(geser_delay1, data, BESAR_DATA_RECIP);
    jml_data_waveform = jml;
    waveform_ms = ms_data;
    remove_dc(geser_delay1, jml_data_waveform);

    for(x = 0; x < jml_data_waveform; x++)
        geser_delay1[x] = geser_delay1[x] * acc_sens1 * conv / 100;
}
void VersusView::get_data_kanal2(float *data, int jml,  int ms_data)
{
    memcpy(geser_delay2, data, BESAR_DATA_RECIP);
    jml_data_waveform = jml;
    waveform_ms = ms_data;
    remove_dc(geser_delay2, jml_data_waveform);

    for(x = 0; x < jml_data_waveform; x++)
        geser_delay2[x] = geser_delay2[x] * acc_sens2 * conv / 100;
}
void VersusView::get_data_kanal3(float *data, int jml, int ms_data)
{
    memcpy(geser_delay3, data, BESAR_DATA_RECIP);
    jml_data_waveform = jml;
    waveform_ms = ms_data;
    remove_dc(geser_delay3, jml_data_waveform);

    for(x = 0; x < jml_data_waveform; x++)
        geser_delay3[x] = geser_delay3[x] * acc_sens3 * conv / 100;
}
void VersusView::get_data_kanal4(float *data, int jml, int ms_data)
{
    memcpy(geser_delay4, data, BESAR_DATA_RECIP);
    jml_data_waveform = jml;
    waveform_ms = ms_data;
    remove_dc(geser_delay4, jml_data_waveform);

    for(x = 0; x < jml_data_waveform; x++)
        geser_delay4[x] = geser_delay4[x] * acc_sens4 * conv / 100;
}

void VersusView::create_contextMenu()
{
    menuPop = new QMenu();

    menuPop->addSeparator();
    SubMenuCopy = menuPop->addMenu("Copy Grafik");
    menuCopyDataWave = SubMenuCopy->addAction("data - waveform");
    menuCopyImageWave = SubMenuCopy->addAction("image - waveform");
    auto_scale_y = menuPop->addAction("Auto scale Y OFF");
    auto_scale_y->setCheckable(true);

    ui->kanal_chart_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->kanal_chart_view,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popMenu(QPoint)));

    connect(menuCopyImageWave, SIGNAL(triggered()), this, SLOT(view_copy_image_wave()));
    connect(menuCopyDataWave, SIGNAL(triggered()), this, SLOT(view_copy_data_wave()));

    connect(auto_scale_y, SIGNAL(triggered()), this, SLOT(auto_scale_Y_change()));

}

void VersusView::popMenu(const QPoint &pos)
{
    menuPop->popup(pos);
    menuPop->exec(QCursor::pos());
}

void VersusView::update_setting()
{
    hitung_param_view();

    if(tipe_data == 1)
    {
        if(tipe_accel == 1) // G
            conv = 0.913242009 / 9.81;
        if(tipe_accel == 2) // mm/s2
            conv = 0.913242009  * 1000;
    }
    if(tipe_data == 2)
    {
        if(tipe_velo == 1) // mm/s
            conv = 0.913242009 * 1000 ;
        if(tipe_velo == 2) // IPS
            conv = 0.913242009  * 1000 / 25.4;
    }
    if(tipe_data == 3)
    {
        if(tipe_disp == 1) // mm
            conv = 0.913242009 * 1000 ;
            //conv = 114243.042799528 ;
        if(tipe_disp == 2) // micron
            conv = 0.913242009 * 1000  * 1000;
            //conv = 114243.042799528  * 1000;
        if(tipe_disp == 3) // mils
            conv = 0.913242009 * 1000  * 39.3700787;
            //conv = 114243.042799528  * 39.3700787;
    }

    wavevs->update_y_scale();
    wavevs->update();
}

void VersusView::view_copy_data_wave()
{

}

void VersusView::view_copy_image_wave()
{
    wavevs->copy_image();
}

void VersusView::on_check_kanal1_clicked()
{
    if(ui->check_kanal1->isChecked() == false)
    {
        kanal1_view_state = 0;
        wavevs->wave1_state = 0;
    }
    if(ui->check_kanal1->isChecked() == true)
    {
        kanal1_view_state = 1;
        wavevs->wave1_state = 1;
    }
}

void VersusView::on_check_kanal2_clicked()
{
    if(ui->check_kanal2->isChecked() == false)
    {
        kanal2_view_state = 0;
        wavevs->wave2_state = 0;
    }
    if(ui->check_kanal2->isChecked() == true)
    {
        kanal2_view_state = 1;
        wavevs->wave2_state = 1;
    }
}

void VersusView::on_check_kanal3_clicked()
{
    if(ui->check_kanal3->isChecked() == false)
    {
        kanal3_view_state = 0;
        wavevs->wave3_state = 0;
    }
    if(ui->check_kanal3->isChecked() == true)
    {
        kanal3_view_state = 1;
        wavevs->wave3_state = 1;
    }
}

void VersusView::on_check_kanal4_clicked()
{
    if(ui->check_kanal4->isChecked() == false)
    {
        kanal4_view_state = 0;
        wavevs->wave4_state = 0;
    }
    if(ui->check_kanal4->isChecked() == true)
    {
        kanal4_view_state = 1;
        wavevs->wave4_state = 1;
    }
}

void VersusView::auto_scale_Y_change()
{
    if(auto_scale_Y_state == 0)
    {
        auto_scale_Y_state = 1;
        wavevs->auto_y = 1;
    }
    else if(auto_scale_Y_state == 1)
    {
        auto_scale_Y_state = 0;
        wavevs->auto_y = 0;
    }

    update_setting();
}

void VersusView::remove_dc(float * data_kanal, int jml)
{
    float mean;
    mean = 0;
    int x;
    for (x=0; x<jml; x++)
    {
        mean += data_kanal[x];
    }

    mean = (double) (mean / jml);

    for (x=0; x<jml; x++)
    {
        data_kanal[x] -= mean;
    }

}

void VersusView::integral_wf(float *in, float *out, int jum, float s_rate)
{
    for (i=1; i<jum; i++)
        in[i] = (double) (in[i] + in[i-1]);

    for (i=1; i<jum; i++)
        out[i] = in[i] * (1.000 / (s_rate * 1.0));
}

void VersusView::highpass_filter(float *data_kanal, int jml)
{
    int i;
    int y;

    memset(temp_filter, 0, (jml + len_highpass) * sizeof (double));

    for (i=0; i<jml; i++)
    {
        for (y=0; y<len_highpass; y++)
        {
            temp_filter[ i + y ] = temp_filter[ i + y ] + ((double)data_kanal[i] * filter_hp[y]);
        }
    }

    /* INI AKAN MENYEBABKAN FASA BERGESER ??? */
    for (i=0; i<jml; i++)
        data_kanal[i] = (float)(temp_filter[i+len_highpass]);

}

void VersusView::proses_view()
{
    //jika filter highpass enable, jumlah data ditambah supaya tidak muncul buntut...
    if(setting.fase_enabled == 0)
        faktor_filter = 1.5;
    if(setting.fase_enabled == 1)
        faktor_filter = 1;
    if(setting.fase_enabled == 0)
    {
        memcpy(data_view1, geser_delay1, BESAR_DATA_RECIP);
        memcpy(data_view2, geser_delay2, BESAR_DATA_RECIP);
        memcpy(data_view3, geser_delay3, BESAR_DATA_RECIP);
        memcpy(data_view4, geser_delay4, BESAR_DATA_RECIP);
    }

    if(setting.fase_enabled == 1)
    {
        // delay adc
        poin_delay_adc = jml_data_waveform * ms_delay/waveform_ms;
        poin_delay_system =  jml_data_waveform / 7.5;

        //1

        for(i = (jml_data_waveform - poin_delay_adc); i < jml_data_waveform; i++)
            geser_system1[i] = geser_delay1[i - (jml_data_waveform - poin_delay_adc)];
        for(i = 0; i < (jml_data_waveform - poin_delay_adc); i++)
            geser_system1[i] = geser_delay1[i+poin_delay_adc];

        for(i = (jml_data_waveform - poin_delay_system); i < jml_data_waveform; i++)
            data_view1[i] = geser_system1[i - (jml_data_waveform - poin_delay_system)];
        for(i = 0; i < (jml_data_waveform - poin_delay_system); i++)
            data_view1[i] = geser_system1[i+poin_delay_system];

        //2

        for(i = (jml_data_waveform - poin_delay_adc); i < jml_data_waveform; i++)
            geser_system2[i] = geser_delay2[i - (jml_data_waveform - poin_delay_adc)];
        for(i = 0; i < (jml_data_waveform - poin_delay_adc); i++)
            geser_system2[i] = geser_delay2[i+poin_delay_adc];

        for(i = (jml_data_waveform - poin_delay_system); i < jml_data_waveform; i++)
            data_view2[i] = geser_system2[i - (jml_data_waveform - poin_delay_system)];
        for(i = 0; i < (jml_data_waveform - poin_delay_system); i++)
            data_view2[i] = geser_system2[i+poin_delay_system];

        //3

        for(i = (jml_data_waveform - poin_delay_adc); i < jml_data_waveform; i++)
            geser_system3[i] = geser_delay3[i - (jml_data_waveform - poin_delay_adc)];
        for(i = 0; i < (jml_data_waveform - poin_delay_adc); i++)
            geser_system3[i] = geser_delay3[i+poin_delay_adc];

        for(i = (jml_data_waveform - poin_delay_system); i < jml_data_waveform; i++)
            data_view3[i] = geser_system3[i - (jml_data_waveform - poin_delay_system)];
        for(i = 0; i < (jml_data_waveform - poin_delay_system); i++)
            data_view3[i] = geser_system3[i+poin_delay_system];

        //4

        for(i = (jml_data_waveform - poin_delay_adc); i < jml_data_waveform; i++)
            geser_system4[i] = geser_delay4[i - (jml_data_waveform - poin_delay_adc)];
        for(i = 0; i < (jml_data_waveform - poin_delay_adc); i++)
            geser_system4[i] = geser_delay4[i+poin_delay_adc];

        for(i = (jml_data_waveform - poin_delay_system); i < jml_data_waveform; i++)
            data_view4[i] = geser_system4[i - (jml_data_waveform - poin_delay_system)];
        for(i = 0; i < (jml_data_waveform - poin_delay_system); i++)
            data_view4[i] = geser_system4[i+poin_delay_system];

    }

    wavevs->get_waveform_param(jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

    if(tipe_data == 1)
    {
        remove_dc(data_view1, jml_data_waveform);
        remove_dc(data_view2, jml_data_waveform);
        remove_dc(data_view3, jml_data_waveform);
        remove_dc(data_view4, jml_data_waveform);
        wavevs->get_data_waveform1(data_view1, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);
        wavevs->get_data_waveform2(data_view2, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);
        wavevs->get_data_waveform3(data_view3, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);
        wavevs->get_data_waveform4(data_view4, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);
        wavevs->update();
    }
    if(tipe_data == 2)
    {
        remove_dc(data_view1, jml_data_waveform);
        remove_dc(data_view2, jml_data_waveform);
        remove_dc(data_view3, jml_data_waveform);
        remove_dc(data_view4, jml_data_waveform);

        if(setting.fase_enabled == 0)
            integral_wf(data_view1,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        if(setting.fase_enabled == 1)
            integrasi(data_view1,data_integrasi1, jml_data_waveform);

        remove_dc(data_integrasi1, jml_data_waveform);

        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }

        wavevs->get_data_waveform1(data_integrasi1, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        if(setting.fase_enabled == 0)
            integral_wf(data_view2,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        if(setting.fase_enabled == 1)
            integrasi(data_view2,data_integrasi1, jml_data_waveform);

        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }
        wavevs->get_data_waveform2(data_integrasi1, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        if(setting.fase_enabled == 0)
            integral_wf(data_view3,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        if(setting.fase_enabled == 1)
            integrasi(data_view3,data_integrasi1, jml_data_waveform);

        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }
        wavevs->get_data_waveform3(data_integrasi1, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        if(setting.fase_enabled == 0)
            integral_wf(data_view4,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        if(setting.fase_enabled == 1)
            integrasi(data_view4,data_integrasi1, jml_data_waveform);

        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }
        wavevs->get_data_waveform4(data_integrasi1, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        wavevs->update();
    }
    if(tipe_data == 3)
    {
        integral_wf(data_view1,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }
        integral_wf(data_integrasi1,data_integrasi2, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi2, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi2, jml_data_waveform);
        }
        wavevs->get_data_waveform1(data_integrasi2, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        integral_wf(data_view2,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi2, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }
        integral_wf(data_integrasi1,data_integrasi2, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi2, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi2, jml_data_waveform);
        }
        wavevs->get_data_waveform2(data_integrasi2, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        integral_wf(data_view3,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }
        integral_wf(data_integrasi1,data_integrasi2, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi2, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi2, jml_data_waveform);
        }
        wavevs->get_data_waveform3(data_integrasi2, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        integral_wf(data_view4,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi1, jml_data_waveform);
        }
        integral_wf(data_integrasi1,data_integrasi2, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi2, jml_data_waveform);
        if(setting.fase_enabled == 0)
        {
            highpass_filter(data_integrasi2, jml_data_waveform);
        }
        wavevs->get_data_waveform4(data_integrasi2, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);

        wavevs->update();
    }
}

void VersusView::on_cb_data_tipe_activated(const QString &arg1)
{
    if(arg1 == "Acceleration")
    {
        tipe_data = 1;
        wavevs->tipe_data = 1;
        ui->cb_sat_accel->setEnabled(true);
        ui->cb_sat_velo->setEnabled(false);
        ui->cb_sat_disp->setEnabled(false);
    }
    else if(arg1 == "Velocity")
    {
        tipe_data = 2;
        wavevs->tipe_data = 2;
        ui->cb_sat_accel->setEnabled(false);
        ui->cb_sat_velo->setEnabled(true);
        ui->cb_sat_disp->setEnabled(false);
    }
    else if(arg1 == "Displacement")
    {
        tipe_data = 3;
        wavevs->tipe_data = 3;
        ui->cb_sat_accel->setEnabled(false);
        ui->cb_sat_velo->setEnabled(false);
        ui->cb_sat_disp->setEnabled(true);
    }
    update_setting();
}

void VersusView::on_cb_sat_accel_activated(const QString &arg1)
{
    if(arg1 == "G")
    {
        tipe_accel = 1;
        wavevs->tipe_sb_y_accel = 1;
    }
    else if(arg1 == "mm/s2")
    {
        tipe_accel = 2;
        wavevs->tipe_sb_y_accel = 2;
    }
    update_setting();
}

void VersusView::on_cb_sat_velo_activated(const QString &arg1)
{
    if(arg1 == "mm/s")
    {
        tipe_velo = 1;
        wavevs->tipe_sb_y_velo = 1;
    }
    else if(arg1 == "IPS")
    {
        tipe_velo = 2;
        wavevs->tipe_sb_y_velo = 2;
    }
    update_setting();
}

void VersusView::on_cb_sat_disp_activated(const QString &arg1)
{
    if(arg1 == "mm")
    {
        tipe_disp = 1;
        wavevs->tipe_sb_y_disp = 1;
    }
    else if(arg1 == "micron")
    {
        tipe_disp = 2;
        wavevs->tipe_sb_y_disp = 2;
    }
    else if(arg1 == "mils")
    {
        tipe_disp = 3;
        wavevs->tipe_sb_y_disp = 3;
    }
    update_setting();
}

void VersusView::on_cb_ymax_activated(const QString &arg1)
{
    if(arg1 == "0.01")
    {
        wavevs->y_max = 0.01;
    }
    else if(arg1 == "0.05")
    {
        wavevs->y_max = 0.05;
    }
    else if(arg1 == "0.1")
    {
        wavevs->y_max = 0.1;
    }
    else if(arg1 == "0.5")
    {
        wavevs->y_max = 0.5;
    }
    else if(arg1 == "1")
    {
        wavevs->y_max = 1;
    }
    else if(arg1 == "5")
    {
        wavevs->y_max = 5;
    }
    else if(arg1 == "10")
    {
        wavevs->y_max = 10;
    }
    else if(arg1 == "50")
    {
        wavevs->y_max = 50;
    }
    else if(arg1 == "100")
    {
        wavevs->y_max = 100;
    }
    else if(arg1 == "500")
    {
        wavevs->y_max = 500;
    }
    else if(arg1 == "1000")
    {
        wavevs->y_max = 1000;
    }
    else if(arg1 == "5000")
    {
        wavevs->y_max = 5000;
    }
    else if(arg1 == "10000")
    {
        wavevs->y_max = 10000;
    }
    else if(arg1 == "50000")
    {
        wavevs->y_max = 50000;
    }
    else if(arg1 == "100000")
    {
        wavevs->y_max = 100000;
    }
    update_setting();
}

void VersusView::on_cb_sat_x_wave_activated(const QString &arg1)
{
    if(arg1 == "ms")
    {
        if(setting.fase_enabled == 0)
        {
            wavevs->tipe_sumbu_x = 1;
        }
        else if(setting.fase_enabled == 1)
        {
            QMessageBox::critical( this, tr( "Setting sumbu X - waveform" ),  tr( "untuk setting dengan triger fasa, sumbu x dalam satuan derajat" ));
            ui->cb_sat_x_wave->setCurrentIndex(1);
            wavevs->tipe_sumbu_x = 2;
        }
    }
    else if(arg1 == "deg")
    {
        if(setting.fase_enabled == 0)
        {
            QMessageBox::critical( this, tr( "Setting sumbu X - waveform" ),  tr( "untuk setting tanpa triger fasa, sumbu x dalam satuan ms" ));
            ui->cb_sat_x_wave->setCurrentIndex(0);
            wavevs->tipe_sumbu_x = 1;
        }
        else if(setting.fase_enabled == 1)
        {
            wavevs->tipe_sumbu_x = 2;
        }
    }
    else if(arg1 == "points")
    {
        wavevs->tipe_sumbu_x = 3;
    }
    update_setting();
}

void VersusView::on_cb_wave_length_activated(const QString &arg1)
{
    if(arg1 == "10%")
    {
        wavevs->persen_tampil = 0.1;
    }
    else if(arg1 == "20%")
    {
        wavevs->persen_tampil = 0.2;
    }
    else if(arg1 == "30%")
    {
        wavevs->persen_tampil = 0.3;
    }
    else if(arg1 == "40%")
    {
        wavevs->persen_tampil = 0.4;
    }
    else if(arg1 == "50%")
    {
        wavevs->persen_tampil = 0.5;
    }
    else if(arg1 == "100%")
    {
        wavevs->persen_tampil = 1.0;
    }
    update_setting();
}

void VersusView::on_cb_window_activated(const QString &arg1)
{
    if(arg1 == "Hanning")
    {
        window_type = 1;
    }
    else if(arg1 == "Blackman")
    {
        window_type = 2;
    }
    else if(arg1 == "Rectangular")
    {
        window_type = 3;
    }
    else if(arg1 == "Hamming")
    {
        window_type = 4;
    }
    update_setting();
}
