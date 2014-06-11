#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char buffer[1024];

int ordem;
int logout = 0;


int n_jogar;

pedido ped;
resposta resp;
jogadores jog;
jogadores jogador;

typedef struct // em teste
{
	char nome[n_jogadores_max][tam_nome_serv];
} jogadores_safe;

void status()
{
int i;
if(jogo_act == 0) // status casa NAO haja jogo a decorrer
	{
	printf("Nao existe jogo a decorrer\nEstao %d jogadores activos\n", n_jogadores_act);
	printf("# | Nome  (#representa a ordem de jogada)\n");
	for(i=0; i< n_jogadores_act; i++)
		{
		printf("#%d  %s", (i+1), jogador.nome[i]);
		if(jogador.emjogo[i]==0)
			printf("(Em espera)\n");
		else
			printf("(Em jogo)\n");
		}
	}
else if(jogo_act == 1) // existe jogo a decorrer
	{
	printf("Existe um jogo a decorrer\nEstao %d jogadores activos\n", n_jogadores_act);
	printf("# | Nome  (#representa a ordem de jogada\n)");
	for(i=0; i<n_jogadores_act; i++)
		{
		printf("#%d  %s", (i+1), jogador.nome[i]);
		if(jogador.emjogo[i] ==0)
			printf("(Em espera)\n");
		else
			printf("(Em jogo)\n");
		}
	}
return;
}

void users()
{
int i;
printf("Info sobre jogadores activos\n");
for(i=0; i< n_jogadores_max ; i++)
{
printf("#%d  %s", (i+1),jogador.nome[i]);
if(jogador.emjogo[i] == 0)
	printf("(Em espera)\n");
else
	printf("(Em jogo)\n");
}
return;
}

void info()
{
	int i,j;
	printf("O molho de pecas tem %d pecas\n", n_molho);
	for(i=0; i< n_jogadores_max; i++)
	{
		printf("# | Nome\n");
		if(jogador.emjogo[i] == 1)
		{
			printf("#%d  %s\n", (i+1), jogador.nome[i]);
			for(j=0; j<NUMPECAS; j++)
			{
				printf("%s ", pecas[molho_client[i][j]]);
			}
			printf("\n");
		}
	}
	return;
}

void game()
{
	system("clear");
	int i;
	int n = jogo_pos_inicial;
	char c;
	//esta função tem uma tarefa muito simples: imprimir o "tabuleiro" de jogo
	//posição inicial do tabuleiro (27) +7 para a frente e -7 para trás
	do
	{
		for(i=(n - 7); i < (n + 7); i++)
		{
			printf("%s ", jogo[i]);
		}
		printf("\n\n");

		if(n == (tamJogo - 7))
		{
			do
			{
				printf("So pode andar para a esquerda\n");
			}
			while(c != 'x' || c != 'e');
		}
		else if(n == 7)
		{
			do
			{
				printf("So pode andar para a direita\n");
			}
			while(c != 'x' || c != 'd');
		}
		if(c == 'e')
			n--;
		else if(c == 'd')
			n++;
	}
	while(c != 'x');
	return;
}

void tiles()
{
	int i;
	for(i=0; i< NUMPECAS; i++)
	{
		printf("%d %s ", molho_client[ordem][i], pecas[molho_client[ordem][i]]);
	}
	return;
}

void get()
{
	srand(time(NULL));
	//só corre se este cliente tiver slots disponiveis para novas peças
	int i,n,r;
	n=0;
	for(i=0; i< NUMPECAS; i++)
	{
		if( molho_client[ordem][i] == -1)
			n++;
	}
	if(n == 0)
	{
		printf("Nao pode retirar pecas pois ainda as tem todas\n");
		return;
	}
	else
	{
		for(i=0; i< NUMPECAS; i++)
		{
			if( molho_client[ordem][i] == -1)
				break; // break do ciclo for quando encontrar uma posiçao com o valor -1 (sem peça)
		}
		r = rand() % 28;
		for(i=0; i<1 ; i++)//procurar peça no molho, aleatoriamente
		{
			if((strcmp(molho[r], "")) != 0)
			{
				molho_client[ordem][i] = r; //dar peça a peça ao jogador em questao(dar a referencia do array)
				strcpy(molho[r], ""); //ir retirando as peças do molho
				n_molho--; // menos 1 peça no molho do jogo
			}
			else
				i--; //porque caso a peça nao exista, i incrementará á mesma, o que deixaria o jogador com as mesmas peças
		}
		return;
	}
}

void quit()
{
	//esvaziar o array de peças deste jogador e coloca las de volta nas devidas posiçoes originais
	//localizar as peças a em molho, a partir das posiçoes guardadas em molho_client

}

void menu_print()
{
	printf("DOMINO! Escolha...\n");
	printf("Novo jogo (new nome intervalo)\n");
	printf("Jogar (join)\n"); //trocou se play por join
	printf("Estado (status)\n");
	printf("Jogadores (users)\n");
	printf("Logout (logout)\n");
	printf("Sair (exit)\n");
	printf("Os seguintes apenas funcionam se estiver num jogo...\n");
	printf("Jogar #peca esq/dir (play numPeca left/right)\n");
	printf("Info (info)\n");
	printf("Mostrar jogo (game)\n");
	printf("Mostrar pecas (tiles)\n");
	printf("Pesca (get)\n");
	printf("Passar (pass)\n");
	printf("Pedir ajuda (help)\n");
	printf("Desistir (quit)\n");
}

