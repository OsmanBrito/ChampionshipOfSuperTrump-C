#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <time.h>
#include <windows.h>

int Acc = 0; //variavel global!

struct carta{
	char cdg[2];
	char nome[50];
	int poder;
	int HP;
	int inteligencia;
	int velocidade;
	struct carta *prox;
	struct carta *ant;
};
typedef struct carta Car;

struct pessoa{
	char nome[20];
	int idade;
	int id;
	char origem[2];
	int titulos;
};
typedef struct pessoa Pe;

struct jogador{
	Pe player;
	Car *Deck;
};
typedef struct jogador Jog;

Car *inseri(Car *l, char cd[2], char nom[50], int pode, int h, int inteligenci, int velocida)
{
	Car *novo = (Car*) malloc(sizeof(Car));
	novo->poder = pode;
	novo->HP = h;
	novo->inteligencia = inteligenci;
	novo->velocidade = velocida;
	strcpy(novo->nome, nom);
	strcpy(novo->cdg, cd);
	if(l == NULL)
	{
		novo->prox = novo;
		novo->ant =novo;
	}
	else
	{
		novo -> prox = l -> prox;
		novo -> ant = l;
		l->prox->ant = novo;
		l->prox = novo;
	}
	return novo;

}

void inserirPar(Pe p[], int n)
{
	
	int i, Aidi = 1;
	for(i = 0; i < n; i++)
	{
		system("cls");
		printf("Nome: ");
		fflush(stdin);
		gets(p[i].nome);
		printf("Idade: ");
		scanf("%d",&p[i].idade);
		printf("Origem: ");
		fflush(stdin);
		gets(p[i].origem);
		printf("Titulos: ");
		scanf("%d",&p[i].titulos);
		p[i].id = Aidi;
	//	printf("%d\n",p[i].id);
		Aidi++;
	}
	system("cls");
	printf("\t\tCadastros efetuados com sucesso.\n");
	sleep(1);
}

Pe tabela(int n, Pe pessoa[], Pe ganhadores[])
{	
	int i;
	if(Acc == 0)//se for a primeira vez q eu entrar na função, colocarei os participantes nas ultimas posições do vetor, nós fol
	{
		for(i = n - 1; i < (n * 2) - 1; i++)
		{
			ganhadores[i] = pessoa[i - (n - 1)];//sempre ira pegar da posicao 0 do vetor pessoa
			//puts(ganhadores[i].nome);
			//system("pause");
		}
	}
	else
	{
		for(i = (Acc - n); i < Acc; i++)
		{
			ganhadores[i] = pessoa[i - (n - 1)];
			//puts(ganhadores[i].nome);
			//system("pause");
		}
	}
	Acc = n - 1;//sempre ele ira pegar a ultima posição q o vetor parou.
}

int sorteio(Jog *j1, Jog *j2)
{
	int caract = rand() % 4, vencedor;//faço o sorteio do tema, vencedor
			
			if(caract == 0)//0 = inteligencia
			{
				if(j1->Deck->inteligencia > j2->Deck->inteligencia)
				{
					vencedor = 1;
				}
				else if(j1->Deck->inteligencia < j2->Deck->inteligencia)
				{
					vencedor = 2;
				}
				else
				{
					vencedor = 0;//empate
				}
			}
			
			else if(caract == 1)//1 = HP
			{
				if(j1->Deck->HP > j2->Deck->HP)
				{
					vencedor = 1;
				}
				else if(j1->Deck->HP < j2->Deck->HP)
				{
					vencedor = 2;
				}
				else
				{
					vencedor = 0;
				}
			}
			
			else if(caract == 2)//2 = Poder
			{
				if(j1->Deck->poder > j2->Deck->poder)
				{
					vencedor = 1;	
				}
				else if(j1->Deck->poder < j2->Deck->poder)
				{
					vencedor = 2;
				}
				else
				{
					vencedor = 0;
				}
			}
			
			else//3 = velocidade
			{
				if(j1->Deck->velocidade > j2->Deck->velocidade)
				{
					vencedor = 1;	
				}
				else if(j1->Deck->velocidade < j2->Deck->velocidade)
				{
					vencedor = 2;
				}
				else
				{
					vencedor = 0;
				}
			}
			return vencedor;
}

Jog *superTrunfo(Jog *j1, Jog *j2)
{
	int x = strcmp(j1->Deck->cdg, "D7");//x = variavel q recebe a comparação de string.
	if(x == 0)
	{
		if(j2->Deck->cdg[1] == '1')//verifico se o jogador 2 esta com a carta q ganha da trunfo(A1 U B1 U C1 U D1)
		{
			return j2;
		}
		else
		{
			return j1;//trunfo ganha de todas, ent retorna o j1 como vencedor
		}
	}
	x = strcmp(j2->Deck->cdg, "D7");
	if(x == 0)
	{
		if(j1->Deck->cdg[1] == '1')//verifico se o jogador 1 esta com a carta q ganha da trunfo(A1 U B1 U C1 U D1)
		{
			return j1;
		}
		else
		{
			return j2;//trunfo ganha de todas, ent retorna o j2 como vencedor
		}
	}
	return NULL;
}

