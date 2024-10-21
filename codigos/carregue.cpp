#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

FILE* carregue(char quadro[9][9]);
FILE* carregue_continue_jogo (char quadro[9][9], char *nome_arquivo);
void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo);
FILE* crie_arquivo_binario(char quadro[9][9]);


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

	int opcao = 0;
	imprima(quadro);

	// apresente um menu com as opcoes
	menu();
	opcao = leia_opcao();
	if (opcao == 1){
	carregue(quadro);
	imprima(quadro);

	/*if (fb == NULL) {
		fb = crie_arquivo_binario(quadro);
	}
*/
	}
}


FILE* carregue(char quadro[9][9]){
	FILE *fb;
	int valor = 0;
	int nread;
	char nomeArquivo[20];
	char txt[5] = {".txt"};
	menu_arquivo();
	printf("Opcao: ");
	scanf("%d", &valor);
	getchar();
	int aux = 0,y = 0;
	// TODO Função incompleta

	if (valor == 1)	
	{
		printf("Qual o nome do arquivo txt: ");
		fgets(nomeArquivo,20,stdin);
		nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
		strcat(nomeArquivo, txt);
		
		fb = fopen(nomeArquivo,"r");
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
		return fb;
		
		
		}

	}else if(valor == 2)
	{
		// continuar jogo
			printf("Qual o nome do arquivo binario");
	}else if(valor ==9){
		printf("9");
	}

		

}

/* -----------------------------------------------------------------------------
 * CARREGAR NOVO JOGO
 * Carrega um novo jogo do Sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo) {
	// TODO
	printf("carregue novo jogo");
}
/* -----------------------------------------------------------------------------
 * CARREGAR CONTINUAR JOGO
 * Carrega um estado de jogo a partir de um arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
 /* -----------------------------------------------------------------------------
 * CRIAR ARQUIVO BINARIO
 * Criar arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* crie_arquivo_binario(char quadro[9][9]) {
	// TODO
	printf("carregue novo jogo");
	
}

FILE* carregue_continue_jogo (char quadro[9][9], char *nome_arquivo) {
	printf("carregue novo jogo");
	// TODO
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
