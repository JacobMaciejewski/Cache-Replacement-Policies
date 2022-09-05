#ifndef BUCKET_LIST_NODE_H
#define BUCKET_LIST_NODE_H

#include "../headers/auxiliarry.h"

class bucketListNode
{
private:
    hashEntry *nodeEntry;
    bucketListNode *nextNode;
public:
    bucketListNode(hashEntry*);
    ~bucketListNode();
    hashEntry* getEntry();
    bucketListNode* getNextNode();
    bool lastEntry();
    bool isEntryDirty();
    bool contains(string*, bool);
    bool containsPage(string*, bool);
    void setEntry(hashEntry*);
    void setNextNode(bucketListNode*);
    void setEntryDirty();
    void insert(hashEntry*);
    bucketListNode* remove(string*, bool*);
    void countDirtyPages(unsigned int*);
    void print();
};


#endif