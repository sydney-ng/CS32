//
//  tree.cpp
//  Tree
//
//  Created by Super on 2/10/18.
//  Copyright © 2018 Sydney. All rights reserved.
//
//REMOVE BEFORE SUBMITTING
#include "testTree.h"
// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    //if you're at the end
    if (n1 <=0)
    {
        if (n2>0)
        {
            return 0;
        }
    }
    
    //if n2 is empty, then there can be no more permutations
    if (n2 <= 0)
    {
        //empty == it's there
        return 1;
    }
    
    if (a1[0] == a2[0])
    {
        //check for perumutaitons
        return countIncludes(a1+1, n1-1, a2, n2) + countIncludes(a1+1, n1-1, a2+1, n2-1);
    }
    else
    {
        //iterate to find a possible match
        return countIncludes(a1+1, n1-1, a2, n2);
    }
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > splitter come before all the other elements,
// and all the elements whose value is < splitter come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= splitter, or n if there is no such element, and firstLess is
// set to the index of the first element that is < splitter, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > splitter
//   * for firstNotGreater <= i < firstLess, a[i] == splitter
//   * for firstLess <= i < n, a[i] < splitter
// All the elements > splitter end up in no particular order.
// All the elements < splitter end up in no particular order.
void split(double a[], int n, double splitter,
           int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > splitter
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == splitter
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < splitter
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < splitter)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > splitter)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    //don't do anything!
    if (n <= 1)
    {
        return;
    }
    int middle_index = (n)/2;
    int FN = -1;
    int FL = n;
    split(a, n, a[middle_index],FN, FL);
    order(a + FN, n-FL);
    order(a, FN);
}


