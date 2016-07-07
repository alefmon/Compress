#include "TAD_lz77.h"
#ifndef KMP_H
#define KMP_H

//Função prefixo, utilizada pelo algoritmo KMP. Ela realiza o pré-processamento de um padrão a ser procurado no texto.
int* prefixo(int* prefix, unsigned char* padrao, int tam_padrao);

//A função corresponde ao algoritmo KMP, que realiza um casamento de strings, ou seja, verifica se um padrão está no texto.
int KMP(int* posicoes, int* prefix, unsigned char* padrao, buffer* texto, int tam_padrao, int tam_texto, int SB_posicao);

#endif
