#include <stdio.h>
#define MAX 10000000

int procuraTraco(char comando[])
{
    int i = 0;
    while (comando[i] != '-' && comando[i] != '\0')
    {
        i++;
        if (comando[i] == 27)
        {
            return 27;
        }
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


int l(FILE* file)
{
    char a[MAX];
    int acc = 1;
    
    while (fgets(a, MAX, file))
    {
        acc++;
    }
    
    return acc;
}

int main()
{
    while (1)
    {
        char comando[512];
        char caminho[256];
        int espaco = -1;
        int linhas = 1;
        FILE* file;
        FILE* file2;
        char caminho1[256];
        char caminho2[256];
        char opcao;
    
        printf(">vwc: ");
        fgets(comando, sizeof(comando), stdin);
        printf("\n");
    
        int indice = procuraTraco(comando);
    
        if (indice == sizeof(comando) / 8)
        {
            return 0;
        }
    
        passaCaminho(indice, comando, caminho, &espaco);
        montaCaminho(caminho, espaco, caminho1, caminho2); 

	file = fopen(caminho1, "r");
	file2 = fopen(caminho2, "r");
    
        opcao = verificaCom(indice, comando);
    
        switch (opcao)
        {
            case 'c':
                break;
            case 'l':
                linhas = l(file);
                printf("Linhas: %d\n", linhas);
                break;
            case 'w':
                break;
            case 'm':
                break;
        }
    }
    return 0;
}
