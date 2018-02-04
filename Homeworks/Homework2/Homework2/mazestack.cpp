//
//  mazestack.cpp
//  Homework2
//
//  Created by Super on 2/2/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <string>
#include <iostream>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

int main ()
{
    /*string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    bool x = pathExists(maze, 10,10, 4,3, 1,8);*/
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    return true;
}
