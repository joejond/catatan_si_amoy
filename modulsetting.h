#ifndef MODULSETTING_H
#define MODULSETTING_H

#include <QWidget>
#include <QSettings>
#include <QString>
#include <stdio.h>
#include <QDebug>

#include "lain.h"
extern struct t_setting setting;

namespace Ui {
class ModulSetting;
}

class ModulSetting : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModulSetting(QWidget *parent = 0);
    ~ModulSetting();
    
private slots:
    void on_pb_update_set_modul_clicked();
    void on_cb_lines_currentIndexChanged(const QString &arg1);
    void on_cb_fstop_currentIndexChanged(const QString &arg1);

    void on_cb_fstart_activated(const QString &arg1);

private:
    Ui::ModulSetting *ui;
    void read_setting();
    void write_setting();
    void update_setting();
    void updateInfo();
};

#endif // MODULSETTING_H
