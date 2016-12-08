#ifndef ALOKASI_H
#define ALOKASI_H

#define BESAR_DATA_RECIP		120000 //30000
#define BESAR_DATA_BIG          36000000 // 1 Mega sample (4 Mega bytes ?)
#define BESAR_DATA_DEG                  1500
#define REAL_SAMPL                      80372       /* sampling rate sesungguhnya */
#define DATA_TIM                        12.44214403 /* 1 dibagi 80372, dalam microsecond */
#define PER_CLOCK                       10.333994   /* dalam nano second */

#define TIPE_DATA_P         2
#define	TIPE_DATA_V         3
#define	TIPE_DATA_DEG		91				/* derajat engkol mobar */

#define MULAI_KONEK             199
#define SUDAH_KONEK				201
#define KIRIM_ULANG				202
#define KIRIM_SELESAI			203

#define LOGGER_KANAL        4
#define LEBAR_AWAL          100     /* dalam milisecond */

#define BESAR_PAKET     1024
#define BESAR_PAKET_F   (BESAR_PAKET/4)     /* floating point */

#endif // ALOKASI_H
