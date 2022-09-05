#ifndef QUEUE_ENTRY_H
#define QUEUE_ENTRY_H

#include "../headers/auxiliarry.h"

class queueEntry
{
private:
    // the id of the process that produced the given entry
    unsigned int pid;
    // the page number in which this memory address is stored
    string *pageNumber;
public:
    queueEntry(unsigned int, string*);
    ~queueEntry();
    unsigned int getProcessID();
    string* getPageNumber();
    bool inPageNumber(string*);
    bool sameEntry(string*, unsigned int*);
    void setPID(unsigned int);
    void setPageNumber(string *);
};


#endif