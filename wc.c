#include <stdio.h>

int procuraTraco(char comando[])
{
	int i = 0;
	while(comando[i] != '-' || comando[i] != '\0')
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

char passaCaminho(int indice, char comando[])
{
	char caminho[256];
	int i = 3;
	do
	{
		caminho[i] = comando[indice+i];
		i++;
	}while(comando[indice+i] != '\0');

	return caminho[256];
}

int main()
{

	char comando[512];
	
	printf(">vwc: ");
	fgets(comando, sizeof(comando), stdin);
	printf("\n");
	
	int indice = procuraTraco(comando[]);
	
	if(indice == sizeof(comando)/8)
	{
		//Fazer ele executar todas as instruções
		return 0;
	}

	char caminho[256] = passaCaminho(indice, comando);
	

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
