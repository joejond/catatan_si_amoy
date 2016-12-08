#ifndef SIGNALGENERATORSET_H
#define SIGNALGENERATORSET_H

#include <QWidget>
#include <QSettings>
#include <QString>
#include <stdio.h>

#include "lain.h"
extern struct t_setting setting;

namespace Ui {
class SignalGeneratorSet;
}

class SignalGeneratorSet : public QWidget
{
    Q_OBJECT
    
public:
    explicit SignalGeneratorSet(QWidget *parent = 0);
    ~SignalGeneratorSet();
    
private slots:
    void on_pb_update_set_siggen_clicked();

private:
    Ui::SignalGeneratorSet *ui;

    void read_setting();
    void write_setting();
    void update_setting();
};

#endif // SIGNALGENERATORSET_H
