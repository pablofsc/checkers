//      02/09/2020: início do desenvolvimento
//      06/09/2020: peças podem ser selecionadas, mas não movidas
//      07/09/2020: peças podem ser movidas, mas não podem comer outras peças
//      10/09/2020: peças podem comer outras peças, mas não viram damas

//                  peças podem virar damas, mas não é possível desfazer a seleção de peça
//      11/09/2020: é possível voltar para a seleção de peça + melhorias na interface
// 1.0: 14/09/2020: vence-se a partida comendo todas as peças do adversário
// 1.1: 19/09/2020: corrigido bug na função dono(), melhorias de usabilidade e interface, implementadas sequências
// 1.2: 20/09/2020: otimizações
//      16/12/2020: início do desenvolvimento da IA
//      09/06/2021: nova função de impressão 
// 2.0: corrigir problemas na interface

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <time.h>

#include "bibl.h"
#include "jogo.h"
#include "ia.h"

int tablr[8][8];

int main() {	
	srand(time(NULL));
	//printf("\n Na seleção de movimento, você pode voltar à seleção de peças pressionando enter sem inserir uma coordenada.");
	//printf("\n Quando houver somente um movimento disponível para uma peça, você pode inserir um ponto no lugar da coordenada.\n");
	//printf("\nPressione enter para iniciar > ");
	//getchar();
	
	int vencedor, primjog = 1, jogdavez;
	
	for(;;) {
		jogdavez = primjog;
		
		zerar(tablr);
		inic(tablr);
		
		vencedor = 0;
		while(vencedor == 0) {
			for(;;) {
				limpartela();
				impr(tablr, 1);
				printf("  ");
				printf("\e[%im" "                    JOGADOR %i                   \n" "\e[0m", cor(jogdavez), jogdavez);
			
				if(jogdavez == 1) {
					printf("\nSelecione uma peça");
					
					int aux;
					
					do {
						aux = selecpeca(jogdavez, tablr);
					} while(aux == 0);
					
					limpartela();
					impr(tablr, jogdavez);

					printf("  ");
					printf("\e[%im" "                    JOGADOR %i                   \n" "\e[0m", cor(jogdavez), jogdavez);
					printf("\nIndique o destino da peça");
					
					do {
						aux = seleccasa(jogdavez, tablr);
					} while(aux > 0);
					
					if(aux == -1) {
						unsel(tablr);
						continue;
					}
				}
				else if(jogdavez == 2) {
					printf("\n\e[6m\e[%im" "                 . . .\n" "\e[0m", cor(jogdavez));
					ia(tablr);
				}
				
				upgrade(tablr);
				limpartela();
				impr(tablr, 1);
				break;
			}
			
			usleep(1000000);
			vencedor = checarvencedor(tablr);
			jogdavez = outro(jogdavez);
		}
		
		printf("O " "\e[%im" "jogador %i" "\e[0m" " venceu a partida!\n", cor(outro(jogdavez)), outro(jogdavez));
		printf("Pressione enter para iniciar outra partida > ");
		getchar();
		primjog = outro(primjog);
	}
}
