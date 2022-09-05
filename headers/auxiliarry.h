#ifndef AUXILIARRY_H
#define AUXILIARRY_H

using namespace std;

#define PAGE_SIZE 4096
// addressing within a page takes log2(page size) bits
// we are using 8 * 4 = 32 bits to represent logical addresses
// so the page number is represented with 32 - log2(pagesize) bits
// in this case 32 - log2(4096) = 20 bits = 5 hexadecimals
#define PAGE_NUMBER_SIZE 5
#define TABLE_SIZE 10

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <string>
#include <iostream>
#include <errno.h>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>
#include <unistd.h>

class queueEntry;
class hashEntry;
class linkedListNode;
class linkedList;
class customQueue;
class bucketList;
class bucketListNode;
class hashTable;

#include "../headers/hashEntry.h"
#include "../headers/hashTable.h"
#include "../headers/customQueue.h"
#include "../headers/queueEntry.h"
#include "../headers/bucketList.h"
#include "../headers/bucketListNode.h"
#include "../headers/linkedList.h"
#include "../headers/linkedListNode.h"


void getArguments(int, char**, string*, string*, string*, unsigned int*, unsigned int*, unsigned int*);
void logicalAddressToPageNumber(string*, unsigned int*);
void openFiles(string*, string*, fstream**, fstream**);
void closeFiles(fstream**, fstream**);
void simulation(string*, unsigned int*, unsigned int*, unsigned int*, fstream*, fstream*);
void extractData(string*, string*, bool*);
void simulateEntry(string*, unsigned int, customQueue*, hashTable*, hashTable**, unsigned int*, unsigned int*);
bool simulateQuery(unsigned int*, unsigned int*, unsigned int*, fstream*, unsigned int, customQueue*, hashTable*, hashTable**, unsigned int*, unsigned int*);

#endif