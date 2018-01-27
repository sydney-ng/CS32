#include "testBasicFunctions.h"
#include <cassert>
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
    
    //after deleting 1 element
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



void testSwap (Map A, Map B)
{
    //one is empty, the other isn't empty
    KeyType Key1 = "one";
    KeyType Key2 = "two";
    KeyType Key3 = "three";
    KeyType Key4 = "four";
    KeyType Key5 = "five";
    KeyType Key6 = "six";
    bool a = A.insertOrUpdate(Key1, 1.2);
    bool b = A.insertOrUpdate(Key2, 2.3);
    bool c = A.insertOrUpdate(Key3, 3.4);
    bool d = A.insertOrUpdate(Key4, 4.5);
    bool e = A.insertOrUpdate(Key5, 5.6);
    assert (b == true);
    assert (a == true);
    assert (c == true);
    assert (d == true);
    assert (e == true);
    assert (B.size() == 0);
    
    A.swap(B);
    
    //make sure that they have each other's values
    assert (A.size() == 0);
    assert (B.size() == 5);
    KeyType tempKeyo = "default";
    ValueType tempValo = 10.1;
    bool al = A.get(0, tempKeyo, tempValo);
    assert (!al);
    assert (tempKeyo == "default" && tempValo == 10.1);
    
    for (int i = -1; i < B.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = B.get(i, tempKey, tempVal);
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
        
    }
    //both are empty
    
    Map C;
    A.swap(C);
    assert (C.size() == 0);
    assert (A.size() == 0);
    bool al1 = A.get(0, tempKeyo, tempValo);
    assert (!al1);
    assert (tempKeyo == "default" && tempValo == 10.1);
    bool al2 = C.get(0, tempKeyo, tempValo);
    assert (!al2);
    assert (tempKeyo == "default" && tempValo == 10.1);
    
    //they both the same
    
    Map D;
    D = B;
    
    B.swap(D);
    assert (D.size() == 5);
    assert (B.size() == 5);
    
    for (int i = -1; i < B.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = B.get(i, tempKey, tempVal);
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
        
    }
    
    for (int i = -1; i < D.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = D.get(i, tempKey, tempVal);
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
        
    }
    
    
    //they both have things
    Map F;
    bool ax = F.insertOrUpdate(Key1, 1.2);
    bool bx = F.insertOrUpdate(Key2, 2.3);
    bool cx = F.insertOrUpdate(Key3, 3.4);
    
    assert (bx == true);
    assert (ax == true);
    assert (cx == true);
    
    F.swap(D);
    assert (D.size() == 3);
    assert (F.size() == 5);
    
    for (int i = -1; i < F.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = F.get(i, tempKey, tempVal);
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
        
    }
    
    for (int i = -1; i < D.size() +1; i++)
    {
        KeyType tempKey = "default";
        ValueType tempVal = 10.1;
        bool x = D.get(i, tempKey, tempVal);
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
            assert (x == false);
            assert (tempKey == "default" && tempVal == 10.1);
            
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
        
    }
    cerr << "swap() --> passed" << endl;
}
