#include "biblioteca.h"

void FirstFit(int ID,int num_particoes) // ACABADO   WORKING
{
    int count= 0;
    resultado_alocacao = 0;

    if((n_particoes_por_ocupar == 0) || (num_particoes > n_particoes_por_ocupar))
    {
        //printf("NUM PARTIÇOES POR OCUPAR %d\n",n_particoes_por_ocupar);
        //printf("Não foi possivel usar o FirstFit para o processo #%d\n",ID);
        numeroDeNos = 0;
        countNEGADOS++;
        return;
    }
    ListaM *aux = ListaMemoria;   
    while(aux != NULL)
    {
        numeroDeNos++;
        if(aux->ID_Process == -2)
        {
            count++;
            if(count == 1)
                inicio = aux;
            if(count == num_particoes)
                break;
        }
        aux = aux->nseg;
    }
    resultado_alocacao = alocate_mem(ID,num_particoes);
	//printListaMemoria(ListaMemoria);
    //printf("\n");
    
    if(resultado_alocacao == -1)
    {//printf("Erro a alocar memoria no FirstFit\n");
    return;}
    numeroTotalDeNos += numeroDeNos;
    tamanho_nos++;
    numero_de_nos = (int*) realloc(numero_de_nos,tamanho_nos * sizeof(int));
    numero_de_nos[tamanho_nos - 1] =  numeroDeNos;
    numeroDeNos = 0;
    return;
}
void WorstFit(int ID,int num_particoes) //ACABDO WORKING
{
    ListaM *aux = ListaMemoria,*aux2 = NULL;
    int count=0,max_count=0;

    resultado_alocacao = 0;

    if((n_particoes_por_ocupar == 0) || (num_particoes > n_particoes_por_ocupar))
    {
        //printf("Não foi possivel usar o WorstFit para o processo #%d\n",ID);
        numeroDeNos = 0;
        countNEGADOS++;
        return;
    }
    while(aux != NULL)
    {
        if(aux->ID_Process == -2)
        {
            aux2 = aux;
            while(aux != NULL)
            {
                if(aux->ID_Process == -2)
                {
                    count++;
                    aux = aux->nseg;
                }
                else break;
            }
            if(max_count < count && count > num_particoes)
            {
                max_count = count; 
                inicio = aux2;
            }
            numeroDeNos += count;
            count = 0;
        }
        else
        {
        numeroDeNos++;
        aux = aux->nseg;
        }
    }
    if(aux == NULL && max_count < num_particoes)
    {
        //printf("Não há um bloco seguido para alocar este processo\n");
        countNEGADOS++;
        numeroDeNos=0;
        return;
    }
    resultado_alocacao = alocate_mem(ID,num_particoes);
    if(resultado_alocacao == -1)
    {//printf("Erro a alocar memoria no WorstFit\n");
    return;}
    
    numeroTotalDeNos += numeroDeNos;
    tamanho_nos++;
    numero_de_nos = (int*) realloc(numero_de_nos,tamanho_nos * sizeof(int));
    numero_de_nos[tamanho_nos - 1] =  numeroDeNos;
    numeroDeNos = 0;
    return;
}
void NextFit(int ID,int num_particoes)//ACABADO WORKING
{
    int count=0,volta=0;

    resultado_alocacao =0;
    if(nextFitPointer == NULL)
        nextFitPointer = ListaMemoria;

    if((n_particoes_por_ocupar == 0) || (num_particoes > n_particoes_por_ocupar))
    {
        //printf("Não é possivel usar o NextFit para o processo #%d\n",ID);
        numeroDeNos = 0;
        countNEGADOS++;
        return;
    }
    
    while(nextFitPointer != NULL)
    {
        numeroDeNos++;
        if(nextFitPointer->ID_Process == -2)
        {
            count++;
            if(count == 1)
                inicio = nextFitPointer;
            if(count == num_particoes)
            {   
                if(nextFitPointer->nseg == NULL)
                {
                    //printf("lmao\n");
                    nextFitPointer = ListaMemoria;
                }
                break;
            }
        }
        else if(volta == 1 && nextFitPointer->nseg == NULL)
        {
            nextFitPointer = ListaMemoria;
            volta = 2;
            //printf("Não foi possivel usar NextFit no processo #%d",ID);
            countNEGADOS++;
            break;
        }    
        else if(nextFitPointer->nseg == NULL && volta == 0)
        {
            nextFitPointer = ListaMemoria;
            volta=1;
        }
        else
        {
            nextFitPointer = nextFitPointer->nseg;
        }
    }
    if(inicio != NULL && volta !=2)
    {
        resultado_alocacao = alocate_mem(ID,num_particoes);
        if(resultado_alocacao == -1)
        {//printf("Erro na alocaçao de memória no NextFit\n");
        return;}
    }
    else
    {
        //printf("Não há um bloco seguido para alocar o processo #%d\n",ID);
        countNEGADOS++;
        numeroDeNos=0;
        return;
    }
    
    numeroTotalDeNos += numeroDeNos;
    tamanho_nos++;
    numero_de_nos = (int*) realloc(numero_de_nos,tamanho_nos * sizeof(int));
    numero_de_nos[tamanho_nos - 1] =  numeroDeNos;
    numeroDeNos = 0;
    return;

}
void BestFit(int ID,int num_particoes) // ACABADO WORKING
{
    ListaM *aux = ListaMemoria,*aux2 = NULL;
    int count=0,min_count=MemoriaTotal,flag=0;

    resultado_alocacao = 0;

    if((n_particoes_por_ocupar == 0) || (num_particoes > n_particoes_por_ocupar))
    {
        //printf("Não foi possivel usar o BestFit para o processo #%d\n",ID);
        numeroDeNos = 0;
        countNEGADOS++;
        return;
    }
    while(aux != NULL)
    {
        if(aux->ID_Process == -2)
        {
            aux2 = aux;
            while(aux != NULL)
            {
                if(aux->ID_Process == -2)
                {
                    count++;
                    aux = aux->nseg;
                }
                else break;
            }
            if((num_particoes <= count) && flag == 0)
            {
                min_count = count; 
                inicio = aux2;
            }
            if((count < min_count) && flag == 1 && (count >= num_particoes))
            {
                min_count = count;
                inicio = aux2;
            }
            numeroDeNos += count;
            count = 0;
            flag = 1;
        }
        else
        {
        numeroDeNos++;
        aux = aux->nseg;
        }
    }
    if(min_count >= num_particoes && inicio != NULL)
    {
        resultado_alocacao = alocate_mem(ID,num_particoes);
        if(resultado_alocacao == -1)
            {
                //printf("Erro na alocação de memória no BestFit\n");
                resultado_alocacao = 0;
                return;
            }
    }
    else
    {
       //printf("Não há um bloco seguido  para alocar o processo #%d\n",ID);
        countNEGADOS++;
        return;
    }
    numeroTotalDeNos += numeroDeNos;
    tamanho_nos++;
    numero_de_nos = (int*) realloc(numero_de_nos,tamanho_nos * sizeof(int));
    numero_de_nos[tamanho_nos - 1] =  numeroDeNos;
    numeroDeNos=0;
    return;
}
void estatisticasFit()
{
    int soma_fragmentos= 0,soma_nos = 0;
    tamanho_fragmento++;
    fragmentos_externos = (int*) realloc(fragmentos_externos,tamanho_fragmento * sizeof(int));
    fragmentos_externos[tamanho_fragmento - 1] = fragment_count();
    for(int i = 0; i < tamanho_fragmento; i++)
        soma_fragmentos += fragmentos_externos[i];

    for(int i = 0; i< tamanho_nos; i++)
        soma_nos += numero_de_nos[i];

    percentagem_vezes = (((double) countNEGADOS / countTOTAL ) * 100);
    fragmentos_medio = ((double) soma_fragmentos / tamanho_fragmento);
    nos_medio = ((double) soma_nos / tamanho_nos);
}
