//
//  linear.cpp
//  Linear
//
//  Created by Super on 2/10/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
using namespace std;

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double *a, int n)
{
    //return condition, you've reached the end
    if (n == 0)
    {
        return true;
    }
    else
    {
        cerr << "checking " << a[n-1] << " ";
        if (somePredicate(a[n-1]) == false)
        {
            cerr << "there's a false" << endl;
            return false;
        }
        else
        {
            cerr << endl;
            return allTrue(a,n-1);
        }
    }
    return false;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.

int firstFalse(const double a[], int n)
{
    //there's nothing on, return -1
    if(n < 1)
    {
        return -1;
    }
    
    //returns false
    else if (somePredicate(a[0]) == false)
    {
         return 0;
    }
    
    else
    {
        int y = firstFalse(a+1, n-1);
        if (y == -1)
        {
            return -1;
        }
        return 1 + firstFalse(a + 1, n-1);
    }
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    //if you've made it to the end, you have no falses
    if (n == 0)
    {
        return 0;
    }
     else
    {
        bool x = somePredicate(a[0]);
        if (x == false)
        {
            return 1 + countFalse(a+1, n-1);
        }
        else
        {
            return countFalse(a+1, n-1);
        }
    }
    
}


// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    //at the last element
    if (n == 1)
    {
        return 0;
    }
    //the size doesn't even exist
    if (n <= 0)
    {
        return -1;
    }
    //starting from the back, compare current index to rest
    if (a[n-1] < a[indexOfMin(a, n-1)])
    {
        return n-1;
    }
    //if the final is the least, return it
    return indexOfMin(a, n-1);
}


// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    //reached the end of the shorter list
    if (n2 == 0)
    {
        return true;
    }
    
    if (n1 == 0)
    {
        return false;
    }
    
    //your current index of a1 and a2 are equal
    //increment both by one
    if (a1[0] == a2[0])
    {
        return includes(a1+1, n1-1, a2+1, n2-1);
    }
    //your current index of a1 and a2 are NOT equal
    //increment a1 by 1 to see if the next index matches

    if (a1[0] != a2[0])
    {
        return includes(a1+1, n1-1, a2, n2);
    }
    return true;
}
