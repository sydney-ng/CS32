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
void testErase (Map A);
void testSwap (Map A, Map B);
void testCombine (Map A, Map B);


int main ()
{
    //declaring KeyTypes
    ValueType val;
    KeyType Key1 = "cats";
    KeyType Key2 = "dogs";
    KeyType Key3 = "pigs";
    KeyType Key4 = "goat";
    KeyType Key5 = "cheese";
    Map A;
    
    //inserting values into the list
    A.insert(Key1, 1.2);
    A.insert(Key2, 3.4);
    A.insert(Key5, 3.4);
    A.insert(Key4, 8.9);
    A.insert(Key3, 4.5);
    Map B;
    B.insert(Key1, 1.2);
    B.insert(Key2, 6.7);
    B.insert(Key4, 7.8);
    
    testErase(A);
    //testGet2(A);
    //testCombine(A,B);
    //A.erase(Key2);
    //A.get(1, Keys, val);
    //cerr << "val is: " << val << endl;
    //A.dump();
    //Map B = A;
    cerr <<"done" <<endl ;
}

void testErase (Map A)
{
    /* 
     cats, dogs, cheese, goat, pigs 
    */
    //erase from beginning
    
    /*A.erase("cats");
    cerr << "finished removing cats " << endl;

    //erase from end
    A.erase("pigs");
    A.dump();
    cerr << "finished removing pigs " << endl;*/

    
     //erase from middle
     A.erase("cheese");
     A.dump();
     cerr << "finished removing cheese " << endl;

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
