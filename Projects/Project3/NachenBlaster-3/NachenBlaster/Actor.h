#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

////////////////////////////////IMPLEMENTATION FOR ALLOBJECTS CLASS////////////////////////////////

class AllObjects: public GraphObject
{
public:
    AllObjects(int imageID, double startX, double startY, int dir, double size, int depth);
    virtual void doSomething()
    {
    };
    
    virtual bool CheckIfAlive()
    {
        return true;
    };

};
////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
class Projectiles: public AllObjects
{
public:
    Projectiles(int imageID, double startX, double startY, int dir, double size, int depth);
};

////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
class Cabbage: public Projectiles
{
public:
    Cabbage(int imageID, double startX, double startY, int dir, double size, int depth);
    void doSomething();
};

////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////

class Star : public AllObjects
{
public:
    //constructor
    Star(int imageID, double startX, double startY, int dir, double size, int depth);
    
    //destructor
    virtual ~Star ();
    
    //DoSomething Function
    virtual void doSomething();
    
    //checks if the star has gone off the screen to the left
    virtual bool CheckIfAlive();
};
#endif // ACTOR_H_
