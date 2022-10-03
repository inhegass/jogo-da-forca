#include <stdio.h>
#include <string.h>
//biblioteca para pegar o strlen
#include "forca.h"
//arquivo com as funções do jogo declaradas
//está com aspas por ser um arquivo que não estava já presente no compilador
#include <time.h>
//tem a função time()
#include <stdlib.h>
//tem as funções srand() e rand()


char palavrasecreta[TAMANHO_PALAVRA];
//isso é um arrays que guarda muitas coisas
//também é um ponteiro pra primeira posição, palavrasecreta[0], sendo assim o array é uma sequencia de variáveis declaradas, uma do lado da outra
char chutes[26];
//variáveis golbais visiveis para todas as funções (não precisam ser mais declaradas)
//não muito usada por perder o controle de onde pode ser mudada

void abertura(){
	//função
	//ao colocar void diz que a função devolve nada
	printf("*********************\n");
	printf("*   Jogo da Forca   *\n");
	printf("*********************\n\n");
}

void chuta(int* chutesdados){	
	//"*" no int é porque a variável chutesdados está como ponteiro, sendo assim a mesma da função main, podendo agora salvar valores para serem usados na main
	//ponteiros alocam valores na memoria
	char chute;
	printf("Qual letra?\n");
	scanf(" %c", &chute);
	// coloca o espaço para ignorar o enter e não considera-lo como char
	chutes[(*chutesdados)] =  chute;
	(*chutesdados) ++;
	//salva o valor no número e não no ponteiro
}

int jachutou(char letra, int chutesdados){
	//função com retorno
	int achou = 0;
	for(int j = 0; j < chutesdados; j++){
		if(chutes[j] == letra){
			achou = 1;
			break;
		}
	}	
	return achou;
	//retorna o valor de achou pro main
}

void desenhaforca( int chutesdados){
    


    int erros = chuteserrados(chutesdados);
 printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
	//if ternários (if colocado em string)
	// antes do ":" é verdadeiro e depois dele é falso
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");	
	
	for (int i = 0; i < strlen(palavrasecreta); i++){
		//strlen mostra o tamanho do array ou string
		if(jachutou(palavrasecreta[i], chutesdados)){
			printf("%c ", palavrasecreta[i]);
		}
		else{
			printf("_ ");
		}
	}
	printf("\n");
}

void escolhepalavra(){
	
	//sprintf(palavrasecreta, "MELANCIA");
	//sprintf imprime em um array (coloca no array a palavra)
	//ultimo caracter do array com spritf é sempre /0, por criar um loop, mas isso n muda o array em sí
	
	FILE * f;
	f = fopen("palavrasforca.txt", "r");
	//função para abrir um arquivo em forma de ponteiro
	//"r" mostra que quero que leia o arquivo
	if(f == 0){
		//caso de problema no arquivo de texto do jogo (não reconheceu ou achou ele)
		printf("Desculpe, banco de dados não disponível\n\n");
		exit(1);
		//para o programa
	}

	int qttdepalavras = 0;
	fscanf(f, "%d", &qttdepalavras);
	//a função le a primeira linha do arquivo até encontrar um enter (\n). Toda vez que for chamada le a linha seguinte
	srand(time(0));
	int randomico = rand() % qttdepalavras;
	// escolhe um número entre 0 e a quantidade de palavras
	for(int i = 0; i <=randomico; i++){
		fscanf(f, "%s", palavrasecreta);
		if(i == randomico){
			break;
		}
	}
	
	fclose(f);
	//para fechar o arquivo (sempre colocar)
}

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados(int chutesdados) {
    int erros = 0;
    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }
    return erros;
}

int acertou(int chutesdados){
	for(int i = 0; i < strlen(palavrasecreta); i++){
		if(!jachutou(palavrasecreta[i], chutesdados)){
			return 0;
		}
	}
	return 1;
}

void adicionapalavra(){
	char quer;
	
	printf("Voce quer adicionar uma nova palavra no jogo? (S/N)\n");
	scanf(" %c", &quer);
	//NÃO ESQUECER DO ESPAÇO ANTES DO %c !!!!!!
	
	if(quer == 'S'){
		
		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra?(Digite em letras maiusculas)\n");
		scanf("%s", novapalavra);
		
		FILE* f;
		f = fopen("palavrasforca.txt", "r+");
		//para editar o arquivo de texto
		
		if(f == 0){
			printf("Desculpe, banco de dados não disponível\n\n");
			exit(1);
		}
		
		int qtd;
		fscanf(f, "%d", qtd);
		//salva o número da primeira linha como a variável qtd
		qtd++;
		fseek(f, 0, SEEK_SET);
		//fseek é uma função para posicionar para ler ou escrever no arquivo
		//SEEK_SET começa a andar do inicio do arquivo
		//se aumentar o número de 0 para outro, irá para o proximo byte do arquivo
		//SEEK_KCUR anda a poartir do ponto atual
		fprintf(f, "%d", qtd);
		//edita o texto
		fseek(f, 0, SEEK_END);
		//SEEK_END posiciona o ponteiro no fim do arquivo
		fprintf(f, "\n%s", novapalavra);
		fclose(f);
	}
}

int enforcou(int chutesdados) {
    return chuteserrados(chutesdados) >= 5;
}

int main(){
		
	int chutesdados = 0;
		
	abertura();
	escolhepalavra();
	
	do {			
	//similar ao while, mas executa uma vez mesmo que o programa ja tenha a função falseada
		desenhaforca(chutesdados);
		chuta(&chutesdados);
	} while (!acertou(chutesdados) && !enforcou(chutesdados));
	//a "!" serve como negação (0)
	//"&&" = "e"
	
	if (acertou(chutesdados)){
        printf("\nParabens, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");			
	}
	
	else{
        printf("\nPuxa, voce foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");		
	}
	adicionapalavra();
}
