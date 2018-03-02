#include "Actor.h"
#include "StudentWorld.h"

//REMOVE
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

////////////////////////////////IMPLEMENTATION FOR ALLOBJECTS CLASS////////////////////////////////
Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:GraphObject(imageID, startX, startY, dir, size, depth), m_SudentworldPointer(world)
{
    m_isAlive = true;
    m_ImageID = imageID;
    m_isProjectile = false;
    whatWorld(world); 
    cerr << "created object using Actor Constructor " << endl;
}

void Actor::doSomething()
{
    //1. first make sure it's alive before you do anything
    if (m_isAlive == false)
    {
        return;
    }
    
    //2. make sure it's on the screen
    if (CheckIfOffScreen() 	== false)
    {
        setDead();
        return;
    }
    somethingBody();
}
void Actor::setImageID(int ID)
{
    m_ImageID = ID;
}

int Actor::getDamageValue()
{
    return m_DamageValue;
}

void Actor::setIsProjectile (bool projectileBool)
{
    m_isProjectile = projectileBool;

}

void Actor::setDamageVal(int val)
{
    m_DamageValue = val;
}

int Actor::getImageID()
{
    return m_ImageID;
}

bool Actor::getIsProjectile()
{
    return m_isProjectile;
}

Actor::~Actor()
{
}

bool Actor::CheckIfOffScreen()
{
    int x_coord = getX();
    if (x_coord > -1 && x_coord < VIEW_WIDTH)
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

bool Actor::CheckForNBCollisions ()
{
    cerr << "we will check if there was a collision " << endl;
    
    //get coordinates of the NB
    int NB_xCoord = getWorld()->getNachenblasterPointer()->getX();
    int NB_yCoord = getWorld()->getNachenblasterPointer()->getY();
    double NB_radius = getWorld()->getNachenblasterPointer()->getRadius();
    
    //check if it collided with NB
    if (CollisionOccurred(NB_xCoord, NB_yCoord, NB_radius)==true)
    {
        return true;
    }
    return false;
}

bool Actor::CollisionOccurred(int otherXCoord, int otherYCoord, int otherRadius)
{
    //calculate both sides of the equation
    double LH_Side = CalculateEcludianDistance(getX(), getY(), otherXCoord, otherYCoord);
    double RH_Side = 0.75 * (getRadius() + otherRadius);
    
    if (LH_Side < RH_Side)
    {
        //there was a collision
        return true;
    }
    return false;
}

double Actor::CalculateEcludianDistance(double x1, double y1, double x2, double y2)
{
    double distance_between;
    double x_dist = x1 - x2;
    double y_dist = y1 - y2;
    
    distance_between = pow(x_dist,2)+pow(y_dist,2);
    distance_between = sqrt(distance_between);
    
    return distance_between;
}

void Actor::setLevelOver()
{
    //decrement the number of NB lives by 1
    m_SudentworldPointer->decLives();
    int temp = m_SudentworldPointer->getLives() - 0;
    //if ( temp == 0 || temp < 0)
    //{
        m_SudentworldPointer->setNBDead();
    //}
}

void Actor::setStatusBar(int hitNum, int cabbNum, int torpNum)
{
    cerr << "in StatusBar(), the num of hits you have is " << hitNum << endl;
    stringstream stream;

    //LIVES
    stream.fill('0');
    int lives_Num = m_SudentworldPointer->getLives();
    stream << "Lives: ";
    stream << setw(1) << lives_Num;
    
    //HEALTH
    double health_Num = (hitNum/50.0) * 100.0;
    stream << "  Health: ";
    if (health_Num == 100)
    {
        stream << setw(3) << health_Num << "%";
    }
    else
    {
        stream << setw(2) << health_Num << "%";
    }
    
    //SCORE
    int score_Num = m_SudentworldPointer->getScore();
    stream << "  Score: ";
    stream << setw(1) << score_Num;
    
    //LEVEL
    int level_Num = m_SudentworldPointer->getLevel();
    stream << "  Level: ";
    stream << setw(1) << level_Num;
    
    //CABBAGES
    stream << "  Cabbages: ";
    //stream.precision(1);
    double cabb_Num = (cabbNum/30.0) * 100;
    stream << cabb_Num << "%";

    
    //TORPS
    stream << "  Torpedos: ";
    stream << setw(1) << torpNum;

    m_SudentworldPointer->setGameStatText(stream.str());
}


////////////////////////////////IMPLEMENTATION FOR SHIPS CLASS////////////////////////////////
Ships::Ships(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Actor(imageID, startX, startY, dir, size, depth, world)
{
    //SET THIS EQUAL TO ACTUAL LEVEL LATER
    //setImageID(imageID);
    setIsProjectile(false);
}

Ships::~Ships()
{
}
void Ships::setHitPoints(int hits)
{
    m_HitPoints = hits;
}

int Ships::getHitPoints()
{
    return m_HitPoints;
}

void Ships::doSomething()
{
    cerr << "in doSomething of Ships" <<endl;
    
    //check if alive
    if (CheckIfAlive() == false)
    {
        cerr << "it's not alive, so don't do anything " << endl;
        setDead();
        if (getImageID() == IID_NACHENBLASTER)
        {
            setLevelOver();
        }
        return;
    }
    //check if off the screen
    if (CheckIfOffScreen() ==false)
    {
        cerr << "it's off the screen, set dead" << endl;
        setDead();
        if (getImageID() != IID_NACHENBLASTER)
        {
            getWorld()->decNumOnScreenShips();
        }
        return;
    }
    somethingBody();
}

bool Ships:: CheckIfAlive()
{
    //make sure the hit points are above 0
    if (getHitPoints() < 0 || getHitPoints() == 0)
    {
        return false;
    }
    
    return true;
}

void Ships::SufferDamage(int damagePoints)
{
    cerr << "before suffering damage, the hit points was: " << m_HitPoints << endl;
    m_HitPoints = m_HitPoints - damagePoints;
    cerr << "after suffering damage, the hit points is: " << m_HitPoints << endl;
    
}

void Ships::CheckForProjCollisions()
{
    //check if it's collided w/ a projectile
    std::vector<Actor*> vec = getWorld()->getVector();
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] != nullptr)
        {
            if (vec[i]->getIsProjectile() == true && vec[i]->AliveStatus() == true)
            {
                if (CollisionOccurred(vec[i]->getX(), vec[i]->getY(), vec[i]->getRadius() ) )
                {
                    if (CheckProperSide(vec[i]->getX(), getX())== true)
                    {
                        cerr << "this ship collided with a projectile, minus " << vec[i]->getDamageValue() << "hit points " << endl;
                        
                        //cause damage to the ship that collided w/ it
                        SufferDamage(vec[i]->getDamageValue());
                        
                        //all the other stuff after a projectile collision
                        PostProjectileCollisionActions();
                        
                        //make the projectile dead
                        vec[i]->setDead();
                    }
                }
                else{
                    cerr << "alien didn't collide w/ projectile" << endl;
                }
            }   
        }
    }
}

