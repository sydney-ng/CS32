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

void checkDirections(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec, stack <Coord>& coordStack, Coord* curr_location);

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


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
        
        if (pathExists(maze, 10,10, 4,3, 1,8))
            cout << "Solvable!" << endl;
        else
            cout << "Out of luck!" << endl;
    }

void checkDirections(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec, stack <Coord>& coordStack, Coord* curr_location){
 
    Coord *pointToCheck = new Coord (curr_location->r(), curr_location->c());
    
    //If you can move EAST and haven't encountered that cell yet,
    if (maze[pointToCheck->r()][pointToCheck->c()+1] == '.')
    {
        //then push the coordinate (r,c+1) onto the stack
        Coord *move_to = new Coord (pointToCheck->r(),pointToCheck->c()+1);
        coordStack.push(*move_to);
        
        //update maze
        cerr <<"there was room on the right" << endl;
        cerr << "add to the stack: "  << maze [curr_location->r()][curr_location->c()-1] << endl;
    }

    //If you can move SOUTH and haven't encountered that cell yet,
    if (maze[pointToCheck->r()+1][pointToCheck->c()] == '.')
    {
        //then push the coordinate (r+1,c) onto the stack
        cerr <<"there's room on the bottom" << endl;
        Coord *move_to = new Coord (pointToCheck->r()+1,pointToCheck->c());
        coordStack.push(*move_to);
        
        //maze[r+1][c] to indicate the algorithm has encountered it.
        cerr <<"there was room on the bottom" << endl;
        cerr << "add to the stack "  << maze [curr_location->r()][curr_location->c()-1] << endl;

    }
    
    //If you can move WEST and haven't encountered that cell yet,
    if (maze[pointToCheck->r()][pointToCheck->c()-1] == '.')
    {
        //then push the coordinate (r,c-1) onto the stack
        Coord *move_to = new Coord (pointToCheck->r(),pointToCheck->c()-1);
        coordStack.push(*move_to);
        
        //maze[r][c-1] to indicate the algorithm has encountered it.
        cerr <<"there was room on the left" << endl;
        cerr << "add to the stack "  << maze [curr_location->r()][curr_location->c()-1] << endl;
        //[curr_location->r()][curr_location->c()] = 'C';
        
    }
    //If you can move NORTH and haven't encountered that cell yet,
    if (maze[pointToCheck->r()-1][pointToCheck->c()] != 'X' && maze[pointToCheck->r()-1][pointToCheck->c()] != 'C')
    {
        //then push the coordinate (r-1,c) onto the stack
        Coord *move_to = new Coord (pointToCheck->r()-1,pointToCheck->c());
        coordStack.push(*move_to);
        
        //maze[r-1][c] to indicate the algorithm has encountered it.
        cerr <<"there's room on the top" << endl;
        cerr << "add to the stack "  << maze [curr_location->r()][curr_location->c()-1] << endl;
        //maze[curr_location->r()][curr_location->c()] = 'C';
    }

}


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    //Push the starting coordinate (sr,sc) onto the coordinate stack
    stack <Coord> coordStack;
    Coord *newCoord = new Coord (sr,sc);
    coordStack.push(*newCoord);
    
    //update maze[sr][sc] to indicate that the algorithm has encountered
    //it (i.e., set maze[sr][sc] to have a value other than '.')
   
    //maze [sr][sc]= 'C';
    maze [er][ec]= 'F';
    
    for (int i = 0; i < nCols; i++)
    {
        cout << maze[i] << endl;
    }
    Coord *curr_location = new Coord (0,0);
    //While the stack is not empty
    while (coordStack.empty() == false)
    {
        //Pop the top coordinate off the stack.
        //This gives you the current (r,c) location that your algorithm is exploring.
        curr_location = &coordStack.top();
        cerr << "we are going to check " << curr_location->r() << curr_location->c() << endl;
        cerr << "the value at " << curr_location->r() << curr_location->c() << " is: " << maze [curr_location->r()][curr_location->c()] << endl;

        coordStack.pop();

        //this is a location that is valid
        if (maze[curr_location->r()][curr_location->c()] == '.')
        {
            cerr << "this is a valid location" << endl;
            maze[curr_location->r()][curr_location->c()] = 'L';
            checkDirections(maze,nRows,nCols,sr,sc,er,ec,coordStack,curr_location);
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    cerr << maze[i][j];
                    
                }
                cerr << endl;
            }

        }
        
        //If the current (r,c) coordinate is equal to the ending coordinate,
        else if (curr_location->r() == er && curr_location->c() == ec)
        {
            //then we've solved the maze so return true!
            return true;
        }

 
    }
    return false;
} //closes main loop
