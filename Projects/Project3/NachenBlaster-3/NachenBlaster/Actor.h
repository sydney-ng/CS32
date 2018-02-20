#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Star : public GraphObject
{
public:
    //constructor
    Star(int imageID, double startX, double startY, int dir, double size, int depth);
    
    //destructor
    virtual ~Star ();
    
    //DoSomething Function
    virtual void DoSomething();
    
    //checks if the star has gone off the screen to the left
    virtual bool CheckIfAlive();
};
#endif // ACTOR_H_
