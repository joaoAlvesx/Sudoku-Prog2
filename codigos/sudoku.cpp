#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Constantes */
#define ERROR_FILE_MSG	"Nao foi possivel abrir o arquivo!\n"
#define INVALID_OPTION	"Opcao invalida! Tente novamente!"

/* Definicoes de tipo */
enum boolean {
	FALSO=0, VERDADEIRO=1
};

/* Prototipos */
FILE* carregue(char quadro[9][9]);
FILE* carregue_continue_jogo (char quadro[9][9], char *nome_arquivo);
void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo);
FILE* crie_arquivo_binario(char quadro[9][9]);
int determine_quadrante(int x, int y);
int eh_valido(const char quadro[9][9], int x, int y, int valor);
int eh_valido_na_coluna(const char quadro[9][9], int y, int valor);
int eh_valido_no_quadrante3x3(const char quadro[9][9], int x, int y, int valor);
int eh_valido_na_linha(const char quadro[9][9], int x, int valor);
int existe_posicao_vazia(const char quadro[9][9]);
void imprima(const char quadro[9][9]);
void jogue();
int resolve_completo(FILE*, char quadro[9][9]);
void resolve_um_passo(char quadro[9][9]);
void salve_jogada_bin(FILE* fb, char quadro[9][9]);

/* Funcoes auxiliares */
int fim_x(int quadr);
int fim_y(int quadr);
int leia_opcao();
void gen_random(char *s, const int len);
int ini_x(int quadr);
int ini_y(int quadr);
void menu();
void menu_arquivo();


/* -----------------------------------------------------------------------------
 * -----------------------------------------------------------------------------
 * MAIN
 * /////////////////////////////////////////////////////////////////////////////
 */
int main() {

	// inicia o jogo
	jogue();

	return 0;
}

