#include "biblioteca.h"

int main()
{
	int tamanho_particao;

	
	//parte 2
	countNEGADOS = 0;
	countTOTAL = 0;
	numeroDeNos = 0;
	numeroTotalDeNos = 0;
	resultado_alocacao = 0;
	tamanho_fragmento = 0;
	tamanho_nos = 0;
	dentro_execute = 0;
	tamanho_Fila_Processos = 0;
	terminou_processo = 1;
	//parte 1
	TEMPO=0;
	CPU_COUNTER=1;
	contador_array_ficheiro_memoria=0;
	flag_terminar_simulador = 0;
	x.indicePCB = -1;
	x.PC_exec = -1;
	x.PID_exec = -1;

	memoria = (instrucao *) realloc(memoria, (1000) * sizeof(instrucao));
	PCB_Tabela = NULL;
	readyQueue = NULL;

	int opcao;

	printf("Insira o valor do timequantum\n");
	scanf("%d",&timeQuantum);
//parte 2
	printf("Algoritmo a usar:\n1- First Fit\n2- Worst Fit\n3- Best Fit\n4- Next Fit\n5- Nenhum\n");
	scanf("%d",&QUALFIT);

	if(QUALFIT != 5 && QUALFIT < 5 && QUALFIT > 0)
	{
		printf("Memoria Total do Sistema (25):\n");
		scanf("%d",&MemoriaTotal);
		printf("Tamanho das Partições (1):\n");
		scanf("%d",&tamanho_particao);
		n_particoes = MemoriaTotal / tamanho_particao;
		n_particoes_por_ocupar = n_particoes; // numero de partiçoes que falta ocupar na lista da memoria
		while(n_particoes != 0)
		{
			ListaM *nb = criarNodoLista();
			pushListaMemoria(&ListaMemoria,nb);
			n_particoes--;
		}
		printf("Escolha o tipo de solicitações geradas.\n1- Aleatório\n2- Estaticamente\n3- Trace Não Feita\n");
		scanf("%d",&QUALSOLICITACAO);
		if(QUALSOLICITACAO == 1)
		{
			printf("Insira o numero da seed (12481)\n");
			scanf("%d",&seed);
			srand(seed);
		}
	}
//parte 1
	printf("Escolha um dos algoritmos de escalonamento:\n");
	printf("1. Escalonamento de curto prazo\n");
	scanf("%d" ,&opcao);

	switch(opcao)
	{
    	case 1: 
    		printf("1. FCFS\n2. SJSF\n3. Prioridade\n");
    		scanf("%d" ,&OPCAO_ESCALONAMENTO);

    		switch(OPCAO_ESCALONAMENTO)
			{
    			case 1: 
						gerirProcessosPreemptivo();
				break;
				case 2: 
						printf("1.SJSF Não-Preempetivo\n2.SJSF Preempetivo\n");
						scanf("%d",&OPCAO_ESCALONAMENTO2);
						switch(OPCAO_ESCALONAMENTO2)
						{
							case 1: gerirProcessosPreemptivo();
							break;
							case 2: gerirProcessosPreemptivo();
							break;
							default: printf("Insira uma opção válida\n");
						}
						
    			break;
				case 3: gerirProcessosPreemptivo();

				break;
    			default: printf("Insira uma opção válida!\n");
    		}
    	break;	
        default: printf("Insira uma opção válida!\n");
    }
	// PRINT ESTATISTICAS FIT
	if(QUALFIT != 5 && QUALFIT < 5 && QUALFIT > 0)
	{
		printf("ESTATISTICAS FIT\n");
		printf("NUMERO MÉDIO DE FRAGMENTOS EXTERNOS: %f \n",fragmentos_medio);
		printf("TEMPO MÉDIO DE ALOCAÇÃO: %f \n",nos_medio);
		printf("PERCENTAGENS DE SOLICITAÇÕES NEGADAS: %.2f \n",percentagem_vezes);
	}
/*	for(int i = 0;i<contador_array_ficheiro_memoria;i++)
		printf("Memoria[%d]:{ %c, %d, %s }\n",i,memoria[i].ins,memoria[i].n,memoria[i].nome);*/
	return 0;
}


Nodo *criarNodo(PCB *pcb)
{
	Nodo *nv =(Nodo*) malloc(sizeof(Nodo));
	
	nv->pcb = pcb;
	nv->nseg = NULL;

	return nv;
}

void pushFila3(Nodo **L, Nodo *nv)
{
	nv->nseg = (*L);
	(*L) = nv;
}

int sizeFila(Nodo *fila)
{
	Nodo *aux=fila;
	int count=0;

	while(aux!=NULL)
	{
		aux=aux->nseg;
		count++;
	}

	return count;
}

Nodo *obterElemento(Nodo **L,Nodo *nv)
{
	Nodo *aux = *L,*aux2;

	if(aux->pcb->PID_processo != -5 && aux == nv)
	{
		*L = aux->nseg;
		aux2 = aux;
		return aux2;
	}

	while(aux->pcb->PID_processo != -5)
	{
		if(aux->nseg == nv)
		{
			aux2 = aux;
			aux = aux->nseg;
			aux2->nseg = aux->nseg;
			break;
		}
		aux = aux->nseg;
	}
	return aux;
}
Nodo* obterElementoExecucao(Nodo **L)
{
	Nodo* aux = *L;
	if(aux != NULL)
	{
		*L = NULL;
		if(aux == NULL)
			printf("obterElementoExecucao -> aux == NULL\n");
		return aux;
	}
	return NULL;
}
void printList(Nodo *L)
{
	while(L != NULL)
	{
		printf("Nome: %s, PID: %d\n",L->pcb->nome,L->pcb->PID_processo);
		L = L->nseg;
	}
}
