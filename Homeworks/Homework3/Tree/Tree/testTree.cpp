//
//  testTree.cpp
//  Tree
//
//  Created by Super on 2/14/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include "testTree.h"
#include <cassert> 
#include <iostream>
using namespace std;
void testCountIncludes();
void testOrder();
int main ()
{
    testCountIncludes();
    testOrder();
}


void testCountIncludes()
{
    double original [7]= {10, 50 ,40 ,20, 50, 40, 30};
    double a1 [3] = {10 ,20, 40};
    double a2 [3] = {10 ,40, 30};
    double a3 [3] = {20 ,10, 40};
    double a4 [3] = {50 ,40, 30};
    
    assert (countIncludes(original, 7, a1, 3) == 1);
    assert (countIncludes(original, 7, a2, 3) == 2);
    assert (countIncludes(original, 7, a3, 3) == 0);
    assert (countIncludes(original, 7, a4, 3) == 3);
    cout << "passed" << endl;
    
}
void testOrder()
{
    //empty set
    double original2 [7]= {};
    order (original2,0);

    //negative numbers
    double original [8]= {-10, 10, 50 ,40 ,20, 50, 40, 30};
    order (original,8);

    //already in order
    double original3 [8]= {10, 50 ,40 ,20, 50, 40, 30};
    order (original3,7);
    cerr << endl;

    
}
