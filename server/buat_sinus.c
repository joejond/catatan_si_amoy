/*
	22 agt 2009
	furkan jadid
	bekasi, daun biru engineering
	
	fungsi untuk generate sinus 
	dicopy dari sig_gen yang dipakai untuk lipi
	
	menghasilkan short 0 - 0xFFFF
	
	30 agt 2009
	test untuk desain filter
	diganti ke float hasilnya
	
	1 Sept 2009
	buat_sinus diumpan array dari luar 

	5 Sept 2012
	buat_sinus diganti parameter fungsinya

	float *sin = buat_sinus(int frek, int sampling_rate);
	dibuat fix untuk 1 detik
	
*/

#include <math.h>

#define def_sampling_rate	50000


float gen_sinus(int t, int period)
{
	float rad = (float) (t * 2 * 3.14 / period);
	//float hasil = (float) (((sin(rad)/2) + 0.5) * 1.0);			// range nya 0 - 1.0
	//float hasil = (float) (sin(rad) * 1.0);			// range nya -1.0 -> 1.0

	float hasil = (float) (sin(rad) * 5.0);			// range nya -5.0 -> 5.0
	
	return (float) hasil;
}

/* return adalah periode yang mungkin */
int buat_sinus(int frek, float *sinout)
{
	int i;
	int period;
	
	if (frek == 0)
	{
		period = 1000;
		
		for (i=0; i<period; i++)	// tes DC
			sinout[i] = 1.00;
		
		return period;
	}
	
	period = (int) ( def_sampling_rate / frek );
		
	for (i=0; i<period; i++)
	{
		sinout[i] = (float) gen_sinus(i, period);

		//if (i < 10)
		//	printf("%f\n", sinout[i]);
	}
	
	return period;
}
