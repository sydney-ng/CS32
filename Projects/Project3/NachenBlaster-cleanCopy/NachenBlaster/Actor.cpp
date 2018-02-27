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
    m_ImageID = imageID;
    m_isProjectile = false;
    cerr << "created object using Actor Constructor " << endl;
}

void Actor::doSomething()
{
    cerr << "In doSomething of Actor, the Base Class! "<< endl;
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

void Actor::setIsProjectile (bool projectileBool)
{
    m_isProjectile = projectileBool;

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

////////////////////////////////IMPLEMENTATION FOR SHIPS CLASS////////////////////////////////
Ships::Ships(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
:Actor(imageID, startX, startY, dir, size, depth, world)
{
    //SET THIS EQUAL TO ACTUAL LEVEL LATER
    setImageID(imageID);
    setIsProjectile(false);
    int curr_level = 1;
    m_HitPoints = 5 * (1 + ( curr_level - 1) * .1);
}

Ships::~Ships()
{
}
void Ships::setHitPoints(int hits)
{
    m_HitPoints = hits;
}
void Ships::UpdateHitPoints (int hits)
{
    m_HitPoints += hits;
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
        return;
    }
    //check if off the screen
    if (CheckIfOffScreen() ==false)
    {
        cerr << "it's off the screen, set dead" << endl;
        setDead();
        return;
    }
    cerr << "about ot call moveShip()" <<endl;
    //call somethingBody
    //moveShip();
    somethingBody();
    
    //moveShip();
}

bool Ships:: CheckIfAlive()
{
    //make sure the hit points are above 0
    if (getHitPoints() <= 0)
    {
        return false;
    }
    
    return true;
}

void Ships::SufferDamage(int ID)
{
    cerr << "before suffering damage, the hit points was: " << m_HitPoints << endl;
    //find out what it it
    if (ID == IID_CABBAGE || ID == IID_TURNIP)
    {
        m_HitPoints -= 2;
    }
    cerr << "after suffering damage, the hit points is: " << m_HitPoints << endl;
    
}
////////////////////////////////IMPLEMENTATION FOR NACHENBLASTER CLASS/////////////////////////////
NachenBlaster::NachenBlaster(StudentWorld *world)
:Ships(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world)
{
    cerr << "in nachenblaster constructor " << endl;
    setHitPoints(50);
    m_CabbageEnergyPoints = 30;
}

void NachenBlaster::somethingBody()
{
    cerr << "status of NACHENBLASTER is: " << AliveStatus() << endl;
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
                //fire a cabbage by adding a new cabbage 12 pxl to the right of NB
                //Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
                
                Cabbage* actorP = new Cabbage (IID_CABBAGE, getX()+12, getY(), 0, .5, 1, getWorld(), 'c');
                getWorld()->AddObjectToVector(actorP);
                getWorld()->playSound(SOUND_PLAYER_SHOOT);
                
                //reduce cabbage points by 5
                m_CabbageEnergyPoints -= 5;
            }
        }
    }
    //give the NB 5 more cabbage points, just cuz
    m_CabbageEnergyPoints += 5;
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
    CheckForAllCollisions();
    
    //setp 4: checking for New Flight plan
    if (CheckForNewFlightPath() == true)
    {
        NewFlightPathActions();
    }
    
    //step 5: new goodie??
    if (CheckForNewGoodie() == true)
    {
        //create the goodie
        NewGoodieActions();
        //don't do anything for the rest of this tick
        return;
    }
    CheckForAllCollisions();
}

bool Aliens::CheckForNewGoodie()
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

void Aliens::NewGoodieActions()
{
    // 1/20 chance of firing a new turnip
    int randNum = randInt(1, 20);
    if (randNum == 1)
    {
        //get goodie coordinates
        int goodie_Xcoord = 14 + (getWorld()->getNachenblasterPointer()->getX());
        int goodie_Ycoord = getY();
        
        //create new turnip & add to vector
        Turnip * newTurnipP = new Turnip (IID_TURNIP, goodie_Xcoord, goodie_Ycoord, 0, .5, 1, getWorld(), 'T');
        getWorld()->AddObjectToVector(newTurnipP);
        
        //play the sound
        getWorld()->playSound(SOUND_ALIEN_SHOOT);
    }
}
bool Aliens::CheckForNewFlightPath()
{
    //flight plan length has reached zero OR is @ top, or bottom
    if (getFlightPlan() == 0 || getY() == VIEW_HEIGHT -1 || getY() < 1)
    {
        return true;
    }
    
    return false;
}

