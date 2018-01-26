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
void testGet2(Map A);

int main ()
{
    //declaring KeyTypes
    ValueType val;
    KeyType Key1 = "cats";
    KeyType Key2 = "dogs";
    KeyType Key3 = "pigs";
    Map A;
    
    //inserting values into the list
    A.insert(Key1, 1.2);
    A.insert(Key2, 3.4);
    A.insert(Key3, 4.5);
    Map B;
    B.insert(Key1, 1.2);

    //A.swap(B);
    //testGet1(A);
    A.dump ();

   
    
    //A.erase(Key2);
    //A.get(1, Keys, val);
    //cerr << "val is: " << val << endl;
    //A.dump();
    //Map B = A;
    cerr <<"done" <<endl ;
}

void testUpdate(Map A)
{
    bool x = A.update("pigzs", 10.1);
    cerr << "0: " << x;
    bool y = A.update("pigzs", 10.1);
    cerr << "1: " << y;
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
    KeyType Key1 = "cats";
    KeyType Key2 = "dogs";
    KeyType Key3 = "pigs";
    ValueType val;

    bool z = A.get(-1, Key1, val);
    cerr << "z is : " << z;
    cout << "val is: " << val << endl;
    
    bool y =A.get(2, Key2, val);
    cerr << "y is : " << y;
    cout << "val is: " << val << endl;
    
    bool x= A.get(3, Key3, val);
    cerr << "x is : " << x;
    cout << "val is: " << val << endl;

}
