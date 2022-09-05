#include "../headers/hashEntry.h"

hashEntry::hashEntry(string *givenPageNum, bool dirtyState)
{
    string *currPageNum = new string(*givenPageNum);

    this->setPageNum(currPageNum);
    this->setDirty(dirtyState);
}

hashEntry::~hashEntry()
{
    delete this->getPageNum();
}

string* hashEntry::getPageNum()
{
    return this->pageNum;
}

bool hashEntry::isDirty()
{
    return this->dirty;
}

bool hashEntry::containsPage(string *givenPageNum)
{
    return ((*(this->getPageNum())) == *givenPageNum);
}

void hashEntry::setPageNum(string *givenPageNum)
{
    this->pageNum = givenPageNum;
}

void hashEntry::setDirty(bool dirtyState)
{
    this->dirty = dirtyState;
}