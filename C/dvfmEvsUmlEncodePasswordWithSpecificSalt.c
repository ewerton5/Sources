/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
Prof. Marcelo Luiz Drumond Lanza
EEL 270 - Computacao II - Turma 2019/2
 
$Author: ewerton.silles $
$Date: 2019/11/30 04:31:06 $
$Log: dvfmEvsUmlEncodePasswordWithSpecificSalt.c,v $
Revision 1.1  2019/11/30 04:31:06  ewerton.silles
Initial revision

Revision 1.1  2019/11/16 03:48:22  ewerton.silles
Initial revision

*/

#include					<stdio.h>
#include					<stdlib.h>
#include					"dvfmEvsUmlFunctions.h"
#include					"dvfmEvsUmlConst.h"

#define DVFM_EVS_NUMBER_ARGUMENTS					3

#define DVFM_EVS_OK									0
#define DVFM_EVS_NUMBER_ARGUMENTS_INVALID			1
#define DVFM_EVS_PASSWORD_IMCOMPATIBLE				2

int
main(int argc,char *argv[ ]) 
{
    dvfmEvsUmlErrorType dvfmEvsUmlErrorCode;
    char dvfmEvsUmlEncryptedPassword [108];
	if (argc != DVFM_EVS_NUMBER_ARGUMENTS) 
	{
		printf("use: %s <flat_password> <full_salt>\n", argv[0]);
		exit(DVFM_EVS_NUMBER_ARGUMENTS_INVALID);
	}
    dvfmEvsUmlErrorCode = DvfmEvsUmlEncodePasswordWithSpecificSalt(argv[1], argv[2], dvfmEvsUmlEncryptedPassword);
	if (dvfmEvsUmlErrorCode)
    {
        printf("%s\n", DvfmEvsUmlGetCliErrorMessage(dvfmEvsUmlErrorCode, dvfmEvsUmlEnglish));
        exit(DVFM_EVS_OK);
    }
	
    printf("Encrypted password: %s.\n", dvfmEvsUmlEncryptedPassword);
	return DVFM_EVS_OK;
}
/* $RCSfile: dvfmEvsUmlEncodePasswordWithSpecificSalt.c,v $ */
