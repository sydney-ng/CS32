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
    //calls CalculateED to check if there's a collision
    bool CollisionOccurred(int otherXCoord, int otherYCoord, int otherRadius);
    //shows how far
    double CalculateEcludianDistance(double x1, double y1, double x2, double y2);
    //checks if NB has collieded w/ alien
    bool CheckForNBCollisions();
    bool AliveStatus()
    {
        cerr << "the alive status () is " << m_isAlive << endl;
        return m_isAlive;
    }
    virtual void setDead()
    {
        m_isAlive = false;
    }
    StudentWorld* getWorld();
    void whatWorld(StudentWorld* world);
   
    int getImageID();
    bool getIsProjectile();
    void setImageID(int ID);
    void setIsProjectile (bool projectileBool);
    virtual void setDamageVal(int val);
    int getDamageValue();
    //bool RandIntTrue(int num_Min, int num_Max); <- implement if time
    //everything of collision for NB
    virtual void PostNBCollisionActions(){};
    void setLevelOver();
    void setStatusBar(size_t hitNum, size_t cabbNum, size_t torpNum);
    

private:
    int m_ImageID;
    int m_DamageValue;
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
    int getHitPoints();
    bool CheckIfAlive();
    virtual void doSomething();
    void SufferDamage(int ID);
    //checks if projectile has collided w/ alien
    void CheckForProjCollisions();
    //if there's a projectile collision it will do things
    virtual void PostProjectileCollisionActions() = 0;
    virtual bool CheckProperSide (int other, int currShip) = 0;
    //adds integer to hit points of object
    void UpdateHitPoints (int hits);
    
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
    void KeyPressMovement();
    virtual void PostProjectileCollisionActions();
    virtual bool CheckProperSide (int other, int currShip);
    //add a certain number of Torpedos
    void UpdateNumTorps (int numTorps);
    

    //CHECK IF THIS WORKS? NO PARAMETERS
    //virtual void SufferDamage(int ID);
private:
    //int m_HitPoints;
    int m_CabbageEnergyPoints;
    int m_FTorps; 
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
    //decrements hit points depending on what hit it
    //virtual void SufferDamage(int ID);
    //everything of collision for projectiles
    virtual void PostProjectileCollisionActions();
    //checks if you need a new FP - snaggle diff
    virtual bool CheckForNewFlightPath();
    //reorients your direction if you need new FP
    virtual void NewFlightPathActions();
    //checks if NB in range for an attack
    bool CheckForAttacking();
    //drops the goodie -> specific to each alien (Snaggle diff)
    virtual bool FireProjectile();
    //tells the alien where to move 
    void MoveInDirection();
    //checks if the projectile is coming from an alien or NB
    bool CheckProperSide (int other, int currShip);
    //if the alien is dead, kill it, increase points & new explosion, sounds 
    virtual void AlienDeadActions();
    //fire a proj possibly & ram possibly?
    virtual bool AttackNB();
    //takes care of CheckForFiringProjectile & FireProjectile
    bool allShootingProjectileStuff();
    //set Travel Direction
    void setFlightDirection(int dir);
    //set FlightPlan length
    void setFlightPlan (int len);
    //set m_TravelSpeed
    void setTravelSpeed (double speed);
    //calls all of the functions when an alien dies
    virtual void AllAlienDeathStuff();
    //not pv because it's smallgons dont have it
    virtual void DropGoodie (){};
    //everything of collision for NB
    virtual void PostNBCollisionActions();

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
    virtual ~Smallgon();
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
    virtual ~Smoregon();
    virtual bool AttackNB();
    void PossiblyCharge();
    virtual void AllAlienDeathStuff();
    virtual void DropGoodie ();

    //virtual void somethingBody();
};

////////////////////////////////IMPLEMENTATION FOR SNAGGLEGON CLASS/////////////////////////////

class Snagglegon: public Aliens
{
public:
    Snagglegon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    virtual ~Snagglegon();
    //checks if within coords
    virtual bool AttackNB();
    //drops the goodie -> specific to each alien (Snaggle diff)
    virtual bool FireProjectile();
    //checks if it's hit top or bottom
    virtual bool CheckForNewFlightPath();
    //reorients your direction if you need new FP
    virtual void NewFlightPathActions();
    //takes care of everything if a snagglegon dies
    virtual void AllAlienDeathStuff();
    //if the alien is dead, kill it, increase points & new explosion, sounds
    virtual void AlienDeadActions();
    virtual void DropGoodie ();
    
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
    virtual bool CheckIfOffScreen();
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
    //virtual int getDamagePoints();
private:
    int m_Owner;
};
////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////

class Star : public Actor
{
public:
    //constructor
    Star(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    
    //destructor
    virtual ~Star ();
    
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
    virtual void PostNBCollisionActions();
    virtual void somethingBody();
    //PV bc all goodies have a power
    virtual void goodiePowers() = 0;
    ~Goodies();
    
};
////////////////////////////////IMPLEMENTATION FOR EXTRALIFE CLASS////////////////////////////////

class ExtraLife: public Goodies
{
public:
    ExtraLife(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    virtual void goodiePowers();
    ~ExtraLife();
};

////////////////////////////////IMPLEMENTATION FOR REPAIRGOODIE CLASS////////////////////////////////
class RepairGoodie: public Goodies
{
    
public:
    RepairGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~RepairGoodie();
    virtual void goodiePowers();
    
};

////////////////////////////////IMPLEMENTATION FOR FT_Goodie CLASS////////////////////////////////
class FT_Goodie: public Goodies
{
    
public:
    FT_Goodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world);
    ~FT_Goodie();
    virtual void goodiePowers();
    
};
#endif // ACTOR_H_
