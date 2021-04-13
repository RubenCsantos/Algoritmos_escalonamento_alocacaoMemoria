#include "biblioteca.h"

void ficheiro_memoria(FILE *f1)
{
	char linha[15];
	char *args[2];

	while(fgets(linha,15,f1)!= NULL)
	{
		
		parse(linha,args);
		if(strcmp(args[0],"Z") == 0 && QUALSOLICITACAO != 2)
				continue;
		if(linha[0] == 'X' && QUALSOLICITACAO != 2)
				continue;
		memoria[contador_array_ficheiro_memoria].ins = args[0][0];
		if(strcmp (args[0], "L") == 0)
		{
			int len=strlen(args[1]);

			if (args[1][len - 1] == '\n')
			args[1][len - 1] = '\0';

			memoria[contador_array_ficheiro_memoria].n = 0;
			strcpy(memoria[contador_array_ficheiro_memoria].nome,  args[1]);
			contador_array_ficheiro_memoria++;
			continue;
		}

		if(strcmp (args[0], "T") == 0)
		{
			memoria[contador_array_ficheiro_memoria].n = 0;
			strcpy(memoria[contador_array_ficheiro_memoria].nome,"NULL");
			contador_array_ficheiro_memoria++;
			return;
		}
		memoria[contador_array_ficheiro_memoria].n = atoi(args[1]); //string para inteiro
		strcpy(memoria[contador_array_ficheiro_memoria].nome,"NULL");

		contador_array_ficheiro_memoria++;
	}

}