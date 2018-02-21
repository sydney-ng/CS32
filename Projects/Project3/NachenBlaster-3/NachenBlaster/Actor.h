#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

////////////////////////////////IMPLEMENTATION FOR ALLOBJECTS CLASS////////////////////////////////

class AllObjects: public GraphObject
{
public:
    AllObjects(int imageID, double startX, double startY, int dir, double size, int depth);

    void doSomething();

    virtual void somethingBody()
    {
    };

    virtual bool CheckIfAlive()
    {
        return true;
    };

};

////////////////////////////////IMPLEMENTATION FOR SHIPS CLASS////////////////////////////////
class Ships: public AllObjects
{
public:
    Ships(int imageID, double startX, double startY, int dir, double size, int depth);

};

////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS////////////////////////////////
class NachenBlaster: public Ships
{
public:
    NachenBlaster(int imageID, double startX, double startY, int dir, double size, int depth);

    virtual bool CheckIfAlive();
    
private:
    int m_HitPoints;
    int m_CabbageEnergyPoints;
};
/*////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
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
    virtual void somethingBody();
    bool CheckIfAlive();
}; */

////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////

class Star : public AllObjects
{
public:
    //constructor
    Star(int imageID, double startX, double startY, int dir, double size, int depth);
    
    //destructor
    virtual ~Star ();
    
    //DoSomething Function
    virtual void somethingBody();
    
    //checks if the star has gone off the screen to the left
    virtual bool CheckIfAlive();
};
#endif // ACTOR_H_
