#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H

#include "../headers/auxiliarry.h"

class hashEntry
{
private:
    string *pageNum;
    bool dirty;
public:
    hashEntry(string*, bool);
    ~hashEntry();
    string *getPageNum();
    bool isDirty();
    bool containsPage(string*);
    void setPageNum(string*);
    void setDirty(bool);
};

#endif