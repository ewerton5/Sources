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

#ifndef DVFM_EVS_UML_GET_PENDING_REGISTRATION_REQUESTS_H
#define DVFM_EVS_UML_GET_PENDING_REGISTRATION_REQUESTS_H "@(#)dvfmEvsUmlGetPendingRegistrationRequests.h $Revision$"

/* ===== beginning of file code ===== */

#include	"dvfmEvsUmlTypes.h"
#include	"dvfmEvsUmlErrors.h"

/*
 * dvfmEvsUmlErrorType
 * DvfmEvsUmlGetPendingRegistrationRequests (dvfmEvsUmlConfigurationOptionsType *,
 *                                           dvfmEvsUmlUserDataType **);
 *
 * Arguments:
 * dvfmEvsUmlConfigurationOptionsType * - Configuration options (I)
 * dvfmEvsUmlUserDataType ** - first element in the list containing data about pending requests for the user in question (O)
 *
 * Returned code:
 * 
 * dvfmEvsUmlErrorType - integer that correspond a error
 * 
 * Description:
 * Return a list of all valid requests not met.
 */

dvfmEvsUmlErrorType
DvfmEvsUmlGetPendingRegistrationRequests (dvfmEvsUmlConfigurationOptionsType *,
                                          dvfmEvsUmlUserDataType **);

/* ===== end of file code ====== */

#endif
/* $RCSfile$ */
