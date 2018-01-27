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
    testInsertOrUpdate ( A);

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

void testErase (Map A)
{
    /* 
     cats, dogs, cheese, goat, pigs
    */
    
    /* //erase from beginning
    A.erase("cats");
    cerr << "finished removing cats " << endl;

    //erase from end
    A.erase("pigs");
    A.dump();
    cerr << "finished removing pigs " << endl;
    
     //erase from middle
     A.erase("cheese");
     A.dump();
     cerr << "finished removing cheese " << endl; */
    
    
    //ERASE if it's there's only 1 node or if it's empty node
    /*Map C;
    
    KeyType Key1 = "cats";
    KeyType Key2 = "dogs";

    C.insert(Key1, 7.8);
    C.dump();
    cout << endl;

    C.erase(Key1);
    C.dump(); */
    
    Map B;

    KeyType Key3 = "cats";
    KeyType Key4 = "dogs";
    cerr << "b is: " << endl;
    B.insert(Key3, 1023.2);
    B.dump();

    B.erase(Key4);
    cerr << "----------------" << endl;
    B.dump();
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

void testGet1(Map A)
{
    A.dump();
    ValueType val;
    bool x= A.get("cats", val);
    cerr << "x: " << x << endl;
    cerr << "val: " << val << endl;

    
    x= A.get("pigs", val);
    cerr << "x: " << x <<endl ;
    cerr << "val: " << val << endl;

    
    x= A.get("dogs", val);
    cerr << "x: " << x << endl;
    cerr << "val: " << val << endl;

    x= A.get("jim", val);
    cerr << "x: " << x << endl;
    cerr << "val: " << val << endl;
}
void testGet2(Map A)
{
    KeyType Key1;
    KeyType Key2;
    KeyType Key3;
    ValueType val;

    bool z = A.get(1, Key1, val);
    cerr << "z is : " << z << endl;
    cout << "key is: " << Key1 << endl;
    cout << "val is: " << val << endl<< endl;
    
    
    bool a =A.get(2, Key2, val);
    cerr << "y is : " << a<< endl;
    cout << "key is: " << Key2 << endl;
    cout << "val is: " << val << endl<< endl;
    
    a =A.get(2, Key2, val);
    cerr << "y is : " << a<< endl;
    cout << "key is: " << Key2 << endl;
    cout << "val is: " << val << endl<< endl;
    
    cout << "-----" << endl;
    
    cout << A.size(); 
    bool x= A.get(0, Key3, val);
    cerr << "x is : " << x<< endl;
    cout << "key is: " << Key3 << endl;
    cout << "val is: " << val << endl;

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
