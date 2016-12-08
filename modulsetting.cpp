#include "modulsetting.h"
#include "ui_modulsetting.h"

ModulSetting::ModulSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModulSetting)
{
    ui->setupUi(this);
    read_setting();
    update_setting();
}

ModulSetting::~ModulSetting()
{
    delete ui;
}

void ModulSetting::read_setting()
{
    QString pth = "setting.ini";
    qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    sprintf(setting.modul_ip, "%s", settings.value("Modul_ip").toString().toAscii().data());
    sprintf(setting.kanal_use, "%s", settings.value("kanal_use").toString().toAscii().data());
    setting.kanal_1 = settings.value("kanal_1").toInt();
    setting.kanal_2 = settings.value("kanal_2").toInt();
    setting.kanal_3 = settings.value("kanal_3").toInt();
    setting.kanal_4 = settings.value("kanal_4").toInt();

    setting.acc_sencitivity1 = settings.value("acc_sencitivity1").toFloat();
    setting.acc_sencitivity2 = settings.value("acc_sencitivity2").toFloat();
    setting.acc_sencitivity3 = settings.value("acc_sencitivity3").toFloat();
    setting.acc_sencitivity4 = settings.value("acc_sencitivity4").toFloat();

    setting.client_status = settings.value("client_status").toInt();

    setting.f_start         = settings.value("f_start").toInt();
    setting.f_stop          = settings.value("f_stop").toInt();
    setting.fft_lines      = settings.value("lines").toInt();
    setting.fase_enabled    = settings.value("fase_enable").toInt();
}

void ModulSetting::update_setting()
{
    QString str_tmp;

    ui->le_ip_modul->setText(setting.modul_ip);
    if(setting.kanal_1 == 1)
        ui->chk_kanal1->setChecked(true);
    if(setting.kanal_1 == 0)
        ui->chk_kanal1->setChecked(false);
    if(setting.kanal_2 == 1)
        ui->chk_kanal2->setChecked(true);
    if(setting.kanal_2 == 0)
        ui->chk_kanal2->setChecked(false);
    if(setting.kanal_3 == 1)
        ui->chk_kanal3->setChecked(true);
    if(setting.kanal_3 == 0)
        ui->chk_kanal3->setChecked(false);
    if(setting.kanal_4 == 1)
        ui->chk_kanal4->setChecked(true);
    if(setting.kanal_4 == 0)
        ui->chk_kanal4->setChecked(false);
    if(setting.fase_enabled == 1)
        ui->chk_fasa_aktif->setChecked(true);
    if(setting.fase_enabled == 0)
        ui->chk_fasa_aktif->setChecked(false);

    if(setting.f_stop == 200)
    ui->cb_fstop->setCurrentIndex(0);
    if(setting.f_stop == 300)
    ui->cb_fstop->setCurrentIndex(1);
    if(setting.f_stop == 400)
    ui->cb_fstop->setCurrentIndex(2);
    if(setting.f_stop == 500)
    ui->cb_fstop->setCurrentIndex(3);
    if(setting.f_stop == 600)
    ui->cb_fstop->setCurrentIndex(4);
    if(setting.f_stop == 700)
    ui->cb_fstop->setCurrentIndex(5);
    if(setting.f_stop == 800)
    ui->cb_fstop->setCurrentIndex(6);
    if(setting.f_stop == 900)
    ui->cb_fstop->setCurrentIndex(7);
    if(setting.f_stop == 1000)
    ui->cb_fstop->setCurrentIndex(8);
    if(setting.f_stop == 1500)
    ui->cb_fstop->setCurrentIndex(9);
    if(setting.f_stop == 2500)
    ui->cb_fstop->setCurrentIndex(10);
    if(setting.f_stop == 3000)
    ui->cb_fstop->setCurrentIndex(11);
    if(setting.f_stop == 5000)
    ui->cb_fstop->setCurrentIndex(12);
    if(setting.f_stop == 10000)
    ui->cb_fstop->setCurrentIndex(13);
//    str_tmp.sprintf("%d", setting.fft_lines);
//    ui->le_lines_req->setText(str_tmp);

    if(setting.f_start == 1)
    ui->cb_fstart->setCurrentIndex(0);
    if(setting.f_start == 5)
    ui->cb_fstart->setCurrentIndex(1);
    if(setting.f_start == 10)
    ui->cb_fstart->setCurrentIndex(2);
    if(setting.f_start == 20)
    ui->cb_fstart->setCurrentIndex(3);
    if(setting.f_start == 60)
    ui->cb_fstart->setCurrentIndex(4);
    if(setting.f_start == 120)
    ui->cb_fstart->setCurrentIndex(5);

    if(setting.fft_lines == 100)
        ui->cb_lines->setCurrentIndex(0);
    if(setting.fft_lines == 200)
        ui->cb_lines->setCurrentIndex(1);
    if(setting.fft_lines == 400)
        ui->cb_lines->setCurrentIndex(2);
    if(setting.fft_lines == 800)
        ui->cb_lines->setCurrentIndex(3);
    if(setting.fft_lines == 1600)
        ui->cb_lines->setCurrentIndex(4);
    if(setting.fft_lines == 3200)
        ui->cb_lines->setCurrentIndex(5);


    str_tmp.sprintf("%.2f", setting.acc_sencitivity1);
    ui->le_acc1->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.acc_sencitivity2);
    ui->le_acc2->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.acc_sencitivity3);
    ui->le_acc3->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.acc_sencitivity4);
    ui->le_acc4->setText(str_tmp);

}