Car *empate(Jog *j1, Jog *j2, Car *empati)//recebo empati para ver se ja entrou alguma vez na função, assim sera adicionado na lista ja criada anteriormente.
{
	if(j1->Deck == j1->Deck->prox || j2->Deck == j2->Deck->prox)
	{
		int sortei = 2;//crio um sortei = 2 para entrar no while.
		while(sortei != 0)//enquanto o sortei for diferente de 0 pois na função sorteio 0 eh empate!
		{
			sortei = sorteio(j1, j2);
		}
		return NULL;
	}
	Car *aux1 = j1->Deck, *aux2 = j2->Deck;
	if(empati == NULL)//quando acontece o primeiro empate, cria-se a lista de cartas empatadas.
	{
		j1->Deck = j1->Deck->prox;//como eh empate, eu avanço o ponteiro dos jogadores para a proxima carta a ser analizada
		j2->Deck = j2->Deck->prox;
									// @ - Arrumar apontamento da lista antes de apontar as cartas empatadas.
									// ! - Apontando cartas empatadas e criando uma lista.
		aux1->ant->prox = aux1->prox;//@
		aux1->prox->ant = aux1->ant;//@
		aux1->prox = aux2;//!
		aux1->ant = aux2;//!
		aux2->ant->prox = aux2->prox;//@
		aux2->prox->ant = aux2->ant;//@
		aux2->prox = aux1;//!
		aux2->ant = aux1;//!
		empati = aux1;
	}
	else
	{
		j1->Deck = j1->Deck->prox;
		j2->Deck = j2->Deck->prox;
		
		aux1->ant->prox = aux1->prox;//@
		aux1->prox->ant = aux1->ant;//@
		aux2->ant->prox = aux2->prox;//@
		aux2->prox->ant = aux2->ant;//@
		aux1->prox = aux2;//!
		aux2->ant = aux1;//!
		aux1->ant = empati->ant;//!
		empati->ant = aux2;//!
		aux1->ant->prox = aux1;//!
		aux2->prox = empati;//!
	}
	return empati;
	
}

Car *GanhadorJ1(Jog *j1, Jog *j2, Car *empati)
{
	if(empati == NULL)//quando n teve empate na jogada anterior
	{
		Car *aux;
		aux = j2->Deck;
		if(j2->Deck->prox == j2->Deck)//quando o jogador q perdeu estiver com uma carta, ele ficara sem nd.
		{
			j1->Deck->prox->ant = aux;
			aux->prox = j1->Deck->prox;
			aux->ant = j1->Deck;
			j1->Deck->prox = aux;
			j1->Deck = j1->Deck->prox->prox;
			j2->Deck = NULL;
		}
		else
		{
			aux = aux -> prox;
			j2->Deck->ant->prox = j2->Deck->prox;//arrumo os apontamentos antes de mandar a carta para o jogador 1
			j2->Deck->prox->ant = j2->Deck->ant;
			j1->Deck->prox->ant = j2->Deck;
			j2->Deck->prox = j1->Deck->prox;
			j2->Deck->ant = j1->Deck;
			j1->Deck->prox = j2->Deck;
			j1->Deck = j1->Deck->prox->prox;
			j2->Deck = aux;		
		}		
	}
	else//quando recebe as cartas empatadas para serem adicionadas ao ganhador.
	{
		Car *aux;
		aux = j2->Deck;
		if(j2->Deck->prox == j2->Deck)//quando o jogador q perdeu estiver com uma carta, ele ficara sem nd.
		{
			aux->prox = j1->Deck->prox;
			aux->ant = empati->ant;
			aux->prox->ant = aux;
			empati->ant->prox = aux;
			j1->Deck->prox = empati;
			empati->ant = j1->Deck;
			j1->Deck = aux->prox;
			j2->Deck = NULL;
		}
		else
		{
			j2->Deck = j2->Deck->prox;
			aux->ant->prox = aux->prox;//arrumo os apontamentos antes de mandar a carta para o jogador 1
			aux->prox->ant = aux->ant;
			empati->ant->prox = aux;
			aux->prox = j1->Deck->prox;
			aux->ant = empati->ant;
			aux->prox->ant = aux;
			empati->ant = j1->Deck;
			j1->Deck->prox = empati;
			j1->Deck = aux->prox;
		}
		return NULL;//dps disso, empati recebe NULL pois n tera mais cartas empatadas.	
	}
	return empati;
}

