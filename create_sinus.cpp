#include "create_sinus.h"

create_sinus::create_sinus()
{
}

float create_sinus::gen_sinus(int t, int period)
{
    float rad = (float) (t * 2 * 3.14 / period);
    //float hasil = (float) (((sin(rad)/2) + 0.5) * 1.0);			// range nya 0 - 1.0
    //float hasil = (float) (sin(rad) * 1.0);			// range nya -1.0 -> 1.0

    float hasil = (float) (sin(rad) * 5.0);			// range nya -5.0 -> 5.0

    return (float) hasil;
}

int create_sinus::buat_sinus(int frek, float *sinout)
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
