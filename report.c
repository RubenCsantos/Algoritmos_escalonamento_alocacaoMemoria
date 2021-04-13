#include "biblioteca.h"

void report()
{
	Nodo *aux_report = NULL;

	printf("TEMPO ACTUAL: %d\n\n",TEMPO);

	printf("PROCESSO EM EXECUÇÃO: ");
	if(x.indicePCB != -1)
	{
		printf("\n%d , %d , %d , %d , %d , %d , %d\n",PCB_Tabela[x.indicePCB].PID_processo, PCB_Tabela[x.indicePCB].PPID_processo, PCB_Tabela[x.indicePCB].prioridade, PCB_Tabela[x.indicePCB].ValorVariavel ,PCB_Tabela[x.indicePCB].tempo_chegada , PCB_Tabela[x.indicePCB].program_counter, PCB_Tabela[x.indicePCB].estado );
	}
	else printf("NÃO EXISTE NENHUM PROCESSO EM EXECUÇÃO.\n\n");


	printf("PROCESSOS BLOQUEADOS:");
	if(Bloqueados != NULL)
	{
		printf("\nFila de processos:\n");
		aux_report=Bloqueados;
		while(aux_report != NULL)
		{
			printf("%d,",aux_report->pcb->PID_processo);
			printf("%d,",aux_report->pcb->PPID_processo);
			printf("%d,",aux_report->pcb->prioridade);
			printf("%d,",aux_report->pcb->ValorVariavel);
			printf("%d\n",aux_report->pcb->tempo_chegada);
			aux_report = aux_report->nseg;
		}
		printf("\n");
	}
	else printf(" NÃO EXISTE NENHUM PROCESSO BLOQUEADO\n\n");

	printf("PROCESSOS PRONTOS A EXECUTAR:");

	if(readyQueue != NULL)
	{
		printf("\nFila de processos:\n");

		aux_report = readyQueue;
		while(aux_report != NULL)
		{
			printf("%d,",aux_report->pcb->PID_processo);
			printf("%d,",aux_report->pcb->PPID_processo);
			printf("%d,",aux_report->pcb->prioridade);
			printf("%d,",aux_report->pcb->ValorVariavel);
			printf("%d\n",aux_report->pcb->tempo_chegada);
			aux_report = aux_report->nseg;
		}
		printf("\n");
	}
	else printf(" NÃO EXISTE NENHUM PROCESSO PRONTO A EXECUTAR\n\n");

	printf("PROCESSOS TERMINADOS:");

	if(terminados != NULL)
	{
		printf("\nFila de processos:\n");
		aux_report = terminados;
		while(aux_report != NULL)
		{
			printf("%d,",aux_report->pcb->PID_processo);
			printf("%d,",aux_report->pcb->PPID_processo);
			printf("%d,",aux_report->pcb->prioridade);
			printf("%d,",aux_report->pcb->ValorVariavel);
			printf("%d\n",aux_report->pcb->tempo_chegada);
			aux_report = aux_report->nseg;
		}
	}
	else printf(" NÃO EXISTE NENHUM PROCESSO TERMINADO\n\n");	
	free(aux_report);
}

void estatisticas_globais()
{
	float avTAT=0,avWT=0;
	int WT;

	printf("Estatísticas Globais: \n\n");
	printf("P#\t AT\t BT\t CT\t TAT\t WT\t\n\n");
	
	for(int f=0;f<(CPU_COUNTER-1);f++)
	{
		if(PCB_Tabela[f].estado != 3)
			continue;
			
		WT = (PCB_Tabela[f].tempo_terminada - (PCB_Tabela[f].tempo_chegada + (PCB_Tabela[f].program_counter + 1)));
		if(WT < 0)
			WT = 0;
		printf("P%d\t %d\t %d\t %d\t %d\t %d\n",f,PCB_Tabela[f].tempo_chegada,(PCB_Tabela[f].program_counter)+1,PCB_Tabela[f].tempo_terminada,(PCB_Tabela[f].tempo_terminada - PCB_Tabela[f].tempo_chegada ),WT);

		avTAT += (PCB_Tabela[f].tempo_terminada - PCB_Tabela[f].tempo_chegada);
		avWT += WT;
	}
	avTAT = (avTAT / (CPU_COUNTER-1));
	avWT = (avWT / (CPU_COUNTER-1));
	if(avWT < 0)
		avWT = 0;

	printf("\n\nAverage Turnaround Time = %f\n",avTAT);
	printf("Average Waiting Time = %f\n\n",avWT);

	return;
}