Car *GanhadorJ2(Jog *j1, Jog *j2, Car *empati)
{
	if(empati == NULL)//quando n teve empate na rodada anterior
	{
		Car *aux;
		aux = j1->Deck;
		if(j1->Deck->prox == j1->Deck)//quando o jogador q perdeu estiver com uma carta, ele ficara sem nd.
		{
			j2->Deck->prox->ant = aux;
			aux->prox = j2->Deck->prox;
			aux->ant = j2->Deck;
			j2->Deck->prox = aux;
			j2->Deck = j2->Deck->prox->prox;
			j1->Deck = NULL;
		}
		else
		{
			aux = aux -> prox;
			j1->Deck->ant->prox = j1->Deck->prox;//arrumo os apontamentos antes de mandar a carta para o jogador 1
			j1->Deck->prox->ant = j1->Deck->ant;
			j2->Deck->prox->ant = j1->Deck;
			j1->Deck->prox = j2->Deck->prox;
			j1->Deck->ant = j2->Deck;
			j2->Deck->prox = j1->Deck;
			j2->Deck = j2->Deck->prox->prox;
			j1->Deck = aux;		
		}		
	}
	else//quando teve empate, logo o jogador q ganhou leva todas as cartas da mesa.
	{
		Car *aux;
		aux = j1->Deck;
		if(j1->Deck->prox == j1->Deck)//quando o jogador q perdeu estiver com uma carta, ele ficara sem nd.
		{
			aux->prox = j2->Deck->prox;
			aux->ant = empati->ant;
			aux->prox->ant = aux;
			empati->ant->prox = aux;
			j2->Deck->prox = empati;
			empati->ant = j2->Deck;
			j2->Deck = aux->prox;
			j1->Deck = NULL;
		}
		else
		{
			j1->Deck = j1->Deck->prox;
			aux->ant->prox = aux->prox;//arrumo os apontamentos antes de mandar a carta para o jogador 1
			aux->prox->ant = aux->ant;//
			empati->ant->prox = aux;
			aux->prox = j2->Deck->prox;
			aux->ant = empati->ant;
			aux->prox->ant = aux;
			empati->ant = j2->Deck;
			j2->Deck->prox = empati;
			j2->Deck = aux->prox;
		}
		return NULL;
	}
	return empati;
}

Jog *Partida(Jog *j1, Jog *j2)
{
	srand(time(NULL));
	printf("entrou\n");
	int vencedor;
	Car *empati = NULL;//ira guardar a memoria das cartas q empataram na rodada em uma nova lista, as das cartas empatadas.
	while(j1->Deck != NULL && j2->Deck != NULL)//ate um dos jogadores perder todas as cartas para o outro.
	{
		Jog *trunfo;
		trunfo = superTrunfo(j1, j2);
		if(trunfo != NULL)//se alguns dos jogadores estiver com o trunfo ele n sera nulo.
		{
			if(trunfo == j1)//j1 ganha a carta
			{	
				empati = GanhadorJ1(j1, j2, empati);	
			}
			else//j2 ganha a carta
			{
				empati = GanhadorJ2(j1, j2, empati);	
			}					
		}
		else//se n tiver trunfo na jogada.
		{
			vencedor = sorteio(j1, j2);
			if(vencedor == 0)//empate!
			{
				empati = empate(j1, j2, empati);//mando os ponteiros das cartas de cada jogador e o ponteiro q recebe a lista do empate.
			}
			else if(vencedor == 1)//ganhador 1
			{
				empati = GanhadorJ1(j1, j2, empati);		
			}
			else if(vencedor == 2)//ganhador 2
			{
				empati = GanhadorJ2(j1, j2, empati);	
			}
		}
	}
	
	
	if(j1->Deck != NULL)
	{
		puts(j2->Deck->cdg);
		return j1;
	}
	else
	{
		return j2;
	}
}

void Pesquisa(Pe p[], int ID, int n, int ant)
{
	int i = n;
	if(ID == p[i].id)
	{
		printf("\nNome: ");
		puts(p[i].nome);
		printf("Origem: ");
		puts(p[i].origem);
		printf("Idade: %d\n",p[i].idade);
		printf("Titulos: %d\n",p[i].titulos);
		system("pause");
		return;
	}
	else if(ID > p[i].id)
	{
		//puts(p[i].nome);
		i = i + ant/2;
		Pesquisa(p, ID, i, n/2);//anterior recebe o tamanho do vetor q sera analisado, novo vetor.			
	}
	else
	{
		//puts(p[i].nome);
		if(n == 1)
		{
			i = i - n;
		}
		else
		{
			i = (n/2);//vai dividindo e indo para o anterior.			
		}
	//	system("pause");
		Pesquisa(p, ID, i, n/2);
	}
	return;
}

