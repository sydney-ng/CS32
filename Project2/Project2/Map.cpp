//
//  map.cpp
//  Project2
//
//  Created by Super on 1/17/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
#include "Map.h"

bool Map::empty()
{
    if (m_MapSize <=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Map::size()
{
    return m_MapSize;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    bool match = false;
    //check if there's a match
    for (int i = 0; i <m_MapSize; i++)
    {
        //there is already this entry
        if (key == m_MapArray[i].m_k)
        {
            match = true;
            break;
        }
    }
    
    
    //there is no matching entry in the array
    if (match == false)
    {
        //check if dictionary is full
        if (m_MapSize != DEFAULT_MAX_ITEMS)
        {
            //ADD TO THE MAP
            return true;
        }
        //dictionary is full
        else
        {
            return false;
        }
    }
    
    //match is equal to true, meaning it's already in dictionary
    return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    //check if there's a match
    for (int i = 0; i <m_MapSize; i++)
    {
        //there is already this entry
        if (key == m_MapArray[i].m_k)
        {
            //update the value the key maps to
            m_MapArray[i].m_v = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (update(key, value) == true)
    {
        return true;
    }
    else if (insert(key, value) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}


