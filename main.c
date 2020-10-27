// 02/09/2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jogo.h"

int tablr[8][8];

int main() {
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
				impr(tablr, jogdavez);
				
				int aux;
				
				printf("\e[%im" "               JOGADOR %i\n" "\e[0m", cor(jogdavez), jogdavez);
				printf("\nSelecione uma peça");
				
				do {
					aux = selecpeca(jogdavez, tablr);
				} while(aux == 0);
				
				limpartela();
				impr(tablr, jogdavez);
				
				printf("\e[%im" "               JOGADOR %i\n" "\e[0m", cor(jogdavez), jogdavez);
				printf("\nIndique o destino da peça");
				
				do {
					aux = seleccasa(jogdavez, tablr);
				} while(aux > 0);
				
				if(aux == -1) {
					unsel(tablr);
					continue;
				}
				
				upgrade(tablr);
				limpartela();
				impr(tablr, jogdavez);
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
