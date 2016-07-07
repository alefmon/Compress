#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "TAD_binario.h"


void empurra_bit_literal(unsigned char* saida, int* bytes_pos, unsigned char literal, int* bits_empurrados){
		int i=(*bytes_pos);
	//Se tiverem 7 bits empurrados, adicionar o zero na última posição.	
		if((*bits_empurrados)%8==7){
			saida[i]= ((saida[i]>>1)<<1);
			(*bits_empurrados)++;
			i++;
			saida[i]= saida[i] | literal ;
			i++;
		}
	//Adicionar o 0 no início.	
		else{
			(*bits_empurrados)++;
			saida[i]= saida[i] | literal >>((*bits_empurrados)%8);
			i++;
			saida[i]= saida[i] | literal << (8-((*bits_empurrados)%8));
		}
		(*bytes_pos)=i;
}
void empurra_bit_ponteiro(unsigned char* saida, int* bytes_pos, unsigned char comprimento, unsigned short r_offset, int* bits_empurrados){
		int i=(*bytes_pos);
	//r_offset1 e r_offset2 auxiliarão na troca do offset para Big Endian.
		unsigned char r_offset1,r_offset2;
		r_offset2= r_offset;
		r_offset1= (r_offset >> 8);
		if((*bits_empurrados)%8==7){
			//colocar o bit 1 para indicar o ponteiro.
			saida[i]= saida[i] | 1;
			i++;
			saida[i]= comprimento;
			i++;
			saida[i]= (r_offset1<<1);
			saida[i]= saida[i] | (r_offset2>>7);
			i++;
			saida[i]= saida[i] | (r_offset2<<1);
		}	
		else{
			//colocar o bit 1 para indicar o ponteiro.
			saida[i]= saida[i] | (1<<(7-((*bits_empurrados)%8)));
			saida[i]= saida[i] | (comprimento>>((*bits_empurrados+1)%8));
			i++;
			saida[i]= saida[i] | (comprimento<<(8-((*bits_empurrados+1)%8)));
			saida[i]= saida[i] | (r_offset1>>((*bits_empurrados)%8));
			i++;
			saida[i]= saida[i] | (r_offset1<<(8-((*bits_empurrados)%8)));
			saida[i]= saida[i] | (r_offset2>>((*bits_empurrados)%8));
			i++;
			saida[i]= saida[i] | (r_offset2<<(8-((*bits_empurrados)%8)));
		}
		(*bytes_pos)=i;

}		

void desempurra_bit_literal(unsigned char* saida, int* bytes_pos, unsigned char* string, int* string_pos, int* bits_empurrados){
		int i=0, j=0;
		i= (*bytes_pos);
		j= (*string_pos);
	//O vetor de saída recebe o próximo caractere.	
		saida[i]= string[j] << ((*bits_empurrados) % 8);
		saida[i]= saida[i] | (string[j+1] >> (8 - ((*bits_empurrados) % 8)));
		i++;
		j++;
		(*bits_empurrados)++;
		if(((*bits_empurrados) % 8)==0)
			j++;
		(*bytes_pos)=i;
		(*string_pos)=j;
}

void desempurra_bit_ponteiro(unsigned char* comprimento, unsigned short* r_offset, unsigned char* string, int* string_pos, int* bits_empurrados){
		int j=0;
	//r_offset1 e r_offset2 auxiliarão na troca do offset para Big Endian.	
		unsigned char r_offset1, r_offset2;
		j= (*string_pos);
	//Obter o valor referente ao comprimento do ponteiro.	
		(*comprimento)= string[j] << ((*bits_empurrados) % 8);
		(*comprimento)= (*comprimento) | (string[j+1] >> (8 - ((*bits_empurrados) % 8)));
		j++;
	//Obter o valor referente ao r_offset do ponteiro.		
		r_offset2= string[j] << ((*bits_empurrados) % 8);
		r_offset2= r_offset2 | (string[j+1] >> (8 - ((*bits_empurrados) % 8)));
		r_offset2= r_offset2 >> 1; 
		if(((*bits_empurrados)%8)!=0)
			j++;
		r_offset1= string[j] << ((*bits_empurrados-1) % 8);
		if(((*bits_empurrados)%8)!=1)
			r_offset1= r_offset1 | (string[j+1] >> (8 - ((*bits_empurrados-1) % 8)));
		j++;
		if(((*bits_empurrados) % 8)==0)
			j++;
		(*r_offset)= (unsigned short)r_offset1;
		(*r_offset)= (*r_offset) | ((unsigned short)r_offset2 << 8);
	//Armazenar o comprimento e o r_offset nas variáveis globais. 	
		(*comprimento)+=3;
		(*r_offset)++;
		(*string_pos)=j;
}
