#ifndef LAIN_H
#define LAIN_H

#define     NAMA_APLIKASI       "Vibration Simulator"
#define     APPLICATION_NAME    NAMA_APLIKASI
#define     VERSI               "3.0"

struct t_setting
{
    /* port komunikasi */
    int  use;               /* 1 serial, 2 bluetooth, 3 usb */
    char port_name[64];
    char port_speed[32];
    char modul_ip[1024];     /* ip address dari module data akuisisi */
    char kanal_use[1024];    /* disiapkan untuk 1024 kanal */
    int client_status;

    /* kanal enable */
    int kanal_1;
    int kanal_2;
    int kanal_3;
    int kanal_4;

    /*  database terakhir dibuka
        supaya saat dijalanin lagi langsung buka database terakhir ini.
    */
    char last_open[1024];

    /* satuan */
    int unit_acc;       /* 1 mm/s2, 2 G */
    float ymax_accel;
    int unit_velo;      /* 1 mm/s, 2 IPS */
    float ymax_velo;
    int unit_disp;      /* 1 mm, 2 micron, 3 mills, */
    float ymax_disp;
    int unit_pcomb;     /* 1 bar, 2 psi */
    int unit_temp;      /* 1 Celecius, 2 Fahrenheit */
    int unit_ihp;       /* 1 kW, 2 horse power */
    int unit_flow_komp; /* 1 MMSCFD, 2 M3/h */
    int unit_frek;      /* 1 Hz, 2 rpm, 3 order */

    /* default rotating */
    int f_start;
    int f_stop;
    int fft_lines;
    int view_lines1;
    int view_lines2;
    int view_lines3;
    int view_lines4;
    int window;
    int averages;
    int PP;
    int fft_lines_index;    // untuk combo box saja
    int lebar_waveform;     // default awal
    int fase_enabled;
    int waveform_x;
    int waveform_y;
    float acc_sencitivity1;
    float acc_sencitivity2;
    float acc_sencitivity3;
    float acc_sencitivity4;

    /* warna2 kurva */
    int chart_mode;

    /* network database */
    char net_hostname[1024];
    char net_db_name[1024];
    char net_user[256];
    char net_passwd[256];
    int  sql_driver;    // 1 SQLITE, 2 MYSQL, 3 POSTGRE

    /* mode simulasi */
    int mode_simulasi;
    int cek_f1;         // simulasi enable
    int cek_f2;
    int cek_f3;
    int cek_f4;
    int cek_f5;

    int tipe_sinyal;
    int radio_bentuk;
    float edit_f1;
    float edit_f2;
    float edit_f3;
    float edit_f4;
    float edit_f5;
    float edit_a1;
    float edit_a2;
    float edit_a3;
    float edit_a4;
    float edit_a5;
    float edit_fasa1;
    float edit_fasa2;
    float edit_fasa3;
    float edit_fasa4;
    float edit_fasa5;
    int flag_simul;     // 1 jika baru saja dirubah.
                        // hal ini untuk menghindari kalkulasi ulang pada
                        // modul

    int wtf_timer;

};

struct t_param_vib
{
    int req_sampling_rate;      // request sampling rate
    int sampling_rate;          // sampling rate yang didapat
    int skip;                   //
    int len_data_wf;            // panjang data dalam satu chart waveform

    /* dicopy dari sebagian struct setting */
    int cek_f1;         // simulasi enable
    int cek_f2;
    int cek_f3;
    int cek_f4;
    int cek_f5;
    int radio_bentuk;
    float edit_f1;
    float edit_f2;
    float edit_f3;
    float edit_f4;
    float edit_f5;
    float edit_a1;
    float edit_a2;
    float edit_a3;
    float edit_a4;
    float edit_a5;
    float edit_fasa1;
    float edit_fasa2;
    float edit_fasa3;
    float edit_fasa4;
    float edit_fasa5;

    int   random_awal;      // sebagai informasi bahwa baru diminta.
    float pecahan_waveform; // satu lines dalam waveform mewakili berapa detik
};

void hitung_param_vibrasi(struct t_setting *set, struct t_param_vib *par);

//#define d_float float
typedef float d_float;

void iir_highpass(d_float *in, d_float *out, int len);
void hitung_koef_IIR_highpass(unsigned int srate, int f_start);

#endif // LAIN_H
