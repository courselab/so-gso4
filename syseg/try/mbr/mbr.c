/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

#include <mbr.h>

/* A string consisting of the CRLF sequence.
   Used by the function-like macro printnl. */

char nl[] = {'\r', '\n', 0x0};


/* Prints the null-terminated string buffer.  */

void __attribute__((fastcall, naked))  print (const char* buffer)
{
__asm__ volatile
(                                                                          
 "        mov   $0x0e, %%ah           ;" /* Video BIOS service: teletype mode */
 "        mov   $0x0, %%si            ;" 
 "loop%=:                             ;"                                    
 "        mov   (%%bx, %%si), %%al    ;"
 "        cmp   $0x0, %%al            ;" /* Repeat until end of string (0x0). */
 "        je    end%=                 ;"                                    
 "        int   $0x10                 ;" /* Call video BIOS service.          */
 "        add   $0x1, %%si            ;"                                    
 "        jmp   loop%=                ;"                                    
 "end%=:                              ;"
 "        ret                         ;" /* Return from this function.         */

:                        
: "b" (buffer)      /* Var. buffer put in bx, referenced as str .*/
: "ax", "cx", "si"        /* Additional clobbered registers         .  */
 );
}

/* Clear the screen and set video colors. */

void __attribute__((naked, fastcall)) clear (void)
{

  __asm__ volatile
    (
     " mov $0x0600, %%ax                 ;" /* Video BIOS service: Scroll up. */
     " mov $0x07, %%bh                   ;" /* Attribute (back/foreground.    */
     " mov $0x0, %%cx                    ;" /* Upper-left corner.             */
     " mov $0x184f, %%dx                 ;" /* Upper-right corner.            */
     " int $0x10                         ;" /* Call video BIOS service.       */
     " ret                                " /* Return from function. */
     ::: "ax", "bx", "cx", "dx"		    /* Additional clobbered registers.*/
     );

}

/* Read string from terminal into buffer. 

   Note: this function does not check for buffer overrun.
         Buffer size is BUFFER_MAX_LENGTH.

	 Good opportunity for contributing.

*/

void __attribute__((fastcall, naked)) read (char *buffer)
{
  
    __asm__ volatile
    (     
     
     "   mov $0x0, %%si               ;" /* Iteration index for (%bx, %si).  */
     "loop%=:                         ;"
     "   movw $0X0, %%ax              ;" /* Choose blocking read operation.  */
     "   int $0x16                    ;" /* Call BIOS keyboard read service. */
     "   movb %%al, %%es:(%%bx, %%si) ;" /* Fill in buffer pointed by %bx.   */
     "   inc %%si                     ;"
     "   cmp $0xd, %%al               ;" /* Reiterate if not ascii 13 (CR)   */

     "   mov   $0x0e, %%ah            ;" /* Echo character on the terminal.  */
     "   int $0x10                    ;"
     
     "   jne loop%=                   ;"

     " mov $0x0e, %%ah                ;" /* Echo a newline.                  */
     " mov $0x0a, %%al                ;"
     "   int $0x10                    ;"
     
     "   movb $0x0, -1(%%bx, %%si)    ;" /* Add buffer a string delimiter.   */
     "   ret                           " /* Return from function             */
     
     :
     : "b" (buffer) 	          /* Ask gcc to store buffer in %bx          */
     : "ax",  "cx", "si" 	  /* Aditional clobbered registers.          */
     );

  
}

/* Output a help(-less) message. */

void __attribute__((naked)) help (void)
{
  printnl ("I wish... (too small a program for anything else).");

  __asm__ ("ret");   	   /* Naked functions lack return. */

}

/* Compare two strings up to position BUFFER_MAX_LENGTH-1. */

int __attribute__((fastcall, naked)) compare (char *s1, char *s2)
{
  __asm__ volatile
    (
      "    mov %[len], %%cx   ;"
      "    mov $0x1, %%ax     ;"
      "    cld                ;"
      "    repe  cmpsb        ;"
      "    jecxz  equal       ;"             
      "    mov $0x0, %%ax     ;"
      "equal:                 ;"
      "    ret                ;"
      :
      : [len] "n" (BUFFER_MAX_LENGTH-1), /* [len] is a constant.   */
	"S" (s1),		/* Ask gcc to store s1 in %si      */
	"D" (s2)		/* Ask gcc to store s2 is %di      */
      : "ax", "cx", "dx"	/* Additional clobbered registers. */
     );

  return 0;                /* Bogus return to fulfill funtion's prototype.*/
}

/* Notes.
   
   We declared all functions with attributes 'naked' and 'fastcall'.

   The 'naked' attribute prevents gcc from outputing asm code beyound
   what is strictly necessary for the particular example to execute.
   In this case, the otherwise extra code would be relevant if we 
   wanted our functions to exchange data using the stack; its omission
   leave us with the burden of taking care of stack integrity ourselves.
   Since we don't use the stack ourselves, we can play with the bare 
   minimal for simplicity.

   One side effect of the 'naked' attribute is that the compiler does not
   output a 'ret' instruction by the end of the function. We have to 
   manually include it via inline asm when applicable.

   Note, for instance, that we've done that in the function void help().

   Note also that in function compare(), we needed to issue 'ret' from within
   the inline asm (since the function is naked), but had to add a C 'return'
   statement as well, so that the preprocessor does not complain based on
   the function prototype. This last return is read by the preprocessor
   but is not converted to a 'ret' instruction by the compiler.

   The other attribute tells the compiler to use the fastcall convention
   to pass parameter among functions. With that, the first argument is
   passed in register %cx and the second in %dx. Further parameters would
   be passed via stack --- and since we opted for naked function, that
   would mean extra work if we had more than three arguments.

   Note that, with fastcall, when we needed the function argument to be 
   copied into another register, say %bx, we could manually do it in asm

       mov %cx, %bx

   or else use GNU extended asm to accomplish this, using the input operands.
   For instance, that's what we did in read() by writing

      : "c" (buffer)

   
   Values are returned by fastcall functions in register %ax.

 */
