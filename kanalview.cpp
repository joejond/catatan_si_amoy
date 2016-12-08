#include "kanalview.h"
#include "ui_kanalview.h"


kanalView::kanalView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::kanalView)
{
    ui->setupUi(this);

    read_setting();

    tipe_spek = 1;
    tipe_data = 1;
    tipe_accel = 1;
    tipe_velo = 1;
    tipe_disp = 1;
    jml_last_masuk = 0;
    last_index_dibaca = 0;
    index_buffer = 0;
    marker_fasa_state = 0;
    auto_scale_Y_state = 1;
    window_type = 1;

    marker_state = 0;
    marker_type = 1;

    color_state = 0;
    proses_state = 0;

    waveform_ms = (int)((setting.fft_lines * 1000) / setting.f_stop);
    jml_data_waveform = 2.56 * (setting.fft_lines);

    data_view = new float[BESAR_DATA_RECIP]();
    temp_filter = new double[BESAR_DATA_RECIP]();
    window_coef = new float[BESAR_DATA_RECIP]();
    buffer = new float[BESAR_DATA_BIG]();
    data_integrasi1 = new float[BESAR_DATA_RECIP]();
    data_integrasi2 = new float[BESAR_DATA_RECIP]();
    geser_delay = new float[BESAR_DATA_RECIP]();
    geser_system = new float[BESAR_DATA_RECIP]();

    wave = new Waveform;
    spektrum = new Spektrum;
    wtf = new WaterFall;
    polar = new Polar;

    //context menu
    create_contextMenu();

    timer_wtf = new QTimer();
    connect(timer_wtf, SIGNAL(timeout()), this, SLOT(tim_wtf()));

    timer_proses = new QTimer();
    connect(timer_proses, SIGNAL(timeout()), this, SLOT(proses_view()));

    //init form, spektrum, waveform & waterfall
    if(setting.fase_enabled == 0)
    {
        ui->vl_spektrum->addWidget(spektrum);
        tipe_spek = 1;
        wave->tipe_sumbu_x = 1;
        ui->cb_sat_x_wave->setCurrentIndex(0);
        ui->cb_wave_length->setEnabled(true);
    }
    else if(setting.fase_enabled == 1)
    {
        ui->vl_spektrum->addWidget(polar);
        tipe_spek = 3;
        wave->tipe_sumbu_x = 2;
        ui->cb_sat_x_wave->setCurrentIndex(1);
        ui->cb_wave_length->setCurrentIndex(5);
        ui->cb_wave_length->setDisabled(true);
    }
    ui->vl_wave->addWidget(wave);

    ui->cb_averages->setCurrentIndex(3);

    ui->cb_sat_accel->setEnabled(true);
    ui->cb_sat_velo->setEnabled(false);
    ui->cb_sat_disp->setEnabled(false);

    hitung_param_view();

    wave->y_max = ui->cb_ymax->currentText().toFloat();
    spektrum->y_max = ui->cb_ymax_spek->currentText().toFloat();
}

kanalView::~kanalView()
{
    delete[] data_view;
    delete[] temp_filter;
    delete[] window_coef;
    delete[] buffer;
    delete[] data_integrasi1;
    delete[] data_integrasi2;
    delete[] geser_delay;
    delete[] geser_system;
    delete ui;
}

