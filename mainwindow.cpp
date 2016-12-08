/*
  Data akuisisi untuk program motor bakar
  furkan jadid
  daun biru engineering

  18 Juli 2011, ITB Bandung, Lab motor bakar

  25 Juli 2011,
  dikasih timer, misalnya untuk paket UDP yang tidak sampai2

  31 Juli 2012
  up & running lagi di motor bakar

  2 Sept 2012
  Dijadikan qt_simul versi 2.0
  Dimodifikasi besar untuk vibration simulator PLN Diklat Suralaya

  6 Sept 2012
  Model pengiriman data banyak berubah dibanding versi 1.3 (motor bakar).

  Mode waveform mestinya bisa seperti osiloskop. Lebar/sempitnya waktu bisa
  diatur on-thefly. Jika mode phase enable, tidak bisa diatur, karena fix trigernya
  kecuali dipersempit ?

  16 Nov 2012
  Mulai digabung dengan modul vibrasinya.
  Ditambahkan juga mode simulasi (dummy sinyal)
  struct tt_ulang dihilangkan saja.

*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

#define VERSI   "3.0"

struct t_setting setting;
struct t_param_vib par_vib;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString st;
    int i;

    modul_state = 0;

    hit = 0;

    ui->setupUi(this);

    st.sprintf("%s V%s (Build %s %s)", NAMA_APLIKASI, VERSI, __DATE__, __TIME__);
    this->setWindowTitle(st);

    read_setting();

    udpSocket = new QUdpSocket(this);
    host1 = "192.168.1.178";
    port1 = 5004;
    jum_buf = 50;

    QObject::connect(udpSocket, SIGNAL(readyRead()), this, SLOT(ada_udp()));

    for (i=0; i<LOGGER_KANAL; i++)
    {
        data_kanal[i] = new float[BESAR_DATA_RECIP + 10]();
    }

    belum_show = 1;
    QApplication::processEvents();

    nomer_kirim = 0;
    count_udp_kirim = 0;

    tim = new QTimer();
    connect(tim, SIGNAL(timeout()), this, SLOT(tim_update()));

    kanal_view_state[0] = false;
    kanal_view_state[1] = false;
    kanal_view_state[2] = false;
    kanal_view_state[3] = false;

    versus_view_state = false;
}

MainWindow::~MainWindow()
{
    write_setting();

    for (int i=0; i<LOGGER_KANAL; i++)
    {
        delete[] data_kanal[i];
    }
    delete ui;
}

void MainWindow::decode_kanal()
{
    int kanal_diminta = 0;
    jum_kanal_aktif = 0;

    if (setting.kanal_1 == 1)
    {
        jum_kanal_aktif++;
        kanal_diminta |= 0x01;
    }

    if (setting.kanal_2 == 1)
    {
        jum_kanal_aktif++;
        kanal_diminta |= 0x02;
    }

    if (setting.kanal_3 == 1)
    {
        jum_kanal_aktif++;
        kanal_diminta |= 0x04;
    }

    if (setting.kanal_4 == 1)
    {
        jum_kanal_aktif++;
        kanal_diminta |= 0x08;
    }

    ulang_g.state = kanal_diminta;
    //qDebug("Kanal akfit %d", jum_kanal_aktif);
}

/* MULAI START REQUEST DATA */
void MainWindow::on_actionStart_triggered()
{
    modul_state = 1;
    kanal_view_start();
    versus_view_start();

    int jml_data;

    qDebug() << "\n=== mulai ambil data ====";
    qDebug() << "\nf-stop =" << setting.f_stop;
    qDebug() << "lines = " << setting.fft_lines;
    float sam_rate = (setting.f_stop * 2.56);
    qDebug() <<__FUNCTION__ <<"() : sampling rate  (2.56 x f-stop) =" << sam_rate;
    int lebar_wv = (int)((setting.fft_lines * 1000) / setting.f_stop);
    qDebug() <<__FUNCTION__ <<"() : kebutuhan lebar waveform  (lines / f-stop x 1000) ="<< lebar_wv  << "(ms)";
    if(setting.fase_enabled == 0)
    {
        jml_data = setting.fft_lines * 2.56*1.5;
        setting.lebar_waveform =  lebar_wv *1.5;
    }
    if(setting.fase_enabled == 1)
    {
        jml_data = setting.fft_lines * 2.56;
        setting.lebar_waveform =  lebar_wv;
    }
    qDebug() <<__FUNCTION__ <<"() : kebutuhan jumlah data (sam_rate x lebar_wf / 1000)="<< jml_data ;


    hitung_param_vibrasi( &setting, &par_vib);
    memcpy(ulang_g.buf, &par_vib, sizeof (par_vib));

    //toolbar setting
    ui->actionStart->setDisabled( true );
    ui->actionStop->setEnabled( true );

    tim_count = 0;
    count_udp = 0;
    count_data_big = 0;
    qDebug("\nKonek UDP, tim_count %d", tim_count);

    M_bandpass = 128;

    bandpass_koef = (double *) malloc ( M_bandpass * 2 * sizeof (double));
    hitung_koef_IIR_highpass((setting.f_stop * 2.56), setting.f_start);

    // hitung dulu ms refresh rate, sebaiknya lebih dari 100 ms
    // berdasarkan lebar waveform yang diinginkan,
    // misalnya jika waveform adalah 500 ms,
    // maka refresh ratenya adalah 500 - 5 = 595 ms
    // supaya tidak ada yang miss saja.

    ms_refresh = setting.lebar_waveform - 5;
    if (ms_refresh < 100 ) ms_refresh = 100;
    qDebug() << "ms_refresh" << ms_refresh;

    udpSocket->connectToHost( setting.modul_ip , port1);
    {
        sprintf(ulang_g.head, "getdata");

        ulang_g.state = MULAI_KONEK;
        ulang_g.jum_sample = par_vib.len_data_wf;
        ulang_g.pos_data=0;

        //qDebug("len_data_wf %d", ulang_g.jum_sample);

        if (setting.fase_enabled == 1)
        {
            qDebug("Enable FASE !");
            ulang_g.fase_enabled = 1;
        }
        else
        {
            ulang_g.fase_enabled = 0;
        }

        /* supaya dikirim dari urutan nol / awal */
        ulang_g.urutan = 0;
        decode_kanal();

        udpSocket->write( (char *) &ulang_g, sizeof (ulang_g) );

        //udpSocket->write("getdata");
        nomer_kirim = 0;
        valid_flag = 1;

        memset( (char *) &paket_hilang, 0, sizeof (paket_hilang));
        jum_hilang = 0;
        sedang_hilang = 0;

        count_udp_kirim++;

        /* jika 200 ms tidak ada respon, maka dikirim lagi */
        tim->start(200);
    }

    hit = 0;
}

