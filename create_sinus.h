#ifndef CREATE_SINUS_H
#define CREATE_SINUS_H
#include <math.h>

#define def_sampling_rate	50000


class create_sinus
{
public:
    create_sinus();
    float gen_sinus(int t, int period);
    int buat_sinus(int frek, float *sinout);
};

#endif // CREATE_SINUS_H
