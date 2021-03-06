/*
  Universidade Federal do Rio de Janeiro
  Escola Politecnica
  Departamento de Eletronica e de Computacao
  Prof. Marcelo Luiz Drumond Lanza
  EEL 270 - Computacao II - Turma 2019/2
 
  $Author: ewerton.silles $
  $Date: 2008/02/01 10:19:06 $
  $Log: dvfmEvsUmlShowCliHelp.h,v $
  Revision 1.1  2008/02/01 10:19:06  ewerton.silles
  Initial revision
 
*/

#include	"dvfmEvsUmlTypes.h"

#ifndef DVFM_EVS_UML_SHOW_CLI_HELP
#define DVFM_EVS_UML_SHOW_CLI_HELP "@(#)dvfmEvsUmlShowCliHelp.h $Revision: 1.1 $"

/* ===== beginning of file code ===== */

/*
 * void
 * DvfmEvsUmlShowCliHelp (dvfmEvsUmlConfigurationOptionsType *,
 *                        dvfmEvsUmlLanguageType);
 *
 *
 * Arguments:
 * dvfmEvsUmlConfigurationOptionsType * - the address of a local variable of type dvfmEvsUmlConfigurationOptionsType (I)
 * dvfmEvsUmlLanguageType - name of the configuration file (I)
 * 
 * Returned code:
 * 
 * void
 * 
 * Description:
 * This function shows help in the CLI environment.
 */

void
DvfmEvsUmlShowCliHelp (dvfmEvsUmlConfigurationOptionsType *,
                       dvfmEvsUmlLanguageType);

/* ===== end of file code ====== */

#endif
/* $RCSfile: dvfmEvsUmlShowCliHelp.h,v $ */