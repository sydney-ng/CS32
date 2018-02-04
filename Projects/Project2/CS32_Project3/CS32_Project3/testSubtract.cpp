//
//  testSubtract.cpp
//  CS32_Project3
//
//  Created by Super on 1/27/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <stdio.h>
#include "testSubtract.h"
#include <cassert>

void testSubtractfunct(Map A, Map B)
{
    //result isn't empty
    Map result1;
    assert (result1.empty() == true);
    assert (result1.size() ==0);
    //result is empty
    
    //test if A and B are empty
    
    Map result2;
    KeyType Key1r = "un";
    KeyType Key2r = "duo";
    KeyType Key3r = "twa";
    KeyType Key4r = "cat";
    
    bool a = result2.insertOrUpdate(Key1r, 1.0);
    bool b = result2.insertOrUpdate(Key2r, 2.0);
    bool c = result2.insertOrUpdate(Key3r, 3.0);
    bool d = result2.insertOrUpdate(Key4r, 4.0);
    assert (a == true);
    assert (b == true);
    assert (c == true);
    assert (d == true);
    
    Subtract_BothEmptyParam(A, B, result1, result2);

    /*assert (result1.empty() == true);
    assert (result1.size() ==0);
    assert (result2.empty() == true);
    assert (result2.size() ==0);*/
    
    //key is only in A
    //key is in both -> same value
    //key is in both -> different valuess
    
    KeyType Key1 = "one";
    KeyType Key2 = "two";
    KeyType Key3 = "three";
    KeyType Key4 = "four";
    KeyType Key5 = "five";
    KeyType Key6 = "six";
    KeyType Key7 = "seven";

    
    bool ax = A.insertOrUpdate(Key1, 1.2); //unique to A
    bool cx = A.insertOrUpdate(Key3, 3.4); //both same values
    bool dx = A.insertOrUpdate(Key5, 4.5); //both maps, but different values
    bool bx = A.insertOrUpdate(Key2, 2.3); //unique to A
    bool gx = A.insertOrUpdate(Key6, 6.7); //unique to A

    assert (ax == true && bx == true && cx == true && dx == true && gx == true);
    assert (A.size() == 5 );
    assert (A.empty() == false);
    
    //key is only in B
    //key is in both -> same value
    //key is in both -> different valuess
    
    bool ex = B.insertOrUpdate(Key5, 5.6); //in both maps, but different value
    bool x1 = B.insertOrUpdate(Key7, 7.8);//unique to B
    bool cx2 = B.insertOrUpdate(Key3, 3.4); //both same values
    bool dx2 = B.insertOrUpdate(Key4, 99.9); //unique to B
    assert (ex == true && cx2 == true && dx2 == true && x1 ==true);
    assert (B.size() == 4 && B.empty() == false);
    
    Subtract_Normal(A, B, result1, result2);
    Subtract_SameValue(A, B, result1, result2);
    Subtract_SameObject(A, B, result1, result2);
    Subtract_OneEmptyParam (A, B, result1, result2);
    cerr << "subtract() --> passed" << endl;

}

void Subtract_OneEmptyParam (Map A, Map B, Map result1, Map result2)
{
    Map C;
    subtract(C, B, result1);
    subtract(B, C, result2);
    assert (result1.size() == 0 && result1.empty() == true);
    assert (result2.size() == 4 && result2.empty() == false);
    
    //test result 1
    KeyType tempKey = "default";
    ValueType tempVal = 10.1;
    bool x = result1.get(0, tempKey, tempVal);
    assert (x == false);
    assert (tempKey == "default" && tempVal== 10.1);
    
    //test result2

    for (int i = -1; i < result2.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = result2.get(i, tempKey, tempVal);
        
        if (i == -1)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        if (i == 0)
        {
            assert (x == true);
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "seven" && tempVal == 7.8);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 3)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
    }

}
//set B equal to As
void Subtract_SameValue(Map A, Map B, Map result1, Map result2)
{
    A = B;
    subtract(A, B, result1);
    subtract(B, A, result2);
    assert (result1.size() == 0 && result1.empty() == true);
    assert (result2.size() == 0&& result2.empty() == true);
    KeyType tempKey = "default";
    KeyType tempKey2 = "default2";
    
    ValueType tempVal = 10.1;
    ValueType tempVal2 = 10.12;
    
    bool x = result1.get(0, tempKey, tempVal);
    
    assert (x == false);
    assert (tempKey == "default" && tempVal== 10.1);
    
    bool y = result2.get(0, tempKey2, tempVal2);
    
    assert (y == false);
    assert (tempKey2 == "default2" && tempVal2 == 10.12);
}

//set B equal to A
void Subtract_SameObject(Map A, Map B, Map result1, Map result2)
{
    subtract(A, A, result1);
    subtract(B, B, result2);
    assert (result1.size() == 0&& result1.empty() == true);
    assert (result2.size() == 0 && result2.empty() == true);
    KeyType tempKey = "default";
    KeyType tempKey2 = "default2";
    
    ValueType tempVal = 10.1;
    ValueType tempVal2 = 10.12;
    
    bool x = result1.get(0, tempKey, tempVal);
    
    assert (x == false);
    assert (tempKey == "default" && tempVal== 10.1);
    
    bool y = result2.get(0, tempKey2, tempVal2);
    
    assert (y == false);
    assert (tempKey2 == "default2" && tempVal2 == 10.12);
}

//both have nothing
void Subtract_BothEmptyParam (Map A, Map B, Map result1, Map result2)
{
    subtract(A, B, result1);
    subtract(B, A, result2);
    assert (result1.size() == 0 && result1.empty() == true);
    assert (result2.size() == 0 && result2.empty() == true);
    
    KeyType tempKey = "default";
    KeyType tempKey2 = "default2";

    ValueType tempVal = 10.1;
    ValueType tempVal2 = 10.12;

    bool x = result1.get(0, tempKey, tempVal);

    assert (x == false);
    assert (tempKey == "default" && tempVal== 10.1);
    
    bool y = result2.get(0, tempKey2, tempVal2);

    assert (y == false);
    assert (tempKey2 == "default2" && tempVal2 == 10.12);
}


void Subtract_Normal (Map A, Map B, Map result1, Map result2)
{
    subtract(A, B, result1);
    subtract(B, A, result2);
    assert(result1.size() == 3);
    assert(result2.size() == 2);

    for (int i = -1; i < result1.size(); i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = result1.get(i, tempKey, tempVal);
        
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
            assert (tempKey == "two" && tempVal == 2.3);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "six" && tempVal == 6.7);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
    }
    
    for (int i = 0; i < result2.size(); i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = result2.get(i, tempKey, tempVal);
        
        if (i == -1)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        if (i == 0)
        {
            assert (x == true);
            assert (tempKey == "seven" && tempVal == 7.8);
        }
        if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
    }
}









