/*
 *    SPDX-FileCopyrightText: 2001 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

#include <utils.h>

void __attribute__((naked)) init()
{
  echo (" Stage 2: second stage loaded sucessuflly!" NL);

  system_halt();
}