void menu(char opt[tam_resposta], int inGame)
{

	srand(time(NULL));
	int i,j,r;
	int n;
	char aux[2];

	char *corrigir_string;	//fgets coloca um \n no fim das strings, este pequeno codigo "limpa" a string
	if ((corrigir_string = strchr(opt, '\n')) != NULL)
		*corrigir_string = '\0';

	//escolha da opÃ§ao
	//simples
	if(strcmp(opt, "join") == 0) //como causa conflitos com o outro comando play # esq/dir alterou-se o nome para "join" (juntar a um jogo")
	{
		if(jogo_act == 0) // nenhum jogo activo, return
		{
		printf("Nao existe nenhum jogo activo.\n");
		return;
		}
		else //jogo activo, juntar
		{
		n_jogadores_jog++;
		jogador.emjogo[ordem] = 1; // colocar este jogador como num jogo

		// como foi implementado em "new" distribuir peças pelos primeiros DOIS jogadores, aqui só serao distribuidas mais peças caso o 3º e/ou 4º jogadores entrem
		if(n_jogadores_jog == 1) //está 1 só jogador num jogo
			return; //porque este jogador receberá as suas peças doutra função
		else if(n_jogadores_jog >= 2)
			{
				//preencher o array de peças deste cliente
					for(j=0; j< NUMPECAS; j++) //distribuir peças 
							{
								r = rand() % 28;
								if((strcmp(molho[r], "")) != 0)
								{
									molho_client[ordem][j] = r; //dar peça a peça ao jogador em questao(dar a referencia do array)
									strcpy(molho[r], ""); //ir retirando as peças do molho
									n_molho--; // menos 1 peça no molho do jogo
								}
								else
									j--; //para nao fazer com que o jogador receba um numero menor de peças
							}
					return;
			}
		}
	}
	else if(strcmp(opt, "status") == 0)
	{
		status(); // chama funÃ§ao que trata de status 
		return;
	}
	else if(strcmp(opt, "users") == 0)
	{
		users(); //chama funÃ§ao que trata da info de users
 		return;
	}
	else if(strcmp(opt, "logout") == 0)
	{
		logout = 1;
		return;
	}
	else if(strcmp(opt, "exit") == 0)
	{
		exit = 1;
		return;
	}
	else if(strcmp(opt, "info") == 0 && jogador.emjogo[ordem] == 1)
	{
		info();
		return;
	}
	else if(strcmp(opt, "game") == 0 && jogador.emjogo[ordem] == 1)
	{
		game();
		return;
	}
	else if(strcmp(opt, "tiles") == 0 && jogador.emjogo[ordem] == 1)
	{
		tiles();
		return;
	}
	else if(strcmp(opt, "get") == 0 && jogador.emjogo[ordem] == 1)
	{
		get();
		return;
	}
	else if(strcmp(opt, "pass") == 0 && jogador.emjogo[ordem] == 1)
	{
		printf("Passou a sua vez\n");
		proximo++;
		return;
	}
	else if(strcmp(opt, "help") == 0 && jogador.emjogo[ordem] == 1)
	{
		printf("%s", opt);
	}
	else if(strcmp(opt, "quit") == 0 && jogador.emjogo[ordem] == 1)
	{
		//sai do jogo actual mas nao do programa
		quit();
		return;
	}
	//opçoes mais complexas
	else if(opt[0] == 'n' && opt[1] == 'e' && opt[2] == 'w')
	{
		if(opt[3] != ' ')
		{
			printf(err_sint);
		}
		else if(opt[3] == ' ' && opt[4] != ' ')
		{
			for(n = 4; opt[n] != ' ' ; n++)	//guardar o nome do servidor
			{
				strncpy(&nome_serv[n-4],&opt[n], 1); // copiar char a char o nome do jogo para nome_serv
			}
			if(opt[n] != ' ')
			{
				printf(err_sint);
			}
			else if(opt[n] == ' ' && opt[n+1] != ' '  && opt[n+2] == '\0')
			{
				printf("Coloque um intervalo superior a 10.\n");
			}
			else if(opt[n] == ' ' && opt[n+1] != ' '  && opt[n+2] != ' ' && opt[n+3] == '\0') // obter numero referente ao intervalo
			{
				aux[0] = opt[n+1];
				aux[1] = opt[n+2];
				intervalo = atoi(aux);
			}
		}
		if(jogo_act != 0)
			printf("Nao é possivel executar este comando, já está um jogo a decorrer.\n");
		else//começar um novo jogo
			{
				jogo_act = 1; //jogo a decorrer;
				jogador.emjogo[ordem] = 1; //colocar este client como "em jogo"
				n_jogadores_jog ++; // +1 jogador dentro do jogo
				//preencher o array molho
				for (i=0; i< numTotalPecas ; i++)
				{
					strcpy(molho[i], pecas[i]);
					n_molho++;
				}
				//array preenchido;
				//mais nada é feito aqui, inicia-se a contagem intervalo e caso mais nenhum jogador se junte, o jogo termina
				for(i=0; i< intervalo; i++)
					{
						_sleep(999); //	sleep 999 milisegundos
						if(n_jogadores_jog >1) // parar ciclo quando houver + do que 1 jogador (2 minimo)
							break;
					}
				if(n_jogadores_jog < 2) //terminar jogo caso nao haja mais do que 1 jogador 
					{
						n_jogadores_jog = 0;
						jogo_act = 0; // nenhum jogo a correr
						for(i=0; i< n_jogadores_act ; i++)
						{
							jogador.emjogo[i] = 0; //colocar todos os jogadores como fora de jogo
						}
						//esvaziar o array molho
					for (i=0; i< numTotalPecas ; i++)
						{
							strcpy(molho[i], "");
							n_molho--;
						}
					}
				else if(n_jogadores_jog > 1)
				{
					//há mais de 1 jogador, identificar todos
					printf("Jogadores no jogo sao:\n");
					for(i=0; i< n_jogadores_max; i++)
					{
						if(jogador.emjogo[i] == 1)
						{
							printf("#%d  %s\n",(i+1), jogador.nome[i]);
							for(j=0; j< NUMPECAS; j++) //distribuir peças por cada um dos que está no jogo
							{
								r = rand() % 28;
								if((strcmp(molho[r], "")) != 0)
								{
									molho_client[i][j] = r; //dar peça a peça ao jogador em questao(dar a referencia do array)
									strcpy(molho[r], ""); //ir retirando as peças do molho
									n_molho--; // menos 1 peça no molho do jogo
								}
								else
									j--; //para nao fazer com que o jogador receba um numero menor de peças
							} // neste ponto já os primeiros 2 jogadores que estão no jogo terão recebido as suas peças 
						}
					}
				}
				proximo = 0; //prox jogador a jogar é o que tem a posiçao 0 nos arrays
				return;
			}
	}
	else if(opt[0] == 'p' && opt[1] == 'l' && opt[2] == 'a' && opt[3] == 'y' && jogador.emjogo[ordem] == 1)
	{
		if(opt[4] != ' ' && opt[6] != ' ')
		{
			printf(err_sint);
		}
		else if(opt[4] == ' ' && opt[5] != ' ' && opt[6] == ' ')
		{
			aux[0] = opt[5];
			n_jogar = atoi(aux); // numero da peça já guardado em n_jogar, por isso aux pode ser usada de novo para outra coisa qualquer
		}
		else if(opt[6] == ' ' && opt[7] == ' ')
		{
			printf(err_sint);
		}
		else if(opt[6] == ' ' && opt[7] == 'l'&& opt[8] == 'e'&& opt[9] == 'f'&& opt[10] == 't') // left 
		{

		}
		else if(opt[6] == ' ' && opt[7] == 'r'&& opt[8] == 'i'&& opt[9] == 'g'&& opt[10] == 'h' && opt[11] == 't') // right
		{

		}
	}
	else (printf("Comando incorrecto ou inexistente!\n"));

}


