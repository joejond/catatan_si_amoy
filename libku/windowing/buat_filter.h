#ifndef BUAT_FILTER_H
#define BUAT_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif


typedef float dfloat;

void buat_hanning(dfloat *out, int M);
void buat_hamming(dfloat *out, int M);
void buat_blackman(dfloat *out, int M);
void buat_rectangular(dfloat *out, int M);

//void konvolusi( dfloat *in, dfloat *out, dfloat *kernel, int M, int size);
//void buat_highpass(int M, dfloat fc, unsigned short kind, dfloat *out);

#ifdef __cplusplus
}
#endif

#endif // BUAT_FILTER_H
