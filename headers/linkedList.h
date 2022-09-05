#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../headers/auxiliarry.h"

class linkedList
{
    private:
        linkedListNode* head;
        linkedListNode* tail;
        unsigned int limit;
        unsigned int size;
    public:
        linkedList(unsigned int);
        ~linkedList();
        linkedListNode* getHead();
        linkedListNode* getTail();
        unsigned int getLimit();
        unsigned int getSize();
        bool isFull();
        bool isEmpty();
        bool isLastEntry();
        void setLimit(unsigned int);
        void setSize(unsigned int);
        void increaseSize();
        void decreaseSize();
        void setHead(linkedListNode*);
        void setTail(linkedListNode*);
        bool insert(queueEntry*, string*, unsigned int*);
        void setLRU(string*, unsigned int*);
        void print();
};

#endif

