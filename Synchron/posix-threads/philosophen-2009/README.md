## INTRODUCTION

This package contains an implementation of Dijkstra's solution to the
Dining Philosophers problem, programmed in C using Posix Threads and semaphores.

It is intended to illustrate multithreaded programming.  It can also be used to
test your Linux (etc.) installation to make sure multithreaded programming is 
possible (that the pthreads library is installed, etc.).

This is part of the Betriebssystem Praktikum at the 
Darmstadt University of Applied Sciences.
 
## CONTENTS

You should have received the following files:

1.	`Makefile`						<-- A Makefile, with comments in German (mostly).
1. `time-killer.h`
1. `randomness.h`
1.	`philosophers-dijkstra-utils.h`
1. `time-killer.c`					<-- Functions for measuring time and for wasting time (i.e. sleeping).
1. `philosophers-dijkstra-utils.c`	<-- Contains utilities such as `put_fork` and ``get_fork` and the ``philosopher` thread
1. `philosophers-dijkstra.c`		<-- Contains `main()*
1. This file - `README.md`;


## INSTALLATION and EXECUTION

    $ make clean
    $ make
    $ ./philosophers-dijkstra

The program has been tested for 64 bit C++ compilers and Linux operating systems.

The program will run until killed.  Use ^C (i.e. Ctl-C i.e. Strg-C) to kill the program!!!

(Prof. Dr. Ronald Moore - FBI - H-DA.DE)
