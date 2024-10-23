#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

FILE* carregue(char quadro[9][9]);
FILE* carregue_continue_jogo (char quadro[9][9], char *nome_arquivo);
void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo);
FILE* crie_arquivo_binario(char quadro[9][9]);
void gen_random(char *s, const int len);
void salve_jogada_bin(FILE* fb, char quadro[9][9]);
/* Funcoes auxiliares */
void imprima(const char quadro[9][9]);
int leia_opcao();
void menu();
void menu_arquivo();


int main(){

	char quadro[9][9] = { {0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0}
};
	FILE *fb = NULL;
	int opcao;
	imprima(quadro);

	// apresente um menu com as opcoes
	menu();
	opcao = leia_opcao();
	if (opcao == 1){
		fb = carregue(quadro);
		imprima(quadro);
		
		if (fb == NULL) {
			fb = crie_arquivo_binario(quadro);
		}
	
		}

}

FILE* carregue(char quadro[9][9]){
	FILE *fb;
	int valor = 0;
	int nread;
	
	menu_arquivo();
	printf("Opcao: ");
	scanf("%d", &valor);
	getchar();
	// TODO Função incompleta

	if (valor == 1)	
	{
		char nomeArquivo[20];
		char txt[5] = {".txt"};
		printf("Qual o nome do arquivo txt: ");
		fgets(nomeArquivo,20,stdin);
		nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
		strcat(nomeArquivo, txt);
		carregue_novo_jogo(quadro,nomeArquivo);
		fb = crie_arquivo_binario(quadro);
		
	}

	else if(valor == 2)
	{
		// continuar jogo
			printf("Qual o nome do arquivo binario");
			char binario[8];
			char bin[5] = {".bin"};
			fgets(binario,4,stdin);
			binario[strcspn(binario, "\n")] = '\0';
			strcat(binario, bin);
			printf("%s",binario);

			fb = carregue_continue_jogo(quadro,binario);


	}else if(valor ==9){
		printf("9");
	}
	return fb;

		
}


/* -----------------------------------------------------------------------------
 * CARREGAR NOVO JOGO
 * Carrega um novo jogo do Sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo) {
		int aux = 0,y = 0;
		int nread;
		
		FILE *fb;
		fb = fopen(nome_arquivo,"r");
		if (fb == NULL){
			printf("nao abriu") ;
		}else{
		for (int i = 0; i < 81; i++) {
			fscanf(fb, "%d", &nread);
			
			if (aux == 9){
				y++;
				aux = 0;
				quadro[y][aux] = nread;
			}
			else{
				quadro[y][aux] = nread;
			}
			aux++;
		}
		imprima(quadro);
		fclose(fb);
		//criar arquivo binario e salvar o quadro no arquivo
}
}

 /* -----------------------------------------------------------------------------
 * CRIAR ARQUIVO BINARIO
 * Criar arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* crie_arquivo_binario(char quadro[9][9]) {
	int n[] ={0};
	char nomeArquivo[8];
	char bin[5] = {".bin"};
	int valor = 0;
	gen_random(nomeArquivo,3);
	nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
	strcat(nomeArquivo, bin);
	FILE * fb;
	fb = fopen(nomeArquivo,"wb");
	fwrite(n,sizeof(int),1,fb);

	for (int x = 0;x < 9;x++){
		for (int y=0;y<9;y++){
			valor = quadro[x][y];
			fwrite(&valor,sizeof(int),1,fb);
		}
	}
	
	printf("%s",nomeArquivo);
	return fb;


	
	
}
/* -----------------------------------------------------------------------------
 * CARREGAR CONTINUAR JOGO
 * Carrega um estado de jogo a partir de um arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* carregue_continue_jogo (char quadro[9][9], char *nome_arquivo) {
		FILE *fb;
		int nread,aux = 0,y=0;
		fb = fopen(nome_arquivo,"rb");
		if (fb == NULL){
			printf("Erro");
		}else{
		fseek(fb,-81*sizeof(int),SEEK_END);	

		for (int i = 0; i <= 81; i++) {
			fread(&nread,sizeof(int), 1, fb);	
				
			printf("%d",nread);	
			if (aux == 9){
			y++;
				aux = 0;
				quadro[y][aux] = nread;
			}
			else{
				quadro[y][aux] = nread;
			}
			aux++;
		}
		}
		imprima(quadro);
		return fb;

		


}


int leia_opcao () {
	int opcao = 0;

	printf("Opcao: ");
	scanf("%d", &opcao);
	printf("dentro da funcao");
	return opcao;
}

/* -----------------------------------------------------------------------------
 * MENU
 * Imprime o menu de opcoes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu() {
	puts("\n~~~~~~~~ SUDOKU ~~~~~~~~");
	puts("[1] - Carregar jogo");
	puts("[2] - Jogar");
	puts("[3] - Resolver um passo");
	puts("[4] - Resolver");
	puts("[9] - Finalizar");
	puts("--------");
}

/* -----------------------------------------------------------------------------
 * MENU ARQUIVO
 * Imprime o menu de opcoes do arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu_arquivo() {
	puts("\n~~~~~ MENU ARQUIVO ~~~~~");
	puts("[1] - Novo jogo");
	puts("[2] - Continuar jogo");
	puts("[9] - Retornar ao menu anterior");
	puts("--------");
}

void imprima(const char quadro[9][9]) {
	int i, j;

//	puts("~~~~~~~~ SUDOKU ~~~~~~~~");
	puts("    1 2 3   4 5 6   7 8 9");
	for (i = 0; i < 9; i++) {
		if (i % 3 == 0)
			puts("  -------------------------");
		for (j = 0; j < 9; j++) {

			if (j == 0)
				printf("%d | ", i+1);
			else if (j % 3 == 0)
				printf("| ");

			if (quadro[i][j] == 0)
				printf("- ");
			else
				printf("%d ", quadro[i][j]);
		}
		puts("|");
	}
	puts("  -------------------------");
}
void gen_random(char *s, const int len) {
	srand(time(NULL));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
	int i;

    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}
void salve_jogada_bin (FILE *fb, char quadro[9][9]) {
	int jogadas =0,valor=0;
	if (fb == NULL) {
        printf("Erro: Arquivo não está aberto.\n");
        return;
    }
	else {
		fread(&jogadas,sizeof(int),1,fb);
		jogadas++;
		fseek(fb, 0, SEEK_SET);
	    fwrite(&jogadas, sizeof(int), 1, fb);
		
		fseek(fb,0,SEEK_END);
		for (int x = 0;x < 9;x++){
		for (int y=0;y<9;y++){
			valor = quadro[x][y];
			fwrite(&valor,sizeof(int),1,fb);
		}
	}
	}


}