void MainWindow::on_actionStop_triggered()
{
    modul_state = 0;
    //toolbar setting
    ui->actionParameter->setEnabled(true);
    ui->actionMode_Simulasi->setEnabled(true);
    ui->actionModul_Akuisisi->setEnabled(true);

    udpSocket->close();
    ui->actionStart->setEnabled( true );

    count_udp_kirim = 0;
    tim->stop();

    kanal_view_stop();
    versus_view_stop();

    count_data_big = 0;

}

/* fungsi saat ada paket udp datang */
void MainWindow::ada_udp(void)
{
    QString s;

    int kanal_array;

    tim->stop();

    /* dibaca saja seperlunya */
    QByteArray buf_temp = udpSocket->read(sizeof (struct tt_req));
    //qDebug("%s(), size %d", __FUNCTION__, buf_temp.size());

    struct tt_req *req;
    req = (struct tt_req *) buf_temp.data();

    /* simpan dulu total paket pada req global */
    if (req->urutan == 0)
    {
        memcpy( (char *) &req_g, buf_temp.data(), sizeof (req_g));
        req_g.lost_paket = 0;
    }

    kanal_array = req->kanal - 1;
    if (kanal_array > LOGGER_KANAL || kanal_array < 0)
    {
        qDebug("Kanal error !");
        req->lost_paket++;
        return;
    }

    /* counter urutan vs nomer kirim */
    if (req->urutan != nomer_kirim) req_g.lost_paket++;
    nomer_kirim++;

    /* masukkan data pada kanal yang dimaksud */

    memcpy( &data_kanal[ kanal_array ] [ (req->urut_kanal * BESAR_PAKET_F)  ], req->buf, BESAR_PAKET );

    if (req->state == KIRIM_SELESAI)
    {

        if (req->last_kanal == jum_kanal_aktif)
        {
            // menyimpan data pada buffer besar
            count_data_big += req_g.jum_sample;
            if (count_data_big > BESAR_DATA_BIG) count_data_big = 0;

            //qDebug() <<__FUNCTION__ <<"() : req_g.jum_sample = " << req_g.jum_sample;
            //qDebug() <<__FUNCTION__ << "() : req->jum_sample" << req->jum_sample;

            nomer_kirim = 0;
            req_g.pos_data += req_g.jum_sample;

            //qDebug("Selesai, lost %d, bat %d, pos %d", req_g.lost_paket, req_g.bat_level, ulang_g.pos_data);

            /* jika ini slave, maka disesuikan dengan master / modul */
            if (req->flag == 2)
            {
                //qDebug("%d, %f, %d", req->sampling_rate, req->pecahan_waveform, req->jum_sample);

                req_g.jum_sample = req->jum_sample;
                req_g.pecahan_waveform = req->pecahan_waveform;

                par_vib.pecahan_waveform = req->pecahan_waveform;
                par_vib.req_sampling_rate = req->sampling_rate;
                par_vib.len_data_wf = req->jum_sample;
            }

            if (req->fase_enabled)
            {
                //qDebug("data per siklus (Fase enable) %d", req->jum_sample);
                req_g.jum_sample = req->jum_sample;
                setting.lebar_waveform = req_g.jum_sample * par_vib.pecahan_waveform;
                hitung_param_vibrasi( &setting, &par_vib);
            }

            if(setting.kanal_1 == 1 && kanal_view_state[0] == 1)
                kanal_view[0]->get_data_kanal(data_kanal[0], req_g.jum_sample, setting.lebar_waveform);
            if(setting.kanal_2 == 1 && kanal_view_state[1] == 1)
                kanal_view[1]->get_data_kanal(data_kanal[1], req_g.jum_sample, setting.lebar_waveform);
            if(setting.kanal_3 == 1 && kanal_view_state[2] == 1)
                kanal_view[2]->get_data_kanal(data_kanal[2], req_g.jum_sample, setting.lebar_waveform);
            if(setting.kanal_4 == 1 && kanal_view_state[3] == 1)
                kanal_view[3]->get_data_kanal(data_kanal[3], req_g.jum_sample, setting.lebar_waveform);

            if(versus_view_state == 1)
            {
                if(setting.kanal_1 == 1)
                    versus_view->get_data_kanal1(data_kanal[0], req_g.jum_sample, setting.lebar_waveform);
                if(setting.kanal_2 == 1)
                    versus_view->get_data_kanal2(data_kanal[1], req_g.jum_sample, setting.lebar_waveform);
                if(setting.kanal_3 == 1)
                    versus_view->get_data_kanal3(data_kanal[2], req_g.jum_sample, setting.lebar_waveform);
                if(setting.kanal_4 == 1)
                    versus_view->get_data_kanal4(data_kanal[3], req_g.jum_sample, setting.lebar_waveform);
            }

            /* update status bar */
            count_udp++;
            s.sprintf("Modul(%s), Count(%d), Lost(%d)", setting.modul_ip, count_udp, req->lost_paket);

            QString s4;
            if (req->flag == 1)
            {
                s.append(", Master");
                setting.client_status = 1;
            }
            else if (req->flag == 2)
            {
                s.append(", Slave");
                // update data2 sesuai dengan yang dikirim oleh master
                s4.sprintf(", (Stop Freq %d)", (int) (req_g.sampling_rate/2.56));
                s.append(s4);
            }

            QString s3;
            if (req_g.arus_charge)
            {
                /* jika lagi ngecharge, yang dipakai sebagai level baterai
                   adalah buck level */
                s3.sprintf(", Bat %.1f V (Charging %d mA)", \
                           (float) (req_g.buck_level/1000.00), req_g.arus_charge * 10);
            }
            else
                s3.sprintf(", Bat %.1f V", (float) (req_g.bat_level/1000.00));

            s.append(s3);


            QString s6;
            if(setting.fase_enabled == 1)
            {
                s6.sprintf(", Trigger Fasa ON");
                s.append(s6);
            }
            if(setting.fase_enabled == 0)
            {
                s6.sprintf(", Trigger Fasa OFF");
                s.append(s6);
            }

            QString s7;

            if(setting.fase_enabled == 0)
                s7.sprintf(", Lebar Waveform %.0f ms", ((setting.lebar_waveform) / 1.5));
            if(setting.fase_enabled == 1)
                s7.sprintf(", Lebar Waveform %d ms", setting.lebar_waveform);
            s.append(s7);

            ui->statusBar->showMessage(s);

            /* request lagi !*/
            tim->start( ms_refresh );

            tim_count = 0;
            tim_ulang = 0;
        }   /* jumlah sudah sesuai */
    }
}

