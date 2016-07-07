#ifndef BIN_H
#define BIN_H 

//A função realiza a manipulação de bits e imprime no vetor de saída os bits correspondentes ao literal.
void empurra_bit_literal(unsigned char* saida, int* bytes_pos, unsigned char literal, int* bits_empurrados);

//A função realiza a manipulação de bits e imprime no vetor de saída os bits correspondentes ao ponteiro.
void empurra_bit_ponteiro(unsigned char* saida, int* bytes_pos, unsigned char comprimento, unsigned short r_offset, int* bits_empurrados);

//A função é utilizada da descompressão de arquivos. Ela imprime no vetor de saída o caractere corresponde aos próximos bits da string.
void desempurra_bit_literal(unsigned char* saida, int* bytes_pos, unsigned char* string, int* string_pos, int* bits_empurrados);

//A função é utilizada na descompressão de arquivos. Quando os próximos bits da string representam um ponteiro, ela obtém os valores do comprimento e do r_offset correspondentes ao ponteiro.
void desempurra_bit_ponteiro(unsigned char* comprimento, unsigned short* r_offset, unsigned char* string, int* string_pos, int* bits_empurrados);


#endif