void kanalView::read_setting()
{
    QString pth = "setting.ini";
    QSettings settings(pth, QSettings::IniFormat);

    sprintf(setting.kanal_use, "%s", settings.value("kanal_use").toString().toAscii().data());
    setting.kanal_1 = settings.value("kanal_1").toInt();
    setting.kanal_2 = settings.value("kanal_2").toInt();
    setting.kanal_3 = settings.value("kanal_3").toInt();
    setting.kanal_4 = settings.value("kanal_4").toInt();

    setting.fase_enabled = settings.value("fase_enable").toInt();

    setting.acc_sencitivity1 = settings.value("acc_sencitivity1").toFloat();
    setting.acc_sencitivity2 = settings.value("acc_sencitivity2").toFloat();
    setting.acc_sencitivity3 = settings.value("acc_sencitivity3").toFloat();
    setting.acc_sencitivity4 = settings.value("acc_sencitivity4").toFloat();

    setting.view_lines1 = settings.value("view_lines1").toInt();
    setting.view_lines2 = settings.value("view_lines2").toInt();
    setting.view_lines3 = settings.value("view_lines3").toInt();
    setting.view_lines4 = settings.value("view_lines4").toInt();

    setting.client_status = settings.value("client_status").toInt();

    setting.unit_acc = settings.value("Unit_acc").toInt();
    setting.unit_velo = settings.value("Unit_velo").toInt();
    setting.unit_disp = settings.value("Unit_disp").toInt();
    setting.unit_frek = settings.value("Unit_frek").toInt();

    setting.window          = settings.value("window").toInt();
    setting.PP                  = settings.value("PP").toInt();
    setting.lebar_waveform  = settings.value("lebar_waveform").toInt();
    setting.waveform_x      = settings.value("waveform_x").toInt();
    setting.waveform_y      = settings.value("waveform_y").toInt();

    setting.f_start = settings.value("f_start").toInt();
    setting.f_stop = settings.value("f_stop").toInt();

    setting.chart_mode      = settings.value("chart_mode").toInt();

    // baca setting simulasi
    setting.mode_simulasi   = settings.value("mode_simulasi").toInt();
    setting.tipe_sinyal    = settings.value("tipe_sinyal").toInt();
}

void kanalView::start_proses_view()
{
    read_setting();
    update_setting();

    if(kanal_id == 1)
        acc_sens = setting.acc_sencitivity1;
    if(kanal_id == 2)
        acc_sens = setting.acc_sencitivity2;
    if(kanal_id == 3)
        acc_sens = setting.acc_sencitivity3;
    if(kanal_id == 4)
        acc_sens = setting.acc_sencitivity4;

    last_index_dibaca = 0;
    jml_last_masuk = 0;

    // global view parameters
    waveform_ms = (int)((setting.fft_lines * 1000) / setting.f_stop);
    jml_data_waveform = 2.56 * (setting.fft_lines);

    //delay adc
    ms_delay = (int)(39000/(setting.f_stop * 2.56));

    qDebug() << "ms_delay" << ms_delay;


    for(i = 0; i < (BESAR_DATA_RECIP); i++)
    {
        data_view[i] = 0.0;
    }

    qDebug() << "f-start" << setting.f_start;
    qDebug() << "s-rate" << setting.f_stop*2.56;

    if(window_type == 1)
        buat_hanning( window_coef, jml_data_waveform );
    if(window_type == 2)
        buat_blackman( window_coef, jml_data_waveform );
    if(window_type == 3)
        buat_rectangular( window_coef, jml_data_waveform );
    if(window_type == 4)
        buat_hamming( window_coef, jml_data_waveform );
    siapkan_filter( (setting.f_stop * 2.56), setting.f_start, setting.f_stop, BAND_PASS);

    len_highpass = 121; // 251
    filter_hp = create1TransSinc( len_highpass, ((double)(setting.f_start) * 1.0), ((double)(setting.f_stop) * 2.56 * 1.0), HIGH_PASS);

    qDebug() << "start proses view sampe sini";
    hitung_param_view();
    jml_last_masuk = 0;
    if(proses_state == 0)
    {
        int ms_proses = setting.fft_lines * 1000 / setting.f_stop;

        qDebug()  << "ms_proses" << ms_proses;
        timer_proses->start(ms_proses / 2);
        timer_wtf->start(wtf_ms);
        qDebug() << "view diproses";
    }
    else if(proses_state == 1)
    {
        qDebug() << "sudah jalan proses view";
    }
    proses_state = 1;
    wave->fasa_enable = setting.fase_enabled;

    wave->reset_data();
    wave->update();

    if(setting.fase_enabled == 0)
    {
        ui->vl_spektrum->removeWidget(polar);
        ui->vl_spektrum->removeWidget(wtf);
        polar->hide();
        wtf->hide();
        ui->vl_spektrum->addWidget(spektrum);
        spektrum->show();
        ui->vl_spektrum->update();
        tipe_spek = 1;
        wave->tipe_sumbu_x = 1;
        ui->cb_sat_x_wave->setCurrentIndex(0);
        ui->cb_wave_length->setEnabled(true);
    }
    else if(setting.fase_enabled == 1)
    {
        ui->vl_spektrum->removeWidget(spektrum);
        ui->vl_spektrum->removeWidget(wtf);
        spektrum->hide();
        wtf->hide();
        ui->vl_spektrum->addWidget(polar);
        polar->show();
        ui->vl_spektrum->update();
        tipe_spek = 3;
        wave->tipe_sumbu_x = 2;
        ui->cb_sat_x_wave->setCurrentIndex(1);
        ui->cb_wave_length->setCurrentIndex(5);
        ui->cb_wave_length->setDisabled(true);
    }

    if(tipe_spek == 1)
    {
        spektrum->reset_data();
        spektrum->update();
    }
    if(tipe_spek == 2)
    {
        wtf->reset_data();
        wtf->update();
    }
}

