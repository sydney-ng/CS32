//
//  testSubract.h
//  CS32_Project3
//
//  Created by Super on 1/27/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#ifndef testSubract_h
#define testSubract_h
#include "Map.h"

void testSubtractfunct(Map A, Map B);

//A and B both have things
void Subtract_Normal (Map A, Map B, Map result1, Map result2);


//both parameters are empty
void Subtract_BothEmptyParam (Map A, Map B, Map result1, Map result2);

//set B equal to A
void Subtract_SameValue(Map A, Map B, Map result1, Map result2);

//passing in the same object to both
void Subtract_SameObject(Map A, Map B, Map result1, Map result2);

//one parameter empty
void Subtract_OneEmptyParam (Map A, Map B, Map result1, Map result2);
#endif /* testSubract_h */