void MainWindow::tim_update(void)
{
#if 1
    /* jika UDP yang diharapkan tidak muncul */
    //qDebug("%s(): %d, nunggu %d", __FUNCTION__, tim_count, nomer_kirim);

    tim_count++;
    if (tim_count > 2)
    {
        //qDebug("Minta lagi dari %d", nomer_kirim);
        tim->stop();
        tim_count = 0;

        tim_ulang++;
        if (tim_ulang > 10)
        {
            tim_ulang = 0;
            qDebug("Tidak ada respon dari Daq, STOP !");
            return;
        }

        memcpy( (void *) &ulang_g, (void *) &req_g, sizeof (ulang_g));
        memcpy(ulang_g.buf, &par_vib, sizeof (par_vib));

        /* minta lagi */
        sprintf(ulang_g.head, "getdata");
        ulang_g.state = MULAI_KONEK;

        /* supaya dikirim dari urutan nol / awal */
        ulang_g.urutan = nomer_kirim;
        if (setting.fase_enabled == 1)
        {
            //qDebug("Enable FASE !");
            ulang_g.fase_enabled = 1;
        }
        else
        {
            ulang_g.fase_enabled = 0;
        }

        decode_kanal();

        udpSocket->write( (char *) &ulang_g, sizeof (ulang_g) );

        //tim->start( 100 );
    }

#endif
}


/* setting modul_akuisisi */
void MainWindow::on_actionModul_Akuisisi_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        set_modul = new ModulSetting();
        ui->mdiArea->addSubWindow(set_modul);

        set_modul->parentWidget()->show();
        set_modul->parentWidget()->setWindowTitle("Setting modul");
        set_modul_state = true;
    }
    else
    {
        set_modul_state = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "Setting modul")
            {
                set_modul->setFocus();
                set_modul_state = true;
            }
        }

        if(set_modul_state == false)
        {
            set_modul = new ModulSetting();
            ui->mdiArea->addSubWindow(set_modul);

            set_modul->parentWidget()->show();
            set_modul->parentWidget()->setWindowTitle("Setting modul");
            set_modul_state = true;
        }
    }
}

