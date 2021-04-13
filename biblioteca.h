#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>



//ESTRUTURAS DE DADOS
typedef struct {
    char ins; //
    int n; 
    char nome[15];
} instrucao;

typedef struct {
    char nome[15];
    int endereco;
    int ValorVariavel;
    int PID_processo;
    int PPID_processo;
    int prioridade;
    int program_counter;
    int estado;
	int tempo_chegada;
	int tempo_terminada;
} PCB;

typedef struct NODO{
	PCB *pcb;
	struct NODO *nseg;
}Nodo;

typedef struct {
	int indicePCB;
	int PID_exec;
	int PC_exec;
}runningState;

typedef struct{

	char nome[20];
	int tempo;
	int prioridade;
    int lido;

}File_Process;

//PARTE 2
typedef struct LISTA{

    int ID_Process;
    struct LISTA *nseg;

}ListaM;

// GLOBAIS 
PCB *PCB_Tabela;
instrucao *memoria;
File_Process *fila;
Nodo *readyQueue;
Nodo *Bloqueados;
Nodo *terminados;
Nodo *execucao;
int TEMPO;
int CPU_COUNTER; //numero de processos da PCBTABLE
int flag_terminar_simulador;
int aux_primeiro_endereco;
int contador_array_ficheiro_memoria;
int flag_control;
int contador;
int numero_de_processos,aux_numero_de_processos,processo_stdin; // fila[i] e flag de fim(as vezes)
//char lastcommand;
char buffer_ler_instrucao;
runningState x;
int timeQuantum;



//PARTE 2
ListaM *ListaMemoria,*inicio; //LISTA MEMORIA IMPORTANTE
int QUALFIT,QUALSOLICITACAO; //decisoes do user
int MemoriaTotal; // pedida pelo user
int n_particoes; // valor obtido (Nós da lista)
int seed; // semente para a geração dos numeros aleatorios
int tamanho_particao; // management da lista memoria
int n_particoes_por_ocupar; // managemente para os Fits
int resultado_alocacao; //insignificante na nossa aplicação
ListaM *nextFitPointer; //essential NextFit
int numeroDeNos,numeroTotalDeNos,countNEGADOS,countTOTAL; //dados estisticos
int *fragmentos_externos,tamanho_fragmento; //dados estatisticos
int *numero_de_nos,tamanho_nos;// dados estatisticos
double fragmentos_medio,nos_medio,percentagem_vezes; // dados estatisticos
int OPCAO_ESCALONAMENTO,OPCAO_ESCALONAMENTO2,dentro_execute,indice_para_executar;
int SJFS_count, tempo_restante_SJFS2,tamanho_Fila_Processos;
int terminou_processo;



//FUNÇÕES

void parse (char *buf, char **args);

char *parsePRG(char *string);

void ficheiro_memoria(FILE *f1);


Nodo *criarNodo(PCB *pcb);


void report();

void estatisticas_globais();


void minha_stdin();

void lercomandos();

void LongoPrazo();

int sizeFila(Nodo *fila);

///---------- PARTE 2

void gerirFits();

int deallocate_mem (int process_id); 

int alocate_mem (int process_id, int num_units); // devolve um int (numero de nós ou -1) mesmo nao usando para nada os valores

int fragment_count (); // acho que tem um bug mas é lidar

 
ListaM *criarNodoLista(); // criar nodos para a lista

void pushListaMemoria(ListaM **Lista,ListaM *no); //  insereção de nodos

void FirstFit(int ID,int num_particoes); // ALG 1

void WorstFit(int ID,int num_particoes); // ALG 2

void BestFit(int ID,int num_particoes); // ALG 3

void NextFit(int ID,int num_particoes);// ALG 4

void estatisticasFit();// atualizações das estatisticas

void SJFS();

void SJFS2();

void pushFila3(Nodo **L,Nodo *nv);

void gerirProcessosPreemptivo();

void execute2(int indice_do_processo);

Nodo* obterElemento(Nodo **L,Nodo *nv);

Nodo* obterElementoExecucao(Nodo **L);

Nodo* menorBurstTime();

void control2(char *array,int count);

void correrFilaProcessos();

void printList(Nodo *L);

void printListaMemoria(ListaM *La);

void FCFS2();

void PRIORIDADE();

Nodo* maiorPrioridade();

Nodo* obterFirst(Nodo **L);

void mudarHead(Nodo **L);