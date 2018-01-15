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
#include "globals.h"

//constructor for history
History::History(int nRows, int nCols)
{
    m_CityObject = new City(nRows, nCols);
    m_HistoryRows = m_CityObject->rows();
    m_HistoryCols = m_CityObject->cols();
};

//returns if ita point is in bounds or not
bool History::record(int r, int c)
{
    return (r >= 1  &&  r <= m_HistoryRows  &&  c >= 1  &&  c <= m_HistoryCols);
}

void History::display() const
{
    //clear the screen
    clearScreen();

    //display the history grid
    m_CityObject->display();
    //write an empty line after the history grid
}
