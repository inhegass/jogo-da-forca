#include <stdio.h>
#include <string.h>
//biblioteca para pegar o strlen

int main(){
	char palavrasecreta[20];
	//isso � um arrays que guarda muitas coisas
	sprintf(palavrasecreta, "MELANCIA");
	//sprintf imprime em um array
	//ultimo caracter do array com spritf � sempre /0, por criar um loop, mas isso n muda o array em s�
	
	int acertou = 0;
	int enforcou = 0 ;
	
	char chutes[26];
	int tentativas = 0;
		
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
		
		char chute;
		printf("Qual letra?\n");
		scanf(" %c", &chute);
		// coloca o espa�o para ignorar o enter e n�o considera-lo como char
		
		chutes[tentativas] = chute;
		tentativas ++;		
	} while (!acertou && !enforcou);
	//executa uma vez mesmo que o programa ja tenha a fun��o falseada
	//a "!" serve como nega��o (0)
	//"&&" = "e"
}
