#include "biblioteca.h"

void lercomandos()
{
    
    int des;

    printf("Quer debugging?\n");
    printf("1-Sim \n2-Nao\n");
    scanf("%d",&des);

    do{
        if(des == 1)
        {
            printf("Quer usar o ficheiro 'control.txt' ou minha_stdin?\n 1-Control.txt \n 2-Stdin \n");
            scanf("%d",&des);
            if(des == 1)
            {
                flag_control = 1;
                break;
            }
            else 
            {
                flag_control = 0;
                break;
            }
            
            break;
        }  
        else if(des == 2)
        {

            flag_control = 1;
            break;
        }
        else
        {
            printf("insere 1 ou 2\n");
        }
    }while(1);
    return ;
}

void minha_stdin()
{
    char car;
    do
    {  //abertura dos programas e preenchimento da memória  
    if(buffer_ler_instrucao == 'N')
    {
        printf("\n");
        scanf(" %c",&car);
        printf("\n");
    }
    else
    {
        correrFilaProcessos();
        TEMPO++;
    }
    

    if(buffer_ler_instrucao == 'N')
    {   
        buffer_ler_instrucao = car;
        if(car == 'E')
        {
            if(x.indicePCB != -1)
            {
                terminou_processo = 0;
                execute2(x.indicePCB);
                buffer_ler_instrucao = 'N';
            }
            else 
            {
                if(OPCAO_ESCALONAMENTO2 == 1)
                {    
                    //printf("1\n");
                    SJFS();
                }
                else if(OPCAO_ESCALONAMENTO2 == 2)
                {    
                    //printf("2\n");
                    SJFS2();
                }
                else if(OPCAO_ESCALONAMENTO == 3)
                {    
                    //printf("3\n");
                    PRIORIDADE();
                }
                else if(OPCAO_ESCALONAMENTO == 1)
                {    
                    FCFS2();
                }
                else printf("DOOR STUCK\n");
            }
        }
        if(car == 'I')
        {
            if(x.indicePCB != -1)
            {
                PCB_Tabela[x.indicePCB].estado = 2;
                x.indicePCB = -1;
                x.PC_exec = -1;
                x.PID_exec = -1;
                pushFila3(&Bloqueados,obterElementoExecucao(&execucao));;
                aux_numero_de_processos++;
                buffer_ler_instrucao ='N';
            }
            
        }
        if(car == 'D')
        {
            LongoPrazo();
            buffer_ler_instrucao ='N';
        }
        if(car == 'R')
        {
            report();
            buffer_ler_instrucao ='N';
        }
        if(car == 'T')
        {
            estatisticas_globais();
            flag_terminar_simulador = 1; // flag global
            buffer_ler_instrucao = 'N';
            return;
        }
        contador++;
    }
    else
    {
        if(buffer_ler_instrucao == 'E')
        {    
            if(readyQueue->pcb->PID_processo != -5 && x.indicePCB == -1) // se ready Queue nao estiver vazia E NADA ESTIVER A CORRER ENCONTRA UM PROCESSO
            { 
                if(OPCAO_ESCALONAMENTO2 == 1)
                {    
                    SJFS();
                }
                else if(OPCAO_ESCALONAMENTO2 == 2)
                {    
                    SJFS2();
                }
                else if(OPCAO_ESCALONAMENTO == 3)
                {    
                    PRIORIDADE();
                }
                else if(OPCAO_ESCALONAMENTO == 1)
                {    
                    FCFS2();
                }
                else printf("Erro.\n");
            }
            
            if(aux_numero_de_processos == tamanho_Fila_Processos)
            {
                buffer_ler_instrucao = 'N';
            }

        }
        else if(buffer_ler_instrucao == 'I')    
        {
            if(x.indicePCB != -1) //DUVIDA
            {
                pushFila3(&Bloqueados,obterElementoExecucao(&execucao));;
                aux_numero_de_processos++;
                buffer_ler_instrucao = 'N';
            }
            else //BLOQUEAR SÓ SE ESTIVER A CORRER
            {    
                buffer_ler_instrucao = 'N';
            }

            // printf("EXECUCAO -> -> -> %s , %d \n",execucao->pcb->nome,execucao->pcb->program_counter);
        }
        TEMPO++;  
    }
    }while(flag_terminar_simulador != 1);
    return;
}
