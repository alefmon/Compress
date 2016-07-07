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
		int i=0, j=0, SB_posicao=6, string_length=0, bytes_pos=0;
		int *prefix, *posicoes;
		unsigned char *CS, *string, *saida;
		buffer *SB;
		CS= (unsigned char*) malloc(4*sizeof(unsigned char));
		prefix= (int*) malloc(4*sizeof(int));
		posicoes= (int*) malloc(32769*sizeof(int));
	//Inicializar os vetores.
		for(i=0;i<32769; i++){
			posicoes[i]=0;
		}
		for(i=0;i<4; i++){
			CS[i]=0;
			prefix[i]=0;
		}
	//Abrir os arquivos de entrada e de saída, passados como parâmetro no terminal.	
		input= fopen(argv[1],"rb");
		output= fopen(argv[2], "wb");
	//Colocar o cursor no fim do arquivo de entrada.
		fseek (input, 0, SEEK_END);
	//Verificar a posição do cursor, a fim de obter o tamanho do arquivo.
	  	tamanho_arquivo = ftell (input);
	  	string_length= tamanho_arquivo;

	  	string= (unsigned char*) malloc((2*tamanho_arquivo)*sizeof(unsigned char));
	  	saida= (unsigned char*) malloc((2*tamanho_arquivo)*sizeof(unsigned char));
	  	SB= (buffer*) malloc((2*tamanho_arquivo)*sizeof(buffer));
	  	for(i=0;i<2*tamanho_arquivo; i++){
	  		SB[i].caractere=0;
			SB[i].flag=0;
			string[i]=0;
			saida[i]=0;
		}
	//Retornar o cursor para o início do arquivo de entrada.
	  	rewind (input);
	//Armazenar o conteúdo do arquivo na string.
		size= fread (string, 1, tamanho_arquivo,input);
	//Copiar para o Search Buffer(SB) os primeiros caracteres da string.
		for(j=1;j<=5;j++){
			SB[j].caractere= string[j-1];
			if(j!=5)	
				SB[j].flag= 1;		
		}			
	//Realizar a compressão dos dados contidos no arquivo.
		LZ77(posicoes, prefix, CS, string, SB, &SB_posicao, output, string_length, saida, &bytes_pos);
	//Escrever os dados comprimidos no arquivo de saída.
		fwrite(saida, 1, bytes_pos+1, output);
		
		fclose(input);
		fclose(output);
		free(posicoes);
		free(prefix);
		free(saida);
		free(string);
		free(SB);
		free(CS);
		return 0;
}
