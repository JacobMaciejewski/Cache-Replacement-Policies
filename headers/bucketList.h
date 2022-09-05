#ifndef BUCKET_LIST_H
#define BUCKET_LIST_H

#include "../headers/auxiliarry.h"

class bucketList
{
private:
    bucketListNode *head;
public:
    bucketList();
    ~bucketList();
    bucketListNode* getHead();
    void insert(hashEntry*);
    bool isEmpty();
    bool contains(string*, bool);
    unsigned int countDirtyPages();
    void remove(string*, bool*);
    void setHead(bucketListNode*);
    void print();
};

#endif