void kanalView::stop_proses_view()
{
    qDebug() << "view proses stop";
    timer_proses->stop();
    proses_state = 0;
}

void kanalView::hitung_param_view()
{
    if(setting.fase_enabled == 0)
        faktor_filter = 1.5;
    if(setting.fase_enabled == 1)
        faktor_filter = 1;

    wave->get_waveform_param(jml_data_waveform/faktor_filter , waveform_ms/faktor_filter);
    spektrum->get_spektrum_param();

    wave->update_y_scale();
    wave->update();

    spektrum->update_y_scale();
    spektrum->update();
}

void kanalView::proses_view()
{
    //jika filter highpass enable, jumlah data ditambah supaya tidak muncul buntut...
    if(setting.fase_enabled == 0)
        faktor_filter = 1.5;
    if(setting.fase_enabled == 1)
        faktor_filter = 1;
    if(setting.fase_enabled == 0)
        memcpy(data_view, geser_delay, BESAR_DATA_RECIP);

    if(setting.fase_enabled == 1)
    {        
        // delay adc
        poin_delay_adc = jml_data_waveform * ms_delay/waveform_ms;
        for(i = (jml_data_waveform - poin_delay_adc); i < jml_data_waveform; i++)
            geser_system[i] = geser_delay[i - (jml_data_waveform - poin_delay_adc)];
        for(i = 0; i < (jml_data_waveform - poin_delay_adc); i++)
            geser_system[i] = geser_delay[i+poin_delay_adc];

        poin_delay_system =  jml_data_waveform / 7.5;

        for(i = (jml_data_waveform - poin_delay_system); i < jml_data_waveform; i++)
            data_view[i] = geser_system[i - (jml_data_waveform - poin_delay_system)];
        for(i = 0; i < (jml_data_waveform - poin_delay_system); i++)
            data_view[i] = geser_system[i+poin_delay_system];
    }

    wave->get_waveform_param(jml_data_waveform/faktor_filter , waveform_ms/faktor_filter);

    if(tipe_data == 1) //acceleration
    {
        remove_dc(data_view, jml_data_waveform);
        if(setting.fase_enabled == 0)
            highpass_filter(data_view, jml_data_waveform);
        wave->get_data_waveform(data_view, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);
        wave->update();
        if(setting.fase_enabled == 0)
        {
            spektrum->get_data_spektrum(data_view);
            spektrum->update();
        }
        else if(setting.fase_enabled == 1)
        {
            polar->get_data_polar(data_view, jml_data_waveform);
            polar->update();
        }
    }
    if(tipe_data == 2) //velocity
    {
        remove_dc(data_view, jml_data_waveform);
        if(setting.fase_enabled == 0)
            integral_wf(data_view,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        if(setting.fase_enabled == 1)
            integrasi(data_view,data_integrasi1, jml_data_waveform);
        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
            highpass_filter(data_integrasi1, jml_data_waveform);
        wave->get_data_waveform(data_integrasi1, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);
        wave->update();
        if(setting.fase_enabled == 0)
        {
            spektrum->get_data_spektrum(data_integrasi1);
            spektrum->update();
        }
        else if(setting.fase_enabled == 1)
        {
            polar->get_data_polar(data_integrasi1, jml_data_waveform);
            polar->update();
        }
    }
    if(tipe_data == 3) //displacement
    {
        remove_dc(data_view, jml_data_waveform);
        integral_wf(data_view,data_integrasi1, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi1, jml_data_waveform);
        if(setting.fase_enabled == 0)
            highpass_filter(data_integrasi1, jml_data_waveform);
        integral_wf(data_integrasi1,data_integrasi2, jml_data_waveform, setting.f_stop*2.56);
        remove_dc(data_integrasi2, jml_data_waveform);
        if(setting.fase_enabled == 0)
            highpass_filter(data_integrasi2, jml_data_waveform);
        wave->get_data_waveform(data_integrasi2, jml_data_waveform/faktor_filter, waveform_ms/faktor_filter);
        wave->update();
        if(setting.fase_enabled == 0)
        {
            spektrum->get_data_spektrum(data_integrasi2);
            spektrum->update();
        }
        else if(setting.fase_enabled == 1)
        {
            polar->get_data_polar(data_integrasi2, jml_data_waveform);
            polar->update();
        }
    }
}

void kanalView::create_contextMenu()
{
    menuPop = new QMenu();

    menuPop->addSeparator();
    SubMenuCopy = menuPop->addMenu("Copy Grafik");
    menuCopyDataWave = SubMenuCopy->addAction("data - waveform");
    menuCopyImageWave = SubMenuCopy->addAction("image - waveform");
    menuCopyDataSpek = SubMenuCopy->addAction("data - spektrum");
    menuCopyImageSpek = SubMenuCopy->addAction("image - spektrum");
    menuCopyImageWtf = SubMenuCopy->addAction("image - waterfall");
    marker_on = menuPop->addAction("spectrum marker ON");
    marker_on->setCheckable(true);
    Sub_marker_type = menuPop->addMenu("spectrum marker type");
    marker_free = Sub_marker_type->addAction("free marker");
    marker_free->setCheckable(true);
    marker_max = Sub_marker_type->addAction("maximum marker");
    marker_max->setCheckable(true);
    marker_harmonic = Sub_marker_type->addAction("harmonic marker");
    marker_harmonic->setCheckable(true);
    marker_fasa_on = menuPop->addAction("phase marker ON");
    marker_fasa_on->setCheckable(true);
    auto_scale_y = menuPop->addAction("Auto scale Y OFF");
    auto_scale_y->setCheckable(true);

    marker_free->setChecked(true);

    ui->kanal_chart_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->kanal_chart_view,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popMenu(QPoint)));

    connect(menuCopyImageWave, SIGNAL(triggered()), this, SLOT(view_copy_image_wave()));
    connect(menuCopyDataWave, SIGNAL(triggered()), this, SLOT(view_copy_data_wave()));
    connect(menuCopyImageSpek, SIGNAL(triggered()), this, SLOT(view_copy_image_spek()));
    connect(menuCopyDataSpek, SIGNAL(triggered()), this, SLOT(view_copy_data_spek()));
    connect(menuCopyImageWtf, SIGNAL(triggered()), this, SLOT(view_copy_image_wtf()));

    connect(marker_on, SIGNAL(triggered()), this, SLOT(marker_state_change()));
    connect(marker_free, SIGNAL(triggered()), this, SLOT(marker_free_on()));
    connect(marker_max, SIGNAL(triggered()), this, SLOT(marker_max_on()));
    connect(marker_harmonic, SIGNAL(triggered()), this, SLOT(marker_harmonic_on()));

    connect(marker_fasa_on, SIGNAL(triggered()), this, SLOT(marker_fasa_change()));

    connect(auto_scale_y, SIGNAL(triggered()), this, SLOT(auto_scale_Y_change()));
}

