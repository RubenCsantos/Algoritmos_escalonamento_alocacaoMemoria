#include "biblioteca.h"

void gerirProcessosPreemptivo()
{
    int count=0;
    char c[1000],*args[3],*control_ins,ler_0[10];
    buffer_ler_instrucao = 'N';

    lercomandos(); //set variavel control = 0 ou control = 1

    FILE *programa = fopen("plano.txt","r"),*controlar = NULL; // abertura do plano.txt
    if(programa == NULL)
    {
        printf("Erro na abertura do ficheiro -> plano.txt");
        return;
    }
    while(fgets(c,1000,programa) != NULL) // preenchimento da fila de processos com todos os processos do ficheiro plano.txt
    {
        parse(c,args);
        if(tamanho_Fila_Processos == 0)
        {
            fila = (File_Process*) malloc(sizeof(File_Process));
            strcpy((fila[0]).nome,args[0]);
            (fila[0]).prioridade = atoi(args[2]);
            (fila[0]).tempo = atoi(args[1]);
        }
        else
        {
        fila = (File_Process *) realloc(fila,((tamanho_Fila_Processos)+1) * sizeof(File_Process));
        strcpy((fila[tamanho_Fila_Processos]).nome,args[0]);
        (fila[tamanho_Fila_Processos]).prioridade = atoi(args[2]);
        (fila[tamanho_Fila_Processos]).tempo = atoi(args[1]);
        }
        tamanho_Fila_Processos++;
    }
    fclose(programa);

    int i=0;
  /*while(i < tamanho_Fila_Processos)
    {
        printf("nome: %s\tprioridade:%d\ttempo chegada:%d\n",fila[i].nome,fila[i].prioridade,fila[i].tempo);
        i++;
    }
    return;*/
    /*printf("%d %d\n",i,tamanho_Fila_Processos);
    return;*/
    if(flag_control == 1)
    {
        controlar = fopen("control.txt","r");            
        if(controlar == NULL)
        {
            printf("Erro na abertura do ficheiro -> control.txt\n");
            return;
        }
        control_ins = (char*) malloc(sizeof(char));
        while(fgets(ler_0,10,controlar) != NULL)
        {
            control_ins = (char*) realloc(control_ins,((count)+1) * sizeof(char));
            control_ins[count] = ler_0[0];
            count++;
        }
        fclose(controlar);
    }
  /*for(int g=0;g<=count;g++)
        printf("%c\n",control_ins[g]);
    return*/
    /* EEEEEEEEEEEEEEERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOOOOOOOOOOOOO*/
    PCB_Tabela = (PCB *) realloc(PCB_Tabela, (CPU_COUNTER) * sizeof(PCB));
    strcpy(PCB_Tabela[CPU_COUNTER-1].nome,"prevenirerro");
    PCB_Tabela[CPU_COUNTER-1].endereco = -1;
    PCB_Tabela[CPU_COUNTER-1].ValorVariavel = -1;
    PCB_Tabela[CPU_COUNTER-1].PID_processo = -5;
    PCB_Tabela[CPU_COUNTER-1].PPID_processo = -1;
    PCB_Tabela[CPU_COUNTER-1].prioridade = -1; // ARGS[2]
    PCB_Tabela[CPU_COUNTER-1].program_counter = -1;
    PCB_Tabela[CPU_COUNTER-1].estado = -1; // estado 0 -> ready ;; estado 1 -> em execução ;; estado 2 -> blocked
    PCB_Tabela[CPU_COUNTER-1].tempo_chegada = -1;
    PCB_Tabela[CPU_COUNTER-1].tempo_terminada = -1;
    Nodo *erro = criarNodo(&(PCB_Tabela[CPU_COUNTER-1]));
    CPU_COUNTER++;
    pushFila3(&readyQueue, erro);
    /* EEEEEEEEEEEEEEERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOOOOOOOOOOOOO*/
    //printf("Tamanho Fila Processos: %d\n",tamanho_Fila_Processos);

    while(flag_terminar_simulador != 1)
    {
        while(1)
        {    
            if(flag_terminar_simulador == 1)
                break;

            if((fila[i]).tempo <= TEMPO && (fila[i]).lido == 0 && (fila[i]).tempo >= 0) // se o processo estiver dentro do tempo para ser executado, irá para a ready queue
            {                                                   // no entanto se não houver nenhum processo no momento de ser executado, TEMPO++ e repete a verificação
                //printf("Fila[%d] = Nome: %s,Tempo: %d,Prioridade: %d \n",i,fila[i].nome,fila[i].tempo,fila[i].prioridade);
                
                FILE *ficheiro = fopen((fila[i]).nome, "r");// abre o ficheiro que está dentro do tempo de execução
                if(ficheiro == NULL)
                {
                    printf("Erro na abertura do ficheiro -> %s\n",(fila[i]).nome);
                    return;
                }

                PCB_Tabela = (PCB *) realloc(PCB_Tabela, (CPU_COUNTER) * sizeof(PCB));
                strcpy(PCB_Tabela[CPU_COUNTER-1].nome, parsePRG((fila[i]).nome));
                PCB_Tabela[CPU_COUNTER-1].endereco = contador_array_ficheiro_memoria;
                PCB_Tabela[CPU_COUNTER-1].ValorVariavel = 0;
                PCB_Tabela[CPU_COUNTER-1].PID_processo = CPU_COUNTER-1;
                PCB_Tabela[CPU_COUNTER-1].PPID_processo = 0;
                PCB_Tabela[CPU_COUNTER-1].prioridade = (fila[i]).prioridade; // ARGS[2]
                PCB_Tabela[CPU_COUNTER-1].program_counter = 0;
                PCB_Tabela[CPU_COUNTER-1].estado = 0; // estado 0 -> ready ;; estado 1 -> em execução ;; estado 2 -> blocked
                PCB_Tabela[CPU_COUNTER-1].tempo_chegada = (fila[i]).tempo;
                PCB_Tabela[CPU_COUNTER-1].tempo_terminada = -1;


               /* printf("PCB_TABELA[%d].nome = %s\n",CPU_COUNTER-1,PCB_Tabela[CPU_COUNTER-1].nome);
                printf("CPU COUNTER -> %d\n",CPU_COUNTER); */
                Nodo *Nodo = criarNodo(&(PCB_Tabela[CPU_COUNTER-1]));
                CPU_COUNTER++;
                //printf("Ready = Nome: %s,Tempo: %d,Prioridade: %d\n",Nodo->pcb->nome,Nodo->pcb->tempo_chegada,Nodo->pcb->prioridade);
                pushFila3(&readyQueue, Nodo);

                ficheiro_memoria(ficheiro);

                (fila[i]).lido = 1;
            }
            if((i+1) == tamanho_Fila_Processos)
            {  
                if(readyQueue->pcb->PID_processo == -5) // MESMA COISA QUE NULL
                {
                    if(aux_numero_de_processos == tamanho_Fila_Processos)
                    {
                        estatisticas_globais();
                        flag_terminar_simulador = 1; // flag global
                        buffer_ler_instrucao = 'N';   
                    }
                    TEMPO++;
                    i=0;
                    continue;
                }
                else
                {     
                    if(flag_control == 1)
                    {i=0;control2(control_ins,count);continue;}
                    else
                    {i=0;minha_stdin();continue;}
                    
                    
                    if(flag_terminar_simulador == 1)
                        break;
                }
            }
            i++;
        }
        break;
    }
    /*for(int s=0;s<contador_array_ficheiro_memoria;s++)
        printf("Memoria[%d] -> %c,%d,%s\n",s,memoria[s].ins,memoria[s].n,memoria[s].nome);*/
    return;
}
void control2(char *array,int count)
{

    //printf("%c -> Buffer\n",buffer_ler_instrucao);
    char ler;
    //printf("%c -> BUFFER\n",buffer_ler_instrucao);
    //printf("%d -> TEMPO\n",TEMPO);
    if(buffer_ler_instrucao == 'N')
    {   
        ler = array[contador]; //printf("%c -> Ler\n",ler);
        buffer_ler_instrucao = ler;
        if(ler == 'E')
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
        if(ler == 'I')
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
        if(ler == 'D')
        {
            LongoPrazo();
            buffer_ler_instrucao ='N';
        }
        if(ler == 'R')
        {
            report();
            buffer_ler_instrucao ='N';
        }
        if(ler == 'T')
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
    return;
}
void correrFilaProcessos()
{
    for(int i = 0; i <= tamanho_Fila_Processos;i++)
    {
        if((fila[i]).tempo <= TEMPO && (fila[i]).lido == 0 && (fila[i]).tempo >= 0) // se o processo estiver dentro do tempo para ser executado, irá para a ready queue
            {                                                   // no entanto se não houver nenhum processo no momento de ser executado, TEMPO++ e repete a verificação
                //printf("Fila[%d] = Nome: %s,Tempo: %d,Prioridade: %d \n",i,fila[i].nome,fila[i].tempo,fila[i].prioridade);
                
                FILE *ficheiro = fopen((fila[i]).nome, "r");// abre o ficheiro que está dentro do tempo de execução
                if(ficheiro == NULL)
                {
                    printf("Erro na abertura do ficheiroo -> %s\n",(fila[i]).nome);
                    return;
                }

                PCB_Tabela = (PCB *) realloc(PCB_Tabela, (CPU_COUNTER) * sizeof(PCB));
                strcpy(PCB_Tabela[CPU_COUNTER-1].nome, parsePRG((fila[i]).nome));
                PCB_Tabela[CPU_COUNTER-1].endereco = contador_array_ficheiro_memoria;
                PCB_Tabela[CPU_COUNTER-1].ValorVariavel = 0;
                PCB_Tabela[CPU_COUNTER-1].PID_processo = CPU_COUNTER-1;
                PCB_Tabela[CPU_COUNTER-1].PPID_processo = 0;
                PCB_Tabela[CPU_COUNTER-1].prioridade = (fila[i]).prioridade; // ARGS[2]
                PCB_Tabela[CPU_COUNTER-1].program_counter = 0;
                PCB_Tabela[CPU_COUNTER-1].estado = 0; // estado 0 -> ready ;; estado 1 -> em execução ;; estado 2 -> blocked
                PCB_Tabela[CPU_COUNTER-1].tempo_chegada = (fila[i]).tempo;
                PCB_Tabela[CPU_COUNTER-1].tempo_terminada = -1;


               /* printf("PCB_TABELA[%d].nome = %s\n",CPU_COUNTER-1,PCB_Tabela[CPU_COUNTER-1].nome);
                printf("CPU COUNTER -> %d\n",CPU_COUNTER); */
                Nodo *Nodo = criarNodo(&(PCB_Tabela[CPU_COUNTER-1]));
                CPU_COUNTER++;
                //printf("Ready = Nome: %s,Tempo: %d,Prioridade: %d\n",Nodo->pcb->nome,Nodo->pcb->tempo_chegada,Nodo->pcb->prioridade);
                pushFila3(&readyQueue, Nodo);

                ficheiro_memoria(ficheiro);

                (fila[i]).lido = 1;
            }
    }


}
