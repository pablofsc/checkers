#ifdef __unix__
	void limpartela() {
		system("clear");
	}
#endif

#ifdef _WIN32
	void limpartela() {
		system("cls");
	}
#endif

void aguardar() {
	getchar();
}

int qtdpecas(int tab[8][8], int jog) {
	int qtd = 0, x, y;
	for(y = 0; y < 8; y++) {
		for(x = 0; x < 8; x++) {
			if(dono(tab[x][y]) == jog) {
				qtd++;
			}
		}
	}
	
	return(qtd);
}

int checarvencedor(int tab[8][8]) {
	if(qtdpecas(tab, 1) == 0) {
		return(2);
	}
	else if(qtdpecas(tab, 2) == 0) {
		return(1);
	}
	
	return(0);
}

int outro(int jogador) {
	if(jogador == 1) {
		return(2);
	}
	else {
		return(1);
	}
}

void zerar(int tab[8][8]) {
	int x, y;
	for(y = 0; y < 8; y++) {
		for(x = 0; x < 8; x++) {
			tab[x][y] = 0;
		}
	}
}

void unsel(int tab[8][8]) {
	int x, y;
	for(y = 0; y < 8; y++) {
		for(x = 0; x < 8; x++) {
			if(tab[x][y] >= 5 && tab[x][y] <= 8) { // faz parar de piscar
				tab[x][y] -= 4;
			}
			else if(tab[x][y] == 9) { // remove marcadores de movimento
				tab[x][y] = 0;
			}
		}
	}
}

int cor(int jog) {
	switch(jog) {
		case 1:
			return(44);
		case 2:
			return(41);
	}
	return(0);
}

int dono(int casa) {
	if(casa == 0 || casa == 9) {
		return(0);
	}
	else if(casa % 2 != 0) {
		return(1);
	}
	else if(casa % 2 == 0) {
		return(2);
	}
	else {
		printf("Erro na função dono().\n");
		aguardar();
		return(-1);
	}
}

void inic(int tab[8][8]) {
	tab[0][0] = 1;
	tab[0][2] = 1;
	tab[1][1] = 1;
	tab[2][0] = 1;
	tab[2][2] = 1;
	tab[3][1] = 1;
	tab[4][0] = 1;
	tab[4][2] = 1;
	tab[5][1] = 1;
	tab[6][0] = 1;
	tab[6][2] = 1;
	tab[7][1] = 1;
	
	tab[0][6] = 2;
	tab[1][7] = 2;
	tab[1][5] = 2;
	tab[2][6] = 2;
	tab[3][7] = 2;
	tab[3][5] = 2;
	tab[4][6] = 2;
	tab[5][7] = 2;
	tab[5][5] = 2;
	tab[6][6] = 2;
	tab[7][7] = 2;
	tab[7][5] = 2;
}

int mostrardirecoes(int tab[8][8], int x, int y) {
	int i, j, jmin, jmax, direcoes = 0;
	
	switch(tab[x][y]) {
		case 1:
			jmin = y + 1;
			jmax = y + 1;
			break;
			
		case 2:
			jmin = y - 1;
			jmax = y - 1;
			break;
			
		case 3:
		case 4:
			jmin = y - 1;
			jmax = y + 1;
			break;
	}
	
	for(i = x - 1; i <= x + 1; i += 2) {
		for(j = jmin; j <= jmax; j += 2) {
			if(i > 7 || j > 7 || i < 0 || j < 0) {
				continue;
			}
			else {
				if(tab[i][j] == 0) {
					direcoes++;
					tab[i][j] = 9;
				}
				else if(dono(tab[i][j]) != dono(tab[x][y])) {
					if(((i + i - x) <= 7) && ((i + i - x) >= 0) && ((j + j - y) <= 7) && ((j + j - y) >= 0)) {
						if(tab[i + i - x][j + j - y] == 0) {
							direcoes++;
							tab[i + i - x][j + j - y] = 9;
						}
					}
				}
			}
		}
	}
	
	return(direcoes);
}

int cortab(int x, int y) {
	if(y % 2 == x % 2) {
		return(100);
	}
	if(y % 2 != x % 2) {
		return(47);
	}
}

void imprpeca(int tab[8][8], int x, int y) {
	switch(tab[x][y]) {
		case 0:
			printf("  ");
			break;
			
		case 1:
		case 2:
			printf("\e[%im" "  " "\e[0m", cor(dono(tab[x][y])));
			break;
			
		case 3:
		case 4:
			printf("\e[%im" "<>" "\e[0m", cor(dono(tab[x][y])));
			break;
			
		case 5:
		case 6:
			printf("\e[5;%im" "  " "\e[0m", cor(dono(tab[x][y])));
			break;

		case 7:
		case 8:
			printf("\e[5;%im" "<>" "\e[0m", cor(dono(tab[x][y])));
			break;
				
		case 9:
			printf("\e[%im" "><", cortab(x ,y));
			break;
					
		default:
			printf("ERR");
	}

	printf("\e[0m");
}

