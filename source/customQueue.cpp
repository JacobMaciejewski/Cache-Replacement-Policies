#include "../headers/customQueue.h"

customQueue::customQueue(unsigned int framesNumber)
{
    // boolean array representing whether ith entry has a second chance
    bool *initialChances;
    // array containing the entries (pages) of the queue
    queueEntry** initialEntries;

    // setting the upper limit of frames in the queue
    this->setMaxEntries(framesNumber);
    // initially the candidate at index 0 is the one to be taken out
    this->setCandidateIndex(0);

    // initially all entries have a second chance
    initialChances = (bool*)(malloc(sizeof(bool) * framesNumber));
    for(unsigned int index = 0; index < framesNumber; index++)
    {
        initialChances[index]= true;
    }
    this->setSecondChances(initialChances);


    // initially no entries in the queue, just allocating memory
    // for the array
    initialEntries = (queueEntry**) (malloc(sizeof(queueEntry*) * framesNumber));
    this->setEntries(initialEntries);
    // NULL implies current spot is not taken
    for(unsigned int index = 0; index < framesNumber; index++)
    {
        this->setIthEntry(index, NULL);
    }   
}

queueLRU::queueLRU(unsigned int pagesNum) : customQueue(pagesNum)
{
    this->listLRU = new linkedList(pagesNum);
}


queueLRU::~queueLRU()
{
    delete this->listLRU;
}

customQueue::~customQueue()
{
    unsigned int totalEntries = this->getMaxEntries();
    queueEntry *currentEntry;

    // freeing the entries of the queue
    for(unsigned int index = 0; index < totalEntries; index++)
    {

        if(this->ithSpotTaken(index))
        {
            currentEntry = this->getIthEntry(index);
            delete(currentEntry);
        }
    }

    // freeing the boolean array
    free(this->getSecondChances());
    free(this->getEntries());
}

// calls general queue destructor
queueClock::~queueClock()
{

}


// returns the array representing
// whether ith entry has a second chance
bool* customQueue::getSecondChances()
{
    return this->secondChances;
}

// checks if entry at given index has a second chance
bool customQueue::hasSecondChance(unsigned int index)
{
    bool *chances = this->getSecondChances();
    return chances[index];
}

// checks whether the ith spot is taken or not
bool customQueue::ithSpotTaken(unsigned int index)
{
    return (this->getIthEntry(index) != NULL);
}


// returns the array of queue's entries
queueEntry** customQueue::getEntries()
{
    return this->entries;
}

// returns the entry at the given index
queueEntry* customQueue::getIthEntry(unsigned int index)
{
    queueEntry** allEntries = this->getEntries();
    return allEntries[index];
}

// returns the index at which the current to remove
// candidate is placed
unsigned int customQueue::getCandidateIndex()
{
    return this->candidateIndex;
}

// returns the maximum amount of entries
// that can be stored in the queue
unsigned int customQueue::getMaxEntries()
{
    return this->maxEntries;
}


void customQueue::setSecondChances(bool *givenChances)
{
    this->secondChances = givenChances;
    return;
}

// changes the state of the spot at the given index
// if it was taken, now it is free and vice versa
void customQueue::changeChanceState(unsigned int index)
{
    bool *currentSecondChances = this->getSecondChances();

    // new state is the negation of the previous one
    currentSecondChances[index] = !currentSecondChances[index];
    return;
}


void customQueue::setEntries(queueEntry **givenEntries)
{   
    this->entries = givenEntries;
    return;
}


void customQueue::setIthEntry(unsigned int index, queueEntry *givenEntry)
{
    queueEntry **currentEntries = this->getEntries();
    currentEntries[index] = givenEntry;
    return;
}


void customQueue::setCandidateIndex(unsigned int newIndex)
{
    this->candidateIndex = newIndex;
}

void customQueue::setMaxEntries(unsigned int givenMaxEntries)
{
    this->maxEntries = givenMaxEntries;
}

// gives second chance to the entry in the queue
void customQueue::giveSecondChange(string *givenPageNum, unsigned int *givenPID)
{
    unsigned int currIndex = this->getCandidateIndex();
    unsigned int queueSize = this->getMaxEntries();
    queueEntry *currEntry;
    bool *currChances;

    while(1)
    {
        currEntry = this->getIthEntry(currIndex);

        if(this->ithSpotTaken(currIndex))
        {
            if(currEntry->sameEntry(givenPageNum, givenPID))
            {
                break;
            }
        }
        currIndex = (currIndex + 1) % queueSize;
    }
    
    currChances = this->getSecondChances();

    currChances[currIndex] = true;

    return;
}

