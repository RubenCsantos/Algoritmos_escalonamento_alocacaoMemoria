#include "biblioteca.h"

ListaM *criarNodoLista()
{
    ListaM *listAux = ( ListaM* ) malloc(sizeof(ListaM));    

    listAux->ID_Process = -2;
    listAux->nseg = NULL;

    return listAux;
}
void pushListaMemoria(ListaM **Lista,ListaM *no)
{
    no->nseg = (*Lista);
    (*Lista) = no;  
}
void printListaMemoria(ListaM *La)
{
    ListaM *L = La;
    while(L != NULL)
    {
        printf("%d",L->ID_Process);
        L = L->nseg;
    }
}
int fragment_count() //ACABADO
{
    ListaM *aux_Lista = ListaMemoria;
    int count=0,size=0;
    
    while(aux_Lista != NULL)
    {
        if(aux_Lista->nseg != NULL)
        {
            if(aux_Lista->ID_Process == -2)
            {
                size++;
                aux_Lista = aux_Lista->nseg;
            }
            else
            {
                if(size <= 2 && size > 0)
                {
                    count++;
                    size = 0;
                    aux_Lista = aux_Lista->nseg;
                }
                else aux_Lista = aux_Lista ->nseg;
            }
        }
        else aux_Lista = aux_Lista->nseg;
    }
    return count;
}
int alocate_mem(int process_id,int num_units) // DUVIDA
{
    int aaaaaaaa = num_units;
    while(num_units != 0)
    {
        inicio->ID_Process = process_id;
        inicio = inicio->nseg;
        num_units--;
    }
    n_particoes_por_ocupar -= aaaaaaaa;
    return numeroDeNos;
}
int deallocate_mem(int process_id) // done
{
    ListaM *aux=ListaMemoria;
    int existe=0,count=0;
    while(aux != NULL)
    {
        if(aux->ID_Process == process_id)
        {    
            aux->ID_Process = -2;
            count++;
            existe = 1;
        }
        aux = aux->nseg;
    }
    n_particoes_por_ocupar += count;
    if(existe == 1)
        return 1;
    else return -1;
}