#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
//added
#include "Actor.h"
//#include <cmath>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    
    //basically destructor
    virtual void cleanUp();
    
    //call after the doSomething to check what to remove
    void removeDead();
    
    //every tick, calculate the probability of a new object being created & execute
    double randDouble(double min, double max);
    
    //get the probability of each of the new objects
    void ProbabilityaddNewObjects();
    
    //add a new object to the vector
    void AddObjectToVector(Actor * ActorP);
    
    //returns current level
    int getCurrentLevel();
    
    NachenBlaster* getNachenblasterPointer();
    
    std::vector<Actor*> getVector();
private:
    std::vector<Actor*> gameObjectVector;
    NachenBlaster * m_NachenBlaster;
    int m_GamePoints;
    int m_CurrentLevel;
    std::vector<Actor*>* m_vectorPointer;
};

#endif // STUDENTWORLD_H_
