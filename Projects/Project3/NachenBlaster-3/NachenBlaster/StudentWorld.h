#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
//added
#include "GraphObject.h"
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();

private:
    std::vector<GraphObject*> AllObjects;
    
};

#endif // STUDENTWORLD_H_
