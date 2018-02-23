#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

////////////////////////////////IMPLEMENTATION FOR ALLOBJECTS CLASS////////////////////////////////
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);

    ~Actor();
    
    void doSomething();

    virtual void somethingBody()
    {
    };

    virtual bool CheckIfAlive()
    {
        return true;
    };
    
    bool AliveStatus()
    {
        return m_isAlive;
    }
    
    void setDead()
    {
        m_isAlive = false;
    }

    
    StudentWorld* getWorld();
    void whatWorld(StudentWorld* world);
    
private:
    bool m_isAlive;
    StudentWorld *m_SudentworldPointer;

};

////////////////////////////////IMPLEMENTATION FOR SHIPS CLASS////////////////////////////////
class Ships: public Actor
{
public:
    Ships(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);

};

////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS////////////////////////////////
class NachenBlaster: public Ships
{
public:
    NachenBlaster(StudentWorld *world);
    virtual ~NachenBlaster();
    virtual bool CheckIfAlive();
    virtual void somethingBody();
private:
    int m_HitPoints;
    int m_CabbageEnergyPoints;
};
/////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
class Projectiles: public Actor
{
public:
    Projectiles(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    virtual ~Projectiles();
};

////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
class Cabbage: public Projectiles
{
public:
    Cabbage(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    virtual ~Cabbage();
    virtual void somethingBody();
    bool CheckIfAlive();
};

////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////

class Star : public Actor
{
public:
    //constructor
    Star(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    
    //destructor
    virtual ~Star ();
    
    //DoSomething Function
    virtual void somethingBody();
    
    //checks if the star has gone off the screen to the left
    virtual bool CheckIfAlive();
};
#endif // ACTOR_H_
