#include "signalgeneratorset.h"
#include "ui_signalgeneratorset.h"

SignalGeneratorSet::SignalGeneratorSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignalGeneratorSet)
{
    ui->setupUi(this);
    read_setting();
    update_setting();
}

SignalGeneratorSet::~SignalGeneratorSet()
{
    delete ui;
}


void SignalGeneratorSet::read_setting()
{
    QString pth = "setting.ini";
    qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    setting.flag_simul = settings.value("mode_simulasi").toInt();

    setting.cek_f1 = settings.value("cek_f1").toInt();
    setting.cek_f2 = settings.value("cek_f2").toInt();
    setting.cek_f3 = settings.value("cek_f3").toInt();
    setting.cek_f4 = settings.value("cek_f4").toInt();

    setting.edit_f1 = settings.value("edit_f1").toFloat();
    setting.edit_f2 = settings.value("edit_f2").toFloat();
    setting.edit_f3 = settings.value("edit_f3").toFloat();
    setting.edit_f4 = settings.value("edit_f4").toFloat();

    setting.edit_a1 = settings.value("edit_a1").toFloat();
    setting.edit_a2 = settings.value("edit_a2").toFloat();
    setting.edit_a3 = settings.value("edit_a3").toFloat();
    setting.edit_a4 = settings.value("edit_a4").toFloat();

    setting.edit_fasa1 = settings.value("edit_fasa1").toFloat();
    setting.edit_fasa2 = settings.value("edit_fasa2").toFloat();
    setting.edit_fasa3 = settings.value("edit_fasa3").toFloat();
    setting.edit_fasa4 = settings.value("edit_fasa4").toFloat();

    setting.tipe_sinyal    = settings.value("tipe_sinyal").toInt();
}

void SignalGeneratorSet::update_setting()
{
    QString str_tmp;

    if(setting.flag_simul == 1)
        ui->chk_flag_simul->setChecked(true);
    if(setting.flag_simul == 0)
        ui->chk_flag_simul->setChecked(false);
    if(setting.cek_f2 == 1)
        ui->chk_sig2->setChecked(true);
    if(setting.cek_f2 == 0)
        ui->chk_sig2->setChecked(false);
    if(setting.cek_f3 == 1)
        ui->chk_sig3->setChecked(true);
    if(setting.cek_f3 == 0)
        ui->chk_sig3->setChecked(false);
    if(setting.cek_f4 == 1)
        ui->chk_sig4->setChecked(true);
    if(setting.cek_f4 == 0)
        ui->chk_sig4->setChecked(false);

    str_tmp.sprintf("%.2f", setting.edit_f1);
    ui->le_f1->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_f2);
    ui->le_f2->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_f3);
    ui->le_f3->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_f4);
    ui->le_f4->setText(str_tmp);

    str_tmp.sprintf("%.2f", setting.edit_a1);
    ui->le_a1->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_a2);
    ui->le_a2->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_a3);
    ui->le_a3->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_a4);
    ui->le_a4->setText(str_tmp);

    str_tmp.sprintf("%.2f", setting.edit_fasa1);
    ui->le_fasa1->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_fasa2);
    ui->le_fasa2->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_fasa3);
    ui->le_fasa3->setText(str_tmp);
    str_tmp.sprintf("%.2f", setting.edit_fasa4);
    ui->le_fasa4->setText(str_tmp);
}

void SignalGeneratorSet::write_setting()
{
    QString pth = "setting.ini";
    qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    settings.setValue("mode_simulasi", setting.flag_simul);

    settings.setValue("cek_f1", setting.cek_f1);
    settings.setValue("cek_f2", setting.cek_f2);
    settings.setValue("cek_f3", setting.cek_f3);
    settings.setValue("cek_f4", setting.cek_f4);

    settings.setValue("edit_f1", setting.edit_f1);
    settings.setValue("edit_f2", setting.edit_f2);
    settings.setValue("edit_f3", setting.edit_f3);
    settings.setValue("edit_f4", setting.edit_f4);

    settings.setValue("edit_a1", setting.edit_a1);
    settings.setValue("edit_a2", setting.edit_a2);
    settings.setValue("edit_a3", setting.edit_a3);
    settings.setValue("edit_a4", setting.edit_a4);

    settings.setValue("edit_fasa1", setting.edit_fasa1);
    settings.setValue("edit_fasa2", setting.edit_fasa2);
    settings.setValue("edit_fasa3", setting.edit_fasa3);
    settings.setValue("edit_fasa4", setting.edit_fasa4);
}

void SignalGeneratorSet::on_pb_update_set_siggen_clicked()
{
    if(ui->chk_flag_simul->isChecked() == true)
    {
        setting.flag_simul = 1;
        setting.cek_f1 = 1;
    }
    if(ui->chk_flag_simul->isChecked() == false)
    {
        setting.flag_simul = 0;
        setting.cek_f1 = 0;
    }
    if(ui->chk_sig2->isChecked() == true)
        setting.cek_f2 = 1;
    if(ui->chk_sig2->isChecked() == false)
        setting.cek_f2 = 0;
    if(ui->chk_sig3->isChecked() == true)
        setting.cek_f3 = 1;
    if(ui->chk_sig3->isChecked() == false)
        setting.cek_f3 = 0;
    if(ui->chk_sig4->isChecked() == true)
        setting.cek_f4 = 1;
    if(ui->chk_sig4->isChecked() == false)
        setting.cek_f4 = 0;

    setting.edit_f1 = ui->le_f1->text().toFloat();
    setting.edit_f2 = ui->le_f2->text().toFloat();
    setting.edit_f3 = ui->le_f3->text().toFloat();
    setting.edit_f4 = ui->le_f4->text().toFloat();

    setting.edit_a1 = ui->le_a1->text().toFloat();
    setting.edit_a2 = ui->le_a2->text().toFloat();
    setting.edit_a3 = ui->le_a3->text().toFloat();
    setting.edit_a4 = ui->le_a4->text().toFloat();

    setting.edit_fasa1 = ui->le_fasa1->text().toFloat();
    setting.edit_fasa2 = ui->le_fasa2->text().toFloat();
    setting.edit_fasa3 = ui->le_fasa3->text().toFloat();
    setting.edit_fasa4 = ui->le_fasa4->text().toFloat();

    write_setting();
}