void mostraGanhador(Pe p[])
{
	system("cls");
	printf("\t\t\t\t\t\t Loading.");
	Beep(1010, 100);
	system("cls");
	printf("\t\t\t\t\t\t Loading..");	
	Beep(9020, 100);
	system("cls");
	printf("\t\t\t\t\t\t Loading...");		
	Beep(2030, 100);
	system("cls");
	printf("\t\t\t\t\t\t Loading....");		
	Beep(8040, 100);
	system("cls");
	printf("\t\t\t\t\t\t Loading.....");		
	Beep(3050, 100);
	system("cls");
	printf("\t\t\t\t\t\t Loading......");
	sleep(1);
	system("cls");
	printf("O ganhador do campeonato eh ");
}

void Analisa(int n)
{
	if(n >= 16)
	{
		printf("\t\t OITAVAS DE FINAL.\n");
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		sleep(2);
	}
	else if(n == 8)
	{
		printf("\t\t QUARTAS DE FINAL.\n");
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		Beep(1000,10);
		sleep(2);
	}
	else if(n == 4)
	{
		printf("\t\t SEMI FINAL!!\n");
		Beep(1000,10);
		Beep(1000,10);
		sleep(2);
	}
	else if(n == 2)
	{
		printf("\t\t A GRANDE FINAAAL!!!\n");
		Beep(4000,100);
		sleep(1);
	}
}

void quadrado(Jog *j1, Jog *j2)
{
	printf("\t\t-----------------\n");
	printf("\t\t|\t\t|\n\t\t\t");
	//printf("|\t\n\t");
	puts(j1->player.nome);
	printf("\t\t|\t\t|\n");
	printf("\t\t-----------------\n");
	printf("\t\t\tVS\t\n");
	printf("\t\t-----------------\n");
	printf("\t\t|\t\t|\n\t\t\t");
	//printf("|\t\n\t");
	puts(j2->player.nome);
	printf("\t\t|\t\t|\n");
	printf("\t\t-----------------\n");
}

int Distribuir(Car *c, Pe p[], int n, Pe ganhadores[])
{
	system("cls");
	Analisa(n);
	int i, aux = 0, auxVetor = 0;//para atribuir os dados;
	Pe vtpGanhadores[n / 2];
	if(n % 2 == 0){
		do
		{
			Jog *j1 = (Jog*) malloc(sizeof(Jog));
			Jog *j2 = (Jog*) malloc(sizeof(Jog));
			Car *primeiro = c;//Pego a primeira carta
			j1->player = p[aux];
			j2->player = p[aux + 1];
			system("cls");
			quadrado(j1, j2);
			sleep(1,4);
			int i;
			for(i = 0; i < 16; i++)//distribuindo as cartas para os jogadores.
			{
				if(i == 15)
				{
					j1->Deck = c;
					c = c -> prox;
					j1->Deck->prox = primeiro;
					primeiro->ant = j1->Deck;
				}
				else
				{
					j1->Deck = c;
					c = c -> prox;					
				}			
			}
			primeiro = c;
			for(i = 0; i < 16; i++)//distribuição de cartas.
			{
				if(i == 15)
				{
					j2->Deck = c;
					c = c -> prox;
					j2->Deck->prox = primeiro;
					primeiro->ant = j2->Deck;
				}
				else
				{
					j2->Deck = c;
					c = c -> prox;					
				}			
			}
			system("pause");
			Jog *ganhador;
			ganhador = Partida(j1, j2);
			
			printf("O ganhador foi o ");
			puts(ganhador->player.nome);
			c = ganhador->Deck;//c = ponteiro do baralho todo recebe o baralho do ganhador da rodada, assim pegando um baralho ja embaralhado
			vtpGanhadores[auxVetor] = ganhador->player;//o vetor recebe o dado do jogador q ganhou para mandar dps por parametro o vetor de pessoas.
			aux+=2;//2 pq sempre sera em duplas.
			auxVetor++;																				//e completo.
			system("pause");
		}while(aux < n);
		
		tabela(auxVetor, vtpGanhadores, ganhadores);
		Distribuir(c, vtpGanhadores, auxVetor, ganhadores);
	}
	else
	{
		mostraGanhador(ganhadores);
	}
	//printf("%d\n%d\n",ganhadores[0].id,ganhadores[0].idade);
//	puts(ganhadores[0].nome);
//	puts(ganhadores[0].origem);
//	system("pause");
	return ganhadores[0].id;//retorno o ID do vencedor para a pesquisa;
}

