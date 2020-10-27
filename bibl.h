struct coordenada {
	int x;
	int y;
};

typedef struct coordenada xy;

void aguardar();
int qtdpecas(int tab[8][8], int jog);
int checarvencedor(int tab[8][8]);
int outro(int jogador);
void zerar(int tab[8][8]);
void unsel(int tab[8][8]);
int cor(int jog);
int dono(int casa);
void inic(int tab[8][8]);
void impr(int tab[8][8], int visao);
xy lerterm();
int selecpeca(int jog, int tab[8][8]);
int seleccasa(int jog, int tab[8][8]);
void upgrade(int tab[8][8]);
