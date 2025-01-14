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
	return (comando[i] == '-') ? i : -1;
}

char verificaCom(int indice, char comando[])
{
	return comando[indice + 1];
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

int c(FILE* file)
{
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

long m(FILE* file, const char caminho[])
{
	fclose(file);
	file = fopen(caminho, "rb");
	if (!file)
	{
		fprintf(stderr, "Error: file %s does not exist\n", caminho);
		return -1;
	}
	fseek(file, 0, SEEK_END);
	long bytes = ftell(file);
	fclose(file);
	return bytes;
}

void todos(FILE* file, const char caminho[])
{
	printf("Caracteres: %d\n", c(file));
	printf("Linhas: %d\n", l(file));
	printf("Palavras: %d\n", w(file));
	long bytes = m(file, caminho);
	if (bytes != -1)
	{
		printf("Bytes: %ld\n", bytes);
	}
}

int main()
{
	while (1)
	{
		char comando[512];
		char caminho[256];
		int espaco = -1;
		FILE* file = NULL;
		FILE* file2 = NULL;
		char caminho1[256];
		char caminho2[256];

		printf(">vwc: ");
		if (!fgets(comando, sizeof(comando), stdin))
		{
			break;
		}

		if (strchr(comando, 27))
		{
			break;
		}

		int tracoPos = procuraTraco(comando);
		if (tracoPos == -1)
		{
			// No commands, just file paths; execute all commands
			sscanf(comando, "%s %s", caminho1, caminho2);
			file = fopen(caminho1, "r");
			if (!file)
			{
				fprintf(stderr, "Error: file %s does not exist\n", caminho1);
				continue;
			}
			todos(file, caminho1);
			fclose(file);

			if (strlen(caminho2) > 0)
			{
				file2 = fopen(caminho2, "r");
				if (!file2)
				{
					fprintf(stderr, "Error: file %s does not exist\n", caminho2);
					continue;
				}
				todos(file2, caminho2);
				fclose(file2);
			}
			continue;
		}

		passaCaminho(tracoPos, comando, caminho, &espaco);
		if (strchr(caminho + espaco + 1, ' ') != NULL)
		{
			fprintf(stderr, "Error: too many files.\n");
			continue;
		}
		montaCaminho(caminho, espaco, caminho1, caminho2);

		file = fopen(caminho1, "r");
		if (!file)
		{
			fprintf(stderr, "Error: file %s does not exist\n", caminho1);
			continue;
		}

		char opcao = verificaCom(tracoPos, comando);
		switch (opcao)
		{
			case 'c':
				printf("Caracteres: %d\n", c(file));
				break;
			case 'l':
				printf("Linhas: %d\n", l(file));
				break;
			case 'w':
				printf("Palavras: %d\n", w(file));
				break;
			case 'm':
				printf("Bytes: %ld\n", m(file, caminho1));
				break;
			default:
				fprintf(stderr, "Error: Invalid command\n");
				break;
		}

		fclose(file);
	}
	return 0;
}
