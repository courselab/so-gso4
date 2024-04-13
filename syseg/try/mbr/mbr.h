/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

#ifndef MBR_H
#define MBR_H

/* 
 *  Core functions.
 */

/* Print the null-terminated buffer on standard output. */

void __attribute((naked, fastcall)) print (const char *buffer);

/* Print the null-terminated string buffer on standard output, and a newline.*/

extern char nl[];

#define printnl(str) do{print(str); print (nl);}while(0)

/* Clear the screen. */

void __attribute__((naked, fastcall)) clear (void);

/* Read standard input into fixed-length buffer (no check). */

void __attribute__((naked, fastcall)) read (char *buffer);

/* Compare to strings up to BUFFER_MAX_LENGTH-1. */

#define BUFFER_MAX_LENGTH 5

int __attribute__((fastcall, naked)) compare (char *s1, char *s2);

/* 
 * Commands.
 */

/* Prints a help message. */

#define HELP_CMD "help"

void __attribute__((naked)) help (void);

/* Quit. */

#define QUIT_CMD "quit"

#define quit() printnl("Sorry...")

#define PROMPT ">"

#define NOT_FOUND "command not found"

#endif	/* MBR_H */