/* read setting and write setting dicopy dari qt_haliza */
void MainWindow::read_setting()
{
    QString pth = "setting.ini";
    QSettings settings(pth, QSettings::IniFormat);

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();

    setting.client_status = settings.value("client_status").toInt();

    setting.kanal_1 = settings.value("kanal_1").toInt();
    setting.kanal_2 = settings.value("kanal_2").toInt();
    setting.kanal_3 = settings.value("kanal_3").toInt();
    setting.kanal_4 = settings.value("kanal_4").toInt();

    setting.unit_acc = settings.value("Unit_acc").toInt();
    setting.unit_velo = settings.value("Unit_velo").toInt();
    setting.unit_disp = settings.value("Unit_disp").toInt();
    setting.unit_pcomb = settings.value("Unit_pcomb").toInt();
    setting.unit_temp = settings.value("Unit_temp").toInt();
    setting.unit_ihp = settings.value("Unit_ihp").toInt();
    setting.unit_frek = settings.value("Unit_frek").toInt();
    setting.unit_flow_komp = settings.value("Unit_flow_komp").toInt();
    setting.ymax_accel = settings.value("ymax_accel").toFloat();
    setting.ymax_velo = settings.value("ymax_velo").toFloat();
    setting.ymax_disp = settings.value("ymax_disp").toFloat();

    setting.f_start         = settings.value("f_start").toInt();
    setting.f_stop          = settings.value("f_stop").toInt();
    setting.fft_lines_index = settings.value("lines_index").toInt();
    setting.fft_lines       = settings.value("lines").toInt();
    setting.window          = settings.value("window").toInt();
    setting.averages        = settings.value("averages").toInt();
    setting.PP              = settings.value("PP").toInt();
    setting.lebar_waveform  = settings.value("lebar_waveform").toInt();
    setting.fase_enabled    = settings.value("fase_enable").toInt();
    setting.waveform_x      = settings.value("waveform_x").toInt();
    setting.waveform_y      = settings.value("waveform_y").toInt();
    setting.wtf_timer = settings.value("wtf_timer").toInt();

    setting.chart_mode      = settings.value("chart_mode").toInt();

    // baca setting simulasi
    setting.cek_f1          = settings.value("cek_f1").toInt();
    setting.cek_f2          = settings.value("cek_f2").toInt();
    setting.cek_f3          = settings.value("cek_f3").toInt();
    setting.cek_f4          = settings.value("cek_f4").toInt();
    setting.cek_f5          = settings.value("cek_f5").toInt();

    setting.edit_f1         = settings.value("edit_f1").toFloat();
    setting.edit_f2         = settings.value("edit_f2").toFloat();
    setting.edit_f3         = settings.value("edit_f3").toFloat();
    setting.edit_f4         = settings.value("edit_f4").toFloat();
    setting.edit_f5         = settings.value("edit_f5").toFloat();

    setting.edit_a1         = settings.value("edit_a1").toFloat();
    setting.edit_a2         = settings.value("edit_a2").toFloat();
    setting.edit_a3         = settings.value("edit_a3").toFloat();
    setting.edit_a4         = settings.value("edit_a4").toFloat();
    setting.edit_a5         = settings.value("edit_a5").toFloat();

    setting.edit_fasa1         = settings.value("edit_fasa1").toFloat();
    setting.edit_fasa2         = settings.value("edit_fasa2").toFloat();
    setting.edit_fasa3         = settings.value("edit_fasa3").toFloat();
    setting.edit_fasa4         = settings.value("edit_fasa4").toFloat();
    setting.edit_fasa5         = settings.value("edit_fasa5").toFloat();

    setting.radio_bentuk    = settings.value("radio_bentuk").toInt();

    // network
    sprintf(setting.net_hostname, "%s", settings.value("net_hostname").toString().toAscii().data());
    sprintf(setting.net_db_name, "%s", settings.value("net_db_name").toString().toAscii().data());
    sprintf(setting.net_user, "%s", settings.value("net_user").toString().toAscii().data());
    sprintf(setting.net_passwd, "%s", settings.value("net_passwd").toString().toAscii().data());

    setting.sql_driver = settings.value("sql_driver").toInt();

    //debug_setting( &setting );

    QString l_open = settings.value("Last_open").toString();
    //qDebug("last open (%d) %s", l_open.length(), l_open.toAscii().data());

    if (l_open.length() > 5)
        sprintf(setting.last_open, "%s", l_open.toAscii().data());

    QString s_modul_ip = settings.value("Modul_ip").toString();
    if (s_modul_ip == 0)
    {
        //kasih default
        qDebug("%s(): modul_ip tidak ditemukan !", __FUNCTION__);
        sprintf(setting.modul_ip, "192.168.1.252");
    }
    else
        sprintf(setting.modul_ip, "%s", s_modul_ip.toAscii().data());

    sprintf(setting.kanal_use, "%s", settings.value("kanal_use").toString().toAscii().data());

    move(pos);
    resize(size);
}

