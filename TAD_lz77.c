#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "TAD_KMP.h"
#include "TAD_lz77.h"
#include "TAD_binario.h"

void LZ77(int* posicoes, int* prefix, unsigned char *CS, unsigned char *string, buffer *SB, int* SB_posicao, FILE* output, int string_length, unsigned char* saida, int* bytes_pos){
		int i=3, j=6, k=0, comprimento=3, r_offset=0, SB_length=0, j1=0, j2=0, m=0, matchings=0, bits_empurrados=0, tamanho_match=3;
		tupla match;
		match.length=0;
		match.offset=32769;
	//Imprimir no veotr de saída os 3 primeiros caracteres da string.
		for(k=0;k<3;k++)
			empurra_bit_literal(saida, bytes_pos, string[k], &bits_empurrados);
		while(i<string_length){
			//Zerar o vetor com as posições de matching.	
				for(k=0;k<32769; k++){
					posicoes[k]=0;
				}
			//Copiar para a Current Substring (CS) os próximos 3 caracteres do string.
				for(k=0; k<3; k++){
					if((i+k)< string_length)
						CS[k+1]=string[i+k];
					else 
						break;
				}
			//Colocar uma flag no primeiro elemento da CS, para indicar que ele e os dois caracteres seguintes foram CS.	
				SB[(*SB_posicao)-2].flag=1;
				SB_length= (*SB_posicao)-1;
			//Quando a CS tem tamanho 3, verificar se há "matching" da CS no Buffer(SB) e a posição em que se encontra. 
				if(k==3)
					matchings= KMP(posicoes, prefix, CS, SB, 3, SB_length, (*SB_posicao));
				else
					matchings=0;
			//Caso não haja nenhum matching, imprimir os bits do primeiro caractere da CS e atualizar o SB.
				if(matchings== 0){
						empurra_bit_literal(saida, bytes_pos, CS[1], &bits_empurrados);
						SB[(*SB_posicao)].caractere=string[j-1];
						(*SB_posicao)++;
						i++;
						j++;
				}
			//Se encontrar matching, imprimir os bits de um ponteiro para a posição inicial da string encontrada.
				else{
						while(matchings>0){
								comprimento= 3;
								r_offset= (i-posicoes[m])+1;
							//Se o comprimento for maior que o r_offset, o matching é auto-referenciado.
								if(comprimento > r_offset){
									j1= posicoes[m]+2;
									j2=	j;
									//Processo de expansão. O processo verifica até onde as strings são equivalentes.
									while(string[j1]==string[j2] && tamanho_match<=258){
										j1++;
										j2++;
										tamanho_match++;
									}
									comprimento= (j2- i);
								}
							//Se o matching não for auto-referenciado.	
								else{
									j1= posicoes[m]+2;
									j2=	j;
									//Processo de expansão. O processo verifica até onde as strings são equivalentes.
									while(string[j1]==string[j2] && tamanho_match<=258){
										j1++;
										j2++;
										tamanho_match++;
									}
									comprimento= (j2- i);
								}
								matchings-=1;
								m++;
							//Verificar o matching que teve o maior comprimento.	
								if(comprimento>match.length){
									match.length= comprimento;
									match.offset= r_offset;
								}		
							//Caso ocorra empate no tamanho dos maiores matchings, verificar o menor r_offset.	
								else if(comprimento==match.length && r_offset<match.offset){
									match.length= comprimento;
									match.offset= r_offset;
								}					
						}	
					//Atualizar o conteúdo do SB.
						for(k=0; k<(match.length);k++){
							if((j+k-1)<string_length){
								SB[(*SB_posicao)].caractere= string[j+k-1];
								(*SB_posicao)++;
							}
						}	
					//Imprimir os bits do ponteiro no vetor de saída.	
						empurra_bit_ponteiro(saida, bytes_pos, (unsigned char) (match.length-3), (unsigned short) (match.offset-1), &bits_empurrados);
						i+=match.length;
						j+=match.length;
				}
			//Zerar as variáveis e os vetores.	
				comprimento=3;
				r_offset=0;
				m=0;
				match.length=0;
				match.offset=32769;
				matchings=0;
				tamanho_match=0;
				for(k=0;k<4; k++){
					CS[k]=0;
					prefix[k]=0;
				}					
			}	
			if((bits_empurrados % 8)==0)
				(*bytes_pos)--;
}


void descompactador_LZ77(unsigned char *string, int string_length, unsigned char* saida, int* bytes_pos, FILE* output){
		int j=0, string_pos=0, bits_empurrados=1;
		unsigned char comprimento;
		unsigned short r_offset=0;
		while(string_pos < string_length){
				if((bits_empurrados % 8)==0)
					string_pos--;
			//Caso o próximo caractere seja um ponteiro.
				if(((string[string_pos]<<((bits_empurrados-1) %8))& 0x80)==0x80){
						if((bits_empurrados % 8)==0)
							string_pos++;
					//Verificar o comprimento e o r_offset do ponteiro.	
						desempurra_bit_ponteiro(&comprimento, &r_offset, string, &string_pos, &bits_empurrados);
					//Imprimir no vetor de saída a string a qual corresponde o ponteiro.
						for(j=0; j<(int)comprimento;j++){
							saida[(*bytes_pos)]= saida[(*bytes_pos)-r_offset];
							(*bytes_pos)++;
						}
				}
			//Caso o próximo caractere seja um literal, imprimir o caractere no vetor de saída.
				else{
					if((bits_empurrados % 8)==0)
						string_pos++;
					desempurra_bit_literal(saida, bytes_pos, string, &string_pos, &bits_empurrados);				
				}	
		}
}

