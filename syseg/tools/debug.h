/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

/* debug.h - Debugging facilities. */
 

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define sysfatal(exp) do{if(exp) {fprintf(stderr, "%s : %d : %s\n", __FILE__, __LINE__, strerror(errno)); exit(EXIT_FAILURE);}}while(0)

#define usage(str) fprintf (stderr, str)
#define argcheck(exp, str) do{if (exp) {usage(str); exit (EXIT_FAILURE);}}while(0)

#endif	/* DEBUG_H */