void MainWindow::write_setting()
{
    QString pth = "setting.ini";
    qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("Com_port", "/dev/ttyUSB0");
    settings.setValue("Com_speed", "115200");

    settings.setValue("client_status", setting.client_status);

    settings.setValue("kanal_1", setting.kanal_1);
    settings.setValue("kanal_2", setting.kanal_2);
    settings.setValue("kanal_3", setting.kanal_3);
    settings.setValue("kanal_4", setting.kanal_4);

    settings.setValue("Unit_acc", setting.unit_acc);
    settings.setValue("Unit_velo", setting.unit_velo);
    settings.setValue("Unit_disp", setting.unit_disp);
    settings.setValue("Unit_pcomb", setting.unit_pcomb);
    settings.setValue("Unit_temp", setting.unit_temp);
    settings.setValue("Unit_ihp", setting.unit_ihp);
    settings.setValue("Unit_flow_komp", setting.unit_flow_komp);
    settings.setValue("Unit_frek", setting.unit_frek);
    settings.setValue("ymax_accel", setting.ymax_accel);
    settings.setValue("ymax_velo", setting.ymax_velo);
    settings.setValue("ymax_disp", setting.ymax_disp);

    /* parameter default rotating */
    settings.setValue("f_start", setting.f_start);
    settings.setValue("f_stop", setting.f_stop);
    settings.setValue("lines_index", setting.fft_lines_index);
    settings.setValue("lines", setting.fft_lines);
    settings.setValue("averages", setting.averages);
    settings.setValue("window", setting.window);
    settings.setValue("PP", setting.PP);
    settings.setValue("lebar_waveform", setting.lebar_waveform);
    settings.setValue("fase_enable", setting.fase_enabled);
    settings.setValue("waveform_x", setting.waveform_x);
    settings.setValue("waveform_y", setting.waveform_y);
    settings.setValue("wtf_timer", setting.wtf_timer);

    settings.setValue("chart_mode", setting.chart_mode);

    /* setting simulasi */
    settings.setValue("cek_f1", setting.cek_f1);
    settings.setValue("cek_f2", setting.cek_f2);
    settings.setValue("cek_f3", setting.cek_f3);
    settings.setValue("cek_f4", setting.cek_f4);
    settings.setValue("cek_f5", setting.cek_f5);

    settings.setValue("edit_f1", setting.edit_f1);
    settings.setValue("edit_f2", setting.edit_f2);
    settings.setValue("edit_f3", setting.edit_f3);
    settings.setValue("edit_f4", setting.edit_f4);
    settings.setValue("edit_f5", setting.edit_f5);

    settings.setValue("edit_a1", setting.edit_a1);
    settings.setValue("edit_a2", setting.edit_a2);
    settings.setValue("edit_a3", setting.edit_a3);
    settings.setValue("edit_a4", setting.edit_a4);
    settings.setValue("edit_a5", setting.edit_a5);

    settings.setValue("edit_fasa1", setting.edit_fasa1);
    settings.setValue("edit_fasa2", setting.edit_fasa2);
    settings.setValue("edit_fasa3", setting.edit_fasa3);
    settings.setValue("edit_fasa4", setting.edit_fasa4);
    settings.setValue("edit_fasa5", setting.edit_fasa5);

    settings.setValue("radio_bentuk", setting.radio_bentuk);


    /* file terakhir dibuka */
    settings.setValue("Last_open", last_file_open);

    /* koneksi database network */
    settings.setValue("net_hostname", setting.net_hostname);
    settings.setValue("net_db_name", setting.net_db_name);
    settings.setValue("net_user", setting.net_user);
    settings.setValue("net_passwd", setting.net_passwd );
    settings.setValue("sql_driver", setting.sql_driver );

    settings.setValue("Modul_ip", setting.modul_ip);
    settings.setValue("kanal_use", setting.kanal_use);
}


void MainWindow::on_actionSetting_Motor_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        set_motor = new MotorControl();
        ui->mdiArea->addSubWindow(set_motor);
        set_motor->parentWidget()->show();
        set_motor->parentWidget()->setWindowTitle("Motor control");
        set_motor_state = true;
    }
    else
    {
        set_motor_state = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "Motor control")
            {
                set_motor->setFocus();
                set_motor_state = true;
            }
        }

        if(set_motor_state == false)
        {
            set_motor = new MotorControl();
            ui->mdiArea->addSubWindow(set_motor);
            set_motor->parentWidget()->show();
            set_motor->parentWidget()->setWindowTitle("Motor control");
            set_motor_state = true;
        }
    }
}

void MainWindow::on_actionMode_Simulasi_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        set_siggen = new SignalGeneratorSet();
        ui->mdiArea->addSubWindow(set_siggen);

        set_siggen->parentWidget()->show();
        set_siggen->parentWidget()->setWindowTitle("Signal Generator");
        set_siggen_state = true;
    }
    else
    {
        set_siggen_state = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "Signal Generator")
            {
                set_siggen->setFocus();
                set_siggen_state = true;
            }
        }

        if(set_siggen_state == false)
        {
            set_siggen = new SignalGeneratorSet();
            ui->mdiArea->addSubWindow(set_siggen);

            set_siggen->parentWidget()->show();
            set_siggen->parentWidget()->setWindowTitle("Signal Generator");
            set_siggen_state = true;
        }
    }
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionCH1_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        kanal_view[0] = new kanalView();
        ui->mdiArea->addSubWindow(kanal_view[0]);

        connect(this, SIGNAL(kanal_view_start()), kanal_view[0], SLOT(start_proses_view()));
        connect(this, SIGNAL(kanal_view_stop()), kanal_view[0], SLOT(stop_proses_view()));
        if(modul_state == 1)
            kanal_view_start();

        kanal_view[0]->parentWidget()->show();
        kanal_view[0]->parentWidget()->setWindowTitle("kanal-1");
        kanal_view_state[0] = true;
        kanal_view[0]->kanal_id = 1;
    }
    else
    {
        kanal_view_state[0] = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "kanal-1")
            {
                kanal_view[0]->setFocus();
                kanal_view_state[0] = true;
            }
        }

        if(kanal_view_state[0] == false)
        {
            kanal_view[0] = new kanalView();
            ui->mdiArea->addSubWindow(kanal_view[0]);

            connect(this, SIGNAL(kanal_view_start()), kanal_view[0], SLOT(start_proses_view()));
            connect(this, SIGNAL(kanal_view_stop()), kanal_view[0], SLOT(stop_proses_view()));
            if(modul_state == 1)
                kanal_view_start();

            kanal_view[0]->parentWidget()->show();
            kanal_view[0]->parentWidget()->setWindowTitle("kanal-1");
            kanal_view_state[0] = true;
            kanal_view[0]->kanal_id = 1;
        }
    }
}

