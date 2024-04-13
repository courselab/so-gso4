dnl    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
dnl   
dnl    SPDX-License-Identifier: GPL-3.0-or-later
dnl
dnl    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
dnl
dnl    >> Usage hint:
dnl
dnl       If you're looking for a file such as README or Makefile, then this one 
dnl       you are reading now is probably not the file you are interested in. This
dnl       and other files named with suffix '.m4' are source files used by SYSeg
dnl       to create the actual documentation files, scripts and other items they
dnl       refer to. If you can't find a corresponding file without the '.m4' name
dnl       extension in this same directory, then chances are that you have missed
dnl       the build instructions in the README file at the top of SYSeg's source
dnl       tree (yep, it's called README for a reason).

include(docm4.m4)

 MbrCmd - Mater Book Record Command interpreter
 ==============================================

 MbrCmd is a very simple command line interpreter that fits entirely within
 the 512-byte master boot record of a USB stick. It is meant to be loaded
 through legacy BIOS boot method and execute in real mode on any x86 platform.

 The program interprets a few built in commands.

 Challenge
 ------------------------------

 1) Build and execute MbrCmd under a x86 emulator (e.g. qemu).

 2) Copy the program to a USB stick and boot it with BIOS legacy mode.

 3) Implement a new command exploring other BIOS services.

    E.g. use BIOS interrupt service 0x12 to report the computer's memory size,
    of 0x1a to read the system time, or any other cool feature you can
    think of.

    Consult reference (1) by the end of this file and related online sources.

    Tip: you may get rid of built in commands implemented in the example
    code if you run out of space for your own commands. Rememer, your binary
    must fit in 512 bytes (not kbytes!) --- actually, 510 bytes if we count
    out the boot signature (so, hands on bit twiddling.) 

DOCM4_CLOSING_WORDS

 References
 ----------

 (1) BIOS interrupt calls, https://en.wikipedia.org/wiki/BIOS_interrupt_call


 ===============================================================================

 APPENDIX
 

DOCM4_EXERCISE_DIRECTIONS

DOCM4_BINTOOLS_DOC

 
