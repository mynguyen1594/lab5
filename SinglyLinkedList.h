//
//  SinglyLinkedList.h
//  lab5
//
//  Created by My Nguyen on 11/13/14.
//  Copyright (c) 2014 MyNguyen. All rights reserved.
//

#ifndef lab5_SinglyLinkedList_h
#define lab5_SinglyLinkedList_h

#include <iostream>

using namespace std;

template <class ItemType>
class LinkedList {
private:
    ItemType * head;
    int count;
    
public:
    LinkedList() {count = 0;}
    ~LinkedList();
    
    int getCount() {return count;}
    void append(ItemType * nodePtr, const ItemType & newEntry);
    void traverse(ItemType * nodePtr, ItemType item, void visit(ItemType &), bool display);
    void clear();
};

// **************************************
//  append function
// **************************************
template <class ItemType>
void LinkedList<ItemType>::append(ItemType * nodePtr, const ItemType & newEntry) {
    ItemType * newNode = new ItemType(newEntry);
    head = nodePtr; // head always has the value
    
    if (nodePtr != NULL) {
        while (nodePtr->getNext() != NULL) {
            nodePtr = nodePtr->getNext();
            
        }
        nodePtr->setNext(newNode);
        this->count++;
    }
    
    return;
}

// **************************************
//  traverse function
// **************************************
template <class ItemType>
void LinkedList<ItemType>::traverse(ItemType *nodePtr, ItemType item, void (visit)(ItemType &), bool display) {
    while (nodePtr != NULL) {
        item.setYear(nodePtr->getYear());
        item.setTitle(nodePtr->getTitle());
        if (!display) {
            cout << "\t\t ";
        }
        visit(item);
        nodePtr = nodePtr->getNext();
    }
    return;
}
#endif
