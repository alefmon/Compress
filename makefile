
CC = gcc
CFLAGS = -O2 


all: compress decompress

compress: compress.o TAD_lz77.o TAD_binario.o TAD_KMP.o
	$(CC) $(CFLAGS) compress.o TAD_lz77.o TAD_binario.o TAD_KMP.o -o compress.exe

compress.o: compress.c TAD_lz77.h TAD_binario.h TAD_KMP.h
	$(CC) $(CFLAGS) -c compress.c

decompress: decompress.o TAD_lz77.o TAD_binario.o TAD_KMP.o
	$(CC) $(CFLAGS) decompress.o TAD_lz77.o TAD_binario.o TAD_KMP.o -o decompress.exe

somador.o: decompress.c TAD_lz77.h TAD_binario.h TAD_KMP.h
	$(CC) $(CFLAGS) -c somador.c


TAD_lz77.o: TAD_lz77.h TAD_lz77.c
	$(CC) $(CFLAGS) -c TAD_lz77.c 
TAD_binario.o: TAD_binario.h TAD_binario.c
	$(CC) $(CFLAGS) -c TAD_binario.c 
TAD_KMP.o: TAD_KMP.h TAD_KMP.c
	$(CC) $(CFLAGS) -c TAD_KMP.c 

clean:
	rm -f compress.exe compress.o TAD_lz77.o TAD_binario.o TAD_KMP.o
	rm -f decompress.exe decompress.o TAD_lz77.o TAD_binario.o TAD_KMP.o
