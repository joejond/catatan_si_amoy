# makefile
CC = gcc
OBJ = server_udp.c
OBJ += buat_sinus.c	\

#		./fft/fourierf.c	\
#		./fft/fftmisc.c		

LIB = -lm

all : pm

pm : 	$(OBJ)
		$(CC) -w -o server_simul $(OBJ) $(LIB)

clean :
	rm server_simul
