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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


int main()
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
        
        if (pathExists(maze, 10,10, 4,3, 1,8))
            cout << "Solvable!" << endl;
        else
            cout << "Out of luck!" << endl;
    }

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    //Push the starting coordinate (sr,sc) onto the coordinate stack
    stack <Coord> coordStack;
    Coord *newCoord = new Coord (sr,sc);
    coordStack.push(*newCoord);
    
    //update maze[sr][sc] to indicate that the algorithm has encountered
    //it (i.e., set maze[sr][sc] to have a value other than '.')
   
    maze [sr][sc]= 'F';
    
    Coord *curr_location = new Coord (0,0);
    //While the stack is not empty
    while (coordStack.empty() == false)
    {
        //Pop the top coordinate off the stack.
        //This gives you the current (r,c) location that your algorithm is exploring.
        curr_location = &coordStack.top();
        coordStack.pop();
        
        //If the current (r,c) coordinate is equal to the ending coordinate,
        if (curr_location->r() == er && curr_location->c() == ec)
        {
            //then we've solved the maze so return true!
            return true;
        }
        
        //Otherwise, Check each place you can move from the current cell as follows:
        else
        {
            //If you can move EAST and haven't encountered that cell yet,
            //then push the coordinate (r,c+1) onto the stack and update
            if (maze[curr_location->r()][curr_location->c()] != 'X' && maze[curr_location->r()][curr_location->c()] != 'F')
            {
                
            }
        }
    }

    return true;
}