void kanalView::popMenu(const QPoint &pos)
{
    menuPop->popup(pos);
    menuPop->exec(QCursor::pos());
}

void kanalView::update_setting()
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
    wave->update_y_scale();
    wave->update();

    spektrum->update_y_scale();
    spektrum->update();    
}

void kanalView::view_copy_image_wave()
{
    wave->copy_image();
}

void kanalView::view_copy_data_wave()
{
    wave->copy_data();
}

void kanalView::view_copy_image_spek()
{
    spektrum->copy_image();
}

void kanalView::view_copy_data_spek()
{
    spektrum->copy_data();
}

void kanalView::view_copy_image_wtf()
{
    wtf->copy_image();
}

void kanalView::marker_state_change()
{
    if(marker_state == 0)
    {
        marker_state = 1;
        marker_on->setChecked(true);
        spektrum->marker_state = 1;
    }
    else if(marker_state == 1)
    {
        marker_state = 0;
        marker_on->setChecked(false);
        spektrum->marker_state = 0;
    }
    update_setting();
}

void kanalView::marker_fasa_change()
{
    if(marker_fasa_state == 0)
    {
        marker_fasa_state = 1;
        marker_fasa_on->setChecked(true);
        wave->marker_fasa_state = 1;
    }
    else if(marker_fasa_state == 1)
    {
        marker_fasa_state = 0;
        marker_fasa_on->setChecked(false);
        wave->marker_fasa_state = 0;
    }
    update_setting();
    wave->update();
}