void ModulSetting::write_setting()
{
    QString pth = "setting.ini";
    qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    settings.setValue("Modul_ip", setting.modul_ip);
    settings.setValue("kanal_use", setting.kanal_use);

    settings.setValue("kanal_1", setting.kanal_1);
    settings.setValue("kanal_2", setting.kanal_2);
    settings.setValue("kanal_3", setting.kanal_3);
    settings.setValue("kanal_4", setting.kanal_4);
    settings.setValue("fase_enable", setting.fase_enabled);

    settings.setValue("acc_sencitivity1", setting.acc_sencitivity1);
    settings.setValue("acc_sencitivity2", setting.acc_sencitivity2);
    settings.setValue("acc_sencitivity3", setting.acc_sencitivity3);
    settings.setValue("acc_sencitivity4", setting.acc_sencitivity4);

    settings.setValue("client_status", setting.client_status);

    settings.setValue("f_start", setting.f_start);
    settings.setValue("f_stop", setting.f_stop);    
    settings.setValue("lines", setting.fft_lines);
}

void ModulSetting::on_pb_update_set_modul_clicked()
{
    sprintf(setting.modul_ip, "%s", ui->le_ip_modul->text().toAscii().data());

    if(ui->chk_kanal1->isChecked() == true)
        setting.kanal_1 = 1;
    if(ui->chk_kanal1->isChecked() == false)
        setting.kanal_1 = 0;
    if(ui->chk_kanal2->isChecked() == true)
        setting.kanal_2 = 1;
    if(ui->chk_kanal2->isChecked() == false)
        setting.kanal_2 = 0;
    if(ui->chk_kanal3->isChecked() == true)
        setting.kanal_3 = 1;
    if(ui->chk_kanal3->isChecked() == false)
        setting.kanal_3 = 0;
    if(ui->chk_kanal4->isChecked() == true)
        setting.kanal_4 = 1;
    if(ui->chk_kanal4->isChecked() == false)
        setting.kanal_4 = 0;

    if(ui->chk_fasa_aktif->isChecked() == true)
        setting.fase_enabled = 1;
    if(ui->chk_fasa_aktif->isChecked() == false)
        setting.fase_enabled = 0;


    setting.f_stop = ui->cb_fstop->currentText().toInt();
    setting.fft_lines = ui->cb_lines->currentText().toInt();

    setting.acc_sencitivity1 = ui->le_acc1->text().toFloat();
    setting.acc_sencitivity2 = ui->le_acc2->text().toFloat();
    setting.acc_sencitivity3 = ui->le_acc3->text().toFloat();
    setting.acc_sencitivity4 = ui->le_acc4->text().toFloat();

    write_setting();
}


void ModulSetting::on_cb_lines_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "100")
    {
        setting.fft_lines = 100;
    }
    if(arg1 == "200")
    {
        setting.fft_lines = 200;
    }
    if(arg1 == "400")
    {
        setting.fft_lines = 400;
    }
    if(arg1 == "800")
    {
        setting.fft_lines = 800;
    }
    if(arg1 == "1600")
    {
        setting.fft_lines = 1600;
    }
    if(arg1 == "3200")
    {
        setting.fft_lines = 3200;
    }
    updateInfo();
}

void ModulSetting::on_cb_fstop_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "200")
    {
        setting.f_stop = 200;
    }
    if(arg1 == "300")
    {
        setting.f_stop = 300;
    }
    if(arg1 == "400")
    {
        setting.f_stop = 400;
    }
    if(arg1 == "500")
    {
        setting.f_stop = 500;
    }
    if(arg1 == "600")
    {
        setting.f_stop = 600;
    }
    if(arg1 == "700")
    {
        setting.f_stop = 700;
    }
    if(arg1 == "800")
    {
        setting.f_stop = 800;
    }
    if(arg1 == "900")
    {
        setting.f_stop = 900;
    }
    if(arg1 == "1000")
    {
        setting.f_stop = 1000;
    }
    if(arg1 == "1500")
    {
        setting.f_stop = 1500;
    }
    if(arg1 == "2000")
    {
        setting.f_stop = 2000;
    }
    if(arg1 == "2500")
    {
        setting.f_stop = 2500;
    }
    if(arg1 == "3000")
    {
        setting.f_stop = 3000;
    }
    if(arg1 == "5000")
    {
        setting.f_stop = 5000;
    }
    if(arg1 == "10000")
    {
        setting.f_stop = 10000;
    }
    updateInfo();
}

void ModulSetting::updateInfo()
{

    //Hitung waktu pengambilan data
    float fETA, fSamplingRate, fJumlahData;

    fSamplingRate=setting.f_stop*2.56;
    fJumlahData=setting.fft_lines*2.56;

    fETA=fJumlahData/fSamplingRate;
    QString str_tmp;

    str_tmp.sprintf("%0.0f Sample/s", fSamplingRate);
    ui->labelSamplingRate->setText(str_tmp);

    str_tmp.sprintf("%0.0f data", fJumlahData);
    ui->labelDataCount->setText(str_tmp);

    str_tmp.sprintf("%0.2f s", fETA);
    ui->labelETA->setText(str_tmp);

    qDebug() << "f-start" << setting.f_start;
}


void ModulSetting::on_cb_fstart_activated(const QString &arg1)
{
    if(arg1 == "1")
    {
        setting.f_start = 1;
    }
    if(arg1 == "5")
    {
        setting.f_start = 5;
    }
    if(arg1 == "10")
    {
        setting.f_start = 10;
    }
    if(arg1 == "20")
    {
        setting.f_start = 20;
    }
    if(arg1 == "60")
    {
        setting.f_start = 60;
    }
    if(arg1 == "120")
    {
        setting.f_start = 120;
    }
    updateInfo();
}
