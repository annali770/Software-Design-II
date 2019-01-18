//
//  Set.h
//  CSCI 235, Fall 2018, Project 2
//
//  Created by Anna Li on 9/13/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include "SetInterface.h"

template<class ItemType>
class Set : public SetInterface<ItemType>
{
    
public:
    Set();
    
    int getCurrentSize() const;
    
    
    bool isEmpty() const;
    
    
    bool add(const ItemType& newEntry);

    
    bool remove(const ItemType& anEntry);

    
    void clear();
    

    bool contains(const ItemType& anEntry) const;

    
    std::vector<ItemType> toVector() const;
    
private:
    static const int DEFAULT_SET_SIZE = 4; // for testing purposes we will keep the set small
    
    ItemType items_[DEFAULT_SET_SIZE]; // array of set items
    
    int item_count_;                  // current count of set items
    
    int max_items_;                   // max capacity of the set
    
    // post: Either returns the index of target in the array items_
    
    // or -1 if the array does not contain the target
    
    int getIndexOf(const ItemType& target) const;
    
    
};

//#include "Set.cpp"
#endif /* Set_h */