void impr(int tab[8][8], int visao) {
	int topo, base, variacao, esquerda, direita;

	switch(visao) {
		case 1:
			topo = 7;
			base = 0;
			esquerda = 0;
			direita = 7;
			variacao = -1;
			printf("\n  A     B     C     D     E     F     G     H     \n");
			break;

		case 2:
			topo = 0;
			base = 7;
			esquerda = 7;
			direita = 0;
			variacao = 1;
			break; 
	}

	int x, y;

	for(y = topo; y != base + variacao; y += variacao) {
		printf(" %i", y);
		for(x = esquerda; x != direita - variacao; x -= variacao) {
			printf("\e[%im" "      ", cortab(x, y));
		}
		printf("\e[0m" "\n");

		printf("  ");
		for(x = esquerda; x != direita - variacao; x -= variacao) {
			printf("\e[%im" "  ", cortab(x, y));
			imprpeca(tab, x, y);
			printf("\e[%im" "  ", cortab(x, y));
		}
		printf("\e[0m" "\n");

		printf("  ");
		for(x = esquerda; x != direita - variacao; x -= variacao) {
			printf("\e[%im" "      ", cortab(x, y));
		}
		printf("\e[0m" "\n");
	}
}

void impr_legacy(int tab[8][8], int visao) {
	int cima, baixo, variacao, esq, dir;
	switch(visao) {
		case 1:
			cima = 7;
			baixo = -1;
			esq = 0;
			dir = 8;
			variacao = -1;
			printf("\n     A   B   C   D   E   F   G   H  \n");
			break;
			
		case 2:
			cima = 0;
			baixo = 8;
			esq = 7;
			dir = -1;
			variacao = 1;
			printf("\n     H   G   F   E   D   C   B   A  \n");
			break;
	}
	
	int x, y;
	
	printf("   ┌───┬───┬───┬───┬───┬───┬───┬───┐\n");
	for(y = cima; y != baixo; y += variacao) {
		printf(" %i ", y);
		for(x = esq; x != dir; x -= variacao) {
			printf("\e[0m" "│");
			switch(tab[x][y]) {
				case 0:
					printf("   ");
					break;
					
				case 1:
				case 2:
					printf("\e[%im" " ■ " "\e[0m", cor(dono(tab[x][y])));
					break;
					
				case 3:
				case 4:
					printf("\e[%im" " ▲ " "\e[0m", cor(dono(tab[x][y])));
					break;
					
				case 5:
				case 6:
					printf("\e[5;%im" " ■ " "\e[0m", cor(dono(tab[x][y])));
					break;
				
				case 7:
				case 8:
					printf("\e[5;%im" " ▲ " "\e[0m", cor(dono(tab[x][y])));
					break;
				
				case 9:
					printf(" x ");
					break;
					
				default:
					printf("ERR");
			}
		}
		
		printf("│ %i\n", y);
		
		if(y != baixo - 1 && y != baixo + 1) {
			printf("   ├───┼───┼───┼───┼───┼───┼───┼───┤\n");
		}
	}
	
	printf("   └───┴───┴───┴───┴───┴───┴───┴───┘\n");
	if(visao == 1) {
		printf("     A   B   C   D   E   F   G   H  \n\n");
	}
	else {
		printf("     H   G   F   E   D   C   B   A  \n\n");
	}
}

xy lerterm() {
	xy retorno;
	char bffr[64];
	
	int i, x, y;
	for(i = 0; i < 64; i++) {
		bffr[i] = '\0';
	}
	
	fgets(bffr, 64, stdin);
	
	if(bffr[0] == '\n') {
		retorno.x = -1;
		retorno.y = -1;
		return(retorno);
	}
	else if(bffr[0] == '.') {
		retorno.x = -1;
		retorno.y = -2;
		return(retorno);
	}
	
	if(bffr[1] - 48 >= 0 && bffr[1] - 48 <= 7) {
		x = bffr[0];
		y = bffr[1];
	}
	else {
		y = bffr[0];
		x = bffr[1];
	}
	
	if(x >= 97 && x <= 122) {
		x -= 97;
	}
	else if(x >= 65 && x <= 90) {
		x -= 65;
	}
	else {
		x = -1;
	}
	
	y -= 48;
	
	if(bffr[2] != '\n') {
		x = -1;
		y = -1;
	}
	
	retorno.x = x;
	retorno.y = y;
	
	return(retorno);
}

