#include <stdio.h>
#include <string.h>

#define MAX 10000000

int procuraTraco(char comando[])
{
    int i = 0;
    while (comando[i] != '-' && comando[i] != '\0')
    {
        i++;
    }
    return i;
}

char verificaCom(int indice, char comando[])
{
    char letra = comando[indice + 1];
    return letra;
}

void passaCaminho(int indice, char comando[], char caminho[], int* espaco)
{
    int i = 3;
    while (comando[indice + i] != '\0' && comando[indice + i] != '\n')
    {
        caminho[i] = comando[indice + i];
        if (caminho[i] == ' ' && *espaco == -1)
        {
            *espaco = i;
        }
        i++;
        if (caminho[i] == ' ' && *espaco != -1)
        {
            fprintf(stderr, "Error: too many files.\n");
            return;
        }
    }
    caminho[i] = '\0';
}

void montaCaminho(char caminho[], int espaco, char caminho1[], char caminho2[])
{
    memset(caminho1, 0, 256);
    memset(caminho2, 0, 256);

    if (espaco != -1)
    {
        for (int i = 0; i < espaco; i++)
        {
            caminho1[i] = caminho[i];
        }
        caminho1[espaco] = '\0';

        int j = 0;
        for (int i = espaco + 1; caminho[i] != '\0'; i++, j++)
        {
            caminho2[j] = caminho[i];
        }
        caminho2[j] = '\0';
    }
    else
    {
        strcpy(caminho1, caminho);
    }
}

int c(FILE* file) {
	int acc = 0;
	char ch;
	while ((ch = fgetc(file)) != EOF)
	{
		acc++;
	}
	return acc;
}

int l(FILE *file)
{
	int acc = 0;
	char ch;
	while ((ch = fgetc(file)) != EOF)
	{
        	if (ch == '\n')
		{
			acc++;
		}
	}
	return acc;
}

int w(FILE *file)
{
	int acc = 0;
	char ch, prev = ' ';
	while ((ch = fgetc(file)) != EOF)
	{
		if ((ch == ' ' || ch == '\n') && prev != ' ' && prev != '\n')
		{
		acc++;
        	}
	prev = ch;
	}
	return acc;
}

long m(FILE* file, char caminho[])
{
	fclose(file);
	file = fopen(caminho, "rb");
	if(!file)
	{
		fprintf(stderr, "Error: file %s does not exist", caminho);
	}
	fseek(file, 0, SEEK_END);
	long bytes = ftell(file);
	return bytes;
}

void todos(file, caminho)
{
	printf("Caracteres: %d\n", c(file));
	printf("Linhas: %d\n", l(file));
	printf("Palavras: %d\n", w(file));
	printf("Bytes: %ld\n", m(file, caminho1));
	fclose(file);
	
}

int main()
{
	while (1)
	{
		char comando[512];
        	char caminho[256];
        	int espaco = -1;
        	FILE* file;
        	FILE* file2;
        	char caminho1[256];
        	char caminho2[256];
        	char opcao;
		int tipo = 0;    

        	printf(">vwc: ");
        	fgets(comando, sizeof(comando), stdin);
        	printf("\n");

		for(int i = 0; i<sizeof(comando); i++)
		{
			if(comando[i] == 27)
			goto end;
		}
    
        	int indice = 0;

        	passaCaminho(indice, comando, caminho, &espaco);
        	montaCaminho(caminho, espaco, caminho1, caminho2); 

		file = fopen(caminho1, "r");
		file2 = fopen(caminho2, "r");

		if(!file)
		{
			fprintf(stderr, "Error: file %s does not exist", caminho1);
			break;
		}

		if(!file2)
		{
			tipo = 1;
		}

		if (indice == sizeof(comando) / 8)
		{
			todos(file, caminho1);
			if(tipo == 0) todos(file2, caminho2);
			break;
        	}
    
        	opcao = verificaCom(indice, comando);
    
        	switch (opcao)
        	{
			case 'c':
				printf("Caracteres: %d\n", c(file));
				if(tipo == 0)
				{
					printf("Caracteres: %d\n", c(file2));
				}
				break;
			case 'l':
            			printf("Linhas: %d\n", l(file));
				if(tipo == 0)
					{
						printf("Linhas: %d\n", l(file2));
					}
				break;
			case 'w':
            			printf("Palavras: %d\n", w(file));
				if(tipo == 0)
				{
					printf("Palavras: %d\n", w(file2));
				}
				break;
			case 'm':
				printf("Bytes: %ld\n", m(file, caminho1));
				if(tipo == 0)
				{
					printf("Bytes: %ld\n", m(file2, caminho2));
				}
				break;
			case 27:
				break;

			default:
				fprintf(stderr, "Error: Invalid command\n");
				break;
                	

        	}
		fclose(file);
		if(file2) fclose(file2);
	
	}
}