void Ships::UpdateHitPoints (int hits)
{
    cerr << "ship's hit points before were: " << m_HitPoints << endl;
    m_HitPoints += hits;
    cerr << "ship's hit points now are: " << m_HitPoints << endl;
}

////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS/////////////////////////////
NachenBlaster::NachenBlaster(StudentWorld *world)
:Ships(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world)
{
    cerr << "in nachenblaster constructor " << endl;
    setHitPoints(50);
    m_CabbageEnergyPoints = 30;
    setDamageVal(0);
    m_FTorps = 0;
}

void NachenBlaster::setNumTorps(int torpnum)
{
    m_FTorps = torpnum;
}

void NachenBlaster::setCabbagePoints(int points)
{
    m_CabbageEnergyPoints = points;
    cerr << " " << endl;
}

bool NachenBlaster::CheckProperSide (int other, int currShip)
{
    //the projectile needs to be coming from the right hand side
    if (other < currShip)
    {
        //the projectile is coming from the left, don't cause damage
        return false;
    }
    else
    {
        //the projectile is coming from the right, cause damage
        return true;
    }
}

void NachenBlaster::somethingBody()
{
    cerr << "status of NACHENBLASTER is: " << AliveStatus() << endl;
    cerr << "IN THE BODY OF NACHENBLASTER" << endl;
    
    //move the NB based on user input
    KeyPressMovement();
    
    //check for collisions
    CheckForProjCollisions();
    
    //give the NB 5 more cabbage points, just cuz
    int toAdd = 5;
    if (m_CabbageEnergyPoints + toAdd > 30 || m_CabbageEnergyPoints + toAdd == 30)
    {
        m_CabbageEnergyPoints = 30;
    }
    else
    {
        m_CabbageEnergyPoints += toAdd;
    }
    
    if (CheckIfAlive() == false)
    {
        setLevelOver();
    }
    
}

