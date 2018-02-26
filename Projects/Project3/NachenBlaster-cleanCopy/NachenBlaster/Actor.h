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
   
    int getImageID();
    bool getIsProjectile();
    void setImageID(int ID);
    void setIsProjectile (bool projectileBool);
    
private:
    int m_ImageID;
    bool m_isAlive;
    bool m_isProjectile;
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
    virtual void SufferDamage(int ID) = 0;
    
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
    //CHECK IF THIS WORKS? NO PARAMETERS
    virtual void SufferDamage(int ID);
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
    bool CollisionOccurred(int otherXCoord, int otherYCoord, int otherRadius);
    double CalculateEcludianDistance(double x1, double y1, double x2, double y2);
    void PostCollisionActions();
    virtual void SufferDamage(int ID);

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
    virtual int getDamagePoints();
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
    virtual int getDamagePoints();

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
    void explodeExplosion();

private:
    int m_AliveTicksLeft;
};

////////////////////////////////IMPLEMENTATION FOR exraLifeGoodie CLASS////////////////////////////////
class Goodies: public Actor
{
    
public:
    Goodies(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~Goodies();
    
};

class ExtraLife: public Goodies
{
public:
    ExtraLife(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~ExtraLife();
};

#endif // ACTOR_H_
