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
//CHANGE GAME POINTS
StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), m_NachenBlaster(nullptr), m_vectorPointer(nullptr)
{
    m_GamePoints = 0;
    m_CurrentLevel = 1;
}

std::vector<Actor*> StudentWorld::getVector()
{
    return gameObjectVector;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::getCurrentLevel()
{
    return m_CurrentLevel;
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

NachenBlaster* StudentWorld::getNachenblasterPointer()
{
    return m_NachenBlaster;
}
void StudentWorld::AddObjectToVector(Actor * ActorP)
{
    gameObjectVector.push_back(ActorP);
    cerr << "added object to the vec" <<endl;
}

int StudentWorld::init()
{
    //create a NachenBlaster
    NachenBlaster *nachenblasterP = new NachenBlaster (this);
    gameObjectVector.push_back(nachenblasterP);
    //set member variable equal to the item in the Vector that is the NB
    m_NachenBlaster = nachenblasterP;
    
    RepairGoodie * RepairGoodieP = new RepairGoodie (IID_REPAIR_GOODIE, 200, 200, 0, .5, 1, this);
    gameObjectVector.push_back(RepairGoodieP);
    
//    FT_Goodie * FT_GoodieP = new FT_Goodie (IID_TORPEDO_GOODIE, 100, 100, 0, .5, 1, this);
//    gameObjectVector.push_back(FT_GoodieP);
//    
//    Smallgon *smallgonP = new Smallgon (IID_SMALLGON, 255 , 100, 0 , 1, 3, this);
//    gameObjectVector.push_back(smallgonP);
//    
//    Smoregon *smoregonP = new Smoregon (IID_SMALLGON, 100 , 100, 0 , 1.5, 1, this);
//    gameObjectVector.push_back(smoregonP);
    
    //create 30 stars
//    for (int i =0; i <30; i ++)
//    {
//        Star *starP = new Star (IID_STAR, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1), 0 , (randDouble(.05, .50)), 3, this);
//        gameObjectVector.push_back(starP);
//    }
    
    //Cabbage * cabbageP = new Cabbage (IID_CABBAGE, 99, 100, 0, .5, 1, this);
    //gameObjectVector.push_back(cabbageP);
    /*
    Turnip *turnipP = new Turnip (IID_TURNIP, 255, 200, 0, .5, 1, this);
    gameObjectVector.push_back(turnipP);
    
    F_Torpedo *f_torpP = new F_Torpedo (IID_TORPEDO, 1, 50, 0, .5, 1, this, IID_NACHENBLASTER);
    gameObjectVector.push_back(f_torpP);
*/
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //add more objects?
    //ProbabilityaddNewObjects();
    cerr << "let's move all the objects! " << endl << endl;
        cerr << "still objects in Vector, size @ beginning of move is: " << gameObjectVector.size() << endl;
        for (int i = 0; i < gameObjectVector.size(); i++)
        {
            cerr << "about to move object number " << i << endl;
            if (gameObjectVector.size() > 0 && gameObjectVector[i]->getWorld() != nullptr)
            {
                cerr << "v size is: " << gameObjectVector.size();
                gameObjectVector[i]->doSomething();
            }
            cerr << "finished the move for object number " << i << endl;
            
        }
    removeDead();
    cerr << "finished removing dead" <<endl;
    return GWSTATUS_CONTINUE_GAME;

    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::removeDead()
{
    vector<Actor*>::iterator vi = gameObjectVector.begin();
    
    while (vi != gameObjectVector.end())
    {
        cerr << "is vec empty? " << gameObjectVector.empty() << endl;
        if (gameObjectVector.empty () == false && *vi != nullptr)
        {
            if ((*vi)->AliveStatus() == false)
            {
                delete *vi;
                *vi = nullptr;
                vi = gameObjectVector.erase(vi);
            }
            else
            {
                vi++;
            }
        }
    }
}
void StudentWorld::cleanUp()
{
    for (int i =0; i < gameObjectVector.size(); i ++)
    {
        if (gameObjectVector.empty() == false)
        {
            delete gameObjectVector[i];
            gameObjectVector[i] = nullptr;
            //gameObjectVector.erase(gameObjectVector[i]);
        }
    }
}
