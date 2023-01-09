#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include "randomness.h"
#include "reader-writer-utils.h"

const int maxThreads = 1024;  // Arbitrary. Change, if you like. Just a sanity check.

/********************************************* * main entry point *********************************************/
int main(int argc, char *argv[])
{

    setup_randoms(); // see random.h

    if ( argc != 4 ) {
        printf("Usage: %s numSeconds numReaders numWriters\n", argv[0] );
        exit( 1 );
    }

    numSeconds = atoi( argv[1] );
    numReaders = atoi( argv[2] );
    numWriters = atoi( argv[3] );

    printf("In %s, seconds = %d, writers = %d, readers = %d, ready to go...\n",
           argv[0], numSeconds, numWriters, numReaders );

    assert( (0 < numSeconds) && (numSeconds < (60*60*24)) ); // max 1 day
    assert( (0 <= numReaders) && (numReaders < maxThreads) );
    assert( (0 <= numWriters) && (numWriters < maxThreads) );

    pthread_t rThread[ numReaders ];
    pthread_t wThread[ numWriters ];

    // Create reader AND writer threads.

    // Note: We don't use two separate for loops
    // (one for readers and one for writers)
    // so as not to give either class a (major) head start
    // (this is new in 2021, by the way).
    // Trivial note: <math.h> has a max function for floats,
    // but not ints (as far as I can quickly tell).
    long int r, w;
    r = w = 0;

    while ((r < numReaders) || (w < numWriters)) {
        if ( w < numWriters ) {
            // printf("Creating writer thread %ld\n", t );
            long int ret = pthread_create( &wThread[w], NULL, writer, (void *)w );
            if (ret) {
                printf("ERROR; return code from pthread_create() is %ld\n", ret);
                exit(-1);
            }; // endif ret not 0
            ++w;
        };
        if ( r < numReaders ) {
            // printf("Creating reader thread %d\n", t );
            long int ret = pthread_create( &rThread[r], NULL, reader, (void *)r );
            if (ret) {
                printf("ERROR; return code from pthread_create() is %ld\n", ret);
                exit(-1);
            }; // end if ret not 0
            ++r;
        };
    }; // end while (r < numReaders) || (w < numWriters)
    printf( "Finished creating all threads...\n" );

    long int numReads, numWrites, numTests;
    numWrites = numReads = numTests = 0;

    // Wait for all reader threads
    for ( r = 0; r < numReaders; r++) {
        long int ret = pthread_join(rThread[r], (void **)&numTests );
        if (ret) {
            printf("ERROR return code from pthread_join( reader %ld ) is %ld\n",
                   r, ret);
            exit(-1);
        }; // else, if OK...
        numReads += numTests;
    };
    // printf( "Finished waiting for finished readers...\n" );

    // Wait for all writer threads
    for ( w = 0; w < numWriters; w++) {
        long int ret = pthread_join(wThread[w], (void **)&numTests);
        if (ret) {
            printf("ERROR return code from pthread_join( writer %ld ) is %ld\n",
                   w, ret);
            exit(-1);
        }; // else, if OK...
        numWrites += numTests;
    }

    printf( "Final Result from %s: %ld read events, %ld write events.\n",
            argv[0], numReads, numWrites );
    if ( numSeconds < 60)
        printf ("WARNING: Since numSeconds = %d < 1 minutes, these statistics mean NOTHING!\n", numSeconds );
    printf( "Final Status - Everything %s\n",
            ( everything_ok ? "OK." : "NOT OK!" ) );

    return( 0 );
}