void MainWindow::on_actionCH2_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        kanal_view[1] = new kanalView();
        ui->mdiArea->addSubWindow(kanal_view[1]);

        connect(this, SIGNAL(kanal_view_start()), kanal_view[1], SLOT(start_proses_view()));
        connect(this, SIGNAL(kanal_view_stop()), kanal_view[1], SLOT(stop_proses_view()));
        if(modul_state == 1)
            kanal_view_start();

        kanal_view[1]->parentWidget()->show();
        kanal_view[1]->parentWidget()->setWindowTitle("kanal-2");
        kanal_view_state[1] = true;
        kanal_view[1]->kanal_id = 2;
    }
    else
    {
        kanal_view_state[1] = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "kanal-2")
            {
                kanal_view[1]->setFocus();
                kanal_view_state[1] = true;
            }
        }

        if(kanal_view_state[1] == false)
        {
            kanal_view[1] = new kanalView();
            ui->mdiArea->addSubWindow(kanal_view[1]);

            connect(this, SIGNAL(kanal_view_start()), kanal_view[1], SLOT(start_proses_view()));
            connect(this, SIGNAL(kanal_view_stop()), kanal_view[1], SLOT(stop_proses_view()));
            if(modul_state == 1)
                kanal_view_start();

            kanal_view[1]->parentWidget()->show();
            kanal_view[1]->parentWidget()->setWindowTitle("kanal-2");
            kanal_view_state[1] = true;
            kanal_view[1]->kanal_id = 2;
        }
    }
}

void MainWindow::on_actionCH3_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        kanal_view[2] = new kanalView();
        ui->mdiArea->addSubWindow(kanal_view[2]);

        connect(this, SIGNAL(kanal_view_start()), kanal_view[2], SLOT(start_proses_view()));
        connect(this, SIGNAL(kanal_view_stop()), kanal_view[2], SLOT(stop_proses_view()));
        if(modul_state == 1)
            kanal_view_start();

        kanal_view[2]->parentWidget()->show();
        kanal_view[2]->parentWidget()->setWindowTitle("kanal-3");
        kanal_view_state[2] = true;        
        kanal_view[2]->kanal_id = 3;
    }
    else
    {
        kanal_view_state[2] = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "kanal-3")
            {
                kanal_view[2]->setFocus();
                kanal_view_state[2] = true;
            }
        }

        if(kanal_view_state[2] == false)
        {
            kanal_view[2] = new kanalView();
            ui->mdiArea->addSubWindow(kanal_view[2]);

            connect(this, SIGNAL(kanal_view_start()), kanal_view[2], SLOT(start_proses_view()));
            connect(this, SIGNAL(kanal_view_stop()), kanal_view[2], SLOT(stop_proses_view()));
            if(modul_state == 1)
                kanal_view_start();

            kanal_view[2]->parentWidget()->show();
            kanal_view[2]->parentWidget()->setWindowTitle("kanal-3");
            kanal_view_state[2] = true;
            kanal_view[2]->kanal_id = 3;
        }
    }
}

void MainWindow::on_actionCH4_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        kanal_view[3] = new kanalView();
        ui->mdiArea->addSubWindow(kanal_view[3]);

        connect(this, SIGNAL(kanal_view_start()), kanal_view[3], SLOT(start_proses_view()));
        connect(this, SIGNAL(kanal_view_stop()), kanal_view[3], SLOT(stop_proses_view()));
        if(modul_state == 1)
            kanal_view_start();

        kanal_view[3]->parentWidget()->show();
        kanal_view[3]->parentWidget()->setWindowTitle("kanal-4");
        kanal_view_state[3] = true;
        kanal_view[3]->kanal_id = 4;
    }
    else
    {
        kanal_view_state[3] = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "kanal-4")
            {
                kanal_view[3]->setFocus();
                kanal_view_state[3] = true;
            }
        }

        if(kanal_view_state[3] == false)
        {
            kanal_view[3] = new kanalView();
            ui->mdiArea->addSubWindow(kanal_view[3]);

            connect(this, SIGNAL(kanal_view_start()), kanal_view[3], SLOT(start_proses_view()));
            connect(this, SIGNAL(kanal_view_stop()), kanal_view[3], SLOT(stop_proses_view()));
            if(modul_state == 1)
                kanal_view_start();

            kanal_view[3]->parentWidget()->show();
            kanal_view[3]->parentWidget()->setWindowTitle("kanal-4");
            kanal_view_state[3] = true;
            kanal_view[3]->kanal_id = 4;
        }
    }
}


void MainWindow::on_actionDatabase_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        db_ctl = new DbControl();
        ui->mdiArea->addSubWindow(db_ctl);

        db_ctl->parentWidget()->show();
        db_ctl->parentWidget()->setWindowTitle("Database");
        db_ctl_state = true;
        connect(db_ctl, SIGNAL(buka_db_mainwindow()), this, SLOT(open_db()));
        connect(db_ctl, SIGNAL(simpan_db()), this, SLOT(start_simpan()));
        connect(db_ctl, SIGNAL(load_from_db()), this, SLOT(load_db()));
    }
    else
    {
        set_siggen_state = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "Database")
            {
                db_ctl->setFocus();
                db_ctl_state = true;
            }
        }

        if(db_ctl_state == false)
        {
            db_ctl = new DbControl();
            ui->mdiArea->addSubWindow(db_ctl);

            db_ctl->parentWidget()->show();
            db_ctl->parentWidget()->setWindowTitle("Database");
            db_ctl_state = true;
            connect(db_ctl, SIGNAL(buka_db_mainwindow()), this, SLOT(open_db()));
            connect(db_ctl, SIGNAL(simpan_db()), this, SLOT(start_simpan()));
            connect(db_ctl, SIGNAL(load_from_db()), this, SLOT(load_db()));
        }
    }
}

