//
//  CarMap.cpp
//  Project2
//
//  Created by Super on 1/18/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include "CarMap.h"

CarMap::CarMap ()
{
    Map m_CarObject;
}
bool CarMap::addCar(KeyType license)
{
    if (m_CarObject.contains(license) == false || fleetSize() <  DEFAULT_MAX_ITEMS)
    {
        m_CarObject.insert(license, 0);
        return true;
    }
    else
    {
        return false;
    }
}

//const functions need to call only other const functions
double CarMap::gas(KeyType license) const
{
    // If a car with the given license plate is in the map, return the
    // number of gallons of gas in its tank; otherwise, return -1.
    if (m_CarObject.contains(license) == true)
    {
        ValueType gals;
        m_CarObject.get(license, gals);
        return gals;
    }
    else
    {
        return -1;
    }
}

bool CarMap::addGas(KeyType license, ValueType gallons)
{
    //check if gallons is negative or license isn't in map
    if (gallons < 0 || m_CarObject.contains(license) == false)
    {
        return false;
    }
    else
    {
        m_CarObject.update(license, gallons);
        return true;
    }
}


bool CarMap::useGas(KeyType license, ValueType gallons)
{
    if (m_CarObject.contains(license) == false || gallons < 0 || gallons > gas(license))
    {
        return false;
    }
    else
    {
        //make the calculation
        ValueType temp;
        temp = gas(license) - gallons;
        m_CarObject.update(license, temp);
        return true; 
    }

}

// Return the number of cars in the CarMap.
int CarMap::fleetSize() const
{
    return m_CarObject.size();
}

void CarMap::print() const
{
    KeyType temp_key;
    ValueType temp_value;
    int counter = fleetSize()-1;
    while (counter >= 0)
    {
        m_CarObject.get(counter, temp_key, temp_value);
        std::cout << temp_key << " " << temp_value << std::endl;
        counter --;
    }
}


