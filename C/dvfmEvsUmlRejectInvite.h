/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2019/2
 
 * $Author: ewerton.silles $
 * $Date: 2008/02/01 10:19:06 $
 * $Log: dvfmEvsUmlRejectInvite.h,v $
 * Revision 1.1  2008/02/01 10:19:06  ewerton.silles
 * Initial revision
 *
*/

#ifndef DVFM_EVS_UML_REJECT_INVITE_H
#define DVFM_EVS_UML_REJECT_INVITE_H "@(#)dvfmEvsUmlRejectInvite.h $Revision: 1.1 $"

/* ===== beginning of file code ===== */

#include	"dvfmEvsUmlTypes.h"
#include	"dvfmEvsUmlErrors.h"

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
DvfmEvsUmlRejectInvite (dvfmEvsUmlConfigurationOptionsType *,
                        char *,
                        char *);

/* ===== end of file code ====== */

#endif
/* $RCSfile: dvfmEvsUmlRejectInvite.h,v $ */
