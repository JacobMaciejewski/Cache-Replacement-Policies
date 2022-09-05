#include "../headers/linkedListNode.h"

linkedListNode::linkedListNode(queueEntry* givenEntry)
{
    this->setEntry(givenEntry);
    this->setNextNode(NULL);
}

linkedListNode::~linkedListNode()
{

    if(!this->isLast())
    {
        delete(this->getNextNode());
    }

    delete(this->getEntry());
}

void linkedListNode::setEntry(queueEntry* givenEntry)
{
    this->nodeEntry = givenEntry;
}

void linkedListNode::setNextNode(linkedListNode *givenNextNode)
{
    this->nextNode = givenNextNode;
}

void linkedListNode::print()
{
    queueEntry *currEntry = this->getEntry();
    string *currPageNum = currEntry->getPageNumber();
    unsigned int currPID = currEntry->getProcessID();
    

    cout << "Page_Num[" << *currPageNum << "], Process_ID[" << currPID << "]" << endl;

    if(!this->isLast())
    {
        this->getNextNode()->print();
    }
}

queueEntry* linkedListNode::getEntry()
{
    return this->nodeEntry;
}

linkedListNode* linkedListNode::getNextNode()
{
    return this->nextNode;
}

linkedListNode* linkedListNode::disconnect(string *requestedPageNum, unsigned int requestedPID, linkedListNode **searchedNode)
{
    linkedListNode *currNextNode = this->getNextNode();

    if(this->contains(requestedPageNum, requestedPID))
    {
        *searchedNode = this;
        // no need to update the priority of the LRU page
        if(this->isLast())
        {
            return this;
        }else
        {
            return currNextNode;
        }
    }else
    {
        this->setNextNode(currNextNode->disconnect(requestedPageNum, requestedPID, searchedNode));
        return this;
    }
}


bool linkedListNode::contains(string *requestedPageNum, unsigned int requestedPID)
{
    queueEntry *currEntry = this->getEntry();

    return (currEntry->sameEntry(requestedPageNum, &requestedPID));
}

bool linkedListNode::isLast()
{
    return (this->getNextNode() == NULL);
}