//
//  History.cpp
//  Project1
//
//  Created by Super on 1/14/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <stdio.h>
#include "History.h"
#include <iostream>
using namespace std;
#include "City.h"

History::History(int nRows, int nCols)
{
    m_CityObject = new City(nRows, nCols);
};

bool History::record(int r, int c)
{
    //check if row r, column c is not within the City
    //lower bounds: r >= 0 and c >=0
    //upper bounds:
        //return false
    
    //else return true
    return true;
} 
