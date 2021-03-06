/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2019/2
 
 * $Author: ewerton.silles $
 * $Date: 2008/02/01 10:19:06 $
 * $Log: dvfmEvsUmlRejectInvite.c,v $
 * Revision 1.1  2008/02/01 10:19:06  ewerton.silles
 * Initial revision
 *
*/

#include	<stdio.h>
#include	<string.h>
#include	"dvfmEvsUmlRejectInvite.h"
#include	"dvfmEvsUmlGetUsers.h"
#include	"dvfmEvsUmlFunctions.h"

/*
 * dvfmEvsUmlErrorType
 * DvfmEvsUmlRejectInvite (dvfmEvsUmlConfigurationOptionsType *,
 *                         char *,
 *                         char *);
 *
 * Arguments:
 * dvfmEvsUmlConfigurationOptionsType * - Configuration options (I)
 * char * - nickname string (I)
 * char * - temporary password string (I)
 *
 * Returned code:
 * 
 * dvfmEvsUmlErrorType - integer that correspond a error
 * 
 * Description:
 * Remove a invited user from the invited user list.
 */

dvfmEvsUmlErrorType
DvfmEvsUmlRejectInvite (dvfmEvsUmlConfigurationOptionsType *dvfmEvsUmlSettings,
                        char *dvfmEvsUmlNickname,
                        char *dvfmEvsUmlTemporaryPassword)
{
    dvfmEvsUmlErrorType dvfmEvsUmlErrorCode;
    dvfmEvsUmlUserDataType *dvfmEvsUmlUserData = (dvfmEvsUmlUserDataType *) malloc(sizeof(dvfmEvsUmlUserDataType));
    FILE *dvfmEvsUmlRead, *dvfmEvsUmlWrite;
    char dvfmEvsUmlBuffer [DVFM_EVS_UML_MAXIMUM_LENGTH_CONFIG_FILE];
    unsigned dvfmEvsUmlIndex;
    dvfmEvsUmlUserIdentifierType dvfmEvsUmlNumericIndentifier;
	char *dvfmEvsUmlValidation, dvfmEvsUmlNumericIndentifierString [10], dvfmEvsUmlAuxiliary [2] = "0\0";

    if (!dvfmEvsUmlSettings)
        return dvfmEvsUmlFirstEmptyPointer;

    if (!dvfmEvsUmlNickname)
        return dvfmEvsUmlSecondEmptyPointer;

    if (!dvfmEvsUmlTemporaryPassword)
        return dvfmEvsUmlThirdEmptyPointer;

    dvfmEvsUmlErrorCode = DvfmEvsUmlGetUsers (dvfmEvsUmlSettings, &dvfmEvsUmlUserData);
    if (dvfmEvsUmlErrorCode)
        return dvfmEvsUmlSecondaryFunction;

    while (strcmp(dvfmEvsUmlUserData->dvfmEvsUmlNickname, dvfmEvsUmlNickname))
        dvfmEvsUmlUserData = dvfmEvsUmlUserData->dvfmEvsUmlNextUserData;
    
    if (!dvfmEvsUmlUserData)
        return dvfmEvsUmlUserNotFound;

    dvfmEvsUmlErrorCode = DvfmEvsUmlCheckPassword (dvfmEvsUmlUserData->dvfmEvsUmlPassword, dvfmEvsUmlTemporaryPassword);
    if (dvfmEvsUmlErrorCode)
        return dvfmEvsUmlSecondaryFunction;

    if(!(dvfmEvsUmlRead = fopen(dvfmEvsUmlSettings->dvfmEvsUmlUsersDataFilename, "r")))
        return dvfmEvsUmlCantOpenFile;

    if(!(dvfmEvsUmlWrite = fopen(dvfmEvsUmlSettings->dvfmEvsUmlUsersDataFilename, "w")))
        return dvfmEvsUmlCantOpenFile;

    while(fgets(dvfmEvsUmlBuffer, DVFM_EVS_UML_MAXIMUM_LENGTH_CONFIG_FILE, dvfmEvsUmlRead))
    {
        if (!strstr(dvfmEvsUmlBuffer, ":"))
        {
            fclose(dvfmEvsUmlRead);
            fclose(dvfmEvsUmlWrite);
            return dvfmEvsUmlReadError;
        }

        dvfmEvsUmlIndex = strlen(dvfmEvsUmlBuffer) - strlen(strstr(dvfmEvsUmlBuffer, ":"));
        dvfmEvsUmlBuffer [dvfmEvsUmlIndex] = '\0';
        dvfmEvsUmlNumericIndentifier = (dvfmEvsUmlUserIdentifierType) strtoul(dvfmEvsUmlBuffer, &dvfmEvsUmlValidation, 10);
        dvfmEvsUmlBuffer [dvfmEvsUmlIndex] = ':';
        if (dvfmEvsUmlUserData->dvfmEvsUmlNumericIndentifier != dvfmEvsUmlNumericIndentifier)
            fprintf(dvfmEvsUmlWrite, "%s", dvfmEvsUmlBuffer);
    }
    fprintf(dvfmEvsUmlWrite, "%c", EOF);

    if(ferror(dvfmEvsUmlRead))
    {
        fclose(dvfmEvsUmlRead);
        fclose(dvfmEvsUmlWrite);
        return dvfmEvsUmlReadError;
    }

    fclose(dvfmEvsUmlRead);
    fclose(dvfmEvsUmlWrite);

    if(!(dvfmEvsUmlRead = fopen(dvfmEvsUmlSettings->dvfmEvsUmlInvitedUsersDataFilename, "rb")))
        return dvfmEvsUmlCantOpenFile;

    if(!(dvfmEvsUmlWrite = fopen(dvfmEvsUmlSettings->dvfmEvsUmlInvitedUsersDataFilename, "wb")))
        return dvfmEvsUmlCantOpenFile;

    while(fgets(dvfmEvsUmlBuffer, DVFM_EVS_UML_MAXIMUM_LENGTH_CONFIG_FILE, dvfmEvsUmlRead))
    {
        if (!strstr(dvfmEvsUmlBuffer, ":"))
        {
            fclose(dvfmEvsUmlRead);
            fclose(dvfmEvsUmlWrite);
            return dvfmEvsUmlReadError;
        }

        strcpy(dvfmEvsUmlNumericIndentifierString, strstr(dvfmEvsUmlBuffer, ":"));
        dvfmEvsUmlAuxiliary [0] = dvfmEvsUmlNumericIndentifierString[1];
        strcpy(dvfmEvsUmlNumericIndentifierString, strstr(dvfmEvsUmlNumericIndentifierString, dvfmEvsUmlAuxiliary));

        if (!strstr(dvfmEvsUmlNumericIndentifierString, ":"))
        {
            fclose(dvfmEvsUmlRead);
            fclose(dvfmEvsUmlWrite);
            return dvfmEvsUmlReadError;
        }

        dvfmEvsUmlNumericIndentifierString [strlen(dvfmEvsUmlNumericIndentifierString) - strlen(strstr(dvfmEvsUmlNumericIndentifierString, ":"))] = '\0';
        dvfmEvsUmlNumericIndentifier = (dvfmEvsUmlUserIdentifierType) strtoul(dvfmEvsUmlNumericIndentifierString, &dvfmEvsUmlValidation, 10);
        if (dvfmEvsUmlUserData->dvfmEvsUmlNumericIndentifier != dvfmEvsUmlNumericIndentifier)
            fprintf(dvfmEvsUmlWrite, "%s", dvfmEvsUmlBuffer);
    }
    fprintf(dvfmEvsUmlWrite, "%c", EOF);

    if(ferror(dvfmEvsUmlRead))
    {
        fclose(dvfmEvsUmlRead);
        fclose(dvfmEvsUmlWrite);
        return dvfmEvsUmlReadError;
    }

    fclose(dvfmEvsUmlRead);
    fclose(dvfmEvsUmlWrite);
    
    if(!(dvfmEvsUmlWrite = fopen("dvfmEvsUmlMailFile", "w")))
        return dvfmEvsUmlCantOpenFile;

    fprintf(dvfmEvsUmlWrite, "%s\n%s",
                             "You have declined the invitation and your data has been deleted from the system.\n",
                             "If you did not make these changes contact us.\n");
    fclose(dvfmEvsUmlWrite);

    sprintf(dvfmEvsUmlBuffer, "sendmail %s < %s", dvfmEvsUmlUserData->dvfmEvsUmlEmail ,"dvfmEvsUmlMailFile");
    system(dvfmEvsUmlBuffer);

    remove("dvfmEvsUmlMailFile");

    return dvfmEvsUmlOk;
}

/* $RCSfile: dvfmEvsUmlRejectInvite.c,v $ */
