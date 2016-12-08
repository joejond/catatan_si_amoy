#ifndef DBCONTROL_H
#define DBCONTROL_H

#include <QWidget>
#include <stdio.h>
#include <QSqlTableModel>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <stdio.h>

//#include "db_utils.h"
#include <QSettings>
#include "lain.h"
#include "simpanthread.h"

#include "alokasi.h"


extern struct t_setting setting;

namespace Ui {
class DbControl;
}

class DbControl : public QWidget
{
    Q_OBJECT
    
public:
    explicit DbControl(QWidget *parent = 0);
    ~DbControl();


private slots:
    void on_pb_open_db_clicked();

    void on_table_db_clicked(const QModelIndex &index);

    void on_pb_save_db_clicked();

    void on_pb_load_db_clicked();

    void on_pb_delete_record_clicked();

private:
    Ui::DbControl *ui;
     void read_setting();
    void buka_database(void);
    void load_setting_db(int id_waktu);
    void tulis_info();

    /* database */
    QString last_file_open;
    QSqlDatabase db;
    QSqlQuery query_w;
    QSqlTableModel *model_waktu;
    int last_w_id;
    int urut_simpan;
    SimpanThread *thd_simpan;
    int jml_data_disimpan;

public:
    QString fileName;
    int id_waktu_loaded;

signals:
    void buka_db_mainwindow();
    void simpan_db();
    void load_from_db();
};

#endif // DBCONTROL_H
