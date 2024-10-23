#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* -----------------------------------------------------------------------------
 * E VALIDO NA COLUNA
 * Verifica se um valor na coluna y e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
enum boolean {
	FALSO=0, VERDADEIRO=1
};
void imprima(const char quadro[9][9]);
int eh_valido_na_coluna(const char quadro[9][9], int y, int valor);
int eh_valido_no_quadrante3x3(const char quadro[9][9], int x, int y, int valor);
int eh_valido_na_linha(const char quadro[9][9], int x, int valor);
int existe_posicao_vazia(const char quadro[9][9]);
int determine_quadrante(int x, int y);
int fim_x(int quadr);
int fim_y(int quadr);
int ini_x(int quadr);
int ini_y(int quadr);
int eh_valido(const char quadro[9][9], int x, int y, int valor);

int main(){
	char quadro[9][9] =
		   {{2, 1, 7, 0, 0, 0, 0, 0, 0},
			{3, 5, 8, 0, 0, 0, 0, 0, 0},
			{4, 6, 0, 0, 0, 0, 0, 0, 0},
			{1, 0, 0, 0, 0, 0, 0, 0, 0},
			{5, 0, 0, 0, 0, 0, 0, 0, 0},
			{6, 0, 0, 0, 0, 0, 0, 0, 0},
			{7, 0, 0, 0, 0, 0, 0, 0, 0},
			{8, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0}	
};
	int valor;
	int x;
	int y;
	imprima(quadro);
	printf("informe o valor");
	scanf("%d",&valor);
	printf("informe o y");
	scanf("%d",&y);
	printf("informe o x");
	scanf("%d",&x);
	int coluna = eh_valido_na_coluna(quadro,y,valor);
	int linha = eh_valido_na_linha(quadro,x,valor);
	int quaddrante = eh_valido_no_quadrante3x3(quadro,x,y,valor);
	printf("\ncoluna:%d linha:%d quadrante:%d\n", coluna,linha,quaddrante);
	int valido = eh_valido(quadro,x,y,valor);
	printf("eh valido em tudo: %d",valido);	
	
}	
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
			return 7;
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
			return 7;
	}
}
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