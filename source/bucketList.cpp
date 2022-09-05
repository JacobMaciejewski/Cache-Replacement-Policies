#include "../headers/bucketList.h"

bucketList::bucketList()
{
    this->setHead(NULL);
}

bucketList::~bucketList()
{
    if(!this->isEmpty())
    {
        delete this->getHead();
    }
}

bucketListNode* bucketList::getHead()
{
    return this->head;
}

void bucketList::insert(hashEntry *newHashEntry)
{
    bucketListNode *currHead;


    if(this->isEmpty())
    {
        currHead = new bucketListNode(newHashEntry);
        this->setHead(currHead);
    }else
    {
        currHead = this->getHead();
        currHead->insert(newHashEntry);
    }
    
}

bool bucketList::isEmpty()
{
    return (this->getHead() == NULL);
}

bool bucketList::contains(string *pageNum, bool setDirty)
{
    bucketListNode *currHead;

    if(this->isEmpty())
    {
        return false;
    }else
    {
        currHead = this->getHead();
        return currHead->contains(pageNum, setDirty);
    }
    
}

unsigned int bucketList::countDirtyPages()
{
    unsigned int totalDirtyPages = 0;
    bucketListNode *currHead = this->getHead();

    if(!this->isEmpty())
    {
        currHead->countDirtyPages(&totalDirtyPages);
    }

    return totalDirtyPages;
}

// removes requested frame from memory
// returns true if it was a dirty frame
void bucketList::remove(string *pageNumber, bool *wasDirty)
{
    bucketListNode *currHead = this->getHead();
    bucketListNode *newHead;

    newHead = currHead->remove(pageNumber, wasDirty);

    if(newHead != currHead)
    {
        *wasDirty = currHead->isEntryDirty();
        currHead->setNextNode(NULL);
        delete currHead;
        this->setHead(newHead);
    }
    return;
}

void bucketList::setHead(bucketListNode *newHead)
{
    this->head = newHead;
}

void bucketList::print()
{
    if(this->isEmpty())
    {
        cout << "<EMPTY>" << endl;
    }else
    {
        this->getHead()->print();
    }   
}
