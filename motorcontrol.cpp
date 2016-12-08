#include "motorcontrol.h"
#include "ui_motorcontrol.h"


MotorControl::MotorControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorControl),
    m_modbus(NULL)
{
    ui->setupUi(this);
}

MotorControl::~MotorControl()
{
    delete ui;
}

void MotorControl::read_setting()
{

    QString pth = "setting.ini";
    QSettings settings(pth, QSettings::IniFormat);

    sprintf(setting.port_name, "%s", settings.value("Com_port").toString().toAscii().data());
    setting.client_status = settings.value("client_status").toInt();

}

void MotorControl::write_setting()
{
    QString pth = "setting.ini";
    qDebug("%s", pth.toAscii().data());
    QSettings settings(pth, QSettings::IniFormat);

    settings.setValue("Com_port", setting.net_hostname);
    settings.setValue("client_status", setting.client_status);

}

void MotorControl::init_motor()
{
    //SETTING GLOBAL
    inverter_type=HITACHI_X200;

    //INISIASI VARIABEL
    serial_ok=0;
    init_serial=0;
    //motor_status=1;

    modbus_busy=false;

    //ENUMERASI SERIAL PORT
    int portIndex = 0;
    int i = 0;


    ui->cb_port->setCurrentIndex(portIndex);
    foreach(QextPortInfo port, QextSerialEnumerator::getPorts())
    {
        ui->cb_port->addItem(port.friendName);
        ++i;
    }

    //set_frekuensi = (ui->spinBox_motor->text().toInt()) / 60;
    set_frekuensi = 10;
    set_arah = 0;

}

void MotorControl::update_inverter_status()
{
    //qDebug("%s()", __FUNCTION__);

    if(m_modbus == NULL)
    {
        return;
    }

    //Cek Inverter Status
    delay_motor_command();
    sendModbusRequest(8);

    //Cek Motor Status
    delay_motor_command();
    sendModbusRequest(9);

    //Cek Coil Status
    delay_motor_command();
    sendModbusRequest(10);

    return;
}

