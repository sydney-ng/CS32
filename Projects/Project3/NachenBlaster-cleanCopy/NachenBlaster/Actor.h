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
    virtual bool CheckIfOffScreen();
    
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
    void SufferDamage(int ID);
    
private:
    int m_HitPoints;
};

////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS////////////////////////////////
class NachenBlaster: public Ships
{
public:
    NachenBlaster(StudentWorld *world);
    virtual ~NachenBlaster();
    virtual void somethingBody(); 
    //CHECK IF THIS WORKS? NO PARAMETERS
    //virtual void SufferDamage(int ID);
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
    virtual void somethingBody();
    bool CollisionOccurred(int otherXCoord, int otherYCoord, int otherRadius);
    //shows how far 
    double CalculateEcludianDistance(double x1, double y1, double x2, double y2);
    //everything of collision for NB
    void PostNBCollisionActions();
    //decrements hit points depending on what hit it
    //virtual void SufferDamage(int ID);
    //checks if NB & projectile has collieded w/ alien
    void CheckForAllCollisions ();
    //everything of collision for projectiles
    void PostAlienProjectileCollisionActions(int projectileID);
    //checks if you need a new FP
    bool CheckForNewFlightPath();
    //reorients your direction if you need new FP
    void NewFlightPathActions();
    //checks if NB in range for a new goodie to be dropped
    bool CheckForNewGoodie();
    //drops the goodie -> specific to each alien (PV)
    virtual void NewGoodieActions();
    //tells the alien where to move 
    void MoveInDirection();
private:
    int m_flightPlan;
    int m_flightDirection;
    double m_TravelSpeed;
};

/////////////////////////////////IMPLEMENTATION FOR SMALLGON CLASS////////////////////////////////
class Smallgon: public Aliens
{
public:
    Smallgon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~Smallgon();
    //virtual void somethingBody();
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
    Projectiles(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, char d_Name);
    virtual ~Projectiles();
    virtual int getDamagePoints();
    //allows derived classes to set damageName
    void setDamageName(char passedIn_DName);
private:
    char m_DamageName;
};

////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
class Cabbage: public Projectiles
{
public:
    Cabbage(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, char d_Name);
    virtual ~Cabbage();
    virtual void somethingBody();
    virtual bool CheckIfOffScreen();
};

////////////////////////////////IMPLEMENTATION FOR TURNIP CLASS////////////////////////////////
class Turnip: public Projectiles
{
public:
    Turnip(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, char d_Name);
    virtual ~Turnip();
    virtual void somethingBody();
private:
};
////////////////////////////////IMPLEMENTATION FOR FLATULAN TORPEDO CLASS//////////////////////////////////////
class F_Torpedo: public Projectiles
{
public:
    F_Torpedo(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, int owner, char d_Name);
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
    virtual bool CheckIfOffScreen();
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
////////////////////////////////IMPLEMENTATION FOR EXTRALIFE CLASS////////////////////////////////

class ExtraLife: public Goodies
{
public:
    ExtraLife(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~ExtraLife();
};

////////////////////////////////IMPLEMENTATION FOR REPAIRGOODIE CLASS////////////////////////////////
class RepairGoodie: public Goodies
{
    
public:
    RepairGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~RepairGoodie();
    
};

////////////////////////////////IMPLEMENTATION FOR FT_Goodie CLASS////////////////////////////////
class FT_Goodie: public Goodies
{
    
public:
    FT_Goodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~FT_Goodie();
    
};
#endif // ACTOR_H_
