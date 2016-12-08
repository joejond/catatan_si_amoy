#include "dbcontrol.h"
#include "ui_dbcontrol.h"

DbControl::DbControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DbControl)
{
    ui->setupUi(this);

    QString con_name;
    con_name.sprintf("sqlite conn");
    db = QSqlDatabase::addDatabase("QSQLITE", con_name);
}

DbControl::~DbControl()
{
    delete ui;
}

void DbControl::read_setting()
{
    QString pth = "setting.ini";
    //qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    sprintf(setting.kanal_use, "%s", settings.value("kanal_use").toString().toAscii().data());
    setting.kanal_1 = settings.value("kanal_1").toInt();
    setting.kanal_2 = settings.value("kanal_2").toInt();
    setting.kanal_3 = settings.value("kanal_3").toInt();
    setting.kanal_4 = settings.value("kanal_4").toInt();

    setting.fft_lines = settings.value("lines").toInt();

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

    // baca setting simulasi
    setting.mode_simulasi   = settings.value("mode_simulasi").toInt();
    setting.tipe_sinyal    = settings.value("tipe_sinyal").toInt();
}

void DbControl::buka_database(void)
{
    qDebug("%s(): filename %s", __FUNCTION__, setting.last_open);
    db.setDatabaseName(setting.last_open);

    if (!db.open())
    {
        qDebug("ERR: Tidak bisa buka database !");
        return;
    }
    else
    {
        qDebug("Ok database bisa dibuka !");
        qDebug("nama koneksi %s", db.connectionName().toAscii().data());
        query_w = QSqlQuery( db );

        model_waktu = new QSqlTableModel(this, db);

        model_waktu->setTable("waktu");
        model_waktu->select();

        ui->table_db->setModel( model_waktu );



        ui->table_db->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->table_db->setSelectionMode(QTableView::SingleSelection);
        //view->setEditTriggers( QAbstractItemView::NoEditTriggers );

        ui->table_db->hideColumn( 0 );
        //view->hideColumn( 1 );

        //return fileName;
        last_file_open = setting.last_open;
        qDebug("Ok last open disimpan : %s", last_file_open.toAscii().data());

    }
}


void DbControl::on_pb_open_db_clicked()
{
    QFileDialog dlg_open;
    fileName = dlg_open.getOpenFileName(this, tr("New Database File"), "./data/", "(*.dbc)");
    if(fileName != "")
    {
        sprintf(setting.last_open, "%s", fileName.toAscii().data());
        db.close();
        buka_database();
    }

    buka_db_mainwindow();
}

void DbControl::tulis_info()
{
    ui->label_info->setText("<html><body><p>F-start = "+ QString::number(setting.f_start) + " Hz</p>" +
                            "<p>F-Stop = "+ QString::number(setting.f_stop) + " Hz</p>" +
                             "<p>request line = "+ QString::number(setting.fft_lines) + "</p>" +
                            "<p>Fase Enabled = No</p>" +
                            "<p>Accelerometer1 = "+ QString::number(setting.acc_sencitivity1) + " (mV/G)</p>" +
                            "<p>Accelerometer2 = "+ QString::number(setting.acc_sencitivity2) + " (mV/G)</p>" +
                            "<p>Accelerometer3 = "+ QString::number(setting.acc_sencitivity3) + " (mV/G)</p>" +
                            "<p>Accelerometer4 = "+ QString::number(setting.acc_sencitivity4) + " (mV/G)</p>" +
                            "</body></html>");
}

void DbControl::load_setting_db(int id_waktu)
{
    query_w.prepare("select nama, nilai from setting where id_waktu = ?");
    query_w.bindValue(0, id_waktu);
    if (!query_w.exec())
    {
        qDebug() << "query list data salah";
    }
    else
    {
        query_w.first();
        while (query_w.next())
        {
            if(query_w.value(0).toString() == "f_start")
                setting.f_start = query_w.value(1).toInt();
            else if(query_w.value(0).toString() == "f_stop")
                setting.f_stop = query_w.value(1).toInt();
            else if(query_w.value(0).toString() == "fase_enable")
                setting.fase_enabled = query_w.value(1).toInt();
            else if(query_w.value(0).toString() == "acc1")
                setting.acc_sencitivity1 = query_w.value(1).toFloat();
            else if(query_w.value(0).toString() == "acc2")
                setting.acc_sencitivity2 = query_w.value(1).toFloat();
            else if(query_w.value(0).toString() == "acc3")
                setting.acc_sencitivity3 = query_w.value(1).toFloat();
            else if(query_w.value(0).toString() == "acc4")
                setting.acc_sencitivity4 = query_w.value(1).toFloat();
        }

        tulis_info();
    }
}

void DbControl::on_table_db_clicked(const QModelIndex &index)
{
    id_waktu_loaded =  index.model()->sibling((int)index.row(), 0, index).data().toInt();
    load_setting_db(id_waktu_loaded);
}

void DbControl::on_pb_save_db_clicked()
{
    simpan_db();
    model_waktu->setTable("waktu");
    model_waktu->select();
}

void DbControl::on_pb_load_db_clicked()
{
    load_from_db();
}

void DbControl::on_pb_delete_record_clicked()
{
    query_w.prepare("select waktu from waktu where id = ?; ");
    query_w.bindValue(0, id_waktu_loaded);
    query_w.exec();
    query_w.first();

    QString pesan = "Are you sure to delete this record? \n"+ query_w.value(0).toString();

    int tanya = QMessageBox::question(this, tr("Confirm"), pesan, QMessageBox::Ok | QMessageBox::Cancel );

    if(tanya == QMessageBox::Cancel)
    {
        qDebug() << "gak jadi delete";
    }
    if(tanya == QMessageBox::Ok)
    {
        qDebug() << "delete lanjut";
        query_w.prepare("delete from data where id_waktu = ?;");
        query_w.bindValue(0, id_waktu_loaded);
        query_w.exec();

        query_w.prepare("delete from waktu where id = ?;");
        query_w.bindValue(0, id_waktu_loaded);
        query_w.exec();

        model_waktu->setTable("waktu");
        model_waktu->select();
    }

}
