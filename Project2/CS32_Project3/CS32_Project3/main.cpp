//
//  main.cpp
//  CS32_Project3
//
//  Created by Super on 1/24/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
#include "Map.h"
#include "testInsertUpdateFunctions.h"
#include "testBasicFunctions.h"
#include "testGetFunctions.h"
#include "testCombineSubtract.h"
#include "testSubtract.h"
#include <iostream>
#include <cassert>
#include <string>


int main ()
{
    Map A, B;
    testSubtractfunct(A,B);
    testCombine(A,B);
    testSwap (A,B);
    test_SizeEmptyContains(A);
    testInsert(A);
    testUpdate(A);
    testInsertOrUpdate ( A);
    testGet1(A);
    testGet2(A);
    testErase(A);
}
