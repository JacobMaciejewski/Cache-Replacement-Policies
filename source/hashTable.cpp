#include "../headers/hashTable.h"

hashTable::hashTable(unsigned int tableSize)
{
    this->bucketNum = tableSize;
    bucketList *currentBucket;
    bucketList **currentBuckets = (bucketList**)(malloc(sizeof(bucketList*) * tableSize));

    this->setBuckets(currentBuckets);

    for(unsigned int index = 0; index < tableSize; index++)
    {
        currentBucket = new bucketList();
        this->setIthBucket(index, currentBucket);
    }
    return;
}

hashTable::~hashTable()
{
    unsigned int tableSize = this->getBucketsNum();

    for(unsigned int index = 0; index < tableSize; index++)
    {
        delete(this->getIthBucket(index));
    }

    free(this->getBuckets());
}


//returns index to hash table array of lists of buckets
unsigned int hashTable::hashFunction(string *givenPageNum)
{
    string myString = *givenPageNum;
    unsigned int hashVal = 0;
    unsigned int totalBuckets = this->getBucketsNum();

    for (unsigned int letter = 0; letter < myString.length(); ++letter)
    {
        hashVal ^= (hashVal << 5) +
                   (hashVal >> 2) +
                   myString[letter];
    }
    return hashVal % totalBuckets;
}

unsigned int hashTable::getBucketsNum()
{
    return this->bucketNum;
}

unsigned int hashTable::countDirtyPages()
{
    unsigned int totalBuckets = this->getBucketsNum();
    unsigned int totalDirtyPages = 0;

    for(unsigned int index = 0; index < totalBuckets; index++)
    {
        totalDirtyPages += this->getIthBucket(index)->countDirtyPages();
    }

    return totalDirtyPages;
}

// returns the list into which the new entry will be entered
bucketList* hashTable::getTargetBucket(string *givenPageNum)
{
    unsigned int targetIndex;
    targetIndex = this->hashFunction(givenPageNum);

    return this->getIthBucket(targetIndex);
}


bucketList* hashTable::getIthBucket(unsigned int index)
{
    bucketList **currBuckets = this->getBuckets();
    return currBuckets[index];
}

bucketList** hashTable::getBuckets()
{
    return this->buckets;
}

void hashTable::setBuckets(bucketList **givenBuckets)
{
    this->buckets = givenBuckets;
}

void hashTable::setIthBucket(unsigned int index, bucketList *givenBucket)
{
    bucketList **currBuckets = this->getBuckets();
    currBuckets[index] = givenBucket;
}

void hashTable::setBucketsNum(unsigned int tableSize)
{
    this->bucketNum = tableSize;
}

void hashTable::insert(hashEntry *givenEntry)
{
    string *entryPageNum = givenEntry->getPageNum();
    // simply get the index through hashing the page number
    bucketList *targetBucket = this->getTargetBucket(entryPageNum);
    targetBucket->insert(givenEntry);
    return;
}

void hashTable::print()
{
    unsigned int tableSize = this->getBucketsNum();
    bucketList *currBucket;

    for(unsigned int index = 0; index < tableSize; index++)
    {
        cout << endl << "Bucket[" << index + 1 << "]: " << endl;
        currBucket = this->getIthBucket(index);
        currBucket->print();
    }
    return;
}

// finds the bucket where entry of an address belonging to the given
// page would be stores
// asks bucket to remove entry of given page number
bool hashTable::remove(string *givenPageNum)
{
    bool removedDirtyPage = false;
    bucketList *targetBucket = this->getTargetBucket(givenPageNum);
    
    targetBucket->remove(givenPageNum, &removedDirtyPage);

    return removedDirtyPage;
}

// finds the bucket where entry of an address belonging to the given
// page would be stores
// asks bucket if it contains page number entry
// sets it as dirty if second paremeter is true
bool hashTable::contains(string *givenPageNum, bool setDirty)
{
    bucketList *targetBucket = this->getTargetBucket(givenPageNum);

    return targetBucket->contains(givenPageNum, setDirty);
}
