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
        cerr << "we aren't at the end, check another point" << endl;
        //Mark the start location as visted ('V')
        maze[sr][sc] = 'V';
        //then call pathExists starting from that location (and ending at the same ending location as in the current call).
        
        //check if EAST is unvisted
        if ((maze[sr][sc+1] != 'V') && (maze[sr][sc+1] != 'X'))
        {
            //sc = sc + 1;
            //maze[sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open east point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec) == true)
            {
                return true;
            }
        }
        
        //check if SOUTH is unvisted
        if ((maze[sr+1][sc] != 'V') && (maze[sr+1][sc] != 'X'))
        {
            //sr = sr + 1;
            //maze [sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open south point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec) == true)
            {
                return true;
            }

        }
        
        //check if WEST is unvisited
        if ((maze[sr][sc-1] != 'V') && (maze[sr][sc-1] != 'X'))
        {
            //sc = sc - 1;
            //maze [sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open west point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec) == true)
            {
                return true;
            }

        }
        
        //check if NORTH is unvisited
        if ((maze[sr-1][sc] != 'V') && (maze[sr-1][sc] != 'X'))
        {
            //sr = sr-1;
            //maze [sr][sc] = 'V';
            cerr  << sr << " " << sc << " is a open north point" << endl;
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }
            cerr << endl;
            if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec) == true)
            {
                return true;
            }

        }
        
    }
   
    return false;
}
