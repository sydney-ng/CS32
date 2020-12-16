//
//  Game.h
//  Project1
//
//  Created by Super on 1/14/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "City.h"
int decodeDirection(char dir);

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};


#endif /* Game_h */
