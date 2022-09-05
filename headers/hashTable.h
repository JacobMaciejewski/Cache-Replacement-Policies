#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../headers/auxiliarry.h"

class hashTable
{
private:
    bucketList **buckets;
    unsigned int bucketNum;
public:
    hashTable(unsigned int);
    ~hashTable();
    unsigned int getBucketsNum();
    unsigned int hashFunction(string*);
    unsigned int countDirtyPages();
    bucketList* getIthBucket(unsigned int);
    bucketList* getTargetBucket(string*);
    bucketList** getBuckets();
    void setBuckets(bucketList**);
    void setIthBucket(unsigned int, bucketList*);
    void setBucketsNum(unsigned int);
    void insert(hashEntry*);
    void print();
    bool remove(string*);
    bool contains(string*, bool);
    
};

#endif