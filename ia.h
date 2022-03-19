int modulo(int entrada) {
	if(entrada < 0) {
		return entrada*(-1);
	}
	else {
		return entrada;
	}
}

void ia(int tablr[8][8]) {
	if(qtdpecas(tablr, 2) == 0) return;
	
	int x, y, xb, yb, qtd = 0;
	
	xy opcoes[2][48];
	int pont[48];
	
	for(y = 0; y < 8; y++) {
		for(x = 0; x < 8; x++) {
			if(dono(tablr[x][y]) == 2) {
				if(mostrardirecoes(tablr, x, y) > 0) {
					//limpartela();
					//impr(tablr, 1);
					//printf("\e[%im" "               JOGADOR %i\n" "\e[0m", cor(2), 2);
					//printf("\n\e[6m\e[%im" "                 . . .\n" "\e[0m", cor(2));
					//usleep(150000);
					
					for(yb = 0; yb < 8; yb++) {
						for(xb = 0; xb < 8; xb++) {
							if(tablr[xb][yb] == 9) {
								opcoes[0][qtd].x = x;
								opcoes[0][qtd].y = y;
								
								opcoes[1][qtd].x = xb;
								opcoes[1][qtd].y = yb;
								
								qtd++;
							}
						}
					}
					
					unsel(tablr);
				}
			}
		}
	}
	
	//limpartela();
	//impr(tablr, 1);
	//printf("\e[%im" "               JOGADOR %i\n" "\e[0m", cor(2), 2);
	//printf("\n\e[6m\e[%im" "                 . . .\n" "\e[0m", cor(2));
	//usleep(1000000);
	
	//printf("\nQuantidade de movimentos possÃ­veis: %i\n", qtd);
	int i;
	for(i = 0; i < qtd; i++) {
		printf("%c%i -> %c%i\n", opcoes[0][i].x + 'A', opcoes[0][i].y, opcoes[1][i].x + 'A', opcoes[1][i].y);
	}
	
	aguardar();
	
	for(i = 0; i < qtd;) {
		if(modulo(opcoes[1][i].x - opcoes[0][i].x) == 2) {
			break;
		}
		else {
			i++;
		}
	}
	
	if(i == qtd) { // se percorreu toda a lista e nao encontrou possibilidades de comer, escolher uma aleatoriamente
		i = rand() % qtd;
	}
	
	tablr[opcoes[1][i].x][opcoes[1][i].y] = tablr[opcoes[0][i].x][opcoes[0][i].y]; // duplica a peça para o destino
	tablr[opcoes[0][i].x][opcoes[0][i].y] = 0; // remove a peça da origem
	
	if(modulo(opcoes[1][i].x - opcoes[0][i].x) == 2) { // verifica se uma peÃ§a foi comida
		tablr[(opcoes[1][i].x + opcoes[0][i].x)/2][(opcoes[1][i].y + opcoes[0][i].y)/2] = 0; // remove a peça comida
	}
}
