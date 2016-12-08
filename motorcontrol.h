#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <QWidget>
#include <QMessageBox>
#include <QTimer>

#include <QDebug>

#include "modbus.h"
#include "modbus-private.h"
#include "qextserialenumerator.h"
#include <cerrno>
#include <QTime>
#include <QSettings>

#include "lain.h"

#define INVERTER_STATUS 1

#define HITACHI_L200 1
#define HITACHI_X200 2

extern struct t_setting setting;

namespace Ui {
class MotorControl;
}

class MotorControl : public QWidget
{
    Q_OBJECT
    
public:
    explicit MotorControl(QWidget *parent = 0);
    ~MotorControl();
    
private:
    Ui::MotorControl *ui;

    /* motor control */
    void init_motor();
    void update_inverter_status();
    void sendModbusRequest(int command);
    void delay_motor_command();

    /* motor control */
    modbus_t * m_modbus;
    bool modbus_busy;
    static inline QString embracedString( const QString & s )
    {
        return s.section( '(', 1 ).section( ')', 0, 0 );
    }

    int inverter_type;
    int serial_ok;
    int init_serial;
    int inverter_status;
    int inverter_ready;
    int inverter_freq_output;

    int set_frekuensi;
    int set_arah;

    int realtime_frek;
    int realtime_current;
    int realtime_arah;
    int realtime_feedback_hi;
    int realtime_feedback_lo;
    int realtime_input_status;
    int realtime_output_status;

    int command_run;
    int command_arah;
    int command_trip;
    int command_trip_reset;

    void read_setting();
    void write_setting();

    void updateInfo();

private slots:
    void set_serialport(int j);
    void ResetStatus();
    void on_chk_motor_enable_clicked(bool checked);
    void on_rb_motor_fw_clicked();
    void on_rb_motor_rev_clicked();
    void on_pb_motor_start_clicked();
    void on_pb_motor_stop_clicked();
    void on_comboBox_activated(const QString &arg1);
};

#endif // MOTORCONTROL_H
