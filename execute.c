#include "biblioteca.h"

void execute2(int indice) 
{
	//char linha[15],*args[2];
	int tempoaux = TEMPO,i,numero_aleatorio,numero_aleatorio_aloc_dealoc,erro_dealoc; // contas
	x.indicePCB = indice;

	do // executar instruçoes
	{
		if(OPCAO_ESCALONAMENTO == 1)
		{
			if(terminou_processo == 1)
			{
				dentro_execute = 1;
				FCFS2();
				dentro_execute = 0;
				indice = indice_para_executar;
				x.indicePCB = indice;
			}
		}
		else if(OPCAO_ESCALONAMENTO == 3)
		{
			if(terminou_processo == 1)
			{
				dentro_execute = 1;
				PRIORIDADE();
				dentro_execute = 0;
			//	printf("INDICE %d\n",indice_para_executar);
				indice = indice_para_executar;
				x.indicePCB = indice;
			}
		}
		else
		{
			switch (OPCAO_ESCALONAMENTO2)
			{
				case 1:
				if(terminou_processo == 1)
				{
					dentro_execute = 1;
					SJFS();
					dentro_execute = 0;
					indice = indice_para_executar;
					x.indicePCB = indice;
				}
				break;
				case 2:
					dentro_execute = 1;
					correrFilaProcessos();
					SJFS2();
					dentro_execute = 0;
					indice = indice_para_executar;
					x.indicePCB = indice;
				break;
			}
		}
		i = (PCB_Tabela[indice].endereco + PCB_Tabela[indice].program_counter);
	//	printf("INDICE PARA EXECUTAR %d\n",indice_para_executar);
	//  printf("INSTRUCAO: %c , %d   -> TEMPO: %d\n",memoria[i].ins,memoria[i].n,TEMPO);
	//	printf("I -> %d \t indice -> %d\n",i,indice); 

		if(memoria[i].ins == 'Z')
		{
			countTOTAL++;
			switch(QUALFIT)
			{
				case 1: FirstFit(x.indicePCB,memoria[i].n);// done
						estatisticasFit();
				break;
				case 2: WorstFit(x.indicePCB,memoria[i].n);// done
						estatisticasFit();
				break;
				case 3: BestFit(x.indicePCB,memoria[i].n);// done
						estatisticasFit();
				break;
				case 4: NextFit(x.indicePCB,memoria[i].n);// done 
						estatisticasFit();
				break;
			}
		}
		
		if(memoria[i].ins == 'X') // DONE
		{
			deallocate_mem(x.indicePCB);
		//	printf("VALOR M-> %d \n",PCB_Tabela[indice].ValorVariavel);
		}
		
		if(memoria[i].ins == 'M')
		{
			PCB_Tabela[indice].ValorVariavel = memoria[i].n;
		//	printf("VALOR M-> %d \n",PCB_Tabela[indice].ValorVariavel);
		}

		if(memoria[i].ins == 'A')
		{
			PCB_Tabela[indice].ValorVariavel += memoria[i].n;
		//	printf("VALOR A-> %d \n",PCB_Tabela[indice].ValorVariavel);
		}

		if(memoria[i].ins == 'S')
		{
			PCB_Tabela[indice].ValorVariavel -= memoria[i].n;
		//	printf("VALOR S-> %d \n",PCB_Tabela[indice].ValorVariavel);
		}

		if(memoria[i].ins == 'B')
		{		
			PCB_Tabela[indice].estado = 2;
			x.indicePCB = -1;
			x.PC_exec = -1;
			x.PID_exec = -1;
			pushFila3(&Bloqueados,obterElementoExecucao(&execucao));
			aux_numero_de_processos++;
			break;
		
		}

		if(memoria[i].ins == 'T')
		{
			PCB_Tabela[indice].estado = 3;
			PCB_Tabela[indice].tempo_terminada = TEMPO+1;
			aux_numero_de_processos++;
			x.indicePCB = -1;
			x.PC_exec = -1;
			x.PID_exec = -1;
			pushFila3(&terminados,obterElementoExecucao(&execucao));
			terminou_processo = 1;
			break;
		//	printf("TEMPO : %d   , TEMP_AUX + TIME QUANTUM : %d    , MEMORIA.INS : %c\n",TEMPO,(tempoaux + timeQuantum),memoria[i].ins);	
		}

	    /*if(memoria[i].ins == 'C')
		{
            //insereção do processo na fila de processos
			PCB_Tabela = (PCB *) realloc(PCB_Tabela, (CPU_COUNTER) * sizeof(PCB));
			
		    strcpy(PCB_Tabela[CPU_COUNTER-1].nome, PCB_Tabela[indice].nome); 
			PCB_Tabela[CPU_COUNTER-1].endereco = PCB_Tabela[indice].endereco;
            PCB_Tabela[CPU_COUNTER-1].ValorVariavel = PCB_Tabela[indice].ValorVariavel;
            PCB_Tabela[CPU_COUNTER-1].PID_processo = CPU_COUNTER-1;
            PCB_Tabela[CPU_COUNTER-1].PPID_processo = PCB_Tabela[indice].PID_processo;
            PCB_Tabela[CPU_COUNTER-1].prioridade = PCB_Tabela[indice].prioridade; // ARGS[2]
            PCB_Tabela[CPU_COUNTER-1].program_counter = PCB_Tabela[indice].program_counter;
            PCB_Tabela[CPU_COUNTER-1].estado = PCB_Tabela[indice].estado; // estado 0 -> ready ;; estado 1 -> em execução ;; estado 2 -> blocked
            PCB_Tabela[CPU_COUNTER-1].tempo_chegada = PCB_Tabela[indice].tempo_chegada; // estado 0 -> ready ;; estado 1 -> em execução ;; estado 2 -> blocked
            PCB_Tabela[CPU_COUNTER-1].tempo_terminada = -1;  

			x.indicePCB = CPU_COUNTER-1;
			x.PC_exec = PCB_Tabela[CPU_COUNTER-1].program_counter;
			x.PID_exec = PCB_Tabela[CPU_COUNTER-1].PID_processo;

			CPU_COUNTER++;
			
			PCB_Tabela[indice].program_counter = PCB_Tabela[indice].program_counter + memoria[i].n;
			PCB_Tabela[indice].estado = 0;
			continue;

		}*/
		if(memoria[i].ins == 'L')
		{
			int x=0;
			for(int a=0;a<(CPU_COUNTER -1);a++)
			{
				if(strcmp(memoria[i].nome,PCB_Tabela[a].nome) == 0) // procurar CASO JÁ EXISTA
				{	
					PCB_Tabela[indice].endereco = PCB_Tabela[a].endereco;
					PCB_Tabela[indice].ValorVariavel = 0;
					strcpy(PCB_Tabela[indice].nome,PCB_Tabela[a].nome);
					PCB_Tabela[indice].program_counter = 0;
					x = 1;
					break; // ?????	
				}
			}
			if(x != 1) // se nao existe este processo na tabela
			{
				char aux_nome[20];
				strcpy(aux_nome,memoria[i].nome);
				strcat(aux_nome,".txt");

				FILE *fp = fopen(aux_nome,"r");
				if(fp == NULL)
					printf("Erro na abertura do ficheiro -> L -> %s\n",aux_nome);

			//	for(int s=0;s<contador_array_ficheiro_memoria;s++)
        	//		printf("Memoria[%d] -> %c,%d,%s\n",s,memoria[s].ins,memoria[s].n,memoria[s].nome);

				PCB_Tabela[indice].endereco = contador_array_ficheiro_memoria;
				PCB_Tabela[indice].ValorVariavel = 0;
				strcpy(PCB_Tabela[indice].nome,memoria[i].nome);
				PCB_Tabela[indice].program_counter = 0;
				PCB_Tabela[indice].tempo_chegada = TEMPO;
				ficheiro_memoria(fp);
				free (fp);

			}
			continue;

		}
		if(QUALSOLICITACAO == 1)
		{
			numero_aleatorio_aloc_dealoc = (rand() % (1 - 0 + 1)) + 0;
			if(numero_aleatorio_aloc_dealoc == 1)
			{
				erro_dealoc = deallocate_mem(indice);
				if(erro_dealoc == 1)
				{

				}
				//printf("O processo #%d nao está alocado na lista memoria\n",indice);
				//printf("Processo #%d dealocado\n",indice);
				//printListaMemoria(ListaMemoria);
				//printf("\n");
			}
			else
			{
				numero_aleatorio = (rand() % (10 - 3 + 1)) + 3;
				//printf("NUMERO ALEATORIO: %d\n",numero_aleatorio);
				countTOTAL++;
				switch(QUALFIT)
				{
					case 1: FirstFit(indice,numero_aleatorio);// done working
							estatisticasFit();
					break;
					case 2: WorstFit(indice,numero_aleatorio);// done working
							estatisticasFit();
					break;
					case 3: BestFit(indice,numero_aleatorio);// done working
							estatisticasFit();
					break;
					case 4: NextFit(indice,numero_aleatorio);// done working
							estatisticasFit();
					break;
				}
			}
		}
		//printf("PCB_TABELA[%d].valor_variavel = %d\n",indice,PCB_Tabela[indice].ValorVariavel);
		PCB_Tabela[indice].program_counter = PCB_Tabela[indice].program_counter + 1;
	//	printf("TEMPO : %d , PROGRAM COUNTER: %d , PROCESSO: %s , I: %d\n",TEMPO,PCB_Tabela[indice].program_counter,PCB_Tabela[indice].nome,i);
		i++;
		TEMPO++;
		if(OPCAO_ESCALONAMENTO2 == 2)
			tempo_restante_SJFS2--;
		if(tempo_restante_SJFS2 == 0 && OPCAO_ESCALONAMENTO2 == 2)
			break;

		}while(TEMPO <= (tempoaux + timeQuantum));
		terminou_processo = 1;
	return;
}

