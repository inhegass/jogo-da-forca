#include <stdio.h>
#include <string.h>
//biblioteca para pegar o strlen

void abertura(){
	printf("*********************\n");
	printf("*   Jogo da Forca   *\n");
	printf("*********************\n\n");
}

void chuta(char chutes[26],int tentativas){	
	//função
	char chute;
	printf("Qual letra?\n");
	scanf(" %c", &chute);
	// coloca o espaço para ignorar o enter e não considera-lo como char
	chutes[tentativas] =  chute;
}

int main(){
	char palavrasecreta[20];
	//isso é um arrays que guarda muitas coisas
	sprintf(palavrasecreta, "MELANCIA");
	//sprintf imprime em um array
	//ultimo caracter do array com spritf é sempre /0, por criar um loop, mas isso n muda o array em sí
	
	int acertou = 0;
	int enforcou = 0 ;
	
	char chutes[26];
	int tentativas = 0;
		
	abertura();
	
	do {		
		for (int i = 0; i < strlen(palavrasecreta); i++){
			//strlen mostra o tamanho do array ou string
			int achou = 0;
			for(int j = 0; j < tentativas; j++){
				if(chutes[j] == palavrasecreta[i]){
					achou = 1;
					break;
				}
			}
			if(achou){
				printf("%c ", palavrasecreta[i]);
			}
			else{
				printf("_ ");
			}
		}
		printf("\n");
		
		chuta(chutes, tentativas);
		tentativas ++;
	} while (!acertou && !enforcou);
	//executa uma vez mesmo que o programa ja tenha a função falseada
	//a "!" serve como negação (0)
	//"&&" = "e"
}
