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

void StudentWorld::ProbabilityaddNewObjects()
{
    //add a possible star?
    int StarChance = randInt(1, 15);
    if (StarChance == 1)
    {
        Star *starP = new Star (IID_STAR, 255, randInt(0, VIEW_HEIGHT-1), 0 , (randDouble(.05, .50)), 3, this);
        gameObjectVector.push_back(starP);
    }
    
}

void StudentWorld::AddObjectToVector(Actor * ActorP)
{
    gameObjectVector.push_back(ActorP);
    cerr << "added cabbage to the vec" <<endl;
}

int StudentWorld::init()
{
    //create a NachenBlaster
    NachenBlaster *nachenblasterP = new NachenBlaster (this);
    gameObjectVector.push_back(nachenblasterP);

    //create 30 stars
    for (int i =0; i <30; i ++)
    {
        Star *starP = new Star (IID_STAR, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1), 0 , (randDouble(.05, .50)), 3, this);
        gameObjectVector.push_back(starP);
    }
    
    
    Cabbage * cabbageP = new Cabbage (IID_CABBAGE, 0, 100, 0, .5, 1, this);
    gameObjectVector.push_back(cabbageP);
    
    Turnip *turnipP = new Turnip (IID_TURNIP, 255, 200, 0, .5, 1, this);
    gameObjectVector.push_back(turnipP);
    
    F_Torpedo *f_torpP = new F_Torpedo (IID_TORPEDO, 1, 50, 0, .5, 1, this, IID_NACHENBLASTER);
    gameObjectVector.push_back(f_torpP);

    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //add more objects?
    ProbabilityaddNewObjects();
    for (int i = 0; i < gameObjectVector.size(); i++)
    {
        
        cerr << "object number " << i << endl;
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

void StudentWorld::removeDead()
{
    cerr << "at the beginning, remove dead size is : " << gameObjectVector.size();
    vector<Actor*>::iterator vi = gameObjectVector.begin();
    while (vi!= gameObjectVector.end())
    {
        if ((*vi)->AliveStatus() == false)
        {
            cerr << "found a dead one " << endl;
            delete *vi;
            vi = gameObjectVector.erase(vi);
        }
        vi++;
    }
    
    cerr << "at the end, remove dead size is : " << gameObjectVector.size();
}

void StudentWorld::cleanUp()
{
    for (int i =0; i < gameObjectVector.size(); i ++)
    {
        delete gameObjectVector[i];
        gameObjectVector[i] = nullptr;
        //gameObjectVector.erase(gameObjectVector[i]);
    }
}