void MainWindow::open_db()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "main_conn");
    db.setDatabaseName(db_ctl->fileName);
    qDebug() << "database" << db_ctl->fileName  << "dibuka di mainwindow";

    if (!db.open())
    {
        qDebug("ERR: Tidak bisa buka database !");
        return;
    }
    else
    {
        qDebug("Ok database bisa dibuka !");
        query_w = QSqlQuery( db );
    }
}

void MainWindow::start_simpan()
{

    if(setting.kanal_1 == 1 || setting.kanal_2 == 1 || setting.kanal_3 == 1 || setting.kanal_4 == 1)
    {
        QDateTime now = QDateTime::currentDateTime();
        qDebug()<< now.toString("dd/MM/yyyy - hh:mm");

        query_w.exec("select max(id) from waktu;");
        query_w.first();

        int last_id_waktu =  query_w.value(0).toInt() + 1;

        query_w.prepare("insert into waktu (id, waktu, note) values (?, ?, ?);");
        query_w.bindValue(0, last_id_waktu);
        query_w.bindValue(1, now.toString("dd/MM/yyyy - hh:mm"));
        char note[30];
        sprintf(note, "%s%d", "catatan ke-", last_id_waktu);
        query_w.bindValue(2, note);

        if (query_w.exec())
        {
            qDebug("OK sip");
        }


        if(setting.kanal_1 == 1)
        {
            QByteArray ba;
            QSqlError er;

            int jml_disimpan = kanal_view[0]->last_index_dibaca;
            for(int n = 0; n < jml_disimpan; n++)
            {
                QByteArray ba1(reinterpret_cast<const char*>(&(kanal_view[0]->buffer[n])), sizeof(kanal_view[0]->buffer[n]));
                ba.append(ba1);
            }

            // referensi : http://www.sqlite.org/faq.html#q19
            query_w.exec("PRAGMA synchronous = OFF");

            query_w.prepare("Insert into data (id_waktu, id_kanal,  data) Values ( ?, ?, ?)");
            query_w.bindValue(0, last_id_waktu);
            query_w.bindValue(1, 1);
            query_w.bindValue(2, ba);

            if (!query_w.exec())
            {
                er = query_w.lastError();
                qDebug("Masukin Blob error %s", er.text().toAscii().data());

                return;
            }
            else qDebug("OK sip");

        }
        if(setting.kanal_2 == 1)
        {
            QByteArray ba;
            QSqlError er;

            int jml_disimpan = kanal_view[1]->last_index_dibaca;
            for(int n = 0; n < jml_disimpan; n++)
            {
                QByteArray ba1(reinterpret_cast<const char*>(&(kanal_view[1]->buffer)), jml_disimpan);
                ba.append(ba1);
            }

            // referensi : http://www.sqlite.org/faq.html#q19
            query_w.exec("PRAGMA synchronous = OFF");

            query_w.prepare("Insert into data (id_waktu, id_kanal,  data) Values ( ?, ?, ?)");
            query_w.bindValue(0, last_id_waktu);
            query_w.bindValue(1, 2);
            query_w.bindValue(2, ba);

            if (!query_w.exec())
            {
                er = query_w.lastError();
                qDebug("Masukin Blob error %s", er.text().toAscii().data());

                return;
            }
            else qDebug("OK sip");
        }
        if(setting.kanal_3 == 1)
        {
            QByteArray ba;
            QSqlError er;

            int jml_disimpan = kanal_view[2]->last_index_dibaca;
            for(int n = 0; n < jml_disimpan; n++)
            {
                QByteArray ba1(reinterpret_cast<const char*>(&(kanal_view[2]->buffer)), jml_disimpan);
                ba.append(ba1);
            }

            // referensi : http://www.sqlite.org/faq.html#q19
            query_w.exec("PRAGMA synchronous = OFF");

            query_w.prepare("Insert into data (id_waktu, id_kanal,  data) Values ( ?, ?, ?)");
            query_w.bindValue(0, last_id_waktu);
            query_w.bindValue(1, 3);
            query_w.bindValue(2, ba);

            if (!query_w.exec())
            {
                er = query_w.lastError();
                qDebug("Masukin Blob error %s", er.text().toAscii().data());

                return;
            }
            else qDebug("OK sip");
        }
        if(setting.kanal_4 == 1)
        {
            QByteArray ba;
            QSqlError er;

            int jml_disimpan = kanal_view[3]->last_index_dibaca;
            for(int n = 0; n < jml_disimpan; n++)
            {
                QByteArray ba1(reinterpret_cast<const char*>((kanal_view[3]->buffer)), jml_disimpan);
                ba.append(ba1);
            }

            // referensi : http://www.sqlite.org/faq.html#q19
            query_w.exec("PRAGMA synchronous = OFF");

            query_w.prepare("Insert into data (id_waktu, id_kanal,  data) Values ( ?, ?, ?)");
            query_w.bindValue(0, last_id_waktu);
            query_w.bindValue(1, 4);
            query_w.bindValue(2, ba);

            if (!query_w.exec())
            {
                er = query_w.lastError();
                qDebug("Masukin Blob error %s", er.text().toAscii().data());

                return;
            }
            else qDebug("OK sip");
        }
    }
}