int selecpeca(int jog, int tab[8][8]) {
	xy auxcoord;
	int x = -1, y = -1, direcoes = 0;
	
	if(qtdpecas(tab, jog) == 1) {
		printf("\n");
		for(y = 7; y >= 0; y--) { // encontra a peça restante
			for(x = 0; x < 8; x++) {
				if(dono(tab[x][y]) == jog) {
					break;
				}
			}
			
			if(dono(tab[x][y]) == jog) {
				break;
			}
		}
	}
	else {
		do {
			printf("\e[%im" " > " "\e[0m", cor(jog));
			auxcoord = lerterm();
			x = auxcoord.x;
			y = auxcoord.y;
		} while(((y < 0 || y > 7) || (x < 0 || x > 7)) && printf("Não é uma coordenada válida"));
		
		if(dono(tab[x][y]) != jog) {
			if(tab[x][y] == 0) {
				printf("Não há peça nesta posição");
			}
			else {
				printf("Esta peça não é sua");
			}
			
			return(0);
		}
		//printf("%i, %i, %i", x, y, tab[x][y]);
	}
	
	direcoes = mostrardirecoes(tab, x, y);
	
	if(direcoes == 0) {
		printf("Esta peça está presa");
	}
	else {
		tab[x][y] = tab[x][y] + 4;
	}
	
	return(direcoes);
}

int seleccasa(int jog, int tab[8][8]) {
	xy auxcoord;
	
	int i, j;
	for(j = 7; j >= 0; j--) { // encontra a peça selecionada
		for(i = 0; i < 8; i++) {
			if(tab[i][j] == jog + 4 || tab[i][j] == jog + 6) {
				break;
			}
		}
		
		if(tab[i][j] == jog + 4 || tab[i][j] == jog + 6) {
			break;
		}
	}
	
	int x = -1, y = -1;
	
	do {
		printf("\e[%im" " > " "\e[0m", cor(jog));
		auxcoord = lerterm();
		x = auxcoord.x;
		y = auxcoord.y;
	} while(((y < 0 || y > 7) || (x < 0 || x > 7)) && auxcoord.x != -1 && printf("Não é uma coordenada válida"));
	
	if(auxcoord.x == -1) {
		int q = 0;
		switch(auxcoord.y) {
			case -1:
				return(-1); // entrada vazia, voltar para seleção de peça
			
			case -2: // entrada com ponto, selecionada único movimento possível
				for(auxcoord.y = 7; auxcoord.y >= 0; auxcoord.y--) {
					for(auxcoord.x = 0; auxcoord.x < 8; auxcoord.x++) {
						if(tab[auxcoord.x][auxcoord.y] == 9) {
							x = auxcoord.x;
							y = auxcoord.y;
							q++;
						}
					}
				}
				
				if(q > 1) {
					printf("Há mais de um movimento disponível");
					return(1);
				}
		}
	}
	
	if(tab[x][y] != 9) {
		printf("Esta peça não pode ir para a casa selecionada");
		return(1);
	}
	
	//printf("%i, %i, %i", x, y, tab[x][y]);
	
	tab[x][y] = tab[i][j] - 4;
	tab[i][j] = 0;
	
	int comeu = 0;
	if((x - i) == 2 || (x - i) == -2) {
		comeu = 1;
		tab[(x + i)/2][(y + j)/2] = 0;
	}
	
	unsel(tab);
	
	if(comeu == 1) { // buscar sequências
		mostrardirecoes(tab, x, y);
		
		for(j = 7; j >= 0; j--) { // exclui as possibilidades de se movimentar sem comer outras peças
			for(i = 0; i <= 7; i++) {
				if(i - x != 2 && i - x != -2 && j - y != 2 && j - y != -2) {
					if(tab[i][j] == 9) {
						tab[i][j] = 0;
					}
				}
			}
		}
		
		for(i = - 2; i <= 2; i += 4) {
			for(j = - 2; j <= 2; j += 4) {
				if(x + i < 8 && x + i >= 0 && y + j < 8 && y + j >= 0) {
					if(tab[x + i][y + j] == 9) {
						tab[x][y] += 4;
						limpartela();
						impr(tab, jog);
						
						printf("Sequência");
						seleccasa(jog, tab);
						
						unsel(tab);
						return(0);
					}
				}
				else {
					continue;
				}
			}
		}
		
		unsel(tab);
	}
	
	return(0);
}

void upgrade(int tab[8][8]) {
	int i;
	for(i = 0; i <= 7; i++) {
		if(tab[i][7] == 1) {
			tab[i][7] = 3;
		}
	}
	
	for(i = 0; i <= 7; i++) {
		if(tab[i][0] == 2) {
			tab[i][0] = 4;
		}
	}
}
