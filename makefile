#some name types for readable make file
OB = lib/auxiliarry.o lib/bucketList.o lib/bucketListNode.o lib/hashEntry.o lib/customQueue.o lib/queueEntry.o lib/main.o lib/hashTable.o lib/linkedList.o lib/linkedListNode.o
HEADERS = headers/auxiliarry.h headers/bucketList.h headers/bucketListNode.h headers/hashEntry.h headers/customQueue.h headers/queueEntry.h headers/hashTable.h headers/linkedList.h headers/linkedListNode.h
EXEC = p2
COMP = g++
FLAGS = -g -Wall -c -ggdb3
#executable
all : p2

lib/auxiliarry.o: source/auxiliarry.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/auxiliarry.cpp
	mv auxiliarry.o lib/auxiliarry.o

lib/customQueue.o: source/customQueue.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/customQueue.cpp
	mv customQueue.o lib/customQueue.o 

lib/queueEntry.o: source/queueEntry.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/queueEntry.cpp
	mv queueEntry.o lib/queueEntry.o

lib/main.o: source/main.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/main.cpp
	mv main.o lib/main.o

lib/bucketList.o: source/bucketList.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/bucketList.cpp
	mv bucketList.o lib/bucketList.o

lib/bucketListNode.o: source/bucketListNode.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/bucketListNode.cpp
	mv bucketListNode.o lib/bucketListNode.o

lib/linkedList.o: source/linkedList.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/linkedList.cpp
	mv linkedList.o lib/linkedList.o

lib/linkedListNode.o: source/linkedListNode.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/linkedListNode.cpp
	mv linkedListNode.o lib/linkedListNode.o

lib/hashEntry.o: source/hashEntry.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/hashEntry.cpp
	mv hashEntry.o lib/hashEntry.o

lib/hashTable.o: source/hashTable.cpp $(HEADERS)
	$(COMP) $(FLAGS) source/hashTable.cpp
	mv hashTable.o lib/hashTable.o

p2: $(OB)
	$(COMP) -g $(OB) -o $(EXEC)

clean :
	rm -f $(OB) $(EXEC)