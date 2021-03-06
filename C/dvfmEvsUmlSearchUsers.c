/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2019/2
 
 * $Author: ewerton.silles $
 * $Date: 2008/02/01 10:19:06 $
 * $Log: dvfmEvsUmlSearchUsers.c,v $
 * Revision 1.1  2008/02/01 10:19:06  ewerton.silles
 * Initial revision
 *
*/

#include	<string.h>
#include	"dvfmEvsUmlSearchUsers.h"
#include	"dvfmEvsUmlGetUsers.h"

/*
 * dvfmEvsUmlErrorType
 * DvfmEvsUmlSearchUsers (dvfmEvsUmlConfigurationOptionsType *,
 *                        char *,
 *                        char *,
 *                        dvfmEvsUmlProfileType,
 *                        dvfmEvsUmlUserDataType **);
 *
 * Arguments:
 * dvfmEvsUmlConfigurationOptionsType * - Configuration options (I)
 * char * - full name or part of the name string (I)
 * char * - full email or part of the email string (I)
 * dvfmEvsUmlProfileType - profile (I)
 * dvfmEvsUmlUserDataType ** - first element in the list containing data about all users (O)
 *
 * Returned code:
 * 
 * dvfmEvsUmlErrorType - integer that correspond a error
 * 
 * Description:
 * Search and return a list of all users.
 */

dvfmEvsUmlErrorType
DvfmEvsUmlSearchUsers (dvfmEvsUmlConfigurationOptionsType *dvfmEvsUmlSettings,
                       char *dvfmEvsUmlName,
                       char *dvfmEvsUmlEmail,
                       dvfmEvsUmlProfileType dvfmEvsUmlProfile,
                       dvfmEvsUmlUserDataType **dvfmEvsUmlUserData)
{
    dvfmEvsUmlErrorType dvfmEvsUmlErrorCode;
    dvfmEvsUmlUserDataType *dvfmEvsUmlAllUsersData = (dvfmEvsUmlUserDataType *) malloc(sizeof(dvfmEvsUmlUserDataType));
    dvfmEvsUmlUserDataType *dvfmEvsUmlFilteredUserData = (dvfmEvsUmlUserDataType *) malloc(sizeof(dvfmEvsUmlUserDataType));
    dvfmEvsUmlBool dvfmEvsUmlInFilter;

    if (!dvfmEvsUmlSettings)
        return dvfmEvsUmlFirstEmptyPointer;

    if (!dvfmEvsUmlUserData)
        return dvfmEvsUmlFifthEmptyPointer;

    dvfmEvsUmlErrorCode = DvfmEvsUmlGetUsers (dvfmEvsUmlSettings, &dvfmEvsUmlAllUsersData);
    if (dvfmEvsUmlErrorCode)
        return dvfmEvsUmlSecondaryFunction;

    dvfmEvsUmlFilteredUserData->dvfmEvsUmlPreviousUserData = NULL;

    while (dvfmEvsUmlAllUsersData)
    {
        dvfmEvsUmlInFilter = dvfmEvsUmlTrue;
        
        if (dvfmEvsUmlName)
            if (!strstr(dvfmEvsUmlAllUsersData->dvfmEvsUmlFullName, dvfmEvsUmlName))
                dvfmEvsUmlInFilter = dvfmEvsUmlFalse;
        if (dvfmEvsUmlEmail)
            if (!strstr(dvfmEvsUmlAllUsersData->dvfmEvsUmlEmail, dvfmEvsUmlEmail))
                dvfmEvsUmlInFilter = dvfmEvsUmlFalse;
        if (dvfmEvsUmlProfile && (dvfmEvsUmlAllUsersData->dvfmEvsUmlProfile != dvfmEvsUmlProfile))
                dvfmEvsUmlInFilter = dvfmEvsUmlFalse;
        if(dvfmEvsUmlInFilter)
        {
            dvfmEvsUmlFilteredUserData = dvfmEvsUmlAllUsersData;
            dvfmEvsUmlFilteredUserData->dvfmEvsUmlNextUserData = (dvfmEvsUmlUserDataType *) malloc(sizeof(dvfmEvsUmlUserDataType));
            dvfmEvsUmlFilteredUserData->dvfmEvsUmlNextUserData->dvfmEvsUmlPreviousUserData = dvfmEvsUmlFilteredUserData;
            dvfmEvsUmlFilteredUserData = dvfmEvsUmlFilteredUserData->dvfmEvsUmlNextUserData;
        }
        dvfmEvsUmlAllUsersData = dvfmEvsUmlAllUsersData->dvfmEvsUmlNextUserData;
    }

    dvfmEvsUmlFilteredUserData = dvfmEvsUmlFilteredUserData->dvfmEvsUmlPreviousUserData;
    if (dvfmEvsUmlFilteredUserData)
        dvfmEvsUmlFilteredUserData->dvfmEvsUmlNextUserData = NULL;

    if (dvfmEvsUmlFilteredUserData)
        return dvfmEvsUmlEmptyList;

    while (dvfmEvsUmlFilteredUserData->dvfmEvsUmlPreviousUserData)
        dvfmEvsUmlFilteredUserData = dvfmEvsUmlFilteredUserData->dvfmEvsUmlPreviousUserData;
    
    *dvfmEvsUmlUserData = dvfmEvsUmlFilteredUserData;
    
    return dvfmEvsUmlOk;
}

/* $RCSfile: dvfmEvsUmlSearchUsers.c,v $ */
