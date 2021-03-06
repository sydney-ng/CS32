//
//  newMap.cpp
//  Project2
//
//  Created by Super on 1/17/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include "newMap.h"

Map::Map()
 {
     m_MaxSize = DEFAULT_MAX_ITEMS;
     m_MapSize = 0;
     m_MapArray = new MapType[DEFAULT_MAX_ITEMS];
 }

Map::Map (const int& array_size)
 {
     m_MapSize = 0;
     m_MaxSize = array_size;
     m_MapArray = new MapType[array_size];
 }

Map::~Map()
{
    
    delete [] m_MapArray;
}

Map::Map(const Map &map_2)
{
    m_MapArray = new MapType[map_2.m_MaxSize];
    
    m_MaxSize = map_2.m_MaxSize;
    m_MapSize = map_2.m_MapSize;

    //iterate through map2 and set it 
    for (int i = 0; i < m_MapSize; i ++)
    {
        m_MapArray [i] = map_2.m_MapArray[i];
    }
    
}

Map& Map::operator=(const Map &map_2)
{
    if (&map_2 == this)
        return *this;
    
    else
    {
        delete [] m_MapArray;
        m_MapArray = new MapType[map_2.m_MaxSize];
        
        m_MaxSize = map_2.m_MaxSize;
        m_MapSize = map_2.m_MapSize;
        
        //iterate through map2 and set it to temp
        for (int i = 0; i < m_MapSize; i ++)
        {
            m_MapArray [i] = map_2.m_MapArray[i];
        }
        return *this;
    }
   
}

bool Map::empty () const
{
    if (m_MapSize <=0)
    {
        return true;
    }
    return false;
}

int Map::size() const
{
    return m_MapSize;
}

// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).


bool Map::insert(const KeyType& key, const ValueType& value)
{
    //key isn't currently in map
    if (contains(key) == false)
    {
        //check there's room in map
        if (m_MapSize < m_MaxSize)
        {
            //increase the size of array & addd to array
            m_MapSize++;
            m_MapArray[m_MapSize-1].m_k = key;
            m_MapArray[m_MapSize-1].m_v = value;
            return true;
        }
        
    }
    
    return false;
}

void Map::dump () const
{
    std::cerr << "m_MapSize is: " << m_MapSize <<  std::endl;
    std::cerr << "m_MapArray is: " <<  std::endl;
    for (int i = 0; i < m_MapSize; i ++)
    {
        std::cerr << std:: endl << "item #" << i << ", key: " << m_MapArray[i].m_k << ", value : " << m_MapArray[i].m_v <<  std::endl << std::endl;
    }
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

// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.
bool Map::erase(const KeyType& key)
{
    //check if key is equal to a current key in the map
    for (int i = 0; i <m_MapSize; i++)
    {
        //there is already this entry
        if (key == m_MapArray[i].m_k)
        {
            //shift everything to the right over one
            for (int k = i; k < m_MapSize-1; k++)
            {
                m_MapArray[k] = m_MapArray[k+1];
            }
            m_MapSize = m_MapSize -1;
            return true;
        }
    }
    return false;
}

// Return true if key is equal to a key currently in the map, otherwise false
bool Map::contains(const KeyType& key) const
{
    //check if there's a match
    for (int i = 0; i <m_MapSize; i++)
    {
        //there is already this entry
        if (key == m_MapArray[i].m_k)
        {
            return true;
        }
    }
    return false;
}

//set value if there's a key match
bool Map::get(const KeyType& key, ValueType& value) const
{
    //check if there's a match
    for (int i = 0; i <m_MapSize; i++)
    {
        //there is already this entry
        if (key == m_MapArray[i].m_k)
        {
            value = m_MapArray[i].m_v;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < size() && i >= 0)
    {
        key = m_MapArray[i].m_k;
        value = m_MapArray[i].m_v;
        return true;
    }
    return false;
}

//switch contents of map w/ another one
void Map::swap(Map& other)
{
    Map intermediary = other;
    other = *this;
    *this = intermediary;
}
