//
//  testGetFunctions.cpp
//  CS32_Project3
//
//  Created by Super on 1/27/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <cassert>
#include "testGetFunctions.h"


void testGet2 (Map A)
{
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.
    
    KeyType Key1 = "one";
    KeyType Key2 = "two";
    KeyType Key3 = "three";
    KeyType Key4 = "four";
    KeyType Key5 = "five";
    
    bool a = A.insertOrUpdate(Key1, 1.2);
    bool b = A.insertOrUpdate(Key2, 2.3);
    bool c = A.insertOrUpdate(Key3, 3.4);
    bool d = A.insertOrUpdate(Key4, 4.5);
    bool e = A.insertOrUpdate(Key5, 5.6);
    assert (a == true);
    assert (b == true);
    assert (c == true);
    assert (d == true);
    assert (e == true);
    
    for (int i = -1; i < A.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = A.get(i, tempKey, tempVal);
        if (i == -1)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        if (i == 0)
        {
            assert (x == true);
            assert (tempKey == "one" && tempVal == 1.2);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == Key2 && tempVal == 2.3);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 3)
        {
            assert (x == true);
            assert (tempKey == Key4 && tempVal == 4.5);
        }
        else if (i == 4)
        {
            assert (x == true);
            assert (tempKey == Key5 && tempVal == 5.6);
        }
        else if (i == 5)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        
        else if (i == 6)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
    }
    
    cerr << "Get2() --> passed" << endl;
    
    
}
void testGet1(Map A)
{
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    assert (A.size()==0);
    assert (A.empty()==true);
    
    KeyType Key1 = "a";
    KeyType Key2 = "b";
    
    //key is in map, return true
    
    ValueType val;
    //updating an empty map, will not work
    bool x = A.insertOrUpdate(Key1, 1.2);
    assert (A.size()==1);
    assert (A.empty()==false);
    assert (x == true);
    assert (A.contains(Key1) == true);
    assert (A.get(Key1, val) == true && Key1 == "a" && val == 1.2);
    
    //key isn't in map, return false
    assert (A.get(Key2, val) == false && Key2 == "b" && val == 1.2);
    ValueType val2 = 0;
    assert (A.get(Key2, val2) == false && Key2 == "b" && val2 == 0);
    cerr << "Get1() --> passed" << endl;
    
}
