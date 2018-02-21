#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
//remove?
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

//CREATE NACHENBLASTER HERE?????
StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), m_NachenBlaster(nullptr)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

double StudentWorld::randDouble(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    double x = min + f * (max - min);
    return abs(x);
}

void StudentWorld::addNewObjects()
{
    //add a possible star?
    int StarChance = randInt(1, 15);
    if (StarChance == 1)
    {
        Star *starP = new Star (IID_STAR, 255, randInt(0, VIEW_HEIGHT), 0 , (randDouble(.05, .50)), 3);
        gameObjectVector.push_back(starP);
    }
}


int StudentWorld::init()
{
    NachenBlaster *nachenblasterP = new NachenBlaster ();
    //create 30 stars
    for (int i =0; i <30; i ++)
    {
        Star *starP = new Star (IID_STAR, randInt(0, VIEW_WIDTH), randInt(0, VIEW_HEIGHT), 0 , (randDouble(.05, .50)), 3);
        gameObjectVector.push_back(starP);
    }
    //create a NachenBlaster
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //add more objects?
    addNewObjects();
    for (int i = 0; i < gameObjectVector.size(); i++)
    {
        
        cerr << "object number " << i << endl;
        if (gameObjectVector.size() > 0)
        {
            gameObjectVector[i]->doSomething();
        }
    }
    return GWSTATUS_CONTINUE_GAME;

    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    delete m_NachenBlaster;
    for (int i =0; i < gameObjectVector.size(); i ++)
    {
        delete gameObjectVector[i];
    }
}
