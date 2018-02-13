//
//  maze.cpp
//  Maze
//
//  Created by Super on 2/9/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    cerr << "we're at the point " << sr << " " << sc << endl;
    cerr << "ending points are : " << er << " " << ec << endl;
    //base condition: start == end
    if (sr == er && sc == ec)
    {
        cerr << "made it to the end" << endl;
        //path does exist, return true
        return true;
    }

    else
    {
        //Mark the start location as visted ('V')
        maze[sr][sc] = 'V';
        //then call pathExists starting from that location (and ending at the same ending location as in the current call).
        
        //check if EAST is unvisted
        if ((maze[sr][sc+1] != 'V') && (maze[sr][sc+1] != 'X'))
        {
            sc = sc + 1;
            maze[sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            return pathExists(maze, nRows, nCols, sr, sc, er, ec);
        }
        
        //check if SOUTH is unvisted
        if ((maze[sr+1][sc] != 'V') && (maze[sr+1][sc] != 'X'))
        {
            sr = sr + 1;
            maze [sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            pathExists(maze, nRows, nCols, sr, sc, er, ec);

        }
        
        //check if WEST is unvisited
        if ((maze[sr][sc-1] != 'V') && (maze[sr][sc-1] != 'X'))
        {
            sc = sc - 1;
            maze [sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            pathExists(maze, nRows, nCols, sr, sc, er, ec);

        }
        
        //check if NORTH is unvisited
        if ((maze[sr-1][sc] != 'V') && (maze[sr-1][sc] != 'X'))
        {
            sr = sr-1;
            maze [sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            pathExists(maze, nRows, nCols, sr, sc, er, ec);

        }
        
    }
   
    return false;
}

int main ()
{
    string maze[10] = {
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
    
    if (pathExists(maze, 10,10, 4,3, 4,4))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
