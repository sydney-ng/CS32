//
//  testInsertUpdateFunctions.cpp
//  CS32_Project3
//
//  Created by Super on 1/27/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <stdio.h>
#include "testInsertUpdateFunctions.h"
#include <cassert>

void testInsertOrUpdate (Map A)
{
    
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    
    KeyType Key1 = "a";
    KeyType Key2 = "b";
    KeyType Key3 = "a";
    
    //UPDATE FUNCTIONS
    
    ValueType val = 0;
    //updating an empty map, will not work
    bool x = A.insertOrUpdate(Key1, 1.2);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (x == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key1, val) == true && Key1 == "a" && val == 1.2);
    
    //update it, exiting key w/ new value
    bool y = A.insertOrUpdate (Key1, 1.3);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (y == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key1, val) == true && Key1 == "a" && val == 1.3);
    
    //update it, exiting key w/ new value
    bool yz = A.insertOrUpdate (Key1, 1.3);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (yz == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key1, val) == true && Key1 == "a" && val == 1.3);
    
    
    //INSERT FUNCTIONS
    
    ValueType val1 = 0;
    bool xinsert = A.insertOrUpdate (Key2, 1.5);
    assert (A.size()==2);
    assert (A.empty()==false);
    assert (xinsert == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key2, val1) == true && Key2 == "b" && val1 == 1.5);
    
    //basically just update
    ValueType val2 = .998;
    bool yza = A.insertOrUpdate (Key1, 1.009);
    assert (A.size()==2);
    assert (A.empty()==false);
    assert (yza == true);
    assert (A.get(Key1, val2) == true && val2 == 1.009);
    
    //insert empty string as key, new value -> false
    ValueType valzz;
    KeyType EmptyrStr = "";
    bool yzab = A.insertOrUpdate (EmptyrStr, 99.9);
    assert (A.size()==3);
    assert (A.empty()==false);
    assert (yzab == true);
    assert (A.get(EmptyrStr, valzz) == true && valzz == 99.9);
    
    cerr << "InsertOrUpdate() --> passed" << endl;
}
void testUpdate (Map A)
{
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    
    KeyType Key1 = "a";
    KeyType Key2 = "b";
    KeyType Key3 = "a";
    
    ValueType val = 0;
    //updating an empty map, will not work
    bool x = A.update(Key1, 1.2);
    assert (A.size()==0);
    assert (A.empty()==true);
    assert (x == false);
    assert (A.contains(Key1) == false);
    assert (A.get(Key1, val) == false && Key1 == "a" && val == 0);
    
    //add an item
    bool z = A.insert(Key1,1.2);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (z == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key1, val) == true && Key1 == "a" && val == 1.2);
    
    //update it, exiting key w/ new value
    bool y = A.update (Key1, 1.3);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (y == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key1, val) == true && Key1 == "a" && val == 1.3);
    
    //update it, exiting key w/ existing value
    bool yz = A.update (Key1, 1.3);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (yz == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key1, val) == true && Key1 == "a" && val == 1.3);
    cerr << "Update() --> passed" << endl;
    
}

void testInsert (Map A)
{
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full.
    KeyType Key1 = "a";
    KeyType Key2 = "b";
    KeyType Key3 = "a";
    
    //insert new key, new value -> true
    //insert new key, same value -> false
    //insert already key, new value -> false
    //insert empty key, any value -> true
    
    assert (A.size()==0);
    assert (A.empty()==true);
    
    //insert new key, new value -> true
    bool x = A.insert (Key1, 1.2);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (x == true);
    assert (A.insertOrUpdate(Key1, 1.2) == true);
    assert (A.contains(Key1));
    
    //insert new key, same value -> false
    ValueType val;
    bool y = A.insert (Key1, 1.2);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (y == false);
    assert (A.insertOrUpdate (Key1, 1.2) == true);
    assert (A.get(Key1, val) == true && val == 1.2);
    
    //insert already key, new value -> false
    ValueType valz;
    bool yz = A.insert (Key1, 99.9);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (yz == false);
    assert (A.get(Key1, valz) == true && valz == 1.2);
    
    //insert already key, new value -> false
    ValueType val2 = 1.0;
    bool z = A.insert (Key3, 1.3);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (z == false);
    assert (A.get(Key1, val2) == true && val2 == 1.2);
    
    //normal, new key w/ new value
    ValueType val3 = 10.1;
    bool za = A.insert (Key2, 1.5);
    assert (A.size()==2);
    assert (A.empty()==false);
    assert (za == true);
    assert (A.insertOrUpdate (Key2, 1.5) == true);
    assert (A.get(Key2, val3) == true && val3 == 1.5);
    cerr << "Insert() --> passed" << endl;
    
}
