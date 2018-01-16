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
    m_HistoryRows = nRows;
    m_HistoryCols = nCols;
    for (int i = 0; i < m_HistoryRows; i++)
    {
        for (int j = 0; j < m_HistoryCols; j++)
        {
            m_HistoryArray[i][j] = '.';
        }
    }
};

bool History::record(int r, int c)
{
    //check if in bounds
    if (r >=1 && c >=1 && r <= m_HistoryRows && c <= m_HistoryCols)
    {
        //check if it's already been accounted for
        if (m_HistoryArray[r][c] == '.')
        {
            cerr << "this is the first one" << endl;
            m_HistoryArray[r][c] = 'A';
        }
        
        else if (m_HistoryArray[r][c] >= 'A')
        {
            //if it hasn't been accounted for yet

            
            //must also be smaller than Z
            if (m_HistoryArray[r][c] <= 'Z')
            {
                m_HistoryArray[r][c]++;
            }
            
            
            //if not between A-Z
            else
            {
                return false;
            }
        }

        /*cerr <<"history board looks like:" << endl;
        for (int i = 0; i < m_HistoryRows; i++)
        {
            for (int j = 0; j < m_HistoryCols; j++)
            {
                cerr << m_HistoryArray[i][j];
            }
            cerr << endl;
        */
        return true;
    }
    
    //if not in bounds
    else
    {
        return false;
    }
}

void History::display() const
{
    //clear the screen
    clearScreen();

    //iterate throug the nRows and nCols and show
    for (int i = 0; i < m_HistoryRows; i++)
    {
        for (int j = 0; j < m_HistoryCols; j++)
        {
            cout << m_HistoryArray[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << "Press enter to continue.";
    cin.ignore(10000,'\n');
}
