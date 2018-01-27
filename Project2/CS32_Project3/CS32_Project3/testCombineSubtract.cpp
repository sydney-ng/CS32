//
//  testCombineSubtract.cpp
//  CS32_Project3
//
//  Created by Super on 1/27/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include "testCombineSubtract.h"
#include <cassert> 
void testCombine (Map A, Map B)
{
    //result isn't empty
     Map result1;
    assert (result1.empty() == true);
    assert (result1.size() ==0);
    //result is empty
    
    
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

    //key is only in A
    //key is in both -> same value
    //key is in both -> different valuess
    
    KeyType Key1 = "one";
    KeyType Key2 = "two";
    KeyType Key3 = "three";
    KeyType Key4 = "four";
    KeyType Key5 = "five";
    
    bool ax = A.insertOrUpdate(Key1, 1.2); //unique to A
    bool bx = A.insertOrUpdate(Key2, 2.3); //unique to A
    bool cx = A.insertOrUpdate(Key3, 3.4); //both same values
    bool dx = A.insertOrUpdate(Key4, 4.5); //both different values
   
    assert (ax == true);
    assert (bx == true);
    assert (cx == true);
    assert (dx == true);
    assert (A.size() == 4 && A.empty() == false);
    
    //key is only in B
    //key is in both -> same value
    //key is in both -> different valuess
    bool ex = B.insertOrUpdate(Key5, 5.6); //unique to B
    bool cx2 = B.insertOrUpdate(Key3, 3.4); //both same values
    bool dx2 = B.insertOrUpdate(Key4, 99.9); //both different values
    assert (ex == true);
    assert (cx2 == true);
    assert (dx2 == true);
    assert (B.size() == 3 && B.empty() == false);

    combine(A, B, result1);
    combine(A, B, result2);
    assert (result1.empty() == true);
    assert (result1.size() ==0);
    
    assert (result2.empty() == true);
    assert (result2.size() ==0);
    cerr << "Combine() --> passed" << endl;

    /*
    for (int i = -1; i < result1.size() +1; i++)
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
    } */
}
