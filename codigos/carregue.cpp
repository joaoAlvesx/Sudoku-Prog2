 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
FILE* carregue(char quadro[9][9]) {
	int opcao;

	menu_arquivo();
	opcao = leia_opcao();

	// TODO Função incompleta

	switch(opcao) {

		// carregar novo sudoku
		case 1:
			printf("Qual o nome do arquivo txt");
			carregue_novo_jogo()

		// continuar jogo
		case 2:
			printf("Qual o nome do arquivo binario");

		// retornar ao menu anterior
		case 9:
			return;

		default:
			break;
}
/* -----------------------------------------------------------------------------
 * CARREGAR NOVO JOGO
 * Carrega um novo jogo do Sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo) {
	// TODO
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
}

FILE* carregue_continue_jogo (char quadro[9][9], char *nome_arquivo) {
	// TODO
}

