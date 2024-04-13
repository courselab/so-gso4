/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

extern void __END_STACK__;	/* Defined in the linder script. */

/* This is our program's entry point. */

void __attribute__((naked)) _start()
{
  __asm__ 
    (

     /* BIOS is not guaranteed to initialize all segemnt registers.
	We therefore do it manually. */
     
     "        cli                          \n" /* Disable interrupts.  */
     "        ljmp $0x0,$init0             \n" /* Zero code segment.   */
     "init0:                               \n" 
     "        xorw %ax, %ax                \n" 
     "        movw %ax, %ds                \n" /* Zero data segment.    */
     "        movw %ax, %es                \n" /* Zero extra segment.   */
     "        movw %ax, %fs                \n" /* Zero extra segment 2. */
     "        movw %ax, %gs                \n" /* Zero extra segment 3. */
     "        movw %ax, %ss                \n" /* Zero stack segment 4. */
     "        mov $__END_STACK__, %sp      \n" /* Setup stack.          */
     "        sti                          \n" /* Eenable interrupts.   */

     /* Call main. */

     "        call main                    \n" /* Call main */
     " halt:                               \n" /* Safeguard. */
     "        hlt                          \n" /* Halt. */
     "        jmp halt                     \n"
     
     );
}

/* Notes.

   Our rt0 file is not C with inline asm.

 */
