#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Star::Star(int imageID, double startX, double startY, int dir, double size, int depth)
: GraphObject(IID_STAR, startX, startY, 0, randInt(.05, .50), 3)
{
}
