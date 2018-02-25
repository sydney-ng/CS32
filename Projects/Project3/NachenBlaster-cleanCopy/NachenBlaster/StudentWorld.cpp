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
: GameWorld(assetDir), m_NachenBlaster(nullptr)
{
    m_GamePoints = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

void StudentWorld::SetGamePoints(int points)
{
    cerr << "before the game points were " << m_GamePoints << endl;
    m_GamePoints += points;
    cerr << "now the game points are: " << m_GamePoints << endl;
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
    cerr << "added cabbage to the vec" <<endl;
}

int StudentWorld::init()
{
    //create a NachenBlaster
    NachenBlaster *nachenblasterP = new NachenBlaster (this);
    gameObjectVector.push_back(nachenblasterP);
    
    Smallgon *smallgonP = new Smallgon (IID_SMALLGON, 0, 128, 0 , (randDouble(.05, .50)), 3, this);
    gameObjectVector.push_back(smallgonP);
    //set member variable equal to the item in the Vector that is the NB
    m_NachenBlaster = nachenblasterP;
    
    //create 30 stars
    /*for (int i =0; i <30; i ++)
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
*/
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //PUT BACK IN
    //add more objects?
   // ProbabilityaddNewObjects();
    cerr << "let's move all the objects! " << endl << endl;
    cerr << "the object vector size at the beginning of move is: " << gameObjectVector.size() << endl;

    for (int i = 0; i < gameObjectVector.size(); i++)
    {
        
        cerr << "about to move object number " << i << endl;
        if (gameObjectVector.size() > 0 && gameObjectVector[i]->getWorld() != nullptr)
        {
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
    cerr << "at the beginning, remove dead size is : " << gameObjectVector.size() << endl;;
    vector<Actor*>::iterator vi = gameObjectVector.begin();
    int counter = 0;
    while (vi!= gameObjectVector.end())
    {
        cerr << "on object " << counter << endl;
        if (*vi != nullptr)
        {
            cerr << "going to check if it's alive" <<endl;
            if ((*vi)->AliveStatus() == false)
            {
                cerr << "object " << counter << " is dead "<< endl;
                delete *vi;
                vi = gameObjectVector.erase(vi);
                counter --;
            
                cerr << "the size of objectVector after deleting this object is now: " << gameObjectVector.size() << endl;
            }
        }
                cerr << "okay, now go to the next one" << endl << endl;
        vi++;
        counter = counter + 1;

    }
    
    cerr << "at the end of all removes, the vector size is : " << gameObjectVector.size() <<endl;
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
