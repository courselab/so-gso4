/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

/* main.c - Main program. */
 

#include <mbr.h>

int main()
{
  char cmd[BUFFER_MAX_LENGTH];

  /* Clear screen. */
  
  clear();

  /* Main loop. */
  
  while (1)
    {
  
      print (PROMPT);		        /* Show prompt. */

      read (cmd);		        /* Read user command. */

      /* Process user command. */
      
      if (compare(cmd, HELP_CMD))       /* Command help. */
	help();
      else if (compare(cmd, QUIT_CMD))  /* Command quit. */
	quit();
      else
	{
	  print (cmd);		        /* Unkown command. */
	  printnl (NOT_FOUND);
	}
    }
  
  return 0;

}
