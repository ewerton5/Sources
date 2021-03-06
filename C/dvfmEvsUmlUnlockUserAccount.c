/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2019/2
 
 * $Author: ewerton.silles $
 * $Date: 2008/02/01 10:19:06 $
 * $Log: dvfmEvsUmlUnlockUserAccount.c,v $
 * Revision 1.1  2008/02/01 10:19:06  ewerton.silles
 * Initial revision
 *
*/

#include    <stdio.h>
#include    <string.h>
#include	"dvfmEvsUmlUnlockUserAccount.h"
#include	"dvfmEvsUmlGetUsers.h"

/*
 * dvfmEvsUmlErrorType
 * DvfmEvsUmlUnlockUserAccount (dvfmEvsUmlConfigurationOptionsType *,
 *                              char *,
 *                              char *);
 *
 * Arguments:
 * dvfmEvsUmlConfigurationOptionsType * - Configuration options (I)
 * char * - administrator nickname string (I)
 * char * - blocked user nickname string (I)
 *
 * Returned code:
 * 
 * dvfmEvsUmlErrorType - integer that correspond a error
 * 
 * Description:
 * Unlocks a user account.
 */

dvfmEvsUmlErrorType
DvfmEvsUmlUnlockUserAccount (dvfmEvsUmlConfigurationOptionsType *dvfmEvsUmlSettings,
                             char *dvfmEvsUmlAdminNickname,
                             char *dvfmEvsUmlBlockedUserNickname)
{
    dvfmEvsUmlUserDataType *dvfmEvsUmlUserData = (dvfmEvsUmlUserDataType *) malloc(sizeof(dvfmEvsUmlUserDataType));
    dvfmEvsUmlBool dvfmEvsUmlAdmin = dvfmEvsUmlFalse;
    dvfmEvsUmlUserIdentifierType dvfmEvsUmlNumericIndentifier, dvfmEvsUmlNumericIndentifierFirstNumber;
    FILE *dvfmEvsUmlRead, *dvfmEvsUmlWrite;
    unsigned dvfmEvsUmlIndex1, dvfmEvsUmlIndex2, dvfmEvsUmlCounter;
    char dvfmEvsUmlBuffer [DVFM_EVS_UML_MAXIMUM_LENGTH_CONFIG_FILE],
         dvfmEvsUmlAuxiliaryBuffer [DVFM_EVS_UML_MAXIMUM_LENGTH_CONFIG_FILE],
         *dvfmEvsUmlValidation, dvfmEvsUmlNumericIndentifierString [10],
         dvfmEvsUmlNickname [DVFM_EVS_UML_MAX_SIZE_NICKNAME];

    if (!dvfmEvsUmlSettings)
        return dvfmEvsUmlFirstEmptyPointer;

    if (!dvfmEvsUmlBlockedUserNickname)
        return dvfmEvsUmlThirdEmptyPointer;
    
    if (dvfmEvsUmlAdminNickname)
        if(strlen(dvfmEvsUmlAdminNickname))
            dvfmEvsUmlAdmin = dvfmEvsUmlTrue;

    if (dvfmEvsUmlAdmin)
    {
        if (DvfmEvsUmlGetUsers (dvfmEvsUmlSettings, &dvfmEvsUmlUserData))
            return dvfmEvsUmlSecondaryFunction;

        while (strcmp(dvfmEvsUmlUserData->dvfmEvsUmlNickname, dvfmEvsUmlAdminNickname))
            dvfmEvsUmlUserData = dvfmEvsUmlUserData->dvfmEvsUmlNextUserData;
        
        if (!dvfmEvsUmlUserData)
            return dvfmEvsUmlUserNotFound;

        if (dvfmEvsUmlUserData->dvfmEvsUmlProfile != dvfmEvsUmlAdministrator)
            return dvfmEvsUmlUserIsNotAdministrator;

        while (dvfmEvsUmlUserData->dvfmEvsUmlPreviousUserData)
            dvfmEvsUmlUserData = dvfmEvsUmlUserData->dvfmEvsUmlPreviousUserData;

        while (strcmp(dvfmEvsUmlUserData->dvfmEvsUmlNickname, dvfmEvsUmlBlockedUserNickname))
            dvfmEvsUmlUserData = dvfmEvsUmlUserData->dvfmEvsUmlNextUserData;
        
        if (!dvfmEvsUmlUserData)
            return dvfmEvsUmlUserNotFound;

        if(!(dvfmEvsUmlRead = fopen(dvfmEvsUmlSettings->dvfmEvsUmlLockedUsersDataFilename, "rb")))
            return dvfmEvsUmlCantOpenFile;
 
        if(!(dvfmEvsUmlWrite = fopen(dvfmEvsUmlSettings->dvfmEvsUmlLockedUsersDataFilename, "wb")))
            return dvfmEvsUmlCantOpenFile;

        while(fgets(dvfmEvsUmlBuffer, DVFM_EVS_UML_MAXIMUM_LENGTH_CONFIG_FILE, dvfmEvsUmlRead))
        {
            if (!strstr(dvfmEvsUmlAuxiliaryBuffer, ":"))
            {
                fclose(dvfmEvsUmlRead);
                fclose(dvfmEvsUmlWrite);
                return dvfmEvsUmlReadError;
            }

            dvfmEvsUmlIndex1 = strlen(dvfmEvsUmlBuffer) - strlen(strstr(dvfmEvsUmlBuffer, ":"));
            dvfmEvsUmlBuffer [dvfmEvsUmlIndex1] = '\0';
            dvfmEvsUmlNumericIndentifier = (dvfmEvsUmlUserIdentifierType) strtoul(dvfmEvsUmlBuffer, &dvfmEvsUmlValidation, 10);
            dvfmEvsUmlBuffer [dvfmEvsUmlIndex1] = ':';
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

            dvfmEvsUmlIndex1 = strlen(dvfmEvsUmlBuffer) - strlen(strstr(dvfmEvsUmlBuffer, ":"));
            dvfmEvsUmlBuffer [dvfmEvsUmlIndex1] = '\0';
            if (dvfmEvsUmlUserData->dvfmEvsUmlNumericIndentifier == (dvfmEvsUmlUserIdentifierType) strtoul(dvfmEvsUmlBuffer, &dvfmEvsUmlValidation, 10))
            {
                dvfmEvsUmlBuffer [dvfmEvsUmlIndex1] = ';';

                if (!strstr(dvfmEvsUmlBuffer, ":"))
                {
                    fclose(dvfmEvsUmlRead);
                    fclose(dvfmEvsUmlWrite);
                    return dvfmEvsUmlReadError;
                }

                dvfmEvsUmlIndex2 = strlen(dvfmEvsUmlBuffer) - strlen(strstr(dvfmEvsUmlBuffer, ":"));
                dvfmEvsUmlBuffer [dvfmEvsUmlIndex2] = ';';

                if (!strstr(dvfmEvsUmlBuffer, ":"))
                {
                    fclose(dvfmEvsUmlRead);
                    fclose(dvfmEvsUmlWrite);
                    return dvfmEvsUmlReadError;
                }
                
                strcpy(dvfmEvsUmlAuxiliaryBuffer, strstr(dvfmEvsUmlBuffer, ":"));
                dvfmEvsUmlBuffer [dvfmEvsUmlIndex1] = ':';
                dvfmEvsUmlBuffer [dvfmEvsUmlIndex2] = ':';
                dvfmEvsUmlBuffer [dvfmEvsUmlIndex2 + 1] = '\0';
                strcat(dvfmEvsUmlBuffer, dvfmEvsUmlUserData->dvfmEvsUmlPassword);
                strcat(dvfmEvsUmlBuffer, dvfmEvsUmlAuxiliaryBuffer);
            }
            dvfmEvsUmlBuffer [dvfmEvsUmlIndex1] = ':';
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
                                "Sua conta foi desbloqueada, você já pode fazer log in normalmente.\n",
                                "Your account has been unlocked, you can already log in normally.\n");
        fclose(dvfmEvsUmlWrite);

        sprintf(dvfmEvsUmlBuffer, "sendmail %s < %s", dvfmEvsUmlUserData->dvfmEvsUmlEmail ,"dvfmEvsUmlMailFile");
        system(dvfmEvsUmlBuffer);

        remove("dvfmEvsUmlMailFile");
    }
    else
    {
        if (DvfmEvsUmlGetUsers (dvfmEvsUmlSettings, &dvfmEvsUmlUserData))
            return dvfmEvsUmlSecondaryFunction;

        while (strcmp(dvfmEvsUmlUserData->dvfmEvsUmlNickname, dvfmEvsUmlBlockedUserNickname))
            dvfmEvsUmlUserData = dvfmEvsUmlUserData->dvfmEvsUmlNextUserData;
        
        if (!dvfmEvsUmlUserData)
            return dvfmEvsUmlUserNotFound;

        strcpy(dvfmEvsUmlNickname, dvfmEvsUmlUserData->dvfmEvsUmlNickname);
        dvfmEvsUmlNumericIndentifier = dvfmEvsUmlUserData->dvfmEvsUmlNumericIndentifier;

        for(dvfmEvsUmlIndex1 = 0; dvfmEvsUmlNumericIndentifier;dvfmEvsUmlIndex1++)
        {
            dvfmEvsUmlNumericIndentifierFirstNumber = dvfmEvsUmlNumericIndentifier;
            for (dvfmEvsUmlCounter = 0; dvfmEvsUmlNumericIndentifierFirstNumber > 10; dvfmEvsUmlCounter++)
                dvfmEvsUmlNumericIndentifierFirstNumber = (dvfmEvsUmlUserIdentifierType) dvfmEvsUmlNumericIndentifierFirstNumber/10;
            dvfmEvsUmlNumericIndentifierString [dvfmEvsUmlIndex1] = (char) dvfmEvsUmlNumericIndentifierFirstNumber + '0';
            dvfmEvsUmlNumericIndentifier = dvfmEvsUmlNumericIndentifier - dvfmEvsUmlNumericIndentifierFirstNumber*pow(10, dvfmEvsUmlCounter);
        }
        dvfmEvsUmlNumericIndentifierString [dvfmEvsUmlIndex1] = '\0';

        if(!(dvfmEvsUmlWrite = fopen(dvfmEvsUmlSettings->dvfmEvsUmlUnlockingUsersDataFilename, "a")))
            return dvfmEvsUmlCantOpenFile;

        strcpy(dvfmEvsUmlBuffer, "86400:");
        strcat(dvfmEvsUmlBuffer, dvfmEvsUmlNumericIndentifierString);
        strcpy(dvfmEvsUmlBuffer, "\n");

        fprintf(dvfmEvsUmlWrite, "%s", dvfmEvsUmlBuffer);

        fclose(dvfmEvsUmlWrite);

        while (dvfmEvsUmlUserData->dvfmEvsUmlPreviousUserData)
            dvfmEvsUmlUserData = dvfmEvsUmlUserData->dvfmEvsUmlPreviousUserData;

        if(!(dvfmEvsUmlWrite = fopen("dvfmEvsUmlMailFile", "w")))
            return dvfmEvsUmlCantOpenFile;

        fprintf(dvfmEvsUmlWrite, "O usuário %s solicitou desbloqueio de conta.\n", dvfmEvsUmlNickname);

        fclose(dvfmEvsUmlWrite);

        while (dvfmEvsUmlUserData)
        {
            if (dvfmEvsUmlUserData->dvfmEvsUmlProfile == dvfmEvsUmlAdministrator)
            {
                sprintf(dvfmEvsUmlBuffer, "sendmail %s < %s", dvfmEvsUmlUserData->dvfmEvsUmlEmail ,"dvfmEvsUmlMailFile");
                system(dvfmEvsUmlBuffer);
            }
            dvfmEvsUmlUserData = dvfmEvsUmlUserData->dvfmEvsUmlNextUserData;
        }
        remove("dvfmEvsUmlMailFile");
    }
    return dvfmEvsUmlOk;
}

/* $RCSfile: dvfmEvsUmlUnlockUserAccount.c,v $ */
