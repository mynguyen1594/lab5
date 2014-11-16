//
//  HashTable.h
//  lab5
//
//  Created by My Nguyen on 11/12/14.
//  Copyright (c) 2014 MyNguyen. All rights reserved.
//
#include <iostream>
#include "Movie.h"
#include "SinglyLinkedList.h"

using namespace std;

#ifndef lab5_HashTable_h
#define lab5_HashTable_h

#define TABLE_SIZE 10

template <class ItemType>
class HashTable {
private:
    ItemType table[TABLE_SIZE];
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
};

// **************************************
//  Constructor
// **************************************
template <class ItemType>
HashTable<ItemType>::HashTable() {
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
        currentPtr = table[i];
        while (currentPtr != NULL) {
            nextPtr = currentPtr->getNext();
            delete currentPtr;
            currentPtr = nextPtr;
        }
        table[i] = NULL;
    }
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
    LinkedList<ItemType> * listPtr = new LinkedList<ItemType>();
    
    if (loadFactor < TABLE_SIZE) {
        int index = hash(newEntry); // Get the index
        
        // if the place is empty
        if (index >= 0 && index < TABLE_SIZE && table[index].getTitle() == "") {
            table[index].setInfo(newEntry.getYear(), newEntry.getTitle());
            loadFactor++;
            success = true;
        }
        
        // if not, then create a linked list at this index
        else {
            ItemType * nodePtr = &(table[index]);
            listPtr->append(nodePtr, newEntry);
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
    LinkedList<ItemType> * listPtr;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printItem(table, i, visit);

        if (table[i].getNext() != NULL) {
            ItemType * nodePtr = table[i].getNext();
            listPtr->traverse(nodePtr, item, visit, true);
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
    LinkedList<ItemType> * listPtr;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Index " << i << ": ";
        if (table[i].getYear() != -1) {
            printItem(table, i, visit);
 
            if (table[i].getNext() != NULL) {
                ItemType * nodePtr = table[i].getNext();
                listPtr->traverse(nodePtr, item, visit, false);

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
    LinkedList<ItemType> * listPtr;
    cout << "Number of collision: " << numberOfCollision << endl;
    cout << "Load factor: " << loadFactor << endl;
    cout << "Counter: " << listPtr->getCount() << endl;
    int numList = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].getNext() != NULL) {
            numList++;
        }
    }
    cout << "Number of linked lists: " << numList << endl;
    
    
    return;
}

#endif
