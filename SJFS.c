#include "biblioteca.h"

void SJFS()
{
    Nodo *aux2=NULL,*aux3;

    if(readyQueue->pcb->PID_processo == -5)
    {
        printf("ReadyQueue Vazia\n");
        return;
    }
    if(x.indicePCB != -1) // Se há algum programa a ser executado,não altera
    {
        indice_para_executar = x.indicePCB;
        execute2(indice_para_executar);
        buffer_ler_instrucao = 'N';
        return;
    }
    else// caso não esteja encontra o menor burst time dos programas na readyQueue
    {
        if(terminou_processo == 1)
        {
            aux2 = menorBurstTime();
            if(aux2 != NULL) //se nada está a ser executado e existe um processo na readyQueue com o menor burstTime entao executamos este
            {
                aux3 = obterElemento(&readyQueue,aux2);
                pushFila3(&execucao,aux3);
                indice_para_executar = execucao->pcb->PID_processo;
                if(dentro_execute == 0)
                {
                    terminou_processo = 0;
                    execute2(indice_para_executar);
                    buffer_ler_instrucao = 'N';
                }
            }
        }
    }
    return;
}
void SJFS2()
{
    int valor_restante;
    char *args[2];


    if(readyQueue->pcb->PID_processo == -5)
    {//printf("ReadyQueue Vazia\n");   
     return;
    }
 
    char file[20],ler_executado[15];
    int count=0;
    Nodo *aux2=NULL,*aux3,*aux4,*aux5;

    if(x.indicePCB != -1) //ver o file que está a ser executado
    {
        //printf("A EXECUTAR %d\n",x.indicePCB);
        strcpy(file,PCB_Tabela[x.indicePCB].nome);
        strcat(file , ".txt"); 
    }
    else //encontrar o menor burst time da readyQueue ficando com o nodo -> aux2
    {
       // printf("AQUI\n");
        aux2 = menorBurstTime();
        if(aux2 != NULL) //se nada está a ser executado e existe um processo na readyQueue com o menor burstTime entao executamos este
        {
            aux3 = obterElemento(&readyQueue,aux2);
            pushFila3(&execucao,aux3);
            indice_para_executar = execucao->pcb->PID_processo;
            if(dentro_execute == 0)
            {
                tempo_restante_SJFS2 = timeQuantum;
                execute2(indice_para_executar);
                buffer_ler_instrucao = 'N';
            }
            return;
        }
    }
    
    FILE *f1 = fopen(file,"r");
    while(fgets(ler_executado,15,f1) != NULL)
    {
        parse(ler_executado,args);
        if(strcmp("Z",args[0]) == 0 && QUALSOLICITACAO != 2)
            continue;
        else if(strcmp("X",args[0]) == 0 && QUALSOLICITACAO != 2)
            continue;

        count++; // VER O BURST TIME TOTAL
    }
    fclose(f1);
    valor_restante = count - x.PC_exec; //BURST TIME RESTANTE
    aux4 = menorBurstTime();
    if(aux4->pcb->PID_processo == x.indicePCB)
    {
        //printf("Executando\n");
        indice_para_executar = x.indicePCB;
        return;
    }
    if(valor_restante > SJFS_count) // SE O BURST TIME RESTANTE FOR MAIOR QUE O BURST TIME DE OUTRO PROCESSO NA READYQUEUE TROCA
    {
        aux5 = obterElemento(&readyQueue,aux4);
        aux3 = (execucao);
        pushFila3(&readyQueue,aux3);
        pushFila3(&execucao,aux5);
        indice_para_executar = aux5->pcb->PID_processo;
        return;
    }
    indice_para_executar = x.indicePCB;
    return;
}


Nodo* menorBurstTime()
{
    Nodo *aux=readyQueue,*aux2=NULL;
    char file2[20],ler[15],*args[2];
    int count=0,min_count,iteracao=0,resultado;


    while(aux != NULL)
    {
        if(aux->pcb->PID_processo == -5)
            break;

        iteracao++;
        strcpy(file2,aux->pcb->nome);
        strcat(file2,".txt");

        //printf("%s -> nome PID: %d\t",file2,aux->pcb->PID_processo);

        FILE *f2 = fopen(file2, "r");
        while(fgets(ler,15,f2) != NULL)
        {
            parse(ler,args);
            if(strcmp("Z",args[0]) == 0 && QUALSOLICITACAO != 2)
                continue;
            else if(strcmp("X",args[0]) == 0 && QUALSOLICITACAO != 2)
                continue;

            count++;
        }
        resultado = count - (aux->pcb->program_counter);
        //printf("resultado: %d\n",resultado);
        fclose(f2);
        if(iteracao == 1) // dar um valor minimo
        {
            min_count = resultado; 
            aux2 = aux;
        }
        else if(resultado <= min_count && iteracao > 1)
        {
            min_count = resultado;
            aux2 = aux;
        }
        count = 0;
        aux = aux->nseg;
    }

    SJFS_count = min_count;
    //printf("MENORBURSTTIME -> %d\n",SJFS_count);
    return aux2;
}
