#ifndef LZ77_H
#define LZ77_H

//A estrutura de dados é utilizada para representar os matchings (comprimento e r_offset).
typedef struct{
	int length;
	int offset;
}tupla;

//A estrutura de dados é utilizada para representar os elementos do SB, de forma que cada elemento possa ter uma flag para mostrar se o caractere foi ou não CS.
typedef struct{
	unsigned char caractere;
	int flag;
}buffer;

//A função realiza a compressão dos dados de um arquivo, a partir do algoritmo LZ77.
void LZ77(int* posicoes, int* prefix, unsigned char *CS, unsigned char *LAB, buffer *SB, int* SB_posicao, FILE* output, int LAB_length, unsigned char* saida, int* bytes_pos);

//A função realiza a descompressão dos dados de um arquivo.
void descompactador_LZ77(unsigned char *string, int string_length, unsigned char* saida, int* bytes_pos, FILE* output);


#endif
