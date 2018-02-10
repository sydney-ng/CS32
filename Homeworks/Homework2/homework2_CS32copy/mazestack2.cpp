//
//  mazestack.cpp
//  Homework2
//
//  Created by Super on 2/2/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
#include<stack>

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

void checkDirectionsStack(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec, stack <Coord>& coordStack, int curr_row, int curr_col);
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


void checkDirectionsStack(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec, stack <Coord>& coordStack, int curr_row, int curr_col)
{
    
    //If you can move EAST and haven't encountered that cell yet,
    if (maze[curr_row][curr_col+1] == '.')
    {
        //then push the coordinate (r,c+1) onto the stack
        coordStack.push(Coord(curr_row,curr_col+1));
        
        //update maze
        cerr <<"there was room on the right" << endl;
        cerr << "add to the stack: "  << maze [curr_row][curr_location->c()+1] << endl;
    }

    //If you can move SOUTH and haven't encountered that cell yet,
    if (maze[curr_row+1][curr_col] == '.')
    {
        //then push the coordinate (r+1,c) onto the stack
        coordStack.push(Coord (curr_row+1,curr_col));
        
        //maze[r+1][c] to indicate the algorithm has encountered it.
        cerr <<"there was room on the bottom" << endl;
        cerr << "add to the stack "  << maze [curr_row+1][curr_col] << endl;

    }
    
    //If you can move WEST and haven't encountered that cell yet,
    if (maze[curr_row][curr_col-1] == '.')
    {
        //then push the coordinate (r,c-1) onto the stack
        coordStack.push(Coord (curr_row,curr_col-1));
        
        //maze[r][c-1] to indicate the algorithm has encountered it.
        cerr <<"there was room on the left" << endl;
        cerr << "add to the stack "  << maze [curr_row][curr_col-1] << endl;
        //[curr_location->r()][curr_location->c()] = 'C';
        
    }
    //If you can move NORTH and haven't encountered that cell yet,
    if (maze[curr_row-1][curr_col] == '.')
    {
        //then push the coordinate (r-1,c) onto the stack
        coordStack.push(Coord (curr_row-1,curr_col));
        
        //maze[r-1][c] to indicate the algorithm has encountered it.
        cerr <<"there's room on the top" << endl;
        cerr << "add to the stack "  << maze [curr_row-1][curr_col()] << endl;
        //maze[curr_location->r()][curr_location->c()] = 'C';
    }

}


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    //Push the starting coordinate (sr,sc) onto the coordinate stack
    stack <Coord> coordStack;
    coordStack.push(Coord(sr,sc));
    
    //update maze[sr][sc] to indicate that the algorithm has encountered
    //it (i.e., set maze[sr][sc] to have a value other than '.')
   
    char marker = 'L';
    
    Coord *curr_location;
    //While the stack is not empty
    while (coordStack.empty() == false)
    {
        //Pop the top coordinate off the stack.
        //This gives you the current (r,c) location that your algorithm is exploring.
        curr_location = &coordStack.top();
        cerr << "the value at " << curr_location->r() << curr_location->c() << " is: " << maze [curr_location->r()][curr_location->c()] << endl;

        coordStack.pop();

        //this is a location that is valid
        //If the current (r,c) coordinate is equal to the ending coordinate,
        if (curr_location->r() == er && curr_location->c() == ec)
        {
            //then we've solved the maze so return true!
            return true;
        }
        
        if (maze[curr_location->r()][curr_location->c()] == '.')
        {
            cerr << "this is a valid location" << endl;
            maze[curr_location->r()][curr_location->c()] = marker;
            checkDirectionsStack(maze,nRows,nCols,sr,sc,er,ec,coordStack,curr_location->r(), curr_location->c());
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }

        }
    }
    return false;
} //closes main loop

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //moved test point down one
    bool x = pathExists(maze, 10,10, 5,3, 1,8);
    assert (x == true);
    
    string maze1[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //walls surrounding it
    bool y= pathExists(maze1, 10,10, 1,1, 1,8);
    assert (y == false);
    
    string maze2[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    bool z = pathExists(maze2, 10,10, 5,2, 8,2);
    assert (z == true);
    
    string maze3[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X...X....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X.....X",
        "XXXXXXXXXX"
    };
    
    //multiple ways to get there
    bool a = pathExists(maze3, 10,10, 8,4, 1,2);
    assert (a == true);
    
    string maze4[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //no ways to get there
    bool ab = pathExists(maze4, 10,10, 7,4, 1,2);
    assert (ab == false);
    
    string maze5[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX...X..XX",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XX.X.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //points next to each other separated by a wall
    bool abc = pathExists(maze5, 10,10, 1,1, 1,5);
    assert (abc == false);
    
    string maze6[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X...XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //vertically down
    bool abcd = pathExists(maze6, 10,10, 1,8, 8,8);
    assert (abcd == true);
    
    string maze7[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //vertically up
    bool abcde = pathExists(maze7, 10,10, 8,8, 1,8);
    assert (abcde == true);
    
    string maze8[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //horzontally right
    bool abcdef = pathExists(maze8, 10,10, 4,3, 4,8);
    assert (abcdef == true);
    
    string maze9[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    //horzontally left
    bool abcdefg = pathExists(maze9, 10,10, 4,8, 4,3);
    assert (abcdefg == true);
    
    string maze10[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X.X..X",
        "X.XXXX.X.X",
        "X......X.X",
        "XXXXXXXXXX"
    };
    
    //difficult one, one path
    bool abcdefga = pathExists(maze10, 10,10, 1,8, 7,6);
    assert (abcdefga == true);
    
    string maze11[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XX.......X",
        "X...X.XX.X",
        "X.X.X....X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    bool abcdefgab = pathExists(maze11, 10,10, 1,8, 1,8);
    assert (abcdefgab == true);
    
    
    cerr << "passed all the test cases" << endl;
    return 0;
}
