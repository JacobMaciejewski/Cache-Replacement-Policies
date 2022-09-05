#include "../headers/linkedList.h"
#include "../headers/linkedListNode.h"


linkedList::linkedList(unsigned int givenLimit)
{
    this->setHead(NULL);
    this->setTail(NULL);
    this->setSize(0);
    this->setLimit(givenLimit);
}

linkedList::~linkedList()
{
    linkedListNode *currHead= this->getHead();
    if(!this->isEmpty())
    {
        delete(currHead);
    }
}

linkedListNode* linkedList::getHead()
{
    return this->head;
}

linkedListNode* linkedList::getTail()
{
   return this->tail; 
}

unsigned int linkedList::getLimit()
{
    return this->limit;
}

unsigned int linkedList::getSize()
{
    return this->size;
}

bool linkedList::isEmpty()
{
    return (this->getSize() == 0);
}

bool linkedList::isFull()
{
    return (this->getSize() == this->getLimit());
}

bool linkedList::isLastEntry()
{
    return (this->getSize() == 1);
}

void linkedList::setLimit(unsigned int givenLimit)
{
    this->limit = givenLimit;
}

void linkedList::setSize(unsigned int givenSize)
{
    this->size = givenSize;
}

void linkedList::increaseSize()
{
    this->size = this->size + 1;
}

void linkedList::decreaseSize()
{
    this->size = this->size - 1;
}


void linkedList::setHead(linkedListNode* givenHead)
{
    this->head = givenHead;
}

void linkedList::setTail(linkedListNode* givenTail)
{
    this->tail = givenTail;
}

bool linkedList::insert(queueEntry *givenEntry, string *deletedPage, unsigned int *deletedPID)
{
    linkedListNode *currTail;
    linkedListNode *newNode = new linkedListNode(givenEntry);
    linkedListNode *currHead = this->getHead();
    linkedListNode *newHead;
    // the contents of the removed LRU (head)
    queueEntry *currEntry;
    string *currPage;
    unsigned int currPID;

    // if list is full
    // in the case of one entry, we simply delete it and
    // the new entry is the new head and tail
    // in the other case, we simply delete previous head
    // set new head as the next of the previous one 
    if(this->isFull())
    {
        if(this->isLastEntry())
        {
            this->setTail(newNode);
            this->setHead(newNode);
        }else
        {
            newHead = currHead->getNextNode();
            currHead->setNextNode(NULL);
            this->setHead(newHead);
            currTail = this->getTail();
            currTail->setNextNode(newNode);
            this->setTail(newNode);
        }

        // deleting the LRU (head) of the list
        currEntry = currHead->getEntry();
        currPage = currEntry->getPageNumber();
        currPID = currEntry->getProcessID();


        *deletedPage = *currPage;
        *deletedPID = currPID;

        delete(currHead);

        return true;
    }else
    {
        if(this->isEmpty())
        {
            this->setTail(newNode);
            this->setHead(newNode);
        }else //new node is our new tail
        {
            currTail = this->getTail();
            currTail->setNextNode(newNode);
            this->setTail(newNode);
        }
        this->increaseSize();
        
    }
    return false;
}

void linkedList::setLRU(string *givenPage, unsigned int *givenPID)
{
    linkedListNode *currHead = this->getHead();
    linkedListNode *currTail = this->getTail();
    linkedListNode *newTail;
    linkedListNode *newHead;

    newHead = currHead->disconnect(givenPage, *givenPID, &newTail);

    // no need to change priority to lowest priority page
    if(newTail != currTail)
    {
        newTail->setNextNode(NULL);
        currTail->setNextNode(newTail);
        this->setHead(newHead);
        this->setTail(newTail);
    }else
    {
        
    }
    
    return;
}

void linkedList::print()
{
    if(this->isEmpty())
    {
        cout << "<EMPTY>" << endl;
    }else
    {
        this->getHead()->print();
    }    
}