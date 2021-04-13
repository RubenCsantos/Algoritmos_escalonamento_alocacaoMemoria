#include "biblioteca.h"

/*
    parse . particiona o comando Unix (armazenado em buf) em argumentos
*/

 void parse (char *buf, char **args)
{
    int i=0;

    char delim[] = " ";

    char *ptr = strtok(buf, delim);

    while(ptr != NULL)
    {

        args[i] = ptr;
        i++;
        ptr = strtok(NULL, delim);
    }

    if(i==3)
    {
      args[2][strlen(args[2])-2]=0;
    }
    if(i==2)
    {
      args[1][strlen(args[1])-2]=0;
    }
}

char *parsePRG(char *string)
{
  char delim[] = ".";

  return strtok(string, delim);
}