void kanalView::auto_scale_Y_change()
{
    if(auto_scale_Y_state == 0)
    {
        auto_scale_Y_state = 1;
        wave->auto_y = 1;
        spektrum->auto_y = 1;
    }
    else if(auto_scale_Y_state == 1)
    {
        auto_scale_Y_state = 0;
        wave->auto_y = 0;
        spektrum->auto_y = 0;
    }
    update_setting();
}

void kanalView::marker_free_on()
{
    marker_free->setChecked(true);
    marker_max->setChecked(false);
    marker_harmonic->setChecked(false);
    spektrum->marker_type = 1;
}

void kanalView::marker_max_on()
{
    marker_free->setChecked(false);
    marker_max->setChecked(true);
    marker_harmonic->setChecked(false);
    spektrum->marker_type = 2;
}

void kanalView::marker_harmonic_on()
{
    marker_free->setChecked(false);
    marker_max->setChecked(false);
    marker_harmonic->setChecked(true);
    spektrum->marker_type = 3;
}

void kanalView::remove_dc(float * data_kanal, int jml)
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

void kanalView::highpass_filter(float *data_kanal, int jml)
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

void kanalView::integral_wf(float *in, float *out, int jum, float s_rate)
{
    for (i=1; i<jum; i++)
        in[i] = (double) (in[i] + in[i-1]);

    for (i=1; i<jum; i++)
        out[i] = in[i] * (1.000 / (s_rate * 1.0));
}

void kanalView::get_data_kanal(float *data, int jml, int ms_data)
{
    memcpy(geser_delay, data, BESAR_DATA_RECIP);
    jml_data_waveform = jml;
    waveform_ms = ms_data;

    remove_dc(geser_delay, jml_data_waveform);

    for(x = 0; x < jml_data_waveform; x++)
        geser_delay[x] = geser_delay[x] * acc_sens * conv;
}

void kanalView::tim_wtf()
{
    wtf->update_wtf(spektrum->hasil_avrg, spektrum->tampilkan_points);
    update_setting();
    wtf->update();
}

void kanalView::reset_data()
{
    for(int x = 0; x < BESAR_DATA_BIG; x++)
    {
        buffer[x] = 0.0;
    }
}

void kanalView::on_cb_window_activated(const QString &arg1)
{
    if(arg1 == "Hanning")
    {
        window_type = 1;
        spektrum->tipe_window = 1;
    }
    else if(arg1 == "Blackman")
    {
        window_type = 2;
        spektrum->tipe_window = 2;
    }
    else if(arg1 == "Rectangular")
    {
        window_type = 3;
        spektrum->tipe_window = 3;
    }
    else if(arg1 == "Hamming")
    {
        window_type = 4;
        spektrum->tipe_window = 4;
    }
    update_setting();
}

void kanalView::on_cb_data_tipe_activated(const QString &arg1)
{
    if(arg1 == "Acceleration")
    {
        tipe_data = 1;
        spektrum->tipe_data = 1;
        wave->tipe_data = 1;
        ui->cb_sat_accel->setEnabled(true);
        ui->cb_sat_velo->setEnabled(false);
        ui->cb_sat_disp->setEnabled(false);
    }
    else if(arg1 == "Velocity")
    {
        tipe_data = 2;
        spektrum->tipe_data = 2;
        wave->tipe_data = 2;
        ui->cb_sat_accel->setEnabled(false);
        ui->cb_sat_velo->setEnabled(true);
        ui->cb_sat_disp->setEnabled(false);
    }
    else if(arg1 == "Displacement")
    {
        tipe_data = 3;
        spektrum->tipe_data = 3;
        wave->tipe_data = 3;
        ui->cb_sat_accel->setEnabled(false);
        ui->cb_sat_velo->setEnabled(false);
        ui->cb_sat_disp->setEnabled(true);
    }
    update_setting();
}

