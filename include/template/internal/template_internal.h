#ifndef TEMPLATE_INTERNAL_H
#define	TEMPLATE_INTERNAL_H



#  include <sys/param.h>
#  include <sys/mman.h>
#  include <sys/syscall.h>
#include <sys/uio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>



#include "template/template.h"


/*
 * There are circular dependencies that cannot be broken without
 * substantial performance degradation.  In order to reduce the effect on
 * visual code flow, read the header files in multiple passes, with one of the
 * following cpp variables defined during each pass:
 *
 *   TEMPLATE_H_TYPES   : Preprocessor-defined constants and psuedo-opaque data
 *                        types.
 *   TEMPLATE_H_STRUCTS : Data structures.
 *   TEMPLATE_H_EXTERNS : Extern data declarations and function prototypes.
 *   TEMPLATE_H_INLINES : Inline functions.
 */
/******************************************************************************/
#define	TEMPLATE_H_TYPES

#include "template/internal/xx.h"


#undef TEMPLATE_H_TYPES
/******************************************************************************/
#define TEMPLATE_H_STRUCTS

#include "template/internal/xx.h"


#undef TEMPLATE_H_STRUCTS 
/******************************************************************************/
#define TEMPLATE_H_EXTERNS

#include "template/internal/xx.h"


#undef  TEMPLATE_H_EXTERNS 
/******************************************************************************/
#define TEMPLATE_H_INLINES

#include "template/internal/xx.h"


#undef template_H_INLINES 
/******************************************************************************/
#endif /* TEMPLATE_INTERNAL_H */