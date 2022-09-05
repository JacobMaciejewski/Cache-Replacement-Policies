#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

#include "../headers/auxiliarry.h"

class linkedListNode
{
    private:
        queueEntry *nodeEntry;
        linkedListNode *nextNode;
    public:
        linkedListNode(queueEntry*);
        ~linkedListNode();
        void setEntry(queueEntry*);
        void setNextNode(linkedListNode*);
        void print();
        queueEntry* getEntry();
        linkedListNode* getNextNode();
        linkedListNode* disconnect(string*, unsigned int, linkedListNode**);
        bool contains(string*, unsigned int);
        bool isLast();
};

#endif