#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H


#include "../headers/auxiliarry.h"

class customQueue
{
protected:
    // used to check if current spot is taken by an entry
    bool *secondChances;
    // array containing all queue's entries
    queueEntry **entries;
    // stores the index to the current displacement candidate
    unsigned int candidateIndex;
    // the maximum number of elements in the queue
    unsigned int maxEntries;
public:
    // general function used to decide whether and which
    // entry to replace with the new one
    customQueue(unsigned int);
    virtual ~customQueue();
    bool* getSecondChances();
    bool hasSecondChance(unsigned int);
    bool ithSpotTaken(unsigned int);
    queueEntry** getEntries();
    queueEntry* getIthEntry(unsigned int);
    unsigned int getCandidateIndex();
    unsigned int getMaxEntries();
    void setSecondChances(bool*);
    void changeChanceState(unsigned int);
    void setEntries(queueEntry**);
    void setIthEntry(unsigned int, queueEntry*);
    void setCandidateIndex(unsigned int);
    void setMaxEntries(unsigned int);
    virtual void giveSecondChange(string*, unsigned int*);
    void printQueue();
    virtual bool insert(queueEntry*, unsigned int*, string*);
    bool updateCurrentSpot(unsigned int, queueEntry*, unsigned int**, string**);
};

class queueLRU: public customQueue
{
public:
    linkedList* listLRU;
    queueLRU(unsigned int);
    ~queueLRU();
    bool insert(queueEntry*, unsigned int*, string*) override;
    void giveSecondChange(string*, unsigned int*) override;
};

class queueClock: public customQueue
{
public:
    queueClock(unsigned int pagesNum) : customQueue(pagesNum){}
    ~queueClock();
    bool insert(queueEntry*, unsigned int*, string*) override;
};

customQueue* initializeQueue(string*, unsigned int*);

#endif