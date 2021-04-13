#include "biblioteca.h"

void PRIORIDADE()
{
    Nodo *processo_maior_prio = NULL,*aux3;

    if(readyQueue->pcb->PID_processo == -5)
    {
        printf("READYQUEUE VAZIA\n");
        return;
    }
    //printf("x.INDICEPCB -> %d\n",x.indicePCB);
    if(x.indicePCB != -1)
    {
        indice_para_executar = x.indicePCB;
        execute2(indice_para_executar);
        buffer_ler_instrucao = 'N';   
        return;
    }
    else // encontra o processo com maior prioridade da ready queue
    {
        if(terminou_processo == 1)
        {
            processo_maior_prio = maiorPrioridade();   
            if(processo_maior_prio != NULL)
            {
                aux3 = obterElemento(&readyQueue,processo_maior_prio);
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
Nodo* maiorPrioridade()
{
    int i=0,min_prio;
    Nodo *aux=readyQueue,*aux2=NULL;
    if(readyQueue->pcb->PID_processo != -5 && readyQueue->nseg->pcb->PID_processo == -5 && readyQueue->pcb->prioridade > 0)
    {
        aux2 = readyQueue;
        readyQueue = readyQueue->nseg;
    }
    else
    {
        while(aux != NULL)
        {
            if(aux->pcb->PID_processo == -5)
                break;
            i++;
            if(i==1 && aux->pcb->prioridade > 0)
            {
                min_prio = aux->pcb->prioridade;
                aux2 = aux;
            }
            if(i > 1 && aux->pcb->prioridade < min_prio && aux->pcb->prioridade > 0)
            {
                min_prio = aux->pcb->prioridade;
                aux2 = aux;
            }
            aux = aux->nseg;
        }
    }
    return aux2;
}