//
//  testLinear.cpp
//  Linear
//
//  Created by Super on 2/12/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <stdio.h>
#include "testLinear.h"
#include <iostream>
#include <cassert>
using namespace std;
void testTrueFunction();
void testMinFunction();
void testIncludes();

int main ()
{
    testTrueFunction();
    testMinFunction();
    testIncludes();
    cerr << "finished" << endl;
}

void testTrueFunction()
{
    //all true
    double arr [7] = {100, 50, 40, 20, 50, 40, 30};
    assert (allTrue(arr, 7) == true);
    assert (countFalse(arr, 7)==0);
    assert (firstFalse(arr,7) == -1);

    //all false
    double arr2 [7] = {-100, -50, -40, -20, -50, -40, -30};
    assert (allTrue(arr2, 7) == false);
    assert (firstFalse(arr2, 7) == 0);
    assert (countFalse(arr2, 7)==7);

    //multiple false
    double arr3 [7] = {100, -50, 40, 20, -50, 40, 30};
    assert (allTrue(arr3, 7) == false);
    assert (countFalse(arr3, 7)== 2);
    assert (firstFalse(arr3, 7) == 1);


    //false in beginning
    double arr4 [7] = {-100, 50, 40, 20, 50, 40, 30};
    assert (allTrue(arr4, 7) == false);
    assert (countFalse(arr4, 7)==1);
    assert (firstFalse(arr4, 7) == 0);

    //false in the end
    double arr5 [7] = {100, 50, 40, 20, 50, 40, -30};
    assert (allTrue(arr5, 7) == false);
    assert (countFalse(arr5, 7)==1);
    assert (firstFalse(arr5, 7) == 6);

}

void testMinFunction()
{
    //all the same number
    double arr1 [3] = {100,100, 100};
    assert (indexOfMin(arr1,3) == 0);
    //2 of the same number
    double arr2 [7] = {100, -50, 40, 100};
    assert (indexOfMin(arr2,4) == 1);

    //min @ beginning
    double arr3 [7] = {10, 100, 50, 40, 20, 40, 30};
    assert (indexOfMin(arr3,7) == 0);

    //min @ end
    double arr4 [7] = {100, 50, 40, 20, 50, 40, 10};
    assert (indexOfMin(arr4,7) == 6);

    //min in the middle
    double arr5 [7] = {100, 50, 40, 20, 50, 40, 30};
    assert (indexOfMin(arr5,7) == 3);

    //min as the negative number
    double arr6 [7] = {100, -50, 40, 20, -50, 40, 30};
    assert (indexOfMin(arr6,7) == 1);

    //it's an empty set
    double arr7 [7] = {};
    assert (indexOfMin(arr7,0) == -1);

}

void testIncludes()
{
    double original [7] = {100, 50, 40, 20, 50, 40, 30};
    
    //a2 is empty, return true
    double arr1 [1] = {};
    //exactly the same, return true
    double arr2 [7] = {100, 50, 40, 20, 50, 40, 30};
    //regular, somewhere in the middle, return true
    double arr3[4] = {50,20,50,30};
    //a2 has 3 but a1 has 2, return false
    double arr4[5] = {100, 50,50,50};
    //a2 has duplicate numbers, return true
    double arr5[4] = {100,50,20,50};
    //one item & it's the last one, return true
    double arr6[1] = {30};
    //one item & it's the first one, return true
    double arr7[1] = {100};
    assert (includes(original, 7, arr1, 0) == true);
    assert (includes(original, 7, arr2, 7) == true);
    assert (includes(original, 7, arr3, 4) == true);
    assert (includes(original, 7, arr4, 5) == false);
    assert (includes(original, 7, arr5, 4) == true);
    assert (includes(original, 7, arr6, 1) == true);
    assert (includes(original, 7, arr7, 1) == true);
    


}
