#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
//remove?
#include "Actor.h"
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

int StudentWorld::init()
{
    Star *starP = new Star (IID_STAR, 100, 100, 0, .40, 3);
    gameObjectVector.push_back(starP);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    for (int i = 0; i < 1; i++)
    {
        gameObjectVector[i]->doSomething();
        if (gameObjectVector[i]->CheckIfAlive() == false)
        {
            delete gameObjectVector[i];
            return GWSTATUS_PLAYER_DIED;
        }
    }
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    return GWSTATUS_CONTINUE_GAME;
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}
