/*
	UDP server untuk program
	Online Vibration Simulator

	furkan jadid
	Daun Biru Engineering

	5 Sept 2012

	Contoh UDP didapat dari :
	http://www.abc.se/~m6695/udp.html

	6 Sept 2012
	Ditambahkan informasi kanal untuk setiap paket.
	Ingat, kanal mulai dari kanal 1

	Data hilang tidak usah diurusi lagi, karena pakai UDP/Stremnya
	terus menerus
*/


#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#include "server_udp.h"

#define BUFLEN 512
#define NPACK 1000
#define PORT 5004

#define debug	printf

static struct tt_req t_req;
struct t_data_recip data_recip;

 /* untuk simulasi data saja */
float *sin1;
float *sin2;
int len_period;
int len_period2;
int frek_diminta = 23;	// Hz
int frek_diminta2 = 40;	// Hz
int sampling_rate = 50000;
//int pos_sin;
//int pos_sin2;

void proses_paket(int len, char *uip_appdata, struct sockaddr_in *other, int skt);

void diep(char *s)
{
	perror(s);
    exit(1);
}

/* cirrcular buffer saja */
void init_buffer_float()
{
	//pos_sin = 0;
}

void init_buffer_float2()
{
	//pos_sin2 = 0;
}

float pull_data_float(int *pos)
{
	int b = *pos;
	float a = sin1[ b++ ];
	//pos_sin++;

	if ( b > len_period) b = 0;
	*pos = b;

	return a;
}

float pull_data_float2(int *pos)
{
	float a = sin2[ *pos++ ];
	//pos_sin2++;

	if ( *pos > len_period2) *pos = 0;

	return a;
}

int main(void)
{
	struct sockaddr_in si_me, si_other;
 	int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    int n_paket = 0;
    
    /* alok memory dan generate sinus */
    int temp_size = (int) (sampling_rate / frek_diminta);
	sin1 = (float *) malloc( 5 * temp_size);	
	len_period = buat_sinus(frek_diminta, sin1);
	debug("dapat len_period = %d\n", len_period);
	init_buffer_float();

	/* untuk kanal 2 */
	temp_size = (int) (sampling_rate / frek_diminta2);
	sin2 = (float *) malloc( 5 * temp_size);	
	len_period2 = buat_sinus(frek_diminta2, sin2);
	debug("dapat len_period2 = %d\n", len_period2);
	init_buffer_float2();
	
  
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
          diep("socket");
    
        memset((char *) &si_me, 0, sizeof(si_me));
        si_me.sin_family = AF_INET;
        si_me.sin_port = htons(PORT);
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(s, &si_me, sizeof(si_me))==-1)
            diep("bind");
    
        //for (i=0; i<NPACK; i++) 
		while(1)
        {
          	if (recvfrom(s, buf, BUFLEN, 0, &si_other, &slen)==-1)
            	diep("recvfrom()");

			n_paket++;
           	printf("Received packet (%d) from %s:%d\nData: %s\n\n", n_paket, 
                 inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);

            proses_paket(slen, buf, &si_other, s);
        }
    
        close(s);
        return 0;
}


void proses_paket(int len, char *uip_appdata, struct sockaddr_in *other, int skt)
{
	int i;
	int i_kanal;
	int slen = sizeof (struct sockaddr_in);
	struct tt_req *pt_req;
	//int pos1 = 0;
	//int pos2 = 0;
	
	if (len >= 7)
	{
			memcpy( (char *) &t_req, uip_appdata, sizeof (t_req));
			pt_req = &t_req;
					
			if (strncmp( t_req.head, "getdata", 7) == 0)
			{
				//debug("Ok data request !\n");
				
				/* jika dari urutan = 0, berarti awal permintaan */
				if (t_req.urutan == 0)
				{
					//debug("data urutan = 0, pos_data %d\n", pt_req->pos_data);
					t_req.urut_kanal = 0;
					t_req.jum_sample = 5100;	 // hardcode dulu
					t_req.jum_paket_p = ((t_req.jum_sample * 4)/BESAR_PAKET) + 1;
				}
					
				t_req.total = t_req.jum_paket_p;
				t_req.state = SUDAH_KONEK;

				debug("Total akan dikirim %d paket, mulai dari %d\r\n", t_req.total, t_req.urutan );

				for (i=0; i<= (t_req.total + 1); i++)
				{
					/* 
						Data tiap kanal dikirim selang seling
						kita mulai dari kanal 1 dulu 
					*/

					/* memasukkan data simulasi dalam buffer */
					int y;
					float *p_buf = t_req.buf;

					
					
					for (y=0; y<BESAR_PAKET_F; y++)
					{
						*p_buf++ = pull_data_float( &t_req.pos_data );
					}		
					//debug("pos %d\n", t_req.pos_data);
					/*  nah ini jadi fatal, untuk koneksi yang cepat
						ini bisa diterima satu batch oleh client */
					t_req.kanal = 1;					
					if (sendto(skt, (char *) &t_req, sizeof (t_req), 0, other, slen)==-1) 
						debug("error kirim %d", i);

					t_req.urutan++;
					
					/* kirim data kanal 2 */
					p_buf = (float *) t_req.buf;	
					for (y=0; y<BESAR_PAKET_F; y++)
					{
						*p_buf++ = pull_data_float2( &t_req.pos_data );
					}

					/* jangan lupa, katakan selesai */
					if (t_req.urut_kanal == (t_req.total+1) )
					{
						t_req.state = KIRIM_SELESAI;
						debug("SELESAI\n");
					}
					
					t_req.kanal = 2;
					if (sendto(skt, (char *) &t_req, sizeof (t_req), 0, other, slen)==-1) 
						debug("error kirim2 %d", i);		
					
					t_req.urutan++;
					t_req.urut_kanal++;
				}
			}
			else if (strncmp( t_req.head, "ressend", 7) == 0)
			{
				debug("kommand kirim ulang %d !\r\n", t_req.urutan);
			}
	}

}
