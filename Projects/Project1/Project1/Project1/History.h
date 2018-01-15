//
//  History.h
//  Project1
//
//  Created by Super on 1/14/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#ifndef History_h
#define History_h

#include "City.h"
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    City* m_CityObject;
};


#endif /* History_h */