void customQueue::printQueue()
{
    unsigned int queueSize = this->getMaxEntries();
    unsigned int currIndex = this->getCandidateIndex();
    queueEntry *currEntry;
    string *entryPage;
    unsigned int entryPID;

    cout << endl;

    for(unsigned int index = 0; index < queueSize; index++)
    {
        currEntry = this->getIthEntry(currIndex);
        entryPage = currEntry->getPageNumber();
        entryPID = currEntry->getProcessID();

        if(this->ithSpotTaken(currIndex))
        {

            cout << "Page_Num[" << *entryPage << "], Process_ID[" << entryPID << "]" << endl;
        }else
        {
            cout << "EMPTY SPOT" << endl;
        }
        

        currIndex = (currIndex + 1) % queueSize;
    }

    cout << endl;
}

bool customQueue::insert(queueEntry *inputEntry, unsigned int *removedEntryPid, string *pageNumberToRemove)
{
    return false;
}

// simply checkes whether target spot is empty
// if so, inserts new entry
// otherwise inserts new entry, removes previous one and returns its data through parameters
bool queueLRU::insert(queueEntry *inputEntry, unsigned int *removedEntryPid, string *pageNumberToRemove)
{
    // unsigned int targetIndex = this->getCandidateIndex();
    // unsigned int queueSize = this->getMaxEntries();


    return (this->listLRU->insert(inputEntry, pageNumberToRemove, removedEntryPid));

    // the next candidate is the following after the currenly updated spot
    // this->setCandidateIndex((targetIndex + 1) % queueSize);
    // checks is spot is taken, if so, removes the previous entry
    // in other case, simply stores the new entry
    // return this->updateCurrentSpot(targetIndex, inputEntry, &removedEntryPid, &pageNumberToRemove);
}

// in the case of LRU no second chance is required
// we are simply making the requested page LRU (least recently used)
void queueLRU::giveSecondChange(string *givenPage, unsigned int *givenPID)
{
    this->listLRU->setLRU(givenPage, givenPID);
}

// searches for a spot where to insert new entry based on clock algorithm
// if it is empty, inserts new entry
// otherwise inserts new entry, removes previous one and returns its data through parameters
bool queueClock::insert(queueEntry *inputEntry, unsigned int *removedEntryPid, string *pageNumberToRemove)
{
    unsigned int currIndex = this->getCandidateIndex();
    unsigned int queueSize = this->getMaxEntries();

    // traversing the entries of the queue
    while(this->ithSpotTaken(currIndex))
    {
        // current entry has second chance, take it
        // and keep searching for other candidate
        if(this->hasSecondChance(currIndex))
        {
            this->changeChanceState(currIndex);
        }else
        {
            break;
        }

        currIndex = (currIndex + 1) % queueSize;
    }

    // the next candidate is the following after the currenly updated spot
    this->setCandidateIndex((currIndex + 1) % queueSize);
    // checks is spot is taken, if so, removes the previous entry
    // in other case, simply stores the new entry
    return this->updateCurrentSpot(currIndex, inputEntry, &removedEntryPid, &pageNumberToRemove);
}

// extracts the content of the target spot
// if it is empty, simply stores new entry and returns false
// otherwise, removes previous entry, takes its values and returns true
bool customQueue::updateCurrentSpot(unsigned int index, queueEntry *newEntry, unsigned int **entryPID, string **entryPageNumber)
{
    queueEntry *currentEntry;
    // set to true
    this->getSecondChances()[index] = true;
    // the to remove spot is taken
    // by another entry, extract its data
    // and remove it
    if(this->ithSpotTaken(index))
    {
        currentEntry = this->getIthEntry(index);

        **entryPID = currentEntry->getProcessID();
        **entryPageNumber = *(currentEntry->getPageNumber());
        // deleting the previous entry
        delete currentEntry;
        // new entry added in the place of the previous one
        this->setIthEntry(index, newEntry);

        return true;
    }else // found an empty spot for the new entry
    {
        this->setIthEntry(index, newEntry);
        return false;
    }
}

customQueue* initializeQueue(string *algorithm, unsigned int *framesNumber)
{
    customQueue *newQueue;

    if(*algorithm == "Second_Chance")
    {
        newQueue = new queueClock(*framesNumber);
    }else
    {
        newQueue = new queueLRU(*framesNumber);
    }

    return newQueue;
    
}


