## INTRODUCTION AND WARNING

This package contains a program which is intentionally WRONG!!

This illustrates an INCORRECT (but multithreaded) "solution" to 
the Reader/Writer Problem.  No semaphores are used, so the writers 
create problems which the readers detect.

This is part of the Betriebssystem Praktikum at the 
Darmstadt University of Applied Sciences.
 
## CONTENTS

You should have received the following files:

  1. `Makefile`				 <-- A Makefile, with comments in German (mostly)
  2.  `randomness.c`         <-- source code for random numbers
  3. `randomness.h`         
  4. `reader-writer-utils.c` <-- source code for reader & writer threads & database read & write utilities
                                
  5. `reader-writer-utils.h`
  6. `time-killer.c`         <-- source code for measuring time, and for wasting time

  7. `time-killer.h`
  8.  `reader-writer.c`      <-- source code for `main()`
  9.  `README-md`            <-- This file
  10.  `inputFile.txt`       <-- Test Input (consider making a backup copy).


## INSTALLATION and EXECUTION

### TL;DR

Use `make` to build the program (or `make clean` and then `make`).

Run the program with no arguments and it will tell you what arguments it expects.

### Longer Explanation

Consider the following transcript (lines entered by the user start with $, lines that do not start with $ are output from the shell).

Afterwards, try the commands yourself - you should get similar, but _not identical_results!

```console
$ make clean

$ make
clang -c -g -Wall -fmessage-length=0  -o randomness.o randomness.c
clang -c -g -Wall -fmessage-length=0  -o reader-writer.o reader-writer.c
clang -c -g -Wall -fmessage-length=0  -o reader-writer-utils.o reader-writer-utils.c
clang -c -g -Wall -fmessage-length=0  -o time-killer.o time-killer.c
clang -o reader-writer randomness.o reader-writer.o reader-writer-utils.o time-killer.o -lpthread
touch outputFile.txt

$ ./reader-writer
Usage: ./reader-writer numSeconds numReaders numWriters

$ ./reader-writer 1 1 1
In ./reader-writer, seconds = 1, writers = 1, readers = 1, ready to go...
Writer 0 starting...
Finished creating all threads...
Reader 0 starting ...
READER 0: Finished test 1, sleeping 1 seconds.
WRITER 0: Finished test 1, sleeping 2 seconds.
READER 0: Finished. Returning 1 tests.
WRITER 0: Finished. Returning 1 tests.
Final Result from ./reader-writer: 1 read events, 1 write events.
WARNING: Since numSeconds = 1 < 1 minutes, these statistics mean NOTHING!
Final Status - Everything OK.

$ time ./reader-writer 60 90 10 >sampleOutput.txt
./reader-writer 60 90 10 > sampleOutput.txt  80.62s user 7.21s system 141% cpu 1:02.09 total

$ head sampleOutput.txt 
In ./reader-writer, seconds = 60, writers = 10, readers = 90, ready to go...
Writer 0 starting...
Writer 2 starting...
Reader 2 starting ...
Reader 0 starting ...
Reader 3 starting ...
Writer 4 starting...
READER 3: Finished test 1, sleeping 2 seconds.
READER 0: Finished test 1, sleeping 1 seconds.
READER 2: Finished test 1, sleeping 0 seconds.

$ tail sampleOutput.txt 
READER 72: Finished. Returning 61 tests.
READER 12: Finished. Returning 66 tests.
READER 3: Finished. Returning 50 tests.
READER 52: Finished. Returning 60 tests.
READER 17: Finished. Returning 57 tests.
WRITER 1: Finished. Returning 61 tests.
READER 50: Finished. Returning 53 tests.
READER 76: Finished. Returning 56 tests.
Final Result from ./reader-writer: 5388 read events, 586 write events.
Final Status - Everything NOT OK!

```


## CONCLUSION

Please do not hesitate to contact me if you have questions.

(Prof. Dr. Ronald Moore - FBI - H-DA.DE)
