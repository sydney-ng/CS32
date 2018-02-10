//
//  testStackandQueues.hpp
//  Homework2_StacksQueues
//
//  Created by Super on 2/6/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#ifndef testStackandQueues_h
#define testStackandQueues_h
#include <iostream>
#include <stack>
#include <string> 
using namespace std;
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

void checkDirectionsStack(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec, stack <Coord>& coordStack, Coord* curr_location);

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

#endif /* testStackandQueues_h */
