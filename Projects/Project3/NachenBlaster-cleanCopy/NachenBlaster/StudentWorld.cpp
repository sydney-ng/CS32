#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
//remove?
#include <iostream>
using namespace std;

//LOOK INTO STAR SIZES
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
//    m_numShipsDestroyed = 0;
}

std::vector<Actor*> StudentWorld::getVector()
{
    return gameObjectVector;
}

void StudentWorld:: incNumShipsDestroyed()
{
    cerr << "before incNumShipsDestroyed(), the num of ships you've destroyed is: " << m_numShipsDestroyed << endl;
    m_numShipsDestroyed++;
    m_numOnScreenShips--;
    cerr << "after incNumShipsDestroyed(), the num of ships you've destroyed is: " << m_numShipsDestroyed << endl;

}

void StudentWorld::decNumOnScreenShips()
{
    m_numOnScreenShips--;
    cerr << "num of screen on ships is now: " << m_numOnScreenShips << endl;
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
    
    //add ships?
    if (CheckForAddingShips() == true)
    {
        AddShips();
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

bool StudentWorld::CheckForAddingShips()
{

    int N = numShipsLefToKill();
    
    //calculate the formula for the max number of ships that should be on this level, formula: M = 4 + (.5 * current_level_number)
    int M = 4 + (.5 * getLevel());
    
    //calculate min between N & M
    int minNum;
    if (M < N)
    {
        minNum = M;
    }
    else
    {
        minNum = N;
    }
    
    //compare it to the number of onScreenShips
    if (m_numOnScreenShips < minNum)
    {
        return true;
    }
    return false;
}

int StudentWorld:: numShipsLefToKill()
{
    //get the num of ships you've destroyed so far
    int D = m_numShipsDestroyed;
    
    //calculate the num of ships needed to pass the level, formula: T = 6+(4*n)
    int T = 6 + (4 * getLevel());
    
    //calculate the number of remaining ships needed to
    int N = T - D;
    
    return N;
}

void StudentWorld::AddShips()
{
    int S1 = 60;
    int S2 = 20 + (getLevel() * 5);
    int S3 = 5 + (getLevel() * 10);
    int S = S1 + S2 + S3;
    
    int probSmallgon = randInt(S1, S);
    int probSmoregon = randInt(S2, S);
    int probSnagglegon = randInt(S3, S);
    
    if (probSmallgon < S1 +1)
    {
        Smallgon *smallgonP = new Smallgon (IID_SMALLGON, VIEW_WIDTH-1, randInt(0, VIEW_WIDTH-1), 0 , 1.5, 1, this);
        gameObjectVector.push_back(smallgonP);
        m_numOnScreenShips++;
    }
    if (probSmoregon < S2 +1)
    {
        Smoregon *smoregonP = new Smoregon (IID_SMALLGON, VIEW_WIDTH-1, randInt(0, VIEW_WIDTH-1), 0 , 1.5, 1, this);
        gameObjectVector.push_back(smoregonP);
        m_numOnScreenShips++;
    }
    if (probSnagglegon < S3 +1)
    {
        Snagglegon * SnagglegonP = new Snagglegon (IID_SNAGGLEGON, VIEW_WIDTH-1, randInt(0, VIEW_WIDTH-1), 0, 1.5, 1, this);
        gameObjectVector.push_back(SnagglegonP);
        m_numOnScreenShips++;
    }
}

int StudentWorld:: CalculateGameStatus()
{
    //if you have died, then return get dead,
    if (m_NBDead == true)
    {
        //INDICATE THAT YOU'VE DIED
        return GWSTATUS_PLAYER_DIED;
    }
    //if you're alive and you have killed the right num of aliens, new level
    else if (numShipsLefToKill() == 0 || numShipsLefToKill() < 0)
    {
        return GWSTATUS_FINISHED_LEVEL;
    }
    else
    {
        return GWSTATUS_CONTINUE_GAME;
    }
    //otherwise, just return CONT
}

void StudentWorld::setNBDead()
{
    m_NBDead = true;
    
}


int StudentWorld::init()
{
    m_numShipsDestroyed = 0;
    m_numOnScreenShips = 0;

//
//    Snagglegon * SnagglegonP = new Snagglegon (IID_SNAGGLEGON, VIEW_WIDTH-1, randInt(0, VIEW_WIDTH-1), 0, .5, 1, this);
//    gameObjectVector.push_back(SnagglegonP);
//    m_numOnScreenShips++;

    //create a NachenBlaster
    NachenBlaster *nachenblasterP = new NachenBlaster (this);
    gameObjectVector.push_back(nachenblasterP);
    
    //set member variable equal to the item in the Vector that is the NB
    m_NachenBlaster = nachenblasterP;
    
    m_NBDead = false;

    //give NB full points
    m_NachenBlaster->setHitPoints(50);
    m_NachenBlaster->setCabbagePoints(30);
    m_NachenBlaster->setNumTorps(0);
    
    //create 30 stars
    for (int i =0; i <30; i ++)
    {
        
        Star *starP = new Star (IID_STAR, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1), 0 , (randDouble(.05, .50)), 3, this);
        gameObjectVector.push_back(starP);
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //add more objects?
    ProbabilityaddNewObjects();
    
    //let everything move
    cerr << "in move, we will now iterate to: " << gameObjectVector.size() << endl;
    for (int i = 0; i < gameObjectVector.size(); i++)
        {
            if (gameObjectVector.size() > 0 && gameObjectVector[i] != nullptr)
            {
                cerr << "about to move object number " << i << endl;
                gameObjectVector[i]->doSomething();
                if (m_NBDead == true)
                {
                    //INDICATE THAT YOU'VE DIED
                    return GWSTATUS_PLAYER_DIED;
                }
                else if (numShipsLefToKill() == 0 || numShipsLefToKill() < 0)
                {
                    cleanUp();
                    incLives();
                    playSound(SOUND_FINISHED_LEVEL);
                    return GWSTATUS_FINISHED_LEVEL;
                }
            }
            cerr << "finished the move for object number " << i << endl;
        }
    
    removeDead();
    //UPDATE THE STATUS BAR AT THE TOP
    m_NachenBlaster->StatusBarBody();
    return GWSTATUS_CONTINUE_GAME;
    
    //determine if to end level, end game, cont level
    //if (CalculateGameStatus() == GWSTATUS_PLAYER_WON
}

void StudentWorld::removeDead()
{
    vector<Actor*>::iterator vi = gameObjectVector.begin();
    
    while (vi != gameObjectVector.end())
    {
        cerr << "is vec empty? " << gameObjectVector.empty() << endl;
        if (gameObjectVector.empty () == false)
        {
            if (*vi != nullptr)
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
