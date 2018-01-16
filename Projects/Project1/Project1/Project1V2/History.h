//
//  History.h
//  Project1
//
//  Created by Super on 1/14/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#ifndef History_h
#define History_h

//#include "City.h"
#include "globals.h"
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_HistoryRows;
    int m_HistoryCols;
    char m_HistoryArray[MAXROWS][MAXCOLS];
};


#endif /* History_h */
