// gas.cpp

#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include "globals.h"
#include "City.h"
#include "Player.h"
#include "Game.h"
using namespace std;

class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Flatulan declaration.

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}
