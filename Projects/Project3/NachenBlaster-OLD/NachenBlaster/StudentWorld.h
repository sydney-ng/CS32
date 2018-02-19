#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

//ARE YOU SUPPOSED TO DO THIS?
//class Star;
#include "Actor.h"

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();

private:
    vector<GraphObject*> AllObjects;
};

#endif // STUDENTWORLD_H_
