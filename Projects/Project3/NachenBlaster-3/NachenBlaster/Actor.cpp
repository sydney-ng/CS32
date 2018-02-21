#include "Actor.h"
#include "StudentWorld.h"

//REMOVE
#include <iostream>
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////IMPLEMENTATION FOR ALLOBJECTS CLASS////////////////////////////////
AllObjects::AllObjects(int imageID, double startX, double startY, int dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth)
{
}

void AllObjects::doSomething()
{
    /*if (CheckIfAlive() == false)
    {
        return;
    }*/
    
    somethingBody();
    
}


////////////////////////////////IMPLEMENTATION FOR SHIPS CLASS////////////////////////////////

Ships::Ships(int imageID, double startX, double startY, int dir, double size, int depth)
:AllObjects(imageID, startX, startY, dir, size, depth)
{
}

////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS////////////////////////////////
NachenBlaster::NachenBlaster(int imageID, double startX, double startY, int dir, double size, int depth)
:Ships(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0)
{
    m_HitPoints = 50;
    m_CabbageEnergyPoints = 30;
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


/*////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
Projectiles::Projectiles(int imageID, double startX, double startY, int dir, double size, int depth)
:AllObjects(imageID, startX, startY, dir, size, depth)
{
    
}
////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
Cabbage::Cabbage(int imageID, double startX, double startY, int dir, double size, int depth)
:Projectiles(IID_CABBAGE, startX, startY, 0, .5, 1)
{
    
}

void Cabbage::somethingBody()
{
    //if it's not alive, return false immediately
    if (CheckIfAlive() == false)
    {
        return;
    }
}

bool Cabbage::CheckIfAlive()
{
    if (getX() > VIEW_WIDTH || getX() == VIEW_WIDTH)
    {
        return false;
    }
    return true;
} */
///////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////////
Star::Star(int imageID, double startX, double startY, int dir, double size, int depth)
: AllObjects(imageID, startX, startY, dir, size, depth)
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
    //if (CheckIfAlive() == true)
    //{
        moveTo(getX()-1, getY());
    //}
    //it's off the screen
}

bool Star:: CheckIfAlive()
{
    int x_coord = getX();
    if (x_coord > 0)
    {
        return true;
    }
    return false;
}

