#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "TAD_KMP.h"

int* prefixo(int* prefix, unsigned char* padrao, int tam_padrao){
		int q=2, k=0;
		prefix[1]=0;
		for(q=2; q<tam_padrao+1; q++){
			while(k>0 && padrao[k+1]!=padrao[q])
				k=prefix[k];
			if(padrao[k+1] == padrao[q])
				k++;
			prefix[q]=k;
		}
		return prefix;
}

int KMP(int* posicoes, int* prefix, unsigned char* padrao, buffer* texto, int tam_padrao, int tam_texto, int SB_posicao){
		int i=0, j=0, q=0;
		prefix= prefixo(prefix, padrao, tam_padrao);
	//A procura pelo padrão deve ser feita apenas nas últimas 32768 posições.
		if(SB_posicao>32769)
			i=(SB_posicao-32768);
		else
			i=1;		
	//Realizar a busca pelo padrão no texto.	
		for(; i<tam_texto+1; i++){
				while(q>0 && padrao[q+1]!= texto[i].caractere)
					q=prefix[q];
				if(padrao[q+1]==texto[i].caractere)
					q++;
			// Se achar o padrão, retorna a posição do texto em que está o primeiro caractere do padrão. 
				if(q==tam_padrao){	
					//O padrão só pode ser equivalente ao texto, caso os caracteres do texto tenham sido CS juntos.
					if(texto[i-2].flag==1){
						//Salvar no vetor as posições onde ocorreram o matching.
						posicoes[j]=(i-2);
						j++;
					}	
					//Continua a busca por novos matchings.
					q=prefix[q]; 
			}
		}
	//Retorna o número de matchings ocorridos.
		return j;
}