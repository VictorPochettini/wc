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
    int i = 2;
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
	if(file == NULL)
	{
		fprintf(stderr, "Error: file %s does not exist", caminho);
	}
	fseek(file, 0, SEEK_END);
	long bytes = ftell(file);
	return bytes;
}

int main()
{
    while (1)
    {
        char comando[512];
        char caminho[256];
        int espaco = -1;
        int linhas = 1;
		int linhas2 = 1;
		int pal = 1;
		int pal2 = 1;
		int car = 1;
		int car2 = 1;
		int bytes = 1;
		int bytes2 = 1;
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
			break;
		}
    
        int indice = procuraTraco(comando);

        passaCaminho(indice, comando, caminho, &espaco);
        montaCaminho(caminho, espaco, caminho1, caminho2); 

		file = fopen(caminho1, "r");
		file2 = fopen(caminho2, "r");

		if(file == NULL)
		{
			fprintf(stderr, "Error: file %s does not exist", caminho1);
		}

		if(file2 == NULL)
		{
			tipo = 1;
		}

		if (indice == sizeof(comando) / 8)
        {
			//Caracteres
			car = c(file);
    		printf("Caracteres: %d\n", car);
				if(tipo == 0)
				{
					linhas2 = c(file2);
					printf("Linhas: %d\n", car2);
				}
			//Linhas	
			linhas = l(file);
            printf("Linhas: %d\n", linhas);
			if(tipo == 0)
				{
					linhas2 = l(file2);
					printf("Linhas: %d\n", linhas2);
				}
			//Palavras
			pal = w(file);
            printf("Palavras: %d\n", pal);
			if(tipo == 0)
			{
				pal2 = w(file2);
				printf("Palavras: %d\n", pal2);
			}
			//Bytes
			bytes = m(file, caminho1);
			printf("Bytes: %ld\n", bytes);
			if(tipo == 0)
			{
				bytes2 = m(file2, caminho2);
				printf("Bytes: %ld\n", bytes2);
			}
			break;
        }
    
        opcao = verificaCom(indice, comando);
    
        switch (opcao)
        {
			case 'c':
				car = c(file);
                printf("Caracteres: %d\n", car);
				if(tipo == 0)
				{
					car2 = c(file2);
					printf("Caracteres: %d\n", car2);
				}
				break;
			case 'l':
            	linhas = l(file);
            	printf("Linhas: %d\n", linhas);
				if(tipo == 0)
					{
						linhas2 = l(file2);
						printf("Linhas: %d\n", linhas2);
					}
				break;
			case 'w':
				pal = w(file);
            	printf("Palavras: %d\n", pal);
				if(tipo == 0)
				{
					pal2 = w(file2);
					printf("Palavras: %d\n", pal2);
				}
				break;
                	
			case 'm':
				bytes = m(file, caminho1);
				printf("Bytes: %ld\n", bytes);
				if(tipo == 0)
				{
					bytes2 = m(file2, caminho2);
					printf("Bytes: %ld\n", bytes2);
				}
				break;
			case 27:
				break;

			default:
				fprintf(stderr, "Error: Invalid command\n");
				break;
                	

        }
		if(file != NULL)
		{
			fclose(file);
		}
		if(file2 != NULL)
		{
			fclose(file2);
		}
    }
    return 0;
}