/* -----------------------------------------------------------------------------
 * CARREGAR
 * Inicializa o SUDOKU a partir de um novo jogo ou estado de jogo anterior
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* carregue(char quadro[9][9]) {
	int opcao;
	FILE *fb;
	int valor = 0;
	int nread;

	menu_arquivo();
	opcao = leia_opcao();


	// TODO Função incompleta

	switch(opcao) {

		// carregar novo sudoku
		case 1:{
			char nomeArquivo[20];
			char txt[5] = {".txt"};
			printf("Qual o nome do arquivo txt: ");
			fgets(nomeArquivo,20,stdin);
			nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
			strcat(nomeArquivo, txt);
			carregue_novo_jogo(quadro,nomeArquivo);
			fb = crie_arquivo_binario(quadro);
			return fb;
			break;
		}
		// continuar jogo
		case 2:{
			printf("Qual o nome do arquivo binario");
			char binario[8];
			char bin[5] = {".bin"};
			fgets(binario,4,stdin);
			binario[strcspn(binario, "\n")] = '\0';
			strcat(binario, bin);

			fb = carregue_continue_jogo(quadro,binario);
			return fb;
			break;
		}
		// retornar ao menu anterior
		case 9:{
			return fb;
			break;
		}
		default:{
			return fb;
			break;
		}
		return fb;
}
}
/* -----------------------------------------------------------------------------
 * CARREGAR CONTINUAR JOGO
 * Carrega um estado de jogo a partir de um arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* carregue_continue_jogo (char quadro[9][9], char *nome_arquivo) {
		FILE *fb;
		int nread,aux = 0,y=0;
		fb = fopen(nome_arquivo,"rb+");
		if (fb == NULL){
			printf("Erro");
		}else{
		fseek(fb,-81*sizeof(int),SEEK_END);	

		for (int i = 0; i <= 81; i++) {
			fread(&nread,sizeof(int), 1, fb);	
				
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
			printf("Erro") ;
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
	int n = 0;
	char nomeArquivoBin[8];
	char bin[5] = {".bin"};
	int valor = 0;
	gen_random(nomeArquivoBin,3);
	nomeArquivoBin[strcspn(nomeArquivoBin, "\n")] = '\0';
	strcat(nomeArquivoBin, bin);
	FILE * fb;
	fb = fopen(nomeArquivoBin,"wb+");
	fwrite(&n,sizeof(int),1,fb);
	fseek(fb,0,SEEK_END);
	for (int x = 0;x < 9;x++){
		for (int y=0;y<9;y++){
			valor = quadro[x][y];
			fwrite(&valor,sizeof(int),1,fb);
		}
	}
	fclose(fb);
	fb = fopen(nomeArquivoBin,"rb+");
	return fb;
}

/* -----------------------------------------------------------------------------
 * DETERMINAR QUADRANTE
 * Dado as posicoes x e y, determina o quadrante do quadro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int determine_quadrante(int x, int y) {
	if (x < 3 && y < 3)
		return 1;
	else if (x < 3 && y < 6)
		return 2;
	else if (x < 3 && y < 9)
		return 3;
	else if (x < 6 && y < 3)
		return 4;
	else if (x < 6 && y < 6)
		return 5;
	else if (x < 6 && y < 9)
		return 6;
	else if (x < 9 && y < 3)
		return 7;
	else if (x < 9 && y < 6)
		return 8;
	else
		return 9;
}

/* -----------------------------------------------------------------------------
 * E VALIDO
 * Determina se um valor na posicao x e y eh valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int eh_valido(const char quadro[9][9], int x, int y, int valor) {

	// verifica as tres condicoes
	if (!eh_valido_na_coluna(quadro, y, valor))
		return FALSO;
	if (!eh_valido_na_linha(quadro, x, valor))
		return FALSO;
	if (!eh_valido_no_quadrante3x3(quadro, x, y, valor))
		return FALSO;

	return VERDADEIRO;
}

/* -----------------------------------------------------------------------------
 * E VALIDO NA COLUNA
 * Verifica se um valor na coluna y e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int eh_valido_na_coluna(const char quadro[9][9], int y, int valor) {
	int y_funcao,x;
	
	y_funcao = y;
	int verif =  1;
	for(x = 0;x<9;x++)
	{
		if (quadro[x][y_funcao] == valor){
			return FALSO;
		}
	}
	return VERDADEIRO;



}

/* -----------------------------------------------------------------------------
 * E VALIDO NA LINHA
 * Verifica se um valor na linha x e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int eh_valido_na_linha(const char quadro[9][9], int x, int valor) {

	for (int y = 0;y<9;y++){
		if (quadro[x][y] == valor)
			return FALSO;
	}
	return VERDADEIRO;

}

/* -----------------------------------------------------------------------------
 * E VALIDO NO QUADRO 3X3
 * Verifica se um valor e valido no quadrante da posicao x, y
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int eh_valido_no_quadrante3x3(const char quadro[9][9], int x, int y, int valor) {
    int quadrante = determine_quadrante(x, y); 
    int x_ini = ini_x(quadrante); 
    int x_fim = fim_x(quadrante);  
    int y_ini = ini_y(quadrante);  
    int y_fim = fim_y(quadrante);  

   
    for (int i = y_ini; i <= y_fim; i++) {  
        for (int j = x_ini; j <= x_fim; j++) {  
            if (quadro[j][i] == valor) {
                return FALSO;  
            }
        }
    }

    return VERDADEIRO;  

	
}

/* -----------------------------------------------------------------------------
 * EXISTE CAMPO VAZIO
 * Verifica se existe um campo nao preenchido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int existe_posicao_vazia(const char quadro[9][9]) {
	int i, j;

	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			if (quadro[i][j] == 0)
				return VERDADEIRO;
		}
	}

	return FALSO;
}

/* -----------------------------------------------------------------------------
 * IMPRIMIR
 * Imprime o quadro recebido do sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void imprima(const char quadro[9][9]) {
	int i, j;

//	puts("~~~~~~~~ SUDOKU ~~~~~~~~");
	puts("    0 1 2   3 4 5   6 7 8");
	for (i = 0; i < 9; i++) {
		if (i % 3 == 0)
			puts("  -------------------------");
		for (j = 0; j < 9; j++) {

			if (j == 0)
				printf("%d | ", i);
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

/* -----------------------------------------------------------------------------
 * JOGAR
 * Realiza toda a logica do jogo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void jogue() {
	int opcao;
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
	int jogadas = 0;
	opcao = 0;

	while (opcao != 9) {
		// imprima na tela o quadro atual
		printf("\n\n\n");
		imprima(quadro);

		// apresente um menu com as opcoes
		menu();
		opcao = leia_opcao();

		switch (opcao) {

		// carregue sudoku
		case  1:{
			fb = carregue(quadro);

			if (fb == NULL) {
				fb = crie_arquivo_binario(quadro);
			}
			break;
		}

		// preencha quadro com um valor
		case 2: {
			if (fb == NULL) {
				fb = crie_arquivo_binario(quadro);
			}
			int x, y, valor;

			printf("Entre com a posicao e o valor (linha, coluna, valor): ");
			scanf("%d %d %d", &x, &y, &valor);


			if (eh_valido(quadro, x, y, valor)) {
				quadro[x][y] = valor;
				salve_jogada_bin(fb, quadro);
			}
			else
				puts("Valor ou posicao incorreta! Tente novamente!");
				break;
		}
			

		// resolva 1 passo
		case 3:{
			if (fb == NULL) {
				fb = crie_arquivo_binario(quadro);
			}
			resolve_um_passo(quadro);
			salve_jogada_bin(fb, quadro);
			puts("Um passo resolvido!");
			break;
		}
		// resolva o sudoku completo
		case 4:{
			if (fb == NULL) {
				fb = crie_arquivo_binario(quadro);
			}
			int teste = resolve_completo(fb, quadro);
			if (teste == 1)
				printf("Jogo Resolvido");
			else
				printf("Jogo Sem solução");
			salve_jogada_bin(fb,quadro);
			break;
		}
		case 9:{
			if (fb == NULL) {
				fb = crie_arquivo_binario(quadro);
			}
			puts("Programa finalizado ..");
			fclose(fb);
			break;
		}

		default:{
			puts(INVALID_OPTION);
			fclose(fb);
			break;
		}
	}
}
}
/* -----------------------------------------------------------------------------
 * RESOLVER
 * Resolve o sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int resolve_completo(FILE *fb, char quadro[9][9]) {
	int linha = 0, coluna = 0, vazio = 0;
	FILE *bin = fb;

	
	for (int i = 0; i <= 8 && !vazio; i++) {
		for (int j = 0; j <= 8 && !vazio; j++) {
			if (quadro[i][j] == 0) {
				linha = i;
				coluna = j;
				vazio = 1;
			}
		}
	}

	if (vazio == 0)
		return 1;  

	for (int num = 1; num <= 9; num++) {
		if (eh_valido(quadro, linha, coluna, num)) {
			quadro[linha][coluna] = num;
			
			if (resolve_completo(bin, quadro) == 1) {
				return 1;
			}
			
			quadro[linha][coluna] = 0;
		}
	}
	return 0;  
}

/* -----------------------------------------------------------------------------
 * RESOLVER UM PASSO
 * Preenche apenas um campo vazio
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void resolve_um_passo(char quadro[9][9]) {
	if (existe_posicao_vazia(quadro)){
		for(int i = 0; i <= 8; i++) {
			for(int j = 0; j <= 8; j++) {
				if (quadro[i][j] == 0)
					{
						int feito = FALSO;
						int valor = 1;
						while (feito == FALSO){
						
						if (eh_valido(quadro,i,j,valor))
						{
							quadro[i][j] = valor;
							feito = VERDADEIRO;
							return;
						}else{
							valor++;
							if (valor >= 9){
								feito = VERDADEIRO;
								printf("Nenhum valor eh possivel");
								return;
							}
						}
						}return;
						
					}
			}
	}
	}

}

/* -----------------------------------------------------------------------------
 * SALVAR JOGADA BINARIO
 * Salva o estado atual do quadro no arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salve_jogada_bin (FILE *fb, char quadro[9][9]) {
	int jogadas =0,valor=0;
	if (fb == NULL) {
        printf("Erro: Arquivo não está aberto.\n");
        return;
    }
	else {
		fseek(fb, 0, SEEK_SET);
		fread(&jogadas,sizeof(int),1,fb);
		jogadas++;
		printf("quantidade de jogadas eh %d ", jogadas);
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

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 							FUNCOES AUXILIARES
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/* -----------------------------------------------------------------------------
 * FIM X
 * Indice final da linha para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int fim_x(int quadr) {
	switch(quadr) {
		case 1:
		case 2:
		case 3:
			return 2;

		case 4:
		case 5:
		case 6:
			return 5;

		default:
			return 8;
	}
}

/* -----------------------------------------------------------------------------
 * FIM Y
 * Indice final da coluna para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int fim_y(int quadr) {
	switch(quadr) {
		case 1:
		case 4:
		case 7:
			return 2;

		case 2:
		case 5:
		case 8:
			return 5;

		default:
			return 8;
	}
}

/* -----------------------------------------------------------------------------
 * GEN_RANDOM
 * Gera uma cadeia de caracteres randomica de tamanho len
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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

/* -----------------------------------------------------------------------------
 * INI X
 * Indice inicial da linha para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ini_x(int quadr) {
	switch(quadr) {
		case 1:
		case 2:
		case 3:
			return 0;

		case 4:
		case 5:
		case 6:
			return 3;

		default:
			return 6;
	}
}

/* -----------------------------------------------------------------------------
 * INI Y
 * Indice inicial da coluna para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ini_y(int quadr) {
	switch(quadr) {
		case 1:
		case 4:
		case 7:
			return 0;

		case 2:
		case 5:
		case 8:
			return 3;

		default:
			return 6;
	}
}

/* -----------------------------------------------------------------------------
 * LE OPCAO
 * Imprime a mensagem a faz a leitura da opcao
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int leia_opcao () {
	int opcao;

	printf("Opcao: ");
	scanf("%d", &opcao);
	getchar();

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