void NachenBlaster::StatusBarBody()
{
    setStatusBar(getHitPoints(), m_CabbageEnergyPoints,m_FTorps);
}

void NachenBlaster::PostProjectileCollisionActions()
{
    cerr << "In NB's PostProjectileCollisionActions() " << endl;
    getWorld()->playSound(SOUND_BLAST);
    return;
}
void NachenBlaster::KeyPressMovement()
{
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
                //fire a cabbage by adding a new cabbage 12 pxl to the right of NB
                //Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
                
                Cabbage* actorP = new Cabbage (IID_CABBAGE, getX()+12, getY(), 0, .5, 1, getWorld());
                getWorld()->AddObjectToVector(actorP);
                getWorld()->playSound(SOUND_PLAYER_SHOOT);
                
                //reduce cabbage points by 5
                m_CabbageEnergyPoints -= 5;
            }
        }
        else if (ch == KEY_PRESS_TAB)
        {
            //check if you have any f torps in your inventory
            if (m_FTorps > 0)
            {
                //fire a torpedo
                F_Torpedo * fTorpedoP = new F_Torpedo(IID_TORPEDO, getX()+12, getY(), 0, 1.5, 1, getWorld(), IID_NACHENBLASTER);
                getWorld()->AddObjectToVector(fTorpedoP);
                
                //play torp sound
                getWorld()->playSound(SOUND_TORPEDO);
                
                //decrement num of torps left
                m_FTorps--;
            }
        }
        
    }
}

void NachenBlaster:: UpdateNumTorps (int numTorps)
{
    cerr << "before UpdateNumTorps your numtorps was " << m_FTorps << endl;
    m_FTorps += numTorps;
    cerr << "after UpdateNumTorps your numtorps was " << m_FTorps << endl;
}

NachenBlaster::~NachenBlaster()
{
    cerr << "deconstructing NachenBlaster"<< endl;
}

/////////////////////////////////IMPLEMENTATION FOR ALIENS CLASS////////////////////////////////////