int main(void){

system("clear");

int emjogo = 0; //?

char enviar[tam_resposta];
int fserv, fclient;

char nome_j[24];

        // vereficar se o servidor exite (aceess)
	if(access(FSERV,F_OK)!=0){
	printf("Nao existe nenhum servidor de %s a correr.\n", nomeJogo);
	exit(1);
	}
        // criar fifo do cliente (mkfifo)
	sprintf(ped.fcli,"cli%d",getpid());
	mkfifo(ped.fcli,0600);
        // Abrir fifo do servidor (open - O_WRDONLY)
	fserv= open (FSERV,O_WRONLY);

do
{
//completar LOGOUT
	jog.tmp_id = getpid();
	write(fserv, &jog.tmp_id, sizeof(jog.tmp_id));
	printf("this fifo %s\n", ped.fcli);
	printf("Introduza um nome: ");
	fgets(jog.tmp_nome, 24, stdin);
	if((strcmp(jog.tmp_nome, "exit\n")) != 0) // pode ter \n a mais
	{
		ordem = n_jogadores_act;
		write(fserv, &jog.tmp_nome, sizeof(jog.nome));
		do // ciclo do jogo
		{
		jogador.emjogo[ordem] = 0; //inicializar
		jogador.numvict[ordem] = 0; //inicializar
		system("clear");
		menu_print();
		fgets(enviar, tam_resposta, stdin);
		menu(enviar, jogador.emjogo[ordem]); //enviar resposta para menu 
		if(logout == 1)
			return;
		if(exit == 1)
			return;
		}
		while((strcmp(enviar, "exit\n")) != 0);
	}
	else
		return;
	if(exit == 1)
		return; // avisar servidor (FALTA)

}
while(access(FSERV,F_OK) == 0 || 1 );
close(fserv);
unlink(ped.fcli);
exit(1);
}

