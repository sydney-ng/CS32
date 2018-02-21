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
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    //every tick, calculate the probability of a new object being created & execute
    double randDouble(double min, double max);
    void addNewObjects();
private:
    std::vector<AllObjects*> gameObjectVector;
    
};

#endif // STUDENTWORLD_H_
