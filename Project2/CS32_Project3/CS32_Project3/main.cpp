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
   
    //A.dump ();

   
    
    //A.erase(Key2);
    //A.get(1, Keys, val);
    //cerr << "val is: " << val << endl;
    //A.dump();
    //Map B = A;
    cerr <<"done";
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
