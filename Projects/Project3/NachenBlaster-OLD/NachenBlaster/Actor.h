#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Star: public GraphObject
{
public:
        Star(int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 3);

};
#endif // ACTOR_H_