void Aliens::NewFlightPathActions()
{
    //if y coordinate >= to VIEW_HEIGHT-1
    if (getY() > VIEW_HEIGHT -1 || getY() == VIEW_HEIGHT)
    {
        //then the alien will set its travel direction to down and left.
    }
    else if (getY() < 0 || getY() == 0)
    {
        //then the alien will set its travel direction to up and left.
    }
    else if (m_flightPlan == 0)
    {
        //set a new travel direction: left, up and left, down and left
        
        //pick a new flight plan length from 1-32
        m_flightPlan = randInt(1, 32);
    }
}
void Aliens::CheckForAllCollisions ()
{
    cerr << "we will check if there was a collision " << endl;
    
    //get coordinates of the NB
    int NB_xCoord = getWorld()->getNachenblasterPointer()->getX();
    int NB_yCoord = getWorld()->getNachenblasterPointer()->getY();
    double NB_radius = getWorld()->getNachenblasterPointer()->getRadius();
    
    //check if it collided with NB
    if (CollisionOccurred(NB_xCoord, NB_yCoord, NB_radius)==true)
    {
        return PostNBCollisionActions();
    }
    
    //check if it's collided w/ a projectile
    std::vector<Actor*> vec = getWorld()->getVector();
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i]->getIsProjectile() == true && vec[i]->AliveStatus() == true)
        {
            if (CollisionOccurred(vec[i]->getX(), vec[i]->getY(), vec[i]->getRadius() ) )
            {
                cerr << "alien collided with a projectile!" << endl;
                
                
                PostAlienProjectileCollisionActions(vec[i]->getImageID());
                //make the projectile dead
                vec[i]->setDead();
            }
            else{
                cerr << "alien didn't collide w/ projectile" << endl;
            }
        }
    }
}

void Aliens::PostAlienProjectileCollisionActions(int projectileID)
{
    //cause damage to aliens
    SufferDamage(projectileID);
    //add points to player's game
    getWorld()->UpdateGamePoints(250);

    if (CheckIfAlive() == false)
    {
        setDead();
        Explosion * explosionP = new Explosion (IID_EXPLOSION, getX(), getY(), 0, 1, 0, getWorld());
        getWorld()->AddObjectToVector(explosionP);
    }
}
void Aliens::PostNBCollisionActions()
{
    cerr << "YOU COLLIDED!" << endl;
    //suffer damage to NB
    //SET THIS TO SOMETHING
    int x = 2;
    getWorld()->getNachenblasterPointer()->SufferDamage(x);
    
    //add points to player's game
    getWorld()->UpdateGamePoints(250);

    //play soundDeath
    getWorld()->playSound(SOUND_DEATH);
    
    //INTRODUCE EXPLOSION
    Explosion * explosionP = new Explosion (IID_EXPLOSION, getX(), getY(), 0, 1, 0, getWorld());
    getWorld()->AddObjectToVector(explosionP);
    //make the alien ship dead so it'll be removed
    setDead();
    
    //DROP GOODIE?
}
bool Aliens::CollisionOccurred(int otherXCoord, int otherYCoord, int otherRadius)
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

double Aliens::CalculateEcludianDistance(double x1, double y1, double x2, double y2)
{
     double distance_between;
     double x_dist = x1 - x2;
     double y_dist = y1 - y2;
    
     distance_between = pow(x_dist,2)+pow(y_dist,2);
     distance_between = sqrt(distance_between);
    
     return distance_between;
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
/////////////////////////////////IMPLEMENTATION FOR PROJECTILES CLASS////////////////////////////////
Projectiles::Projectiles(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, char d_Name)
:Actor(imageID, startX, startY, dir, size, depth, world)
{
    setImageID(imageID);
    setIsProjectile(true);
    m_DamageName = d_Name;
}

Projectiles::~Projectiles ()
{
}

int Projectiles::getDamagePoints()
{
    //2 hit points for turnips and cabbages
    return 2;
}

void Projectiles::setDamageName(char passedIn_DName)
{
    m_DamageName = passedIn_DName;
}

////////////////////////////////IMPLEMENTATION FOR CABBAGE CLASS////////////////////////////////
Cabbage::Cabbage(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, char d_Name)
:Projectiles(IID_CABBAGE, startX, startY, 0, .5, 1, world, d_Name)
{
    cerr << "created a cabbage " << endl;
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
Turnip::Turnip(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, char d_Name)
:Projectiles(IID_TURNIP, startX, startY, 0, .5, 1, world, d_Name)
{
    cerr << "created a turnip" << endl;
}

Turnip::~Turnip()
{
    cerr << "deconstructing a turnip" << endl;
}
void Turnip::somethingBody()
{
    moveTo(getX()-6, getY());
    setDirection(20);
}


////////////////////////////////IMPLEMENTATION FOR FLATULAN TORPEDO CLASS//////////////////////////////////////
F_Torpedo::F_Torpedo(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world, int owner, char d_Name)
:Projectiles(IID_TURNIP, startX, startY, 0, .5, 1, world, d_Name)
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

int F_Torpedo::getDamagePoints()
{
    //torpedos cause 8 points of damage
    return 8;
}
///////////////////////////////////IMPLEMENTATION FOR STAR CLASS////////////////////////////////////
Star::Star(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Actor(imageID, startX, startY, 0, .5, 1, world)
{
    setImageID(imageID);
    setIsProjectile(false);
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

////////////////////////////////IMPLEMENTATION FOR REPAIRGOODIE CLASS////////////////////////////////
RepairGoodie::RepairGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld *world)
: Goodies(IID_REPAIR_GOODIE, startX, startY, 0 , 0.5, 1, world)
{
}

RepairGoodie::~RepairGoodie()
{
    cerr << "destructing an RepairGoodie " << endl;
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
