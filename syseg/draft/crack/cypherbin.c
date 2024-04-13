/*
 *    SPDX-FileCopyrightText: 2001 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

/* This program encrypts a binary file using a polyalphabetical substitution
   cypher inspired on Vigenère method. */


#include <stdio.h>
#include <unistd.h>

#include "debug.h"

#define PROGRAM "cypherbin"
#define VERSION "0.1.0"

char usage[] =
  "\n\n"
  "Usage : " PROGRAM " [options] <file-name>\n\n"
  "            Options \n\n"
  "            -h              this help message\n"
  "            -v              show program version\n"
  "            -k <string>     cypher key\n"
  "            -e              encrypt (cypher)\n"
  "            -d              decrypt (decypher)\n"
  "\n\n"
  ;

enum action_t {CYPHER, DECYPHER};

char dfl_key[] = "ABC";

int cypher(int c, int shift);

int main(int argc, char **argv)
{
  int opt;
  char *key = dfl_key;
  FILE *fpin=NULL, *fpout=NULL;
  int c, shift;
  enum action_t action = CYPHER;
  int count=0, length;
  
  while ((opt = getopt(argc, argv, "hvk:ed")) != -1)
    {
      switch (opt)
        {
        case 'h':
          printf("%s", usage);
          exit (EXIT_SUCCESS);
          break;
        case 'v':
          printf(PROGRAM " " VERSION "\n");
          exit (EXIT_SUCCESS);
          break;
	case 'k':
	  key = optarg;
	  break;
	case 'e':
	  action = CYPHER;
	  break;
	case 'd':
	  action = DECYPHER;
	  break;
	default:
          fprintf (stderr, "%s", usage);
          exit (EXIT_FAILURE);
          break;
        }
    }

  /* Input file.  */
  
  fpin = stdin;
  if (argc > optind)
    {
      fpin = fopen (argv[optind], "r");
      sysfatal (!fpin);
    }
  
  /* Output file. */
  
  fpout = stdout;
  if (argc > optind+1)
    {
      fpout = fopen (argv[optind+1], "w");
      sysfatal (!fpout);
    }
  
  length = strlen (key);
  
  while ( (c = fgetc (fpin)) != EOF)
    {
      
      shift = key[count];
      count = (count + 1) % length;
      
      if (action != CYPHER)
	shift = -shift;
	  
      /* c = (c+shift) % 256; */
      
      c = cypher (c, shift);
      
      fputc (c, fpout);
    };

  if (fpin != stdin)
    fclose (fpin);
  if (fpout != stdout)
    fclose (fpout);
  
  return EXIT_SUCCESS;
  
}

int cypher(int c, int shift)
{
  return (c+shift) % 256;
}
