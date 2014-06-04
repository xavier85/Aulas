#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

void initRandom(){
    time_t random_seed;

    random_seed = time (NULL);
    srand (random_seed);
}

int getRandomNum (int nLow, int nHigh){
  
    int nRandomValue;
    nRandomValue = nLow + rand() % (nHigh - nLow + 1);
    return nRandomValue;
}
void jogadores(char cjogador){ char cEscolha, C, Q;
          printf("[2] um Jogador\n");
          printf("[C] computador vs Player\n");
          printf("[Q] Sair\n");
    do{
      printf("Enter a sua escolha: ");
      scanf("%c",&cEscolha);
    if 
        (cEscolha == 2)
        printf("2 Jogadores\n");
    else
      if 
        (cEscolha == C)
        printf("Computador vs. Player\n");
      else 
      if 
        (cEscolha == Q)
        printf("Sair\n");
      else
        printf("Invalido\n");
      }
    switch(cEscolha);
    {
      case 0: printf("Player vs Player\n");
      break;
      case 1: printf("Computador vs Player\n");
      break;
      case 2: printf("Sair\n");
      break;
while(cChoice != 2 || cChoice != C || cChoice != Q);

}
main()
{
char cC, c2, cQ, cEscolha;
printf ("Bem Vindo ao jogo do Domino!\n\n");
players(cEscolha);
}