void kanalView::on_cb_sat_accel_activated(const QString &arg1)
{
    if(arg1 == "G")
    {
        tipe_accel = 1;
        wave->tipe_sb_y_accel = 1;
        spektrum->tipe_sb_y_accel = 1;
    }
    else if(arg1 == "mm/s2")
    {
        tipe_accel = 2;
        wave->tipe_sb_y_accel = 2;
        spektrum->tipe_sb_y_accel = 2;
    }
    update_setting();
}

void kanalView::on_cb_sat_velo_activated(const QString &arg1)
{
    if(arg1 == "mm/s")
    {
        tipe_velo = 1;
        wave->tipe_sb_y_velo = 1;
        spektrum->tipe_sb_y_velo = 1;
    }
    else if(arg1 == "IPS")
    {
        tipe_velo = 2;
        wave->tipe_sb_y_velo = 2;
        spektrum->tipe_sb_y_velo = 2;
    }
    update_setting();
}

void kanalView::on_cb_sat_disp_activated(const QString &arg1)
{
    if(arg1 == "mm")
    {
        tipe_disp = 1;
        wave->tipe_sb_y_disp = 1;
        spektrum->tipe_sb_y_disp = 1;
    }
    else if(arg1 == "micron")
    {
        tipe_disp = 2;
        wave->tipe_sb_y_disp = 2;
        spektrum->tipe_sb_y_disp = 2;
    }
    else if(arg1 == "mils")
    {
        tipe_disp = 3;
        wave->tipe_sb_y_disp = 3;
        spektrum->tipe_sb_y_disp = 3;
    }
    update_setting();
}

void kanalView::on_cb_averages_activated(const QString &arg1)
{
    if(arg1 == "1")
    {
        spektrum->num_avrg = 1;
    }
    else if(arg1 == "2")
    {
        spektrum->num_avrg = 2;
    }
    else if(arg1 == "3")
    {
        spektrum->num_avrg = 3;
    }
    else if(arg1 == "4")
    {
        spektrum->num_avrg = 4;
    }
    update_setting();
}

void kanalView::on_cb_sat_x_wave_activated(const QString &arg1)
{
    if(arg1 == "ms")
    {
        if(setting.fase_enabled == 0)
        {
            wave->tipe_sumbu_x = 1;
        }
        else if(setting.fase_enabled == 1)
        {
            QMessageBox::critical( this, tr( "Setting sumbu X - waveform" ),  tr( "untuk setting dengan triger fasa, sumbu x dalam satuan derajat" ));
            ui->cb_sat_x_wave->setCurrentIndex(1);
            wave->tipe_sumbu_x = 2;
        }
    }
    else if(arg1 == "deg")
    {
        if(setting.fase_enabled == 0)
        {
            QMessageBox::critical( this, tr( "Setting sumbu X - waveform" ),  tr( "untuk setting tanpa triger fasa, sumbu x dalam satuan ms" ));
            ui->cb_sat_x_wave->setCurrentIndex(0);
            wave->tipe_sumbu_x = 1;
        }
        else if(setting.fase_enabled == 1)
        {
            wave->tipe_sumbu_x = 2;
        }
    }
    else if(arg1 == "points")
    {
        wave->tipe_sumbu_x = 3;
    }
    update_setting();
}

void kanalView::on_cb_sat_x_spek_activated(const QString &arg1)
{
    if(arg1 == "Hz")
    {
        spektrum->tipe_sumbu_x = 1;
    }
    else if(arg1 == "cpm")
    {
        spektrum->tipe_sumbu_x = 2;
    }
    else if(arg1 == "points")
    {
        spektrum->tipe_sumbu_x = 3;
    }
    update_setting();
}

