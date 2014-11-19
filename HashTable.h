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

#define TABLE_SIZE 10

template <class ItemType>
class HashTable {
private:
    ItemType * table;
    int loadNumber;
    int numberOfCollision;
    
public:
    HashTable();
    ~HashTable();
    
    ItemType getTable() {return table[TABLE_SIZE];}
    int getloadNumber() {return loadNumber;}
    
    bool isEmpty();
    int hash(const ItemType & newEntry);
    bool insert(const ItemType & newEntry);
    bool search(const ItemType & target, ItemType & returnTarget);
    void printItem(ItemType * nodePtr, bool displayList, void visit(ItemType &));
    void displayList(void visit(ItemType &));
    void printHashTable(void visit(ItemType &));
    void statistics();
    int countNode(int index);
};

// **************************************
//  Constructor
// **************************************
template <class ItemType>
HashTable<ItemType>::HashTable() {
    table = new ItemType[TABLE_SIZE];
    loadNumber = 0;
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
        table[i].setNext(NULL); // Disconnect linked list from hash table
        
        // Start deleting from the beginning
        while (currentPtr != NULL) {
            nextPtr = currentPtr;
            currentPtr = currentPtr->getNext();
            delete nextPtr;
        }
    }
    delete [] table;
}

// *************************************************
//  isEmpty function
//  This function checks each element in the hash

// *************************************************
template <class ItemType>
bool HashTable<ItemType>::isEmpty() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].getTitle() == "") {
            return false;
        }
    }
    return true;
}

// *************************************************
//  hash function
//  This function finds the sum of the newEntry as
//  a title by converting each character to ascii
//  and summing them up.
//  Return: a hashed number less than the TABLE_SIZE
// *************************************************
template <class ItemType>
int HashTable<ItemType>::hash(const ItemType & newEntry) {
    int sum = 0;
    
    for (int i = 0; i < (newEntry.getTitle()).length(); i++) {
        char x = (newEntry.getTitle()).at(i);
        sum += int(x);
    }
    return (sum % TABLE_SIZE);
}

// ******************************************************
//  insert function
//  This function inserts new data into the hash table.
//  If the place in the hash table has been already taken
//  it will create and insert in a singly linked list
//  Return: true if inserted successfully
//          false if not
// ******************************************************
template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType & newEntry) {
    bool success = false;
    ItemType * newNode = new ItemType(newEntry);
    int index = hash(newEntry); // Get the index
        
    // if the place is empty
    if (table[index].getTitle() == "") {
        table[index] = *newNode;
        loadNumber++;
        success = true;
    }
        
    // if not, then create a linked list at this index
    else {
        ItemType * nodePtr = &table[index];
        
        while (nodePtr->getNext())
            nodePtr = nodePtr->getNext();
        nodePtr->setNext(newNode);

        numberOfCollision++;
        success = true;
    }
    
    return success;
}

// *************************************************
//  search function
//  This function searches for the year of the movie
//  by using the title as the key.
//  Return: true if found
//          false if not
// *************************************************
template <class ItemType>
bool HashTable<ItemType>::search(const ItemType & target, ItemType & returnTarget) {
    bool found = false;
    
    int index = hash(target);
    ItemType * nodePtr = &table[index];
    
    while (nodePtr) {
        if (nodePtr->getTitle() == target.getTitle()) {
            returnTarget = *nodePtr;
            found = true;
        }
        nodePtr = nodePtr->getNext();
    }
    
    if (!found)
        found = false;
    
    return found;
}

// ********************************************
//  printItem function
//  This function prints out the year and title
//  Return: none
// ********************************************
template <class ItemType>
void HashTable<ItemType>::printItem(ItemType * nodePtr, bool displayList , void visit(ItemType &)) {
    ItemType item;
    
    item.setYear(nodePtr->getYear());
    item.setTitle(nodePtr->getTitle());
    if (!displayList) {
        cout << "\t\t ";
    }
    visit(item);

    return;
}

// **********************************************
//  displayList function
//  This function displays every item in the file
//  Return: none
// **********************************************
template <class ItemType>
void HashTable<ItemType>::displayList(void visit(ItemType &)) {
    // Print the hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        ItemType * nodePtr = &table[i];
        printItem(nodePtr, true, visit);
        
        // Print the linked list if any
        while (nodePtr->getNext() != NULL) {
            nodePtr = nodePtr->getNext();
            printItem(nodePtr, true, visit);
        }
    }
    return;
}

// **************************************************
//  printHashTable function
//  This function prints out the indented hash table
//  by showing the index and what elements are in the
//  linked list
//  Return: none
// **************************************************
template <class ItemType>
void HashTable<ItemType>::printHashTable(void (visit)(ItemType &)) {
    // Print the hash table and the index
    for (int i = 0; i < TABLE_SIZE; i++) {
        ItemType * nodePtr = &table[i];
        cout << "Index " << i << ": ";
        if (nodePtr->getYear() != -1) {
            printItem(nodePtr, true, visit);
            
            // Print the linked list if any
            while (nodePtr->getNext() != NULL) {
                nodePtr = nodePtr->getNext();
                printItem(nodePtr, false, visit);
            }
        }
        else
            cout << "// Empty" << endl;
    }
    return;
}

// **************************************
//  countNode function
// **************************************
template <class ItemType>
int HashTable<ItemType>::countNode(int index) {
    int number = 0;
    
    if (table[index].getTitle() == "")
        return 0;
    
    else {
        ItemType * nodePtr = &table[index];
        while (nodePtr->getNext()) {
            nodePtr = nodePtr->getNext();
            number++;
        }
    }
    return number;
}
// **************************************
//  statistics function
// **************************************
template <class ItemType>
void HashTable<ItemType>::statistics() {
    cout << "Number of Collision: " << numberOfCollision << endl;

    double loadFactor = (loadNumber*100)/TABLE_SIZE;
    cout << "Load Factor: " <<  loadFactor  << "%" << endl;
    
    int numberOfList = 0;
    int totalNode = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].getNext() != NULL)
            numberOfList++;
        
    }
    cout << "Number of linked lists: " << numberOfList << endl;
    
    int longest = countNode(0);

    for (int i = 1; i < TABLE_SIZE; i++) {
        totalNode++;
        if (longest <= countNode(i)) {
            longest = countNode(i);
        }
    }
    cout << "Total of nodes: " << totalNode << endl;
    cout << "Longest linked list contains : " << longest << " nodes" << endl;
    if (numberOfList > 0) {
        cout << "average number of nodes stored in linked lists: " << totalNode/numberOfList << endl;
    }
    return;
}
#endif
