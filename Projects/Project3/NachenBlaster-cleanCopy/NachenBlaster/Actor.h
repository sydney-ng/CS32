#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

//REMOVE THESE BOTTOM TWO
#include <iostream>
using namespace std;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

////////////////////////////////IMPLEMENTATION FOR ALLOBJECTS CLASS////////////////////////////////
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~Actor();
    virtual void doSomething();
    virtual void somethingBody()
    {
    };
    virtual bool CheckIfAlive();
    bool AliveStatus()
    {
        cerr << "the alive status () is " << m_isAlive << endl;
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
    ~Ships();
    void setHitPoints(int hits);
    void UpdateHitPoints (int hits);
    int getHitPoints();
    bool CheckIfAlive();
    virtual void doSomething();
    virtual void moveShip();

private:
    int m_HitPoints;
};

////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS////////////////////////////////
class NachenBlaster: public Ships
{
public:
    NachenBlaster(StudentWorld *world);
    virtual ~NachenBlaster();
    virtual void moveShip();
    void SufferDamage();
private:
    //int m_HitPoints;
    int m_CabbageEnergyPoints;
};

/////////////////////////////////IMPLEMENTATION FOR ALIENS CLASS////////////////////////////////
class Aliens: public Ships
{
public:
    Aliens(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~Aliens();
    int getFlightPlan();
    double getTravelSpeed();
    virtual void moveShip();
    bool CollisionOccurred();
    double CalculateEcludianDistance(double x1, double y1, double x2, double y2);
    void PostCollisionActions();

private:
    int m_flightPlan;
    double m_TravelSpeed;
};

/////////////////////////////////IMPLEMENTATION FOR SMALLGON CLASS////////////////////////////////
class Smallgon: public Aliens
{
public:
    Smallgon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~Smallgon();
    virtual void somethingBody();
    //private:
  //  int m_flightPlan;
   // double m_TravelSpeed;*/
};

////////////////////////////////IMPLEMENTATION FOR SMOREGON CLASS/////////////////////////////

class Smoregon: public Aliens
{
public:
    Smoregon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    //virtual void somethingBody();
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
    virtual bool CheckIfAlive();
};

////////////////////////////////IMPLEMENTATION FOR TURNIP CLASS////////////////////////////////
class Turnip: public Projectiles
{
public:
    Turnip(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    virtual ~Turnip();
    virtual void somethingBody();
};
////////////////////////////////IMPLEMENTATION FOR FLATULAN TORPEDO CLASS//////////////////////////////////////
class F_Torpedo: public Projectiles
{
public:
    F_Torpedo(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, int owner);
    virtual ~F_Torpedo();
    virtual void somethingBody();
private:
    int m_owner;
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
    //virtual bool CheckIfAlive();
};
////////////////////////////////IMPLEMENTATION FOR EXPLOSION CLASS////////////////////////////////
class Explosion : public Actor
{
public:
    Explosion(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~Explosion();
    virtual void somethingBody();
    virtual bool CheckIfAlive();
private:
    int m_AliveTicksLeft;
};

#endif // ACTOR_H_
