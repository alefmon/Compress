#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "TAD_KMP.h"
#include "TAD_lz77.h"

int main(int argc, char const *argv[])
{
		size_t size;
		unsigned long int tamanho_arquivo;
		FILE *input, *output;
		int i=0, j=0, string_length=0, bytes_pos=0;
		unsigned char *string, *saida;
	//Abrir os arquivos de entrada e de saída, passados como parâmetro no terminal.	
		input= fopen(argv[1],"rb");
		output= fopen(argv[2], "wb");
	//Colocar o cursor no fim do arquivo.
		fseek (input, 0, SEEK_END);
	//Verificar a posição do cursor, a fim de obter o tamanho do arquivo.
	  	tamanho_arquivo = ftell (input);
	  	string_length= tamanho_arquivo;

	  	string= (unsigned char*) calloc(tamanho_arquivo+258,sizeof(unsigned char));
	  	saida= (unsigned char*) calloc((24*tamanho_arquivo),sizeof(unsigned char)); 
	//Retornar o cursor para o início do arquivo.
	  	rewind (input);
	//Armazenar o conteúdo do arquivo na string.
		size= fread (string, 1, tamanho_arquivo,input);
	//Realizar a descompressão dos dados contidos no arquivo
		descompactador_LZ77(string, string_length, saida, &bytes_pos, output);
	//Escrever os dados no arquivo de saída.
		fwrite(saida, 1, bytes_pos-1, output);

		fclose(input);
		fclose(output);
		free(saida);
		free(string);
		return 0;
}
