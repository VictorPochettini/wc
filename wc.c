#include <stdio.h>

int procuraTraco(char comando[])
{
	int i = 0;
	while(comando[i] != '-' && comando[i] != '\0')
	{
		i++;
	}
	return i;
}

char verificaCom(int indice, char comando[])
{
	char letra = comando[indice+1];
	return letra;
}

void passaCaminho(int indice, char comando[], char caminho[], int* espaco, int espaco2)
{
	int i = 0;
	while (comando[indice + i] != '\0' && comando[indice + i] != '\n')
	{
		caminho[i] = comando[indice+i];
		if(caminho[i] == ' ' && *espaco == -1)
		{
			*espaco = i;
		}
		i++;

		if(caminho[i] == ' ' && *espaco != -1)
		{
			*espaco2 = i;
		}
		i++;
		if(caminho[i] == ' ' && *espaco2 != -1)
		{
			fprintf(stderr, "Error: No file informed.\n");
		}
	}

	caminho[i] = '\0';
}

int main()
{

	char comando[512];
	char caminho[256];
	int espaco = -1;
	int* espaco2 = espaco + 1;
	
	printf(">vwc: ");
	fgets(comando, sizeof(comando), stdin);
	printf("\n");
	
	int indice = procuraTraco(comando);
	
	if(indice == sizeof(comando)/8)
	{
		//Fazer ele executar todas as instruções
		return 0;
	}

	passaCaminho(indice, comando, caminho, espaco, espaco2);

	

	opcao = verificaCom(indice, comando);

	switch(opcao)
	{
		case 'c':
			//Número de Bytes
		case 'l':
			//Número de Linhas
		case 'w':
			//Número de Palavras
		case 'm':
			//Número de Caracteres
	}	

	return 0;
}
