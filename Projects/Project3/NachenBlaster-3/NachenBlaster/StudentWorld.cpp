#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
//remove?
#include <vector>
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

//CREATE NACHENBLASTER HERE?????
StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir) //, m_NachenBlaster(nullptr)
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
    //create a NachenBlaster
    NachenBlaster *nachenblasterP = new NachenBlaster ();
    nachenblasterP->whatWorld(this);
    gameObjectVector.push_back(nachenblasterP);

    //create 30 stars
    for (int i =0; i <2; i ++)
    {
        Star *starP = new Star (IID_STAR, randInt(0, VIEW_WIDTH), randInt(0, VIEW_HEIGHT), 0 , (randDouble(.05, .50)), 3);
        gameObjectVector.push_back(starP);
    }
    
    return GWSTATUS_CONTINUE_GAME;
}
void StudentWorld::removeDead()
{
    for (int i =0; i < gameObjectVector.size(); i ++)
    {
        Actor * temp = gameObjectVector[i];
        if (temp == nullptr)
        {
            cerr << "accessing null in removedead() " << endl;
        }
        if (gameObjectVector[i]->AliveStatus() == false)
        {
            cerr << "found a dead one!" << endl;
            delete gameObjectVector[i];
            //gameObjectVector.erase(gameObjectVector[i]);
        }
    }
}

int StudentWorld::move()
{
    //add more objects?
    addNewObjects();
    for (int i = 0; i < gameObjectVector.size(); i++)
    {
        if (gameObjectVector[i] == nullptr)
        {
            cerr <<"accessing null in move()" << endl;
        }
        cerr << "asking object number " << i << " to do something" << endl;
        if (gameObjectVector.size() > 0)
        {
            gameObjectVector[i]->doSomething();
        }
    }
    removeDead();
    
    return GWSTATUS_CONTINUE_GAME;

    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    for (int i =0; i < gameObjectVector.size(); i ++)
    {
        delete gameObjectVector[i];
    }
}
