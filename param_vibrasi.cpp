/*
    9 Sept 2012
    furkan jadid

    parameter vibrasi

    */
#include <QDebug>

#include "lain.h"
#include "math.h"
#include "float.h"


void hitung_param_vibrasi(struct t_setting *set, struct t_param_vib *par)
{
   // qDebug("%s()", __FUNCTION__);

    par->req_sampling_rate = (int) (set->f_stop * 256)/100;
    //qDebug("%s(): f_start %d, f_stop %d, req_rate %d", __FUNCTION__,  set->f_start, set->f_stop, par->req_sampling_rate);

    // hitung panjang data waveform
    // rumus : sampling rate * lebar_wafeform (ms) / 1000 (ms)

    par->len_data_wf = (par->req_sampling_rate * set->lebar_waveform/ 1000);
    //qDebug("%s(): len_data_wf %d", __FUNCTION__, par->len_data_wf);

    /* mengkopi setting2 dummy saja */
    par->cek_f1 = set->cek_f1;
    par->cek_f2 = set->cek_f2;
    par->cek_f3 = set->cek_f3;
    par->cek_f4 = set->cek_f4;
    par->cek_f5 = set->cek_f5;

    par->edit_f1 = set->edit_f1;
    par->edit_f2 = set->edit_f2;
    par->edit_f3 = set->edit_f3;
    par->edit_f4 = set->edit_f4;
    par->edit_f5 = set->edit_f5;

    par->edit_a1 = set->edit_a1;
    par->edit_a2 = set->edit_a2;
    par->edit_a3 = set->edit_a3;
    par->edit_a4 = set->edit_a4;
    par->edit_a5 = set->edit_a5;

    par->edit_fasa1 = set->edit_fasa1;
    par->edit_fasa2 = set->edit_fasa2;
    par->edit_fasa3 = set->edit_fasa3;
    par->edit_fasa4 = set->edit_fasa4;
    par->edit_fasa5 = set->edit_fasa5;

    par->random_awal = rand();

    // hitung pecahan waveform (faktor pengali sumbu x )
    par->pecahan_waveform = (float) (1000.00 / par->req_sampling_rate);
}

#define E_NATURAL	2.718281828

//#define d_float float
//typedef d_float float;
typedef float d_float;

static d_float a0;
static d_float a1;
static d_float b1;


static d_float in_lama;
static d_float out_lama;

void hitung_koef_IIR_highpass(unsigned int srate, int f_start)
{
    d_float pangkat;
    d_float xf;

    //pangkat = (float) ( 0.50 / (float) (srate * 1.0) );
    //pangkat = (float) ( 0.317 / (float) (srate * 1.0) );		// masih kurang separo
    pangkat = (d_float) ( 0.158 / (d_float) (srate * 1.0) );

    d_float ff_start = (d_float) f_start * 1.0;

    pangkat = (d_float) ( ff_start / (d_float) (srate * 1.0) );

    //printf("start %f, rate %d\n", ff_start, srate);

    /* disini menghitung koefisien filter recursive */
    pangkat = (d_float) (2.0 * M_PI * pangkat);

    xf = (d_float) pow( E_NATURAL, pangkat);
    xf = 1.00 / xf;

    // low pass
    a0 = (d_float) (1 - xf);
    b1 = (d_float) xf;

    // high pass
    a0 = (d_float) ((1 + xf)/2.00);
    a1 = (d_float) -1 * a0;
    b1 = xf;

    //a0 = 0.93;
    //a1 = -0.93;
    //b1 = 0.86;

//    printf("%s(): a0 = %.10f, a1= %f, b1 = %.10f, %.20f\r\n", \
//           __FUNCTION__, a0, a1, b1, pangkat);

    in_lama = 0;
    out_lama = 0;

    return;
}

void iir_highpass(d_float *in, d_float *out, int len)
{
    int i;
    out[0] = (a0 * in[0]) + (a1 * in_lama) + (b1 * out_lama);

    i = 0;
    qDebug("%d: %f: %f: %f: %f", i, out[i], in[i], out_lama, in_lama);

    for (i=1;i<len; i++)
    {
         out[i] = (d_float)(a0 * in[i]);
         out[i] += (d_float)(a1 * in[i-1]);
         out[i] += (d_float)(b1 * out[i-1]);

         if (i < 32)
             qDebug("%d: %f: %f: %f: %f", i, out[i], in[i], out[i-1], in[i-1]);
    }
         //a_lama = (a0 * in[i] + (b1 * a_lama);

    in_lama = in[len-1];
    out_lama = out[len-1];
    i = len - 1;
    qDebug("%d: %f: %f: %f: %f", i, out[i], in[i], out_lama, in_lama);
}
