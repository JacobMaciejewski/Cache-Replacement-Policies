#include "../headers/auxiliarry.h"

int main(int argc, char** argv)
{
    // the replacement algorithm
    // the files from which we will be reading the memory addresses
    string algorithm, firstFile, secondFile;
    // the total number of frames in the memory
    // the maximum amount of reads from a file
    unsigned int framesNumber, readsPerQuery, totalReads;
    // files streams
    fstream *firstStream, *secondStream;

    // getting the arguments from the user
    getArguments(argc, argv, &algorithm, &firstFile, &secondFile, &framesNumber, &readsPerQuery, &totalReads);
    // opening the files containing the logical addresses
    openFiles(&firstFile, &secondFile, &firstStream, &secondStream);
    // simulate the page replacement scheme
    simulation(&algorithm, &readsPerQuery, &totalReads, &framesNumber, firstStream, secondStream);
    // closing the files
    closeFiles(&firstStream, &secondStream);
    return 0;
}
