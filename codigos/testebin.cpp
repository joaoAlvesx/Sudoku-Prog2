#include <stdio.h>
#include <string.h>

int main(){

    printf("Qual o nome do arquivo binario");
    char binario[8];
    char bin[5] = {".bin"};
    fgets(binario,4,stdin);
    binario[strcspn(binario, "\n")] = '\0';
    strcat(binario, bin);
   
    FILE *fb;
    int nread[92],aux = 0,y=0;
    fb = fopen(binario,"rb");

    if (fb == NULL){
    printf("Erro"); 
    }else{
    fseek(fb, 0, SEEK_SET);
    int valor[200];
    fread(&nread[0],sizeof(int), 1, fb);
    printf("[%d]\n",nread[0]);
    for(int i = 0;i<91;i++){
        fseek(fb, -81 * sizeof(int), SEEK_END);
        fread(&valor[i],sizeof(int), 1, fb);	
        printf("[%c]",valor[i]);
    }}
    return 0;
}