//
//  testCombineSubtract.h
//  CS32_Project3
//
//  Created by Super on 1/27/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#ifndef testCombineSubtract_h
#define testCombineSubtract_h
#include "Map.h"

//parent function 
void testCombine (Map A, Map B);

//A and B both have things
void CombineNormal (Map A, Map B, Map result1, Map result2);

//set B equal to A
void combineSameParam(Map A, Map B, Map result1, Map result2);

//passing in the same object to both
void combineSameObject(Map A, Map B, Map result1, Map result2);

//one parameter empty
void combineOneEmptyParam (Map A, Map B, Map result1, Map result2);

#endif /* testCombineSubtract_h */