void kanalView::on_cb_ymax_activated(const QString &arg1)
{
    if(arg1 == "0.01")
    {
        wave->y_max = 0.01;
    }
    else if(arg1 == "0.05")
    {
        wave->y_max = 0.05;
    }
    else if(arg1 == "0.1")
    {
        wave->y_max = 0.1;
    }
    else if(arg1 == "0.5")
    {
        wave->y_max = 0.5;
    }
    else if(arg1 == "1")
    {
        wave->y_max = 1;
    }
    else if(arg1 == "5")
    {
        wave->y_max = 5;
    }
    else if(arg1 == "10")
    {
        wave->y_max = 10;
    }
    else if(arg1 == "50")
    {
        wave->y_max = 50;
    }
    else if(arg1 == "100")
    {
        wave->y_max = 100;
    }
    else if(arg1 == "500")
    {
        wave->y_max = 500;
    }
    else if(arg1 == "1000")
    {
        wave->y_max = 1000;
    }
    else if(arg1 == "5000")
    {
        wave->y_max = 5000;
    }
    else if(arg1 == "10000")
    {
        wave->y_max = 10000;
    }
    else if(arg1 == "50000")
    {
        wave->y_max = 50000;
    }
    else if(arg1 == "100000")
    {
        wave->y_max = 100000;
    }
    update_setting();
}

void kanalView::on_cb_wave_length_activated(const QString &arg1)
{
    if(arg1 == "10%")
    {
        wave->persen_tampil = 0.1;
    }
    else if(arg1 == "20%")
    {
        wave->persen_tampil = 0.2;
    }
    else if(arg1 == "30%")
    {
        wave->persen_tampil = 0.3;
    }
    else if(arg1 == "40%")
    {
        wave->persen_tampil = 0.4;
    }
    else if(arg1 == "50%")
    {
        wave->persen_tampil = 0.5;
    }
    else if(arg1 == "100%")
    {
        wave->persen_tampil = 1.0;
    }
    update_setting();
}

void kanalView::on_cb_ymax_spek_activated(const QString &arg1)
{
    if(arg1 == "0.01")
    {
        spektrum->y_max = 0.01;
    }
    else if(arg1 == "0.05")
    {
        spektrum->y_max = 0.05;
    }
    else if(arg1 == "0.1")
    {
        spektrum->y_max = 0.1;
    }
    else if(arg1 == "0.5")
    {
        spektrum->y_max = 0.5;
    }
    else if(arg1 == "1")
    {
        spektrum->y_max = 1;
    }
    else if(arg1 == "5")
    {
        spektrum->y_max = 5;
    }
    else if(arg1 == "10")
    {
        spektrum->y_max = 10;
    }
    else if(arg1 == "50")
    {
        spektrum->y_max = 50;
    }
    else if(arg1 == "100")
    {
        spektrum->y_max = 100;
    }
    else if(arg1 == "500")
    {
        spektrum->y_max = 500;
    }
    else if(arg1 == "1000")
    {
        spektrum->y_max = 1000;
    }
    else if(arg1 == "5000")
    {
        spektrum->y_max = 5000;
    }
    else if(arg1 == "10000")
    {
        spektrum->y_max = 10000;
    }
    else if(arg1 == "50000")
    {
        spektrum->y_max = 50000;
    }
    else if(arg1 == "100000")
    {
        spektrum->y_max = 100000;
    }
    update_setting();
}

void kanalView::on_cb_wtf_intv_activated(const QString &arg1)
{
    if(arg1 == "1")
    {
        wtf_ms = 1000;
    }
    else if(arg1 == "5")
    {
        wtf_ms = 5000;
    }
    else if(arg1 == "5")
    {
        wtf_ms = 5000;
    }
    else if(arg1 == "10")
    {
        wtf_ms = 10000;
    }
    else if(arg1 == "30")
    {
        wtf_ms = 30000;
    }
    else if(arg1 == "60")
    {
        wtf_ms = 60000;
    }
    else if(arg1 == "120")
    {
        wtf_ms = 120000;
    }
}

void kanalView::on_cb_spek_tipe_activated(const QString &arg1)
{
    if(arg1 == "Single")
    {
        ui->vl_spektrum->removeWidget(polar);
        ui->vl_spektrum->removeWidget(wtf);
        polar->hide();
        wtf->hide();
        ui->vl_spektrum->addWidget(spektrum);
        spektrum->show();
        ui->vl_spektrum->update();
        tipe_spek = 1;
    }
    else if(arg1 == "Waterfall")
    {
        ui->vl_spektrum->removeWidget(polar);
        ui->vl_spektrum->removeWidget(spektrum);
        polar->hide();
        spektrum->hide();
        ui->vl_spektrum->addWidget(wtf);
        wtf->show();
        ui->vl_spektrum->update();
        tipe_spek = 2;
    }
}
