/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2019/2
 
 * $Author$
 * $Date$
 * $Log$
*/

#ifndef DVFM_EVS_UML_CHANGE_USER_EMAIL_H
#define DVFM_EVS_UML_CHANGE_USER_EMAIL_H "@(#)dvfmEvsUmlChangeUserEmail.h $Revision$"

/* ===== beginning of file code ===== */

#include	"dvfmEvsUmlTypes.h"
#include	"dvfmEvsUmlErrors.h"

/*
 * dvfmEvsUmlErrorType
 * DvfmEvsUmlChangeUserEmail (dvfmEvsUmlConfigurationOptionsType *,
 *                            char *,
 *                            char *,
 *                            char *,
 *                            char *);
 *
 * Arguments:
 * dvfmEvsUmlConfigurationOptionsType * - Configuration options (I)
 * char * - administrator nickname string (I)
 * char * - user nickname string (I)
 * char * - new email string (I)
 * char * - confirm email string (I)
 *
 * Returned code:
 * 
 * dvfmEvsUmlErrorType - integer that correspond a error
 * 
 * Description:
 * Changes a user email.
 */

dvfmEvsUmlErrorType
DvfmEvsUmlChangeUserEmail (dvfmEvsUmlConfigurationOptionsType *,
                          char *,
                          char *,
                          char *,
                          char *);

/* ===== end of file code ====== */

#endif
/* $RCSfile$ */
