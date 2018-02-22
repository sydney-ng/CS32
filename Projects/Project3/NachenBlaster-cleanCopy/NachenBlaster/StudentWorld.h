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
    virtual void cleanUp();
    void removeDead();
    //every tick, calculate the probability of a new object being created & execute
    double randDouble(double min, double max);
    //get the probability of each of the new objects
    void addNewObjects();
private:
    std::vector<Actor*> gameObjectVector;
    //NachenBlaster * m_NachenBlaster;
};

#endif // STUDENTWORLD_H_
