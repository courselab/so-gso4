/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

/*  Linker script for MBR. */

OUTPUT_FORMAT(binary)		/* Output flat binary (no structure) */
SECTIONS
{
        . = 0x7C00;		/* Line counter is now 0x7c00. */
        .text :
	{
	  *(.text)              /* Copy input section .text to the oputput. */
	  *(.rodata)		/* Copy input section .rodata to the output. */
	  *(.data)		/* Copy input section .data to the output. */
	  *(.bss)		/* Copy input section .bss to the output. */
}	
        . = 0x7c00 + 510;	/* Advance 510 bytes. */
        .signature : 		/* Add a signadure section with this content. */
	{
	    BYTE(0x55)
            BYTE(0xAA)
        }
	__END_STACK__ = 0x7bff;	 /* End of the 64K block. */
}
STARTUP(rt0.o)			 /* Prepend with the start file. */


/* Notes.

   BIOS shall load the program at 0x7c00.
   We position the stack (bottom) just bellow the loaded program.

   Our assemlber outputs an ELF object with several sections: text (executable code),
   .rodata (e.g. inline strings), .bss and .data (global variables). We need to copy
   all them into the executable file. 

   Boot signature 0xaa55 is added at position 511-512.

 */

