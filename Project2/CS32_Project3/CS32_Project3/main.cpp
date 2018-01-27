//
//  main.cpp
//  CS32_Project3
//
//  Created by Super on 1/24/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
#include "Map.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;
void testGet1(Map A);
void testInsert(Map A);
void testGet2(Map A);
void testErase (Map A);
void testSwap (Map A, Map B);
void testCombine (Map A, Map B);
void test_SizeEmptyContains(Map A);
void testUpdate(Map A);
void testInsertOrUpdate (Map A);

int main ()
{
    Map A;
    //test_SizeEmptyContains(A);
    //testInsert(A);
    //testUpdate(A);
    //testInsertOrUpdate ( A);
    //testGet1(A);
    //testGet2(A);
    testErase(A);
    //inserting values into the list
    /*A.insert(Key1, 1.2);
    A.insert(Key2, 3.4);
    A.insert(Key5, 3.4);
    A.insert(Key4, 8.9);
    A.insert(Key3, 4.5);
    Map B;
    B.insert(Key1, 1.2);
    B.insert(Key2, 6.7);
    B.insert(Key4, 7.8); */
    
    
    //testGet2(A);;
    //testCombine(A,B);
    //A.erase(Key2);
    //A.get(1, Keys, val);
    //cerr << "val is: " << val << endl;
    //A.dump();
    //Map B = A;
}


void testErase (Map A)
{
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    KeyType Key1 = "one";
    KeyType Key2 = "two";
    KeyType Key3 = "three";
    KeyType Key4 = "four";
    KeyType Key5 = "five";
    KeyType Key6 = "six";
    
    //key is in the map, only entry
    KeyType tempKeya = "default";
    ValueType tempVala = 10.1;
    bool a = A.insertOrUpdate(Key1, 1.2);
    assert (a == true);
    bool e1 = A.erase(Key1);
    assert (e1 == true);
    assert (A.size() == 0);
    assert (A.contains(Key1) == false);
    bool get1 = A.get(0, tempKeya, tempVala);
    assert(!get1 && tempKeya == "default" && tempVala == 10.1);
    
    a = A.insertOrUpdate(Key1, 1.2);
    bool b = A.insertOrUpdate(Key2, 2.3);
    bool c = A.insertOrUpdate(Key3, 3.4);
    bool d = A.insertOrUpdate(Key4, 4.5);
    bool e = A.insertOrUpdate(Key5, 5.6);
    assert (b == true);
    assert (a == true);
    assert (c == true);
    assert (d == true);
    assert (e == true);

    //key is not in map
    bool e2 = A.erase(Key6);
    assert(!e2);
    assert (A.size() == 5);
    assert (A.contains(Key6) == false);
    
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
    //key is in the map, first position
    bool e3 = A.erase(Key1);
    assert (e3);
    assert (A.size() == 4);
    assert (A.contains(Key1) == false);
    for (int i = 0; i < A.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = A.get(i, tempKey, tempVal);
        if (i == 0)
        {
            assert (x == true);
            assert (tempKey == "two" && tempVal == 2.3);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == Key3 && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 4.5);
        }
        else if (i == 3)
        {
            assert (x == true);
            assert (tempKey == Key5 && tempVal == 5.6);
        }
        else if (i == 5)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }

    }
    //key is in the map, last entry
    bool e4 = A.erase(Key5);
    assert (e4);
    assert (A.size() == 3);
    assert (A.contains(Key5) == false);
    for (int i = 0; i < A.size(); i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = A.get(i, tempKey, tempVal);
        if (i == 0)
        {
            assert (x == true);
            assert (tempKey == "two" && tempVal == 2.3);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == Key3 && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 4.5);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
    }
    //key is in the map, middle entry
    bool e5 = A.erase(Key3);
    assert (e5);
    assert (A.size() == 2);
    assert (A.contains(Key3) == false);
    for (int i = 0; i < A.size(); i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = A.get(i, tempKey, tempVal);
        if (i == 0)
        {
            assert (x == true);
            assert (tempKey == "two" && tempVal == 2.3);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 4.5);

        }
        else if (i == 2)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
    }
    cerr << "Erase() --> passed" << endl;

}

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

void test_SizeEmptyContains(Map A)
{
    //make sure Mapsize is 0 since empty
    KeyType Key2 = "a";
    KeyType Key3 = "b";
    assert (A.contains(Key2)==false);
    assert (A.contains(Key3)==false);
    assert (A.size()==0);
    assert (A.empty()==true);
    
    //after inserting 1 element
    A.insert(Key2, 3.4);
    assert (A.contains(Key2)==true);
    assert (A.contains(Key3)==false);
    A.insert(Key3, 2.4);
    assert (A.empty()==false);
    assert (A.size()== 2);
    assert (A.contains(Key2)==true);
    assert (A.contains(Key3)==true);
    
    A.erase(Key2);
    assert (A.size()== 1);
    assert (A.contains(Key2)==false);
    assert (A.contains(Key3)==true);
    A.update(Key3, 9.9);
    assert (A.contains(Key3)==true);
    assert (A.size()== 1);
    assert (A.empty()==false);
    cerr << "empty() --> passed" << endl;
    cerr << "size() --> passed" << endl;
    cerr << "contains() --> passed" << endl;
    
    //after deleting 1 element

}

void testCombine (Map A, Map B)
{
    cerr << " A IS: " << endl;
    A.dump();
    
    cerr << " B IS: " << endl;
    B.dump();
    Map result;
    KeyType Key1 = "cats";
    ValueType Val1 = 0.1;
    
    KeyType Key2 = "dogs";
    ValueType Val2 = 0.21;
    result.insert(Key1, Val1);
    //result.insert(Key2, Val2);
    cerr << " RESULT IS: " << endl;
    //result.dump();
    combine(A, B, result);
    result.dump();
}

void testSwap (Map A, Map B)
{
    cerr << "2nd dump " << endl;

    A.dump();
    cerr <<"testing if swap worked" << endl << endl << endl;
    A.swap(B);
    //testGet1(A);
    //A.dump ();
    
    cerr << "A is: " << endl;
    A.dump();
    
    cerr << endl << endl << "B is: " << endl;
    B.dump();
}
