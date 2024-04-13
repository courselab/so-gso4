/*
 *    SPDX-FileCopyrightText: 2001 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "debug.h"

enum action_t {CYPHER, DECYPHER};

void cypher(FILE *fpin, int action, const char* key, FILE *fpout)
{
  int c;
  unsigned int length, shift, count=0;
  
  length = strlen (key);
  
  while ( (c = fgetc (fpin)) != EOF)
    {
      
      shift = key[count];
      count = (count + 1) % length;
      
      if (action != CYPHER)
	shift = -shift;
	  
      c = (c+shift) % 256;
      
      fputc (c, fpout);
    };

  if (fpin != stdin)
    fclose (fpin);
  if (fpout != stdout)
    fclose (fpout);
  
}

