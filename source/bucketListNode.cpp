#include "../headers/bucketListNode.h"

bucketListNode::bucketListNode(hashEntry *givenEntry)
{
    this->setEntry(givenEntry);
    this->setNextNode(NULL);
}

bucketListNode::~bucketListNode()
{
    if(!this->lastEntry())
    {   
        delete this->getNextNode();
    }
    delete this->getEntry();
}

hashEntry* bucketListNode::getEntry()
{
    return this->nodeEntry;
}

bucketListNode* bucketListNode::getNextNode()
{
    return this->nextNode;
}

bool bucketListNode::lastEntry()
{
    return (this->getNextNode() == NULL);
}

bool bucketListNode::isEntryDirty()
{
    hashEntry *currEntry = this->getEntry();

    return currEntry->isDirty();
}

// checks if current list node contains a memory address
// from requested page, if not searches in the next node
bool bucketListNode::contains(string *pageNum, bool setDirty)
{
    bucketListNode *nextNode = this->getNextNode();
    if(this->containsPage(pageNum, setDirty))
    {
        return true;
    }else if(this->lastEntry())
    {
        return false;
    }else
    {
        return nextNode->contains(pageNum, setDirty);
    } 
}

// checks if the entry contained within the node
// refers to memory address within the requested page number
// sets its dirty value to true, if it stated so
bool bucketListNode::containsPage(string *pageNum, bool setDirty)
{
    hashEntry *currEntry;
    currEntry = this->getEntry();

    if(currEntry->containsPage(pageNum))
    {
        if(setDirty)
        {
            currEntry->setDirty(true);
        }
        return true;
    }else
    {
        return false;
    }
}

void bucketListNode::setEntry(hashEntry *givenEntry)
{
    this->nodeEntry = givenEntry;
}

void bucketListNode::setNextNode(bucketListNode *givenNode)
{
    this->nextNode = givenNode;
}


void bucketListNode::insert(hashEntry *newEntry)
{
    bucketListNode *currNextNode;

    if(this->lastEntry())
    {
        currNextNode = new bucketListNode(newEntry);
        this->setNextNode(currNextNode);
    }else
    {
        currNextNode = this->getNextNode();
        currNextNode->insert(newEntry);
    }
    
}

// edge case of single node handled by list class
// checks if curret next node contains address within given page number
// if so delete it and connects current node with next, next node
bucketListNode* bucketListNode::remove(string *pageNum, bool *wasDirty)
{
    bucketListNode *currNextNode = this->getNextNode();
    bucketListNode *newNextNode;

    // current node contains the page
    // simply return its next node
    if(this->containsPage(pageNum, false))
    {
        return currNextNode; 
    }else if((newNextNode = currNextNode->remove(pageNum, wasDirty)) != currNextNode)
    {   
        // if the next node doesn't return itself
        // this means that it contained the requested page number
        // take his next node as your new next one and delete the previous next node
        currNextNode->nextNode = NULL;
        *wasDirty = currNextNode->isEntryDirty();
        delete (currNextNode);
        this->setNextNode(newNextNode);
        return this;
    }else
    {
        return this;
    }
    
}

void bucketListNode::countDirtyPages(unsigned int *totalDirtyPages)
{
    unsigned int dirtyUpNow = *totalDirtyPages;


    if(this->isEntryDirty())
    {
        dirtyUpNow += 1;
        *totalDirtyPages = dirtyUpNow;
    }

    if(!this->lastEntry())
    {
        this->getNextNode()->countDirtyPages(totalDirtyPages);
    }

    return;
}

void bucketListNode::print()
{
    hashEntry *currEntry = this->getEntry();
    string *currPageNum = currEntry->getPageNum();
    bool dirtyState = currEntry->isDirty();
    string printString;

    if(dirtyState)
    {
        printString = "Dirty";
    }else
    {
        printString = "Clean";
    }
    
    cout << "Page_Num[" << *currPageNum << "], State[" << printString << "]" << endl;

    if(!this->lastEntry())
    {
        this->getNextNode()->print();
    }
}