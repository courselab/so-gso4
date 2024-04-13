/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

/* rt0.c - Startup file for MbrCmd. */

/* This symbol is defined in the linker script. */

extern void __END_STACK__;

/* This is our program's entry point. */

void __attribute__((naked)) _start()
{
  __asm__ volatile
    (

     /* BIOS is not guaranteed to leave us at segment zero.
	We therefore do it manually. */
     
     "        xorw %%ax, %%ax                ;" 
     "        movw %%ax, %%ds                ;" /* Zero data segment.    */
     "        movw %%ax, %%es                ;" /* Zero extra segment.   */
     "        movw %%ax, %%fs                ;" /* Zero extra segment 2. */
     "        movw %%ax, %%gs                ;" /* Zero extra segment 3. */
     "        movw %%ax, %%ss                ;" /* Zero stack segment.   */


     /* Configure the stack pointer. */
     
     "        mov $__END_STACK__, %%sp     ;" /* Setup stack */

     /* Call main. */

     "        call main                     ;" /* Call main */
     " loop%=:                              ;" 
     "        hlt                           ;" /* Halt. */
     "        jmp loop%=                    "
     
     :::
     );
}

/* Notes. */
