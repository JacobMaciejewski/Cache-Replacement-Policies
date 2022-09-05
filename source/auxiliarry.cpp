#include "../headers/auxiliarry.h"

// ως ορίσματα τον αλγόριθμο αντικατάστασης, τον αριθμό
// πλαισίων της κεντρικής μνήμης και το πλήθος των αναφορών q

// scans the user's terminal input
// extracts the following argument
// -a (algorithm) [LRU/Second_Chance]
// -f1 (first file to read)
// -f2 (second file to read)
// -fn (total number of frames)
// -fr (number of reads per file query)
// -tr (total number of reads from both files)
void getArguments(int argc, char **argv, string *algorithm, string *firstFile, string *secondFile, unsigned int *framesNumber, unsigned int *fileReads, unsigned int *totalReads)
{
    for(int i = 0; i < argc; i++)
    {
        if(!strcmp(argv[i], "-a"))
        {
            *algorithm = string(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-f1"))
        {
            *firstFile = string(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-f2"))
        {
            *secondFile = string(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-fn"))
        {
            *framesNumber = (unsigned int)(atoi(argv[i+1]));
        }
        else if(!strcmp(argv[i], "-fr"))
        {
            *fileReads = (unsigned int)(atoi(argv[i+1]));
        }
        else if(!strcmp(argv[i], "-tr"))
        {
            *totalReads = (unsigned int)(atoi(argv[i+1]));
        }
    }
}

// takes as an input the string of hexadecimal representation
// of the logical address and returns a string as an argument
// containing the string page number representation
void logicalAddressToPageNumber(string *logicalAddress, string *pageNumber)
{
    string partialPageNumber = *logicalAddress;

    partialPageNumber = partialPageNumber.substr(0, PAGE_NUMBER_SIZE);

    *pageNumber = partialPageNumber;
}

// simply open files with given names
// and returns the corresponding streams
void openFiles(string *firstFile, string *secondFile, fstream **firstStream, fstream **secondStream)
{
    *firstStream = new fstream(*firstFile, ios::in | ios::binary);
    *secondStream = new fstream(*secondFile, ios::in | ios::binary);
    return;
}

// simply closes the given streams
void closeFiles(fstream **firstStream, fstream **secondStream)
{
    (*firstStream)->close();
    delete(*firstStream);
    (*secondStream)->close();
    delete(*secondStream);

    return;
}

void extractData(string *line, string *logicalAddress, bool *setDirty)
{
    // word variable to store word 
    string stateString; 
  
    // making a string stream 
    stringstream lineStream(*line); 
  
    lineStream >> *logicalAddress;
    lineStream >> stateString;

    if(stateString == "W")
    {
        *setDirty = true;
    }else
    {
        *setDirty = false;
    }
    
    return;
}


void simulateEntry(string *lineContent, unsigned int currentPID, customQueue *simulationQueue, hashTable *currTable, hashTable **tables, unsigned int *reads, unsigned int *writes)
{
    // logical address and address' page number in string form
    string currentLogicalAddress, currentPageNum;
    // the number of page removed from memory
    string removedPageNum;
    unsigned int removedPID;
    // page containing given logical address can be overwritten, set as dirty
    bool setDirty;
    // entries to be inserted into used data structures
    hashEntry *newHashEntry; 
    queueEntry *newQueueEntry;

    extractData(lineContent, &currentLogicalAddress, &setDirty);
    logicalAddressToPageNumber(&currentLogicalAddress, &currentPageNum);

    *reads = 0;
    *writes = 0;

    if(!currTable->contains(&currentPageNum, setDirty))
    {
        newHashEntry = new hashEntry(&currentPageNum, setDirty);
        newQueueEntry = new queueEntry(currentPID, &currentPageNum);
        currTable->insert(newHashEntry);
        // inserting the new entry
        // true return value, implies an entry has been removed
        if(simulationQueue->insert(newQueueEntry, &removedPID, &removedPageNum))
        {
            if((tables[removedPID])->remove(&removedPageNum))
            {
                *writes = 1;
            }else
            {
                *writes = 0;
            }
        }

        *reads = 1;
    }else
    {
        // page already in the memory, simply give it a second chance
        simulationQueue->giveSecondChange(&currentPageNum, &currentPID);
        *reads = 0;
    }

    return;
}

// simulates a given number of reads for the current file
// executes a query, aka a batch of reads from a specific file
bool simulateQuery(unsigned int *currentLine, unsigned int *readsPerQuery, unsigned int *totalReads, fstream *currentFile, unsigned int currentPID, customQueue *simulationQueue, hashTable *currTable, hashTable **tables, unsigned int *reads, unsigned int *writes)
{
    string lineContent;
    unsigned int currReads = 0;
    unsigned int currWrites = 0;
    bool maxIterations = false;
    bool endOfFile = false;

    *reads = 0;
    *writes = 0;

    for(unsigned int index = 0; index < *readsPerQuery; index++)
    {
        // checking if we have reached the end of file
        endOfFile = !getline(*currentFile, lineContent) ? true : false;
        // checking if we have reached the maximum number of reads within current query
        maxIterations = *currentLine >= *totalReads ? true : false;


        if(maxIterations || endOfFile)
        {
            return false;
        }
        else
        {
            simulateEntry(&lineContent, currentPID, simulationQueue, currTable, tables, &currReads, &currWrites);
            *reads = *reads + currReads;
            *writes = *writes + currWrites;

            *currentLine = *currentLine + 1;
        }
        
    }

    return true;
}

void simulation(string *algorithm, unsigned int *readsPerQuery, unsigned int *maxReads, unsigned int *framesNumber, fstream *firstFile, fstream *secondFile)
{
    unsigned int currentLine = 0;
    unsigned int currentPID = 1;
    // the contents of the current line
    string lineContent;
    // the page we are currently looking for
    string currentPageNum;
    string currentLogicalAddress;
    // the file that we are reading from
    fstream *currentFile;
    // initialzing a queue that will be using the given algorithm
    // if used gave unorthodox input, LRU algorithm is used by default
    customQueue *simulationQueue = initializeQueue(algorithm, framesNumber);
    
    // initializing the hash tables for the two process that will store
    // information about pages available in memory
    hashTable **tables = (hashTable**)(malloc(sizeof(hashTable*) * 2));
    hashTable *currentTable; 
    tables[0] = new hashTable(TABLE_SIZE);
    tables[1] = new hashTable(TABLE_SIZE);
    // read and writes
    unsigned int totalReads = 0;
    unsigned int totalWrites = 0;
    unsigned int currReads = 0;
    unsigned int currWrites = 0;


    while(1)
    {
        currentPID = !currentPID;
        currentFile = currentPID ? secondFile : firstFile;
        currentTable = tables[currentPID];

        // if query simulation shows an error (exceeded the number of total queries or got to the end of file)
        // we should exit the program
        if(!simulateQuery(&currentLine, readsPerQuery, maxReads, currentFile, currentPID, simulationQueue, currentTable, tables, &currReads, &currWrites))
        {
            break;
        }

        totalReads += currReads;
        totalWrites += currWrites;

        currentPID = !currentPID;
        currentFile = currentPID ? secondFile : firstFile;
        currentTable = tables[currentPID];

        // if query simulation shows an error (exceeded the number of total queries or got to the end of file)
        // we should exit the program
        if(!simulateQuery(&currentLine, readsPerQuery, maxReads, currentFile, currentPID, simulationQueue, currentTable, tables, &currReads, &currWrites))
        {
            break;
        }

        totalReads += currReads;
        totalWrites += currWrites;

    }

    // totalReads += currReads;
    // totalWrites += currWrites;

    // print the results
    cout << endl << "Page faults: " << totalReads << endl;
    cout << endl << "Total writes before cleanup: " << totalWrites << endl;


    // the dirty pages that remained in memory, are stored back to disc
    // resulting in new writes
    totalWrites += tables[0]->countDirtyPages();
    totalWrites += tables[1]->countDirtyPages();
    cout << endl << "Total writes after cleanup: " << totalWrites << endl;

    delete tables[0];
    delete tables[1];
    free(tables);
    delete(simulationQueue);
    return;
}