void MotorControl::delay_motor_command()
{
    QTime dieTime = QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MotorControl::set_serialport(int j)
{
    qDebug("%s(): %d", __FUNCTION__, j);


    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    const int iface = ui->cb_port->currentIndex();
    if( ui->cb_port->currentText() != "")
    {

        const QString port = ports[iface].physName;

        if(m_modbus)
        {
            modbus_close(m_modbus);
            modbus_free(m_modbus);
        }

        //Connect modbus obyek ke Port Serial
        m_modbus = modbus_new_rtu( port.toAscii().constData(),
                                   19200,
                                   'N', // "N = NONE, O = ODD, E = EVEN"
                                   8,
                                   1);

        if( modbus_connect( m_modbus ) == -1 )
        {
            serial_ok=0;
            QMessageBox::critical( this, tr( "Connection failed" ),
                                   tr( "Could not connect serial port!" ) );
        }
        else
            serial_ok=1;
        /*
        */
    }
    else
    {
        serial_ok=0;

        if(setting.client_status == 1)
        {
            QMessageBox::critical( this, tr( "No serial port found" ),
                                   tr( "Could not find any serial port "
                                       "on this computer!" ) );
        }
    }
}

void MotorControl::sendModbusRequest(int command)
{
    //qDebug("%s() Command: %d ", __FUNCTION__, command);
    if( m_modbus == NULL )
    {
        return;
    }

    /*int d;
    while(modbus_busy)
    {
        delay();
        d++;

        if(d>5) return;
    }*/

    modbus_busy=true;

    int func;
    int addr;
    int num;
    int data_tulis;

    //Alamat Modbus
    //const int slave = ui->slaveID->value();
    const int slave = 1;

    int inverter_command=command;

    if(inverter_type==HITACHI_L200)
    {
        switch(inverter_command)
        {
        case 1: //CEK STATUS MOTOR X200_CHECK_STATUS
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 1;
            num = 3;
            break;
        case 2: //CEK OUTPUT KONDISI JALAN X200_MONITOR
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 10;//0x0A;
            num = 2;
            break;
        case 3: //CEK REGISTER CONTROL X200_CONTROL_CHECK
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 45;// 0x2D;
            num = 2;
            break;
        case 4: //RUN MOTOR
            func = _FC_WRITE_SINGLE_COIL;
            addr = 01;// 0x2D;
            num = 1;
            data_tulis=1;
            break;
        case 5: //STOP MOTOR
            func = _FC_WRITE_SINGLE_COIL;
            addr = 01;// 0x2D;
            num = 1;
            data_tulis=0;
            break;
        case 6: //SET FREKUENSI
            func = _FC_WRITE_SINGLE_REGISTER;
            addr = 01;// 0x2D;
            num = 1;
            data_tulis=set_frekuensi;
            break;
        case 7: //SET ARAH PUTARAN
            func = _FC_WRITE_SINGLE_COIL;
            addr = 02;//
            num = 1;
            data_tulis=set_arah;
            break;
        case 8: //CEK INVERTER CONTROL STATUS
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 01;//
            num = 2;
            break;
        case 9: //CEK INVERTER REALTIME STATUS
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 10;//
            num = 7;
            break;
        case 10: //CEK COMMAND STATUS
            func = _FC_READ_COILS;
            addr = 1;//
            num = 4;
            break;
        case 11: //CEK INVERTER STATUS
            func = _FC_READ_COILS;
            addr = 16;//
            num = 1;
            break;
        case 45: //SET CONTROL VIA MODBUS
            func = _FC_WRITE_SINGLE_REGISTER;
            addr = 45;//
            num = 1;
            data_tulis=3;
            break;
        case 46: //SET CONTROL FREK VIA MODBUS
            func = _FC_WRITE_SINGLE_REGISTER;
            addr = 46;//
            num = 1;
            data_tulis=3;
            break;
        default:
            return;

        }
    } //ENDIF INVERTER HITACHI L200
    else if(inverter_type==HITACHI_X200)
    {
        switch(inverter_command)
        {
        case 1: //CEK STATUS MOTOR
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 2;
            num = 3;
            break;
        case 2: //CEK OUTPUT KONDISI JALAN
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 4098;// 0x1002 (halaman 22)
            num = 2;
            break;
        case 3: //CEK REGISTER CONTROL
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 4248;// 0x2D;
            num = 2;
            break;
        case 4: //RUN MOTOR
            func = _FC_WRITE_SINGLE_COIL;
            addr = 00;// 0x2D;
            num = 1;
            data_tulis=1;
            break;
        case 5: //STOP MOTOR
            func = _FC_WRITE_SINGLE_COIL;
            addr = 00;// 0x2D;
            num = 1;
            data_tulis=0;
            break;
        case 6: //SET FREKUENSI
            func = _FC_WRITE_SINGLE_REGISTER;
            addr = 01;// 0x2D;
            num = 1;
            data_tulis=set_frekuensi;
            break;
        case 7: //SET ARAH PUTARAN
            func = _FC_WRITE_SINGLE_COIL;
            addr = 01;//
            num = 1;
            data_tulis=set_arah;
            break;
        case 8: //CEK INVERTER CONTROL STATUS
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 4097;//
            num = 2;
            break;
        case 9: //CEK INVERTER REALTIME STATUS
            func = _FC_READ_HOLDING_REGISTERS;
            addr = 4097;//
            num = 3;
            break;
        case 10: //CEK COMMAND STATUS
            func = _FC_READ_COILS;
            addr = 1;//
            num = 4;
            break;
        case 11: //CEK INVERTER STATUS
            func = _FC_READ_COILS;
            addr = 16;//
            num = 1;
            break;
        case 45: //SET CONTROL VIA MODBUS
            func = _FC_WRITE_SINGLE_REGISTER;
            addr = 4120;//
            num = 1;
            data_tulis=3;
            break;
        case 46: //SET CONTROL FREK VIA MODBUS
            func = _FC_WRITE_SINGLE_REGISTER;
            addr = 4121;//
            num = 1;
            data_tulis=3;
            break;
        default:
            return;

        }
    }//ENDIF INVERTER HITACHI X200

    uint8_t dest[1024];
    uint16_t * dest16 = (uint16_t *) dest;

    memset( dest, 0, 1024 );

    int ret = -1;
    bool is16Bit = false;
    bool writeAccess = false;
    //const QString dataType = descriptiveDataTypeName( func );


    /*************************************************************/
    //TULIS PERINTAH KE INVERTER

    //qDebug("-> COMMAND: Slave: %d | alamat: 0x%0.2X | Fungsi: %d  | num: %d",  slave,addr,func,num);

    modbus_set_slave( m_modbus, slave );

    switch( func )
    {
    case _FC_READ_COILS:
        ret = modbus_read_bits( m_modbus, addr, num, dest );
        break;
    case _FC_READ_DISCRETE_INPUTS:
        ret = modbus_read_input_bits( m_modbus, addr, num, dest );
        break;
    case _FC_READ_HOLDING_REGISTERS:
        ret = modbus_read_registers( m_modbus, addr, num, dest16 );
        is16Bit = true;
        break;
    case _FC_READ_INPUT_REGISTERS:
        ret = modbus_read_input_registers( m_modbus, addr, num, dest16 );
        is16Bit = true;
        break;
    case _FC_WRITE_SINGLE_COIL:
        ret = modbus_write_bit( m_modbus, addr,data_tulis);
        writeAccess = true;
        num = 1;
        break;
    case _FC_WRITE_SINGLE_REGISTER:
        ret = modbus_write_register( m_modbus, addr,data_tulis);
        writeAccess = true;
        num = 1;
        break;
    default:
        break;
    }

    //qDebug("-> RESPONSE: %d", ret);
    if( ret == num  )  {

        if( writeAccess )
        {
            //Update status semua yang perlu direset, sambil nunggu respon
            QTimer::singleShot( 2000, this, SLOT( ResetStatus() ) );
        }
        else
        {
            //bool b_hex = is16Bit && ui->checkBoxHexData->checkState() == Qt::Checked;
            QString qs_num;

            if(command==8)
            {
                for( int i = 0; i < num; ++i )
                {
                    int data = is16Bit ? dest16[i] : dest[i];
                    switch (i)
                    {
                    case 0:
                        //qDebug("--Inverter Output Frequency: %d", data);
                        inverter_freq_output=data;
                        break;
                    case 1:
                        //qDebug("--Inverter Status: %d", data);
                        inverter_status=data;
                        break;
                    default:
                        qDebug("--Invalid response");
                        break;
                    }
                }
                // --------- >>>>>> UpdateForm();
            }
            //Baca Register Realtime Status Monitor
            else if(command==9)
            {
                for( int i = 0; i < num; ++i )
                {
                    int data = is16Bit ? dest16[i] : dest[i];
                    switch (i)
                    {
                    case 0:
                        //qDebug("--Realtime Frekuensi: %d", data);
                        realtime_frek=data;
                        break;
                    case 1:
                        //qDebug("--Realtime Current: %d", data);
                        realtime_current=data;
                        break;
                    case 2:
                        //qDebug("--Realtime Direction: %d", data);
                        realtime_arah=data;
                        break;
                    case 3:
                        //qDebug("--Realtime PID Feedback (high): %d", data);
                        realtime_feedback_hi=data;
                        break;
                    case 4:
                        //qDebug("--Realtime PID Feedback (low): %d", data);
                        realtime_feedback_lo=data;
                        break;
                    case 5:
                        qDebug("--Realtime Input Terminal Status: %d", data);
                        realtime_input_status=data;
                        break;
                    case 6:
                        qDebug("--Realtime Output Terminal Status: %d", data);
                        realtime_output_status=data;
                        break;
                    default:
                        qDebug("--Invalid response");
                        break;
                    }
                }
                // -------------->>>>>>>>>>>>> UpdateForm();
            }
            if(command==10)
            {
                for( int i = 0; i < num; ++i )
                {
                    int data = is16Bit ? dest16[i] : dest[i];
                    switch (i)
                    {
                    case 0:
                        //qDebug("--RUN Command: %d", data);
                        command_run=data;
                        /*if(command_run==1)
                                motor_status=1;
                            else
                                motor_status=0;
                            */
                        break;
                    case 1:
                        //qDebug("--FW/RW Comand: %d", data);
                        command_arah=data;
                        break;
                    case 2:
                        //qDebug("--External Trip: %d", data);
                        command_trip=data;
                        break;
                    case 3:
                        //qDebug("--Trip Reset: %d", data);
                        command_trip_reset=data;
                        break;
                    default:
                        //qDebug("--Invalid response");
                        break;
                    }
                }
                // --------->>>>>>>>>>>> UpdateForm();
            }

            if(command==11)
            {
                for( int i = 0; i < num; ++i )
                {
                    int data = is16Bit ? dest16[i] : dest[i];
                    switch (i)
                    {
                    case 0:
                        qDebug("--Inverter Ready: %d", data);
                        inverter_ready=data;
                        break;
                    default:
                        qDebug("--Invalid response");
                        break;
                    }
                }
                /// --------------------->>>>>>>  UpdateForm();
            }
            modbus_busy=false;
        }
    }
    else
    {
        if( ret < 0 )
        {

            if(
        #ifdef WIN32
                    errno == WSAETIMEDOUT ||
        #endif
                    errno == EIO
                    )
            {
                if((command>=8)&&(command<=12))
                {
                    qDebug("Command 8 -> I/O error: did not receive any data from slave." );
                }
                else
                    QMessageBox::critical( this, tr( "I/O error" ),
                                           tr( "I/O error: did not receive any data from slave." ) );

            }
            else
            {
                if(command==8)
                {
                    qDebug("Command 8 -> I/O error: did not receive any data from slave." );
                }
                else if(command==9)
                {
                    qDebug("Command 9 ->I/O error: did not receive any data from slave." );
                }
                else if(command==10)
                {
                    qDebug("Command 10 ->I/O error: did not receive any data from slave." );
                }
                else
                    QMessageBox::critical( this, tr( "Protocol error" ),
                                           tr( "Slave threw exception \"%1\" or "
                                               "function not implemented." ).
                                           arg( modbus_strerror( errno ) ) );
            }
        }
        else
        {
            QMessageBox::critical( this, tr( "Protocol error" ),
                                   tr( "Number of registers returned does not "
                                       "match number of registers "
                                       "requested!" ) );
        }
    }
    /**/

}

void MotorControl::ResetStatus()
{
    //Informasikan bahwa port sudah siap dipakai
    modbus_busy=false;
}

void MotorControl::on_chk_motor_enable_clicked(bool checked)
{
    if(checked == true)
    {
        /* motor control */

        init_motor();

        connect(ui->cb_port, SIGNAL(currentIndexChanged(int)), this, SLOT(set_serialport(int)));

        set_serialport(ui->cb_port->currentIndex());

        //Update Status Inverter dan Motor
        update_inverter_status();

//        ui->cb_serial_port->setEnabled(true);
//        ui->pb_motor_start->setEnabled(true);
//        ui->pb_motor_stop->setEnabled(true);
//        ui->rb_motor_forward->setEnabled(true);
//        ui->rb_motor_reverse->setEnabled(true);
//        ui->spinBox_motor->setEnabled(true);
    }
    else if(checked == false)
    {
//        ui->cb_serial_port->setEnabled(false);
//        ui->pb_motor_start->setEnabled(false);
//        ui->pb_motor_stop->setEnabled(false);
//        ui->rb_motor_forward->setEnabled(false);
//        ui->rb_motor_reverse->setEnabled(false);
//        ui->spinBox_motor->setEnabled(false);
    }
}

void MotorControl::on_rb_motor_fw_clicked()
{
    set_arah=0;
    sendModbusRequest(7);
}

void MotorControl::on_rb_motor_rev_clicked()
{
    set_arah=1;
    sendModbusRequest(7);
}

void MotorControl::on_pb_motor_start_clicked()
{
    if(init_serial==0)
    {
        //Set Komunikasi via Modbus
        sendModbusRequest(45);
        delay_motor_command();
        sendModbusRequest(46);
        delay_motor_command();
        init_serial=1;
    }

    sendModbusRequest(4);

    update_inverter_status();
}

void MotorControl::on_pb_motor_stop_clicked()
{
    sendModbusRequest(5);

    update_inverter_status();
}

void MotorControl::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "0")
    {
        set_frekuensi = 0;
    }
    else if(arg1 == "300")
    {
        set_frekuensi = 300/6;
    }
    else if(arg1 == "600")
    {
        set_frekuensi = 600/6;
    }
    else if(arg1 == "900")
    {
        set_frekuensi = 900/6;
    }
    else if(arg1 == "1200")
    {
        set_frekuensi = 1200/6;
    }
    else if(arg1 == "1500")
    {
        set_frekuensi = 1500/6;
    }
    else if(arg1 == "1800")
    {
        set_frekuensi = 1800/6;
    }
    else if(arg1 == "2100")
    {
        set_frekuensi = 2100/6;
    }
    else if(arg1 == "2400")
    {
        set_frekuensi = 2400/6;
    }
    else if(arg1 == "2700")
    {
        set_frekuensi = 2700/6;
    }
    else if(arg1 == "3000")
    {
        set_frekuensi = 3000/6;
    }
    else if(arg1 == "3300")
    {
        set_frekuensi = 3300/6;
    }
    else if(arg1 == "3600")
    {
        set_frekuensi = 3600/6;
    }

    sendModbusRequest(6);
    update_inverter_status();
}

void MotorControl::updateInfo()
{

}