Aliens::Aliens(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Ships(imageID, startX, startY, dir, size, depth, world)
{
    m_flightPlan = 0;
    m_TravelSpeed = 2.0;
    m_flightDirection = dir;
    
    //SET THIS EQUAL TO ACTUAL CURR LEVEL LATER
    int curr_level = getWorld()->getLevel();
    int temp_Hitpoints = 5 * (1 + ( curr_level - 1) * .1);
    setHitPoints(temp_Hitpoints);
    
    //if a NB collides, take this many points away from NB's hitPoints
    setDamageVal(5);
}

Aliens::~Aliens()
{
}

int Aliens::getFlightPlan()
{
    return m_flightPlan;
}

double Aliens::getTravelSpeed()
{
    return m_TravelSpeed;
}

void Aliens::somethingBody()
{
    //step 3: checking for collisions
    if (CheckForNBCollisions() == true)
    {
        PostNBCollisionActions();
        return;
    }
    CheckForProjCollisions();
    
    //setp 4: checking for New Flight plan
    if (CheckForNewFlightPath() == true)
    {
        NewFlightPathActions();
    }
    
    //step 5: firing a proj?
    if (CheckForAttacking() == true)
    {
        //yes you're within range to attack
        if (AttackNB() == true)
        {
            cerr << "you fired a projectile don't do anything the rest of this tick" << endl;
            //you fired a projectile so don't do anything the rest of the tick
            return;
        }
    }
    
    //step 6: move in direction of it's travel
    MoveInDirection();
    
    if (CheckForNBCollisions() == true)
    {
        PostNBCollisionActions();
        return;
    }
    CheckForProjCollisions();
}

bool Aliens::AttackNB()
{
    return allShootingProjectileStuff();
}

bool Aliens::allShootingProjectileStuff()
{
    //create the goodie
    if (FireProjectile() == true)
    {
        return true;
    }
    return false;
}

bool Aliens::CheckForAttacking()
{
    //get NB x and y coords
    int NB_X = getWorld()->getNachenblasterPointer()->getX();
    int NB_Y = getWorld()->getNachenblasterPointer()->getY();

    //if NB is to the left of the Smallgon
    if (NB_X < getX())
    {
        //check if alien y coord w/in 4 coords of NB's Y
        if (NB_Y + 5 > getY() && NB_Y -5 < getY() )
        {
            return true;
        }
    }
    return false;
}

bool Aliens::CheckProperSide (int other, int currShip)
{
    
    //the projectile needs to be coming from the left hand side
    if (other > currShip)
    {
        //the projectile is coming from the right, don't cause damage
        return false;
    }
    else
    {
        //the projectile is coming from the left, cause damage
        return true;
    }
}
bool Aliens::FireProjectile()
{
    // 1/20 chance of firing a new turnip
    //calculate formula : 1 in ((20/CurrentLevelNumber)+5)
    int currLevel = getWorld()->getLevel();
    int max_Num = (20/currLevel) + 5;
    
    int randNum = randInt(1, max_Num);
    
    if (randNum == 1)
    {
        //get goodie coordinates
        int projectile_Xcoord = getX()- 14;
        int projectile_Ycoord = getY();
        
        cerr << "alien's coords are " << getX() << " " << getY() << endl;
        //create new turnip & add to vector
        cerr << "creating a new turnip at " << projectile_Xcoord << " " <<  projectile_Ycoord << endl;
        Turnip * newTurnipP = new Turnip (IID_TURNIP, projectile_Xcoord, projectile_Ycoord, 0, .5, 1, getWorld());
        getWorld()->AddObjectToVector(newTurnipP);
        
        //play the sound
        getWorld()->playSound(SOUND_ALIEN_SHOOT);
        return true;
    }
    return false;
}
bool Aliens::CheckForNewFlightPath()
{
    //flight plan length has reached zero OR is @ top, or bottom
    if (getFlightPlan() == 0 || getY() > VIEW_HEIGHT -1 ||  getY() == VIEW_HEIGHT -1 || getY() == 0 || getY() < 0)
    {
        return true;
    }
    return false;
}

void Aliens::NewFlightPathActions()
{
    //if y coordinate >= to VIEW_HEIGHT-1
    if (getY() > VIEW_HEIGHT -1 || getY() == VIEW_HEIGHT -1)
    {
        m_flightDirection = 1;
        //then the alien will set its travel direction to down and left.
    }
    else if (getY() < 0 || getY() == 0)
    {
        //then the alien will set its travel direction to up and left.
        m_flightDirection = 2;

    }
    else if (m_flightPlan == 0)
    {
        //set a new travel direction: left, up and left, down and left
        m_flightDirection = randInt(1, 3);
        //pick a new flight plan length from 1-32
        m_flightPlan = randInt(1, 32);
    }
}

void Aliens::MoveInDirection()
{
    //alien will set its travel direction to down and left.
    if (m_flightDirection == 1)
    {
        int newXCoord = getX() - m_TravelSpeed;
        int newYCoord = getY() - m_TravelSpeed;
        moveTo(newXCoord, newYCoord);
    }
    //alien will set its travel direction to up and left.
    else if (m_flightDirection == 2)
    {
        int newXCoord = getX() - m_TravelSpeed;
        int newYCoord = getY() + m_TravelSpeed;
        moveTo(newXCoord, newYCoord);

    }
    //alien will set its travel direction to due left.
    else if (m_flightDirection == 3)
    {
        int newXCoord = getX() - m_TravelSpeed;
        moveTo(newXCoord, getY());
    }
    //reduce flight plan length by 1
    m_flightPlan -- ;
}

void Aliens::PostProjectileCollisionActions()
{
    cerr << "In alien's PostProjectileCollisionActions() " << endl;

    if (CheckIfAlive() == false)
    {
        
        //increment the number of ships destroyed
        getWorld()->incNumShipsDestroyed();
        AllAlienDeathStuff();
    }
    //the alien is still alive
    else
    {
        //play sound to signal it's been hit
        getWorld()->playSound(SOUND_BLAST);
   
    }
}
void Aliens::PostNBCollisionActions()
{
    cerr << "YOU COLLIDED!" << endl;
    //increment the number of ships destroyed
    getWorld()->incNumShipsDestroyed();
    
    //play sound to show that it collided w/ NB
    getWorld()->playSound(SOUND_DEATH);

    //make the NB suffer damage
    int alienDamageValue = getDamageValue();
    getWorld()->getNachenblasterPointer()->SufferDamage(alienDamageValue);
    AllAlienDeathStuff();
}

void Aliens::setFlightDirection(int dir)
{
    m_flightDirection = dir;
}

void Aliens::setFlightPlan(int len)
{
    m_flightPlan = len;
}

void Aliens::setTravelSpeed (double speed)
{
    m_TravelSpeed = speed;
}

void Aliens::AllAlienDeathStuff()
{
    AlienDeadActions();
}

void Aliens::AlienDeadActions()
{
    
    //2a. add points to player's game
    getWorld()->increaseScore(250);
 
    //2b. make the alien ship dead so it'll be removed
    setDead();
    
    //2c. play soundDeath
    getWorld()->playSound(SOUND_DEATH);
    
    //2d. INTRODUCE EXPLOSION
    Explosion * explosionP = new Explosion (IID_EXPLOSION, getX(), getY(), 0, 1, 0, getWorld());
    getWorld()->AddObjectToVector(explosionP);
}


/////////////////////////////////IMPLEMENTATION FOR SMALLGON CLASS////////////////////////////////////
Smallgon::Smallgon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Aliens(IID_SMALLGON, startX, startY, 0, 1.5, 1, world)
{
}
Smallgon::~Smallgon()
{
    cerr << "destructing Smallgon" << endl;
}

//void Smallgon::somethingBody()
//{
//    return;
//
//}

////////////////////////////////IMPLEMENTATION FOR SMOREGON CLASS/////////////////////////////
Smoregon::Smoregon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Aliens(IID_SMOREGON, startX, startY, 0, 1.5, 1, world)
{
    
}

bool Smoregon::AttackNB()
{
    if (allShootingProjectileStuff() == true)
    {
        return true;
    }
    PossiblyCharge();
    return false;
}

void Smoregon::PossiblyCharge()
{
    int currLevel = getWorld()->getLevel();
    int max_Num = (20/currLevel) + 5;
    int randNum = randInt(1, max_Num);
    
    if (randNum == 1)
    {
        //5bi. set Travel Direction to Due Left (which is option 3)
        setFlightDirection(3);
        //5bii. set flight plan to VIEW_WIDTH steps
        setFlightPlan(VIEW_WIDTH);
        cerr << "VIEW_WIDTH IS " << VIEW_WIDTH << endl;
        //5biii. set travel speed to 5 pixels per tick
        setTravelSpeed(5);
    }
}

void Smoregon::AllAlienDeathStuff()
{
    AlienDeadActions();
    int randNum = randInt(1, 3);
    if (randNum == 1)
    {
        DropGoodie();
    }

}

void Smoregon::DropGoodie()
{
    int randNum = randInt(1, 2);
    if (randNum == 1)
    {
        //create a new repair goodie @ the death coordinates
        RepairGoodie * RepairGoodieP = new RepairGoodie (IID_REPAIR_GOODIE, getX(), getY(), 0, .5, 1, getWorld());
        getWorld()->AddObjectToVector(RepairGoodieP);
    }
    else
    {
        FT_Goodie * FT_GoodieP = new FT_Goodie (IID_TORPEDO_GOODIE, getX(), getY(), 0, .5, 1, getWorld());
        getWorld()->AddObjectToVector(FT_GoodieP);
    }
}

Smoregon::~Smoregon()
{
    cerr << "destructing Smoregon!!" << endl;
}

////////////////////////////////IMPLEMENTATION FOR SNAGGLEGON CLASS/////////////////////////////
Snagglegon::Snagglegon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Aliens(IID_SNAGGLEGON, startX, startY, 0, 1.5, 1, world)
{
    //set the hit points
    int curr_level = getWorld()->getLevel();
    int temp_Hitpoints = 10 * (1 + ( curr_level - 1) * .1);
    setHitPoints(temp_Hitpoints);
    
    //set FlightDirection
    setFlightDirection(1);
    
    //set TravelSpeed
    setTravelSpeed(1.75);
    
    //set Damage points
    setDamageVal(15);

}

bool Snagglegon::AttackNB()
{
    if (allShootingProjectileStuff() == true)
    {
        return true;
    }
    return false;
}

void Snagglegon::AlienDeadActions()
{
    
    //2a. add points to player's game
    getWorld()->increaseScore(1000);
    
    //2b. make the alien ship dead so it'll be removed
    setDead();
    
    //2c. play soundDeath
    getWorld()->playSound(SOUND_DEATH);
    
    //2d. INTRODUCE EXPLOSION
    Explosion * explosionP = new Explosion (IID_EXPLOSION, getX(), getY(), 0, 1, 0, getWorld());
    getWorld()->AddObjectToVector(explosionP);
}

bool Snagglegon::CheckForNewFlightPath()
{
    //snagglegon is @ top, or bottom
    if (getY() > VIEW_HEIGHT -1 ||  getY() == VIEW_HEIGHT -1 || getY() == 0 || getY() < 0)
    {
        return true;
    }
    return false;
}

void Snagglegon::AllAlienDeathStuff()
{
    AlienDeadActions();
    int randNum = randInt(1, 6);
    
    if (randNum == 1)
    {
        DropGoodie();
    }
}

void Snagglegon::DropGoodie()
{
    ExtraLife * extraLifeP = new ExtraLife (IID_LIFE_GOODIE, getX(), getY(), 0, 0.5, 1, getWorld());
    getWorld()->AddObjectToVector(extraLifeP);
}

//reorients your direction if you need new FP
void Snagglegon::NewFlightPathActions()
{
    //if y coordinate >= to VIEW_HEIGHT-1
    if (getY() > VIEW_HEIGHT -1 || getY() == VIEW_HEIGHT -1)
    {
        setFlightDirection(1);
    }
    else if (getY() < 0 || getY() == 0)
    {
        //then the alien will set its travel direction to up and left.
        setFlightDirection(2);
        
    }
}
bool Snagglegon::FireProjectile()
{
 
    //calculate formula : 1 in ((20/CurrentLevelNumber)+5)
    int currLevel = getWorld()->getLevel();
    int max_Num = (15/currLevel) + 10;
    int randNum = randInt(1, max_Num);
    
    // you will fire
    if (randNum == 1)
    {
        //add a new torpedo to the vector/screen
        F_Torpedo * fTorpedoP = new F_Torpedo(IID_TORPEDO, getX()-14, getY(), 0, 1.5, 1, getWorld(), IID_SNAGGLEGON);
        getWorld()->AddObjectToVector(fTorpedoP);
        
        //5aii. play torpedo sound
        getWorld()->playSound(SOUND_TORPEDO);
        return true;
    }
    return false;
}

Snagglegon::~Snagglegon()
{
    cerr << "destructing Snagglegon" << endl;
}
/////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
Projectiles::Projectiles(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Actor(imageID, startX, startY, dir, size, depth, world)
{
    setImageID(imageID);
    setIsProjectile(true);
}

Projectiles::~Projectiles ()
{
    cerr << "destructing Projectile" << endl;
}

////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
Cabbage::Cabbage(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Projectiles(IID_CABBAGE, startX, startY, 0, .5, 1, world)
{
    cerr << "created a cabbage " << endl;
    setDamageVal(2);

}

Cabbage::~Cabbage()
{
    cerr << "deconstructing a cabbage" << endl;
}

void Cabbage::somethingBody()
{
    cerr << " in something fx() of cabbage" << endl;

    //move 8 px to the right
    moveTo (getX() + 8, getY());
    setDirection(20);
}

bool Cabbage::CheckIfOffScreen()
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
    cerr << "created a turnip" << endl;
    setDamageVal(2);
}

Turnip::~Turnip()
{
    cerr << "deconstructing a turnip" << endl;
}
void Turnip::somethingBody()
{
    cerr << "old Turnip coords were: " << getX() << " " << getY() << endl;
    moveTo(getX()-6, getY());
    cerr << "new Turnip coords are: " << getX() << " " << getY() << endl;
    setDirection(20);
}


////////////////////////////////IMPLEMENTATION FOR FLATULAN TORPEDO CLASS//////////////////////////////////////
F_Torpedo::F_Torpedo(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, int owner)
:Projectiles(IID_TURNIP, startX, startY, 0, .5, 1, world)
{
    setDamageVal(8);
    m_Owner = owner;
}

F_Torpedo::~F_Torpedo()
{
    cerr << "deconstructing a turnip";
}

void F_Torpedo::somethingBody()
{
    if (m_Owner == IID_NACHENBLASTER)
    {
        //move right by 8 pxl
        moveTo(getX()+8, getY());
    }
    
    if (m_Owner == IID_SNAGGLEGON)
    {
        //move left by 8 pxl
        moveTo(getX()-8, getY());
    }
}

///////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////////
Star::Star(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Actor(imageID, startX, startY, 0, .5, 3, world)
{
    setImageID(imageID);
    setIsProjectile(false);
    setDamageVal(0);
}

Star::~Star ()
{
    cerr << "deconstructing a Star" << endl;
}
void Star::somethingBody()
{
    cerr << "here in Star's somethingBody!" << endl;
    
    //check if it's on the screenq
    moveTo(getX()-1, getY());
}
////////////////////////////////IMPLEMENTATION FOR EXPLOSION CLASS////////////////////////////////
Explosion::Explosion(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Actor(IID_EXPLOSION , startX, startY, 0, 1, 0, world)
{
    setDamageVal(0);
    setImageID(imageID);
    setIsProjectile(false);
    m_AliveTicksLeft = 4;
}

void Explosion::somethingBody()
{
    m_AliveTicksLeft -= 1;
    cerr << "in somethingBody of explosion, Ticks left is: " << m_AliveTicksLeft << endl;
    explodeExplosion();
}
Explosion::~Explosion()
{
    cerr << "destroying explosion";
}

bool Explosion::CheckIfOffScreen()
{
    if (m_AliveTicksLeft > 1)
    {
        return true;
    }
    return false;
}

void Explosion::explodeExplosion()
{
    double newSize = getSize() * 1.5;
    setSize(newSize);
}

////////////////////////////////IMPLEMENTATION FOR GOODIES CLASS////////////////////////////////
Goodies::Goodies(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Actor(imageID, startX, startY, dir , size, depth, world)
{
    setImageID(imageID);
    setIsProjectile(false);
}

void Goodies::somethingBody()
{
    //3. check if NB collided with it
    if (CheckForNBCollisions()==true)
    {
        PostNBCollisionActions();
        //3e. return immediately
        return;
    }
    //4. move .75 units left & down
    moveTo(getX()-.75, getY()-.75);
    
    //5. check for NB collision again
    if (CheckForNBCollisions()==true)
    {
        PostNBCollisionActions();
        //3e. return immediately
        return;
    }
}

void Goodies::PostNBCollisionActions()
{
    //3a. increase points by 100
    getWorld()->increaseScore(100);
    //3b. set its state to dead
    setDead();
    //3c. play SOUND_GOOIDE
    getWorld()->playSound(SOUND_GOODIE);
    //3d. perform specialized goodie powers!
    goodiePowers();
}

Goodies::~Goodies()
{
    cerr << "destructing a goodie " << endl;
}

////////////////////////////////IMPLEMENTATION FOR ExtraLife CLASS////////////////////////////////
ExtraLife::ExtraLife(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Goodies(IID_LIFE_GOODIE, startX, startY, 0 , 0.5, 1, world)
{
}

ExtraLife::~ExtraLife()
{
    cerr << "destructing an ExtraLife " << endl;
}

void ExtraLife::goodiePowers()
{
    cerr <<"INCREASING NUM LIVES BY 1 " << endl;
    //3d. increase number of lives by 1
    getWorld()->incLives();
}

////////////////////////////////IMPLEMENTATION FOR REPAIRGOODIE CLASS////////////////////////////////
RepairGoodie::RepairGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Goodies(IID_REPAIR_GOODIE, startX, startY, 0 , 0.5, 1, world)
{
}

RepairGoodie::~RepairGoodie()
{
    cerr << "destructing an RepairGoodie " << endl;
}

void RepairGoodie::goodiePowers()
{
    //3d. increase NB's hit points by 10
    
    int NB_CurrhitPoints = getWorld()->getNachenblasterPointer()->getHitPoints();
    
    //set NB's hit points to 50 if it's
    int addTo_Points;
    if (addTo_Points + 10 > 50)
    {
        //calculate the difference then
        addTo_Points = 50 - NB_CurrhitPoints;
    }
    
    else
    {   //it won't cause you to go over 50 so just add ten
        addTo_Points = 10;
    }
    getWorld()->getNachenblasterPointer()->UpdateHitPoints(addTo_Points);
}
////////////////////////////////IMPLEMENTATION FOR FT_Goodie CLASS////////////////////////////////
FT_Goodie::FT_Goodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Goodies(IID_TORPEDO_GOODIE, startX, startY, 0 , 0.5, 1, world)
{
}
FT_Goodie::~FT_Goodie()
{
    cerr << "destructing an FT_Goodie " << endl;
}

void FT_Goodie::goodiePowers()
{
    //3d. give the NB 5 more torpedos
    getWorld()->getNachenblasterPointer()->UpdateNumTorps(5);
}
