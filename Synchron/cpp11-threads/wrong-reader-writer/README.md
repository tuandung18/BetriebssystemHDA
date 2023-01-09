## INTRODUCTION AND WARNING

This package contains a program which is intentionally WRONG!!

This illustrates an INCORRECT (but multithreaded) "solution" to 
the Reader/Writer Problem.  No semaphores are used, so the writers 
create problems which the readers detect.

This is part of the Betriebssystem Praktikum at the ./
Darmstadt University of Applied Sciences.
 
## CONTENTS

You should have received the following files:

  1.  `Makefile`		<-- A Makefile, with comments in German (mostly).
  2.  `database.cpp`
  3.  `database.h`              <-- Source code for the database singleton class
  4.  `reader-writer-threads.cpp`
  5.  `reader-writer-threads.h` <-- Souce code for the reader & writer agents (threads)
  6.  `reader-writer.cpp`       <-- Souce code for "main" (the program itself).
  7.  `stopwatch.h`             <-- Source code for measuring elapsed time. 
                                Note that there is NO `stopwatch.cpp` file!
  8.  `README.md`               <--  This file.
  9.  `inputFile.txt`           <-- Test Input (please make a backup copy!).


## INSTALLATION and EXECUTION

### TL;DR

The program (named `reader-writer`) can be built by using the standard linux/unix utility named `make`. 

In other words, enter `make` on the command line to build the program (or to be sure you have a clean build, enter `make clean` first, and when that is finished, enter `make`).

If you then run the program with no arguments, 
it will tell you what arguments it expects.


### Longer Explanation

Consider the following transcript (lines entered by the user start with $,
lines that do not start with $ are output from the shell).

(If you're unfamiliar with the commands time, head or tail, 
look them up with `man time`, `man head` and `man tail`).


```console

$ make
clang++ -c -g -std=c++11 -Wall -MMD -fmessage-length=0 -o database.o database.cpp
clang++ -c -g -std=c++11 -Wall -MMD -fmessage-length=0 -o reader-writer-threads.o reader-writer-threads.cpp
clang++ -c -g -std=c++11 -Wall -MMD -fmessage-length=0 -o reader-writer.o reader-writer.cpp
clang++ -o reader-writer database.o reader-writer-threads.o  reader-writer.o  -lpthread
touch outputFile.txt

$ ./reader-writer
Usage: ./reader-writer numSeconds numReaders numWriters

$ time ./reader-writer 1 1 1
In ./reader-writer, seconds = 1, writers = 1, readers = 1, ready to go...
Writer 0 starting...
Finished creating all threads...
Reader 0 starting...
READER 0 Finished test 1, result = 1, sleeping 0 seconds 
READER 0 Finished test 2, result = 1, sleeping 0 seconds 
READER 0 Finished test 3, result = 1, sleeping 2 seconds 
WRITER 0 Finished test 1, result = 1, sleeping 1 seconds 
WRITER 0Finished. Returning after 1 tests.
READER 0Finished. Returning after 3 tests.
Database Statistics 
--------------------
 Readers: number of read operations  = 3
          average read time          = 3.5111e-05
 Writers: number of write operations = 1
          average write time         = 0.405417
WARNING: Since time was only 1 seconds, the statistics above mean NOTHING.
Simulation finished! Database is OK!

$ time ./reader-writer 60 90 10 >sampleOutput.txt
./reader-writer 60 90 10 > sampleOutput.txt  129.96s user 216.47s system 555% cpu 1:02.39 total

$ head sampleOutput.txt 
In ./reader-writer, seconds = 60, writers = 10, readers = 90, ready to go...
Writer 0 starting...
Reader 0 starting...
Writer 1 starting...
READER 0 Finished test 1, result = 1, sleeping 0 seconds 
Reader 1 starting...
READER 0 Finished test 2, result = 1, sleeping 0 seconds 
READER 0 Finished test 3, result = 1, sleeping 2 seconds 
READER 1 Finished test 1, result = 1, sleeping 1 seconds 
Writer 2 starting...

$ tail sampleOutput.txt 
READER 88Finished. Returning after 69 tests.
READER 76Finished. Returning after 56 tests.
READER 69Finished. Returning after 58 tests.
Database Statistics 
--------------------
 Readers: number of read operations  = 5336
          average read time          = 0.00653853
 Writers: number of write operations = 388
          average write time         = 0.171359
Simulation finished! Database is NOT OK!!!

```

Now please try the commands yourself - you should get similar, but _not identical_
results. 

Also experiment with different values for `numSeconds`, `numReaders` and `numWriters`.


## CONCLUSION

The program has been tested for with the clang compiler, version 9.0.0, 
and with g++, version 9.2.0 on a 64 bit Linux.  

Update: In 2021 this program has been retested with clang and g++, both at version 11.1.0 (coincidentally (?)).

Updated Update: In 2022 this program has been retested with clang and g++ under macOS.  It still works (as well as it ever did).

Please do not hesitate to contact me if you have questions.

(Prof. Dr. Ronald Moore - FBI - H-DA.DE - <ronald.moore@h-da.de>)
