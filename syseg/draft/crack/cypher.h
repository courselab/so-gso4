/*
 *    SPDX-FileCopyrightText: 2001 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

#ifndef CYPHER_H
#define CYPHER_H

void cypher (FILE *fpin, int action, const char* key, FILE *fpout);

enum action_t {CYPHER, DECYPHER};

#endif	/* CYPHER_H */
