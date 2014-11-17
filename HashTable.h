//
//  HashTable.h
//  lab5
//
//  Created by My Nguyen on 11/12/14.
//  Copyright (c) 2014 MyNguyen. All rights reserved.
//
#include <iostream>

using namespace std;

#ifndef lab5_HashTable_h
#define lab5_HashTable_h

#define TABLE_SIZE 31

template <class ItemType>
class HashTable {
private:
    ItemType * table;
    int loadFactor;
    int numberOfCollision;
    
public:
    HashTable();
    ~HashTable();
    
    ItemType getTable() {return table[TABLE_SIZE];}
    int getloadFactor() {return loadFactor;}
    
    int hash(const ItemType & newEntry);
    bool insert(const ItemType & newEntry);
    bool search(const ItemType & target, ItemType & returnTarget);
    void printItem(ItemType table[], int index, void visit(ItemType &));
    void displayList(void visit(ItemType &));
    void printHashTable(void visit(ItemType &));
    void statistics();
    int count(int index);
};

// **************************************
//  Constructor
// **************************************
template <class ItemType>
HashTable<ItemType>::HashTable() {
    table = new ItemType[TABLE_SIZE];
    loadFactor = 0;
    numberOfCollision = 0;
}

// **************************************
//  Destructor
// **************************************
template <class ItemType>
HashTable<ItemType>::~HashTable<ItemType>() {
    ItemType * currentPtr;
    ItemType * nextPtr;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        currentPtr = table[i].getNext();
        table[i].setNext(NULL);
        while (currentPtr != NULL) {
            nextPtr = currentPtr;
            currentPtr = currentPtr->getNext();
            delete nextPtr;
            
        }
        
    }
    delete [] table;
}
// **************************************
//  hash function
//  Return the hashed number as an index
// **************************************
template <class ItemType>
int HashTable<ItemType>::hash(const ItemType & newEntry) {
    int sum = 0;
    
    // Find the sum of the title by converting each character to ascii and summing up
    for (int i = 0; i < (newEntry.getTitle()).length(); i++) {
        char x = (newEntry.getTitle()).at(i);
        sum += int(x);
    }
    return (sum % TABLE_SIZE);
}

// **************************************
//  insert function
// **************************************
template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType & newEntry) {
    bool success = false;
    
    if (loadFactor < TABLE_SIZE) {
        int index = hash(newEntry); // Get the index
        
        // if the place is empty
        if (table[index].getTitle() == "") {
            table[index].setInfo(newEntry.getYear(), newEntry.getTitle());
            loadFactor++;
            success = true;
        }
        
        // if not, then create a linked list at this index
        else {
            ItemType * newNode = new ItemType(newEntry);
            ItemType * nodePtr = table[index].getNext();
            
            if (nodePtr == NULL)
                table[index].setNext(newNode);
            
            else {
                while (nodePtr->getNext() != NULL) {
                    nodePtr = nodePtr->getNext();
                }
                nodePtr->setNext(newNode);
            }

            numberOfCollision++;
            success = true;
        }
    }
    
    return success;
}

// **************************************
//  search function
// **************************************
template <class ItemType>
bool HashTable<ItemType>::search(const ItemType & target, ItemType & returnTarget) {
    bool found = false;
    
    int index = hash(target);
    ItemType * nodePtr = &table[index];
    
    while (nodePtr != NULL) {   // If nodePtr points to something
        if (nodePtr->getTitle() == target.getTitle()) {
            returnTarget = *nodePtr;
            found = true;
        }
        nodePtr = nodePtr->getNext();
    }
    
    if (!found) {
        found = false;
    }
    return found;
}

// **************************************
//  printItem function
// **************************************
template <class ItemType>
void HashTable<ItemType>::printItem(ItemType table[], int index, void visit(ItemType &)) {
    ItemType item;
    
    item.setYear(table[index].getYear());
    item.setTitle(table[index].getTitle());
    visit(item);

    return;
}

// **************************************
//  displayList function
// **************************************
template <class ItemType>
void HashTable<ItemType>::displayList(void visit(ItemType &)) {
    ItemType item;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printItem(table, i, visit);

        if (table[i].getNext() != NULL) {
            ItemType * nodePtr = table[i].getNext();
            
            while (nodePtr != NULL) {
                item.setYear(nodePtr->getYear());
                item.setTitle(nodePtr->getTitle());
                visit(item);
                nodePtr = nodePtr->getNext();
            }
        }
    }
    return;
}

// **************************************
//  printHashTable function
// **************************************
template <class ItemType>
void HashTable<ItemType>::printHashTable(void (visit)(ItemType &)) {
    ItemType item;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Index " << i << ": ";
        if (table[i].getYear() != -1) {
            printItem(table, i, visit);
 
            if (table[i].getNext() != NULL) {
                ItemType * nodePtr = table[i].getNext();
                while (nodePtr != NULL) {
                    item.setYear(nodePtr->getYear());
                    item.setTitle(nodePtr->getTitle());
                    cout << "\t\t ";
                    visit(item);
                    nodePtr = nodePtr->getNext();
                }
            }
        }
        else
            cout << "// Empty" << endl;
    }
    return;
}

// **************************************
//  statistics function
// **************************************
template <class ItemType>
void HashTable<ItemType>::statistics() {
    cout << "Number of collision: " << numberOfCollision << endl;

    double load = 100*loadFactor/TABLE_SIZE;
    cout << "Load percent: " <<  load  << "%" << endl;
    
    int numList = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].getNext() != NULL) {
            numList++;
        }
    }
    cout << "Number of linked lists: " << numList << endl;
    
    int totalNode = 0;
    int longest = count(0);

    for (int i = 1; i < TABLE_SIZE; i++) {
        totalNode++;
        if (longest <= count(i)) {
            longest = count(i);
        }
    }
    cout << "Longest: " << longest << endl;
    double average = totalNode/numList;
    cout << "average number of nodes stored in linked lists: " << average << endl;
    return;
}

// **************************************
//  count function
// **************************************
template <class ItemType>
int HashTable<ItemType>::count(int index) {
    int number = 0;
    
    if (table[index].getTitle() == "") {
        return 0;
    }
    else {
        if (table[index].getNext() != NULL) {
            ItemType * nodePtr = table[index].getNext();
            while (nodePtr != NULL) {
                nodePtr = nodePtr->getNext();
                number++;
            }
        }
        else
            return number;
    }
    return number;
}
#endif
