#include  "../headers/queueEntry.h"
      
queueEntry::queueEntry(unsigned int givenPID, string *givenPageNum)
{
    this->setPID(givenPID);

    string *entryPageNum = new string(*givenPageNum);
    this->setPageNumber(entryPageNum);
}

queueEntry::~queueEntry()
{
    delete(this->getPageNumber());
}


unsigned int queueEntry::getProcessID()
{
    return this->pid;
}

string* queueEntry::getPageNumber()
{
    return this->pageNumber;
}

// checks whether current entry is in the given page's memory space
bool queueEntry::inPageNumber(string *searchedPageNumber)
{
    string *entryPageNum = this->getPageNumber();
    return (*entryPageNum == *searchedPageNumber);
}

// checks if current entry has the same page number
// and was produced by the same process as the given one
bool queueEntry::sameEntry(string *givenPageNum, unsigned int *givenPID)
{
    string *currPageNum = this->getPageNumber();
    unsigned int currPID = this->getProcessID();

    bool firstComp = (*currPageNum == *givenPageNum);
    bool secondComp = (*givenPID == currPID);

    return (firstComp && secondComp);
}

void queueEntry::setPID(unsigned int givenPID)
{   
    this->pid = givenPID;
}

void queueEntry::setPageNumber(string *givenPageNumber)
{
    this->pageNumber = givenPageNumber;
}