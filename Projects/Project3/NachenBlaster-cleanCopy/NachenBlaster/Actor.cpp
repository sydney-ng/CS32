#include "Actor.h"
#include "StudentWorld.h"

//REMOVE
#include <iostream>
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////IMPLEMENTATION FOR ALLOBJECTS CLASS////////////////////////////////
Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:GraphObject(imageID, startX, startY, dir, size, depth), m_SudentworldPointer(world)
{
    m_isAlive = true;
}

void Actor::doSomething()
{
    if (CheckIfAlive() 	== false)
    {
        setDead();
        return;
    }
    cerr << "In doSomething of Base Class! "<< endl;
    somethingBody();
}

Actor::~Actor()
{
}

bool Actor::CheckIfAlive()
{
    int x_coord = getX();
    if (x_coord > 0 && x_coord < VIEW_WIDTH)
    {
        return true;
    }
    return false;
};

StudentWorld* Actor::getWorld()
{
    return m_SudentworldPointer;
}

void Actor::whatWorld(StudentWorld* world)
{
    m_SudentworldPointer = world;
}

////////////////////////////////IMPLEMENTATION FOR SHIPS CLASS////////////////////////////////

Ships::Ships(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Actor(imageID, startX, startY, dir, size, depth, world)
{
}

////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS////////////////////////////////
NachenBlaster::NachenBlaster(StudentWorld *world)
:Ships(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world)
{
    cerr << "in nachenblaster constructor " << endl;
    
    m_HitPoints = 50;
    m_CabbageEnergyPoints = 30;
}

void NachenBlaster::somethingBody()
{
    cerr << "IN THE BODY OF NACHENBLASTER" << endl;
    int ch;
    if (getWorld()->getKey(ch))
    {
    
        if (ch == KEY_PRESS_LEFT)
        {
            int newX = getX()-6;
            if (newX > 0)
            {
                moveTo(newX, getY());
            }
        }
        else if (ch == KEY_PRESS_RIGHT)
        {
            int newX = getX()+6;
            if (newX < VIEW_WIDTH)
            {
                moveTo(newX, getY());
            }
        }
        else if (ch == KEY_PRESS_UP)
        {
            int newY = getY()+6;
            if (newY < VIEW_HEIGHT)
            {
                moveTo(getX(), newY);
            }
        }
        else if (ch == KEY_PRESS_DOWN)
        {
            int newY = getY()-6;
            if (newY > 0)
            {
                moveTo(getX(), newY);
            }
        }
        else if (ch == KEY_PRESS_SPACE)
        {
            if (m_CabbageEnergyPoints > 5 || m_CabbageEnergyPoints == 5)
            {
                //fire a cabbage
                //reduce cabbage points by 5
                m_CabbageEnergyPoints -= 5; 
            }
        }
    }
}

NachenBlaster::~NachenBlaster()
{
    cerr << "deconstructing NachenBlaster"<< endl;
}

bool NachenBlaster:: CheckIfAlive()
{
    //make sure the hit points are above 0
    if (m_HitPoints <= 0)
    {
        return false;
    }
    
    return true;
}


/////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
Projectiles::Projectiles(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Actor(imageID, startX, startY, dir, size, depth, world)
{
}
Projectiles::~Projectiles ()
{
}

////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
Cabbage::Cabbage(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Projectiles(IID_CABBAGE, startX, startY, 0, .5, 1, world)
{
}

Cabbage::~Cabbage()
{
    cerr << "deconstructing a cabbage"; 
}

void Cabbage::somethingBody()
{
    cerr << " in something fx() of cabbage" << endl;

    //move 8 px to the right
    moveTo (getX() + 8, getY());
    setDirection(20);
}

bool Cabbage::CheckIfAlive()
{
    cerr << " in checkIAlive fx() of cabbage" << endl;
    //if it's not alive, return false immediately
    if (getX() > VIEW_WIDTH || getX() == VIEW_WIDTH)
    {
        cerr << "it's dead" << endl;
        return false;
    }
    return true;
}

////////////////////////////////IMPLEMENTATION FOR TURNIP CLASS//////////////////////////////////////
Turnip::Turnip(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Projectiles(IID_TURNIP, startX, startY, 0, .5, 1, world)
{
}

Turnip::~Turnip()
{
    cerr << "deconstructing a turnip";
}
void Turnip::somethingBody()
{
    moveTo(getX()-6, getY());
    setDirection(20);
}


////////////////////////////////IMPLEMENTATION FOR FLATULAN TORPEDO CLASS//////////////////////////////////////
F_Torpedo::F_Torpedo(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, int owner)
:Projectiles(IID_TURNIP, startX, startY, 0, .5, 1, world)
{
    m_owner = owner;
}

F_Torpedo::~F_Torpedo()
{
    cerr << "deconstructing a turnip";
}

void F_Torpedo::somethingBody()
{
    if (m_owner == IID_NACHENBLASTER)
    {
        //move right by 8 pxl
        moveTo(getX()+8, getY());
    }
    
    if (m_owner == IID_SNAGGLEGON)
    {
        //move left by 8 pxl
        moveTo(getX()-8, getY());
    }
}
///////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////////
Star::Star(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Actor(imageID, startX, startY, 0, .5, 1, world)
{
}

Star::~Star ()
{
    cerr << "deconstructing a Star" << endl;
}
void Star::somethingBody()
{
    cerr << "here in Star's somethingBody!" << endl;
    
    //check if it's on the screen
    moveTo(getX()-1, getY());
}