void MainWindow::load_db()
{
    if(kanal_view_state[0] == true)
    {
        kanal_view[0]->reset_data();
        int id_waktu = db_ctl->id_waktu_loaded;
        QSqlError er;
        qDebug() << "mulai load data kanal" << 1 << "pada id_waktu =" << id_waktu;

        query_w.prepare("select data from data where id_waktu = ? and id_kanal = ?");
        query_w.bindValue(0, id_waktu);
        query_w.bindValue(1, 1);

        if (!query_w.exec())
        {
            er = query_w.lastError();
            qDebug("Load data error %s", er.text().toAscii().data());
            return;
        }
        else
        {
            query_w.first();

            QByteArray BA;
            BA = query_w.value(0).toByteArray();
            int len = BA.size();
            QByteArray temp;

            int h = 0;
            for(int s = 0; s < (len/4); s++)
            {
                temp = (BA.mid(h, 4));
                kanal_view[0]->buffer[s] = *reinterpret_cast<const float*>(temp.data());
                h = h+4;
            }

        }

        kanal_view[0]->update();
    }
    if(kanal_view_state[1] == true)
    {
        kanal_view[1]->reset_data();
        int id_waktu = db_ctl->id_waktu_loaded;
        QSqlError er;
        qDebug() << "mulai load data kanal" << 2 << "pada id_waktu =" << id_waktu;

        query_w.prepare("select data from data where id_waktu = ? and id_kanal = ?");
        query_w.bindValue(0, id_waktu);
        query_w.bindValue(1, 2);

        if (!query_w.exec())
        {
            er = query_w.lastError();
            qDebug("Load data error %s", er.text().toAscii().data());
            return;
        }
        else
        {
            query_w.first();

            QByteArray BA;
            BA = query_w.value(0).toByteArray();
            int len = BA.size();
            QByteArray temp;

            int h = 0;
            for(int s = 0; s < (len/4); s++)
            {
                temp = (BA.mid(h, 4));
                kanal_view[1]->buffer[s] = *reinterpret_cast<const float*>(temp.data());
                h = h+4;
            }

        }

        kanal_view[1]->update();
    }
    if(kanal_view_state[2] == true)
    {
        kanal_view[2]->reset_data();
        int id_waktu = db_ctl->id_waktu_loaded;
        QSqlError er;
        qDebug() << "mulai load data kanal" << 3 << "pada id_waktu =" << id_waktu;

        query_w.prepare("select data from data where id_waktu = ? and id_kanal = ?");
        query_w.bindValue(0, id_waktu);
        query_w.bindValue(1, 3);

        if (!query_w.exec())
        {
            er = query_w.lastError();
            qDebug("Load data error %s", er.text().toAscii().data());
            return;
        }
        else
        {
            query_w.first();

            QByteArray BA;
            BA = query_w.value(0).toByteArray();
            int len = BA.size();
            QByteArray temp;

            int h = 0;
            for(int s = 0; s < (len/4); s++)
            {
                temp = (BA.mid(h, 4));
                kanal_view[2]->buffer[s] = *reinterpret_cast<const float*>(temp.data());
                h = h+4;
            }

        }

        kanal_view[2]->update();
    }
    if(kanal_view_state[3] == true)
    {
        kanal_view[3]->reset_data();
        int id_waktu = db_ctl->id_waktu_loaded;
        QSqlError er;
        qDebug() << "mulai load data kanal" << 4 << "pada id_waktu =" << id_waktu;

        query_w.prepare("select data from data where id_waktu = ? and id_kanal = ?");
        query_w.bindValue(0, id_waktu);
        query_w.bindValue(1, 4);

        if (!query_w.exec())
        {
            er = query_w.lastError();
            qDebug("Load data error %s", er.text().toAscii().data());
            return;
        }
        else
        {
            query_w.first();

            QByteArray BA;
            BA = query_w.value(0).toByteArray();
            int len = BA.size();
            QByteArray temp;

            int h = 0;
            for(int s = 0; s < (len/4); s++)
            {
                temp = (BA.mid(h, 4));
                kanal_view[3]->buffer[s] = *reinterpret_cast<const float*>(temp.data());
                h = h+4;
            }

        }

        kanal_view[3]->update();
    }
}


void MainWindow::on_actionCOMPARE_triggered()
{
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        versus_view = new VersusView();
        ui->mdiArea->addSubWindow(versus_view);
        connect(this, SIGNAL(versus_view_start()), versus_view, SLOT(start_proses_view()));
        connect(this, SIGNAL(versus_view_stop()), versus_view, SLOT(stop_proses_view()));
        if(modul_state == 1)
            versus_view_start();

        versus_view->parentWidget()->show();
        versus_view->parentWidget()->setWindowTitle("Compare View");
        versus_view_state = true;
    }
    else
    {
        versus_view_state = false;
        for(int n = 0; n < ui->mdiArea->subWindowList().count(); n++)
        {
            if(ui->mdiArea->subWindowList().at(n)->windowTitle() == "Compare View")
            {
                versus_view->setFocus();
                versus_view_state = true;
            }
        }

        if(versus_view_state == false)
        {
            versus_view = new VersusView();
            ui->mdiArea->addSubWindow(versus_view);
            connect(this, SIGNAL(versus_view_start()), versus_view, SLOT(start_proses_view()));
            connect(this, SIGNAL(versus_view_stop()), versus_view, SLOT(stop_proses_view()));
            if(modul_state == 1)
                versus_view_start();

            versus_view->parentWidget()->show();
            versus_view->parentWidget()->setWindowTitle("Compare View");
            versus_view_state = true;
        }
    }
}
