## INTRODUCTION

This package contains an implementation of Dijkstra's solution to the
Dining Philosophers problem, programmed in C++11.

It is intended to illustrate multithreaded programming.  It can also be used to
test your Linux (etc.) installation to make sure multithreaded programming is 
possible (that the pthreads library is installed, that your compiler can handle 
C++11, etc.).

This is part of the Betriebssystem Praktikum at the Darmstadt University of 
Applied Sciences (Die Hochschule Darmstadt, Fachbereich Informatik).
 
## CONTENTS

You should have received the following files:

(1)	Makefile						
        -- A Makefile, with comments in German (mostly).

(2)	philosophers-dijkstra-utils.h

(3)	philosophers-dijkstra-utils.cpp	
        -- Contains utilities such as put_fork and 
			get_fork and the philosopher thread

(4)	philosophers-dijkstra.c			
        -- Contains main()

(6)	This file -- "README".

(7) stopwatch.h
         -- Source code for measuring elapsed time. 
            Note that there is NO stopwatch.cpp file!

## INSTALLATION and EXECUTION

    $ make clean
    $ make
    $ ./philosophers-dijkstra 60

The program will run for 1 minute (i.e. 60 seconds).  
If you get impatient, just kill it with control-c (like any other process).

The program has been tested with the clang compiler, version 9.0.0, 
and with g++, version 9.2.0 on a 64 bit Linux.  

Update: In 2021 it was retested with g++ and clang, both version 11.1.0 (by some strange coincidence (?)).

Updated Update: In 2022 it was tested with g++ and clang under macOS.  It still works.

Prof. Dr. Ronald Moore 
<email:ronald.moore@h-da.de>
