#include "biblioteca.h"

void FCFS2()
{
	Nodo *primeiro;
	int a=0;
	if(readyQueue->pcb->PID_processo == -5)//erro
		return;
	if(x.indicePCB != -1)
	{
		indice_para_executar = x.indicePCB;
        execute2(indice_para_executar);
        buffer_ler_instrucao = 'N';
		return;
	}
	else
	{
		if(readyQueue->pcb->PID_processo != -5 && readyQueue->nseg->pcb->PID_processo == -5)// 1 + erro
		{
			primeiro = readyQueue;
			mudarHead(&readyQueue);
			primeiro->nseg = NULL;
			//printf("%d ,%s \n",primeiro->pcb->PID_processo,primeiro->pcb->nome);
			a = 1;
		}
		if(a == 0)
		{	
			primeiro = obterFirst(&readyQueue);
		}
		pushFila3(&execucao,primeiro);
		indice_para_executar = execucao->pcb->PID_processo;
		if(dentro_execute == 0)
		{
			terminou_processo = 0;
			execute2(indice_para_executar);
			buffer_ler_instrucao = 'N';
		}
	}	
	return;
}
Nodo* obterFirst(Nodo **L)
{
	Nodo *aux = *L,*aux2;
	while(aux != NULL)
	{
		if(aux->nseg->nseg->pcb->PID_processo == -5)
			break;
		aux = aux->nseg;
	}
	aux2 = aux;
	aux= aux->nseg;
	aux2 ->nseg = aux->nseg;

	return aux;
}
void mudarHead(Nodo **head)
{
	(*head) = (*head)->nseg;
}