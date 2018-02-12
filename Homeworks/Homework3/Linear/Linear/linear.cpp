//
//  linear.cpp
//  Linear
//
//  Created by Super on 2/10/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
using namespace std;
bool allTrue(const double *a, int n);
bool somePredicate(double x);
int countFalse(const double *a, int n);
int firstFalse(const double a[], int n);

bool somePredicate(double x)
{
    return x > 0;
}

bool test(const double *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cerr << &a[i] << endl;
    }
    cerr << "next " << endl;
    for (int i = 0; i < n; i++)
    {
        cerr << a+i << endl;
    }
    return false;
}

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
    cerr << " checking " << a << " which is " << a[0] << endl;
    //return condition, you've reached the end
    if (n == 0)
    {
        return -1;
    }
    
    else
    {
        bool x = somePredicate(a[0]);
        if (x == false)
        {
            cerr << a[0] << " returns false " << endl;

            return n;
        }
        else
        {
            cerr << a[0] << " returns true " << endl;
            return 1 + firstFalse(a+1, n-1);
        }
    }
}

int main ()
{
    double arr [3] = {3.1, 4.3, -2.2};
    int x = firstFalse(arr, 3);
    cerr << "answer " << x;
}
