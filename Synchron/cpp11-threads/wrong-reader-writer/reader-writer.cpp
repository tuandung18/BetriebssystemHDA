#include <iostream>		// for std::cout, cin, etc.
#include <thread>		// for std::thread
#include <cassert>		// for assert()
#include <cstdlib>		// for atoi()
#include <vector>       // for std::vector

#include "database.h"
#include "reader-writer-threads.h"

const int maxThreads = 1024; // increase if you want, meant (only) as sanity check.

/********************************************* * main entry point *********************************************/
int main(int argc, char *argv[])
{
    if ( argc != 4 ) {
        std::cerr << "Usage: "
                  << argv[0]
                  << " numSeconds numReaders numWriters" << std::endl;
        return( -1 );
    }

    int numSeconds = atoi( argv[1] );
    int numReaders = atoi( argv[2] );
    int numWriters = atoi( argv[3] );

    std::cout << "In " << argv[0]
              << ", seconds = " << numSeconds
              << ", writers = " << numWriters
              << ", readers = " << numReaders
              << ", ready to go..." << std::endl;

    assert( (0 < numSeconds) && (numSeconds < (60*60*24)) ); // max 1 day
    assert( (0 <= numReaders) && (numReaders < maxThreads) );
    assert( (0 <= numWriters) && (numWriters < maxThreads) );

    std::vector< std::thread > rThread( numReaders );
    std::vector< std::thread > wThread( numWriters );


    // Create reader AND writer threads.

    // We don't use two separate for loops anymore (one for readers and one for writers),
    // so as not to give either class a (major) head start (this is new in 2021, by the way).
    int r = 0;
    int w = 0;
    while ((w < numWriters) || (r < numReaders)) {
        if ( w < numWriters ) {
            wThread[ w ] = std::thread( writer, w, numSeconds );
            w++;
        };

        if ( r < numReaders ) {
            rThread[ r ] = std::thread( reader, r, numSeconds );
            r++;
        };
    }; // end while w < numWriters || r < numReaders
    std::cout <<  "Finished creating all threads..." << std::endl;

    // Let them run.
    // While the threads are running, we have nothing to do,
    // but wait for writers and readers to finish:
    for ( std::thread& t : rThread )
        t.join();
    for ( std::thread& t : wThread )
        t.join();

    theDatabase.printStatistics();
    if (numSeconds < 60)
        std::cout << "WARNING: Since time was only "
                  << numSeconds << " seconds, the statistics above mean NOTHING."
                  << std::endl;

    std::cout << "Simulation finished! Database is "
              << ( theDatabase.ok() ? "OK!" : "NOT OK!!!" ) << std::endl;

    return( theDatabase.ok() ? 0 :  -2 );

} // end main

