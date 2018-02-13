//
//  testMaze.cpp
//  Maze
//
//  Created by Super on 2/12/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include "testMaze.h"
//
//  testStackandQueues.cpp
//  Homework2_StacksQueues
//
//  Created by Super on 2/6/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include "testMaze.h"

#include <iostream>
using namespace std;
#include <string>
#include <cassert>

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
