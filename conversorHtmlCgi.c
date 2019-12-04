/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
Prof. Marcelo Luiz Drumond Lanza
EEL 270 - Computacao II - Turma 2019/2
 
$Author$
$Date$
$Log$
*/

#include        <stdio.h>
#include        <string.h>
#include        <stdlib.h>

#define DVFM_EVS_NUMBER_ARGUMENTS			    		2

#define DVFM_EVS_OK								    	0
#define DVFM_EVS_NUMBER_ARGUMENTS_INVALID			    1
#define DVFM_EVS_FILE_INVALID           			    2
#define DVFM_EVS_FILE_WRITE           			        3
#define ERRO_LENDO_ARQUIVO					4
int
main(int argc,char *argv[ ])
{
    FILE *leitura;
    FILE *escrita;
    char filenamewrite[50];
    char buffer [500];
    /*char copia [500];*/
    char *beginPrintf = "printf(\"";
    char *endPrintf = "\\n\");\n";
    /*unsigned indiceBuffer;
    unsigned indiceCopia;*/

    filenamewrite[0] = '\0';

    if (argc != DVFM_EVS_NUMBER_ARGUMENTS) 
	{
        printf("Erro: Numero de argumento invalido");
		printf("use: %s <filename>\n", argv[0]);
		exit(DVFM_EVS_NUMBER_ARGUMENTS_INVALID);
	}

    if(!(leitura = fopen(argv[1], "r")))
    {
        printf("Erro: Arquivo nao existe\n");
        printf("use: %s <filename>\n", argv[0]);
        exit(DVFM_EVS_FILE_INVALID);
    }

    strcpy(filenamewrite, argv[1]);
    strcat(filenamewrite, "-cgi.c");

    if(!(escrita = fopen( filenamewrite, "w")))
    {
        printf("Erro: Arquivo nao existe\n");
        printf("use: %s <filename>\n", argv[0]);
        fclose(leitura);
        exit(DVFM_EVS_FILE_WRITE);
    }

    while(fgets(buffer, 500, leitura))
    {
	buffer [strlen(buffer) -1] = '\0';
	
	/*indiceCopia = 0;
	for(indiceBuffer = 0; indiceBuffer < strlen(buffer); indiceBuffer++)
	{printf("oi\n");

		if(buffer [indiceBuffer] == '"' || buffer [indiceBuffer] == '\\')
		{printf("%i\n", indiceBuffer);
			copia[indiceCopia] = '\\';
			indiceCopia++;

			copia[indiceCopia] = buffer [indiceBuffer];
		}
		else
		{
			copia[indiceCopia] = buffer [indiceBuffer];
		}

		indiceBuffer++;
	}*/
	
        fprintf( escrita,"%s",beginPrintf);
        fprintf( escrita, "%s", buffer);
        fprintf( escrita,"%s",endPrintf);
    }

    if (ferror (leitura))
    {
	printf ("Erro lendo arquivo\n");
	fclose (leitura);
	fclose (escrita);
	exit (ERRO_LENDO_ARQUIVO);
    }

    fclose(leitura);
    fclose(escrita);

    return DVFM_EVS_OK;
}


/* $RCSfile$ */
