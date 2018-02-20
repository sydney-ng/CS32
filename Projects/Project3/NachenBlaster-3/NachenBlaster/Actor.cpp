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

////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
Projectiles::Projectiles(int imageID, double startX, double startY, int dir, double size, int depth)
:AllObjects(imageID, startX, startY, dir, size, depth)
{
    
}
////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
Cabbage::Cabbage(int imageID, double startX, double startY, int dir, double size, int depth)
:Projectiles(IID_CABBAGE, startX, startY, 0, .5, 1)
{
    
}

void Cabbage::doSomething()
{
    cerr << "Cabbage's do something!" << endl;
}
///////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////////
Star::Star(int imageID, double startX, double startY, int dir, double size, int depth)
: AllObjects(IID_STAR, startX, startY, 0, randInt(.05, .50), 3)
{
}

Star::~Star ()
{
    cerr << "deconstructing a Star" << endl;
}
void Star::doSomething()
{
    cerr << "here in Star's DoSomething!" << endl;
        //check if it's on the screen
    if (CheckIfAlive() == true)
    {
        moveTo(getX()-1, getY());
    }
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

