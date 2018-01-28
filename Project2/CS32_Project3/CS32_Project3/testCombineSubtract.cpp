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
    
    //test if A and B are empty
    
    combine(A, B, result1);
    
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

    
    combine(A, B, result1);
    combine(A, B, result2);
    assert (result1.empty() == true);
    assert (result1.size() ==0);
    assert (result2.empty() == true);
    assert (result2.size() ==0);

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

    combineSameParam(A,B, result1, result2);
    CombineNormal(A, B, result1, result2);
    combineSameObject(A, B, result1, result2);
    //combineSame(A, result1, result2);
    cerr << "Combine() --> passed" << endl;

}

//SAME THING
void combineSameObject (Map A, Map B, Map result1, Map result2)
{
    A = B;
    combine(B, B, result1);
    combine(A, A, result2);
    
    assert (result1.size() == 3);
    assert (result1.size() == 3);
    
    /*
     bool ex = B.insertOrUpdate(Key5, 5.6); //unique to B
     bool cx2 = B.insertOrUpdate(Key3, 3.4); //both same values
     bool dx2 = B.insertOrUpdate(Key4, 99.9);*/
    
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
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
}
//both param the same
void combineSameParam (Map A, Map B, Map result1, Map result2)
{
    A = B;
    combine(A, B, result1);
    combine(B, A, result2);
    
    assert (result1.size() == 3);
    assert (result1.size() == 3);
    
    /*
     bool ex = B.insertOrUpdate(Key5, 5.6); //unique to B
     bool cx2 = B.insertOrUpdate(Key3, 3.4); //both same values
     bool dx2 = B.insertOrUpdate(Key4, 99.9);*/
    
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
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
}

//one param is empty
void combineOneEmptyParam (Map B, Map result1, Map result2)
{
    Map C;
    combine(C, B, result1);
    combine(B, C, result2);
    cerr << result1.size();
    
    assert (result1.size() == 3);
    assert (result1.size() == 3);
    
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
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 1)
        {
            assert (x == true);
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 2)
        {
            assert (x == true);
            assert (tempKey == "four" && tempVal == 99.9);
        }
        else if (i == 3)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
}
//both param have things
void CombineNormal (Map A, Map B, Map result1, Map result2)
{
    combine(A, B, result1);
    combine(A, B, result2);
    
    assert (result1.size() == 4);
    assert (result1.size() == 4);
    
    for (int i = 0; i < result1.size(); i++)
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
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 3)
        {
            assert (x == true);
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
            assert (tempKey == "three" && tempVal == 3.4);
        }
        else if (i == 3)
        {
            assert (x == true);
            assert (tempKey == "five" && tempVal == 5.6);
        }
        else if (i == 4)
        {
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
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
}
