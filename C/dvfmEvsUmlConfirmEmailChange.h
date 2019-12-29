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

#ifndef DVFM_EVS_UML_CONFIRM_EMAIL_CHANGE_H
#define DVFM_EVS_UML_CONFIRM_EMAIL_CHANGE_H "@(#)dvfmEvsUmlConfirmEmailChange.h $Revision$"

/* ===== beginning of file code ===== */

#include	"dvfmEvsUmlTypes.h"
#include	"dvfmEvsUmlErrors.h"

/*
 * dvfmEvsUmlErrorType
 * DvfmEvsUmlConfirmEmailChange (dvfmEvsUmlConfigurationOptionsType *,
 *                               char *,
 *                               char *);
 *
 * Arguments:
 * dvfmEvsUmlConfigurationOptionsType * - Configuration options (I)
 * char * - user nickname string (I)
 * char * - validation key string (I)
 *
 * Returned code:
 * 
 * dvfmEvsUmlErrorType - integer that correspond a error
 * 
 * Description:
 * Validate an email.
 */

dvfmEvsUmlErrorType
DvfmEvsUmlConfirmEmailChange (dvfmEvsUmlConfigurationOptionsType *,
                              char *,
                              char *);

/* ===== end of file code ====== */

#endif
/* $RCSfile$ */