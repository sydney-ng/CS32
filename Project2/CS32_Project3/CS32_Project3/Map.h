// Map.h

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

// Later in the course, we'll see that templates provide a much nicer
// way of enabling us to have Maps of different types.  For now, we'll
// use type aliases.

#include <string>
//REMOVE THIS:
#include <iostream>
using namespace std;

using KeyType = std::string;
using ValueType = double;

const int DEFAULT_MAX_ITEMS = 250;

class Map
{
public:
    Map();               // Create an empty map (i.e., one with no key/value pairs)
    
    ~Map();             //Deconstructor
    
    void dump() const;          //dump function 
    
    Map& operator=(const Map& rhs); //assignment operator
    
    Map(const Map& other); //Copy Constructor
    
    bool empty() const;  // Return true if the map is empty, otherwise false.
    
    int size() const;    // Return the number of key/value pairs in the map.
    
    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full.
    
    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full.
    
    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    
    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    
    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    
    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.
    
    void swap(Map& other);
    // Exchange the contents of this map with the other one.
    
private:
    
    // Since this structure is used only by the implementation of the
    // Map class, we'll make it private to Map.
    
    struct Pair
    {
        KeyType   m_key;
        ValueType m_value;
    };
    
    struct Node
    {
        Node *next;
        Node *previous;
        Pair MapValues;
    };
    
    Node *tail;
    Node *head;
    
    //No longer needed: using LL instead
    //Pair m_data[DEFAULT_MAX_ITEMS];  // the pairs in the map
    int  m_size;                     // number of pairs in the map
    
    // At any time, the elements of m_data indexed from 0 to m_size-1
    // are in use.
    
    Node * find(const KeyType& key) const;
    // Return index of the pair in m_data whose m_key == key if there is
    // one, else -1
    
    //NEW IMPLEMENTATION: will return the address of the pair if it's found in the map 
    
    bool doInsertOrUpdate(const KeyType& key, const ValueType& value, bool mayInsert, bool mayUpdate);
    // If the key is not present in the map and if mayInsert is true, insert
    // the pair if there is room.  If the key is present and mayUpdate is
    // true, update the pair with the given key.
};

// Inline implementations

inline
int Map::size() const
{
    return m_size;
}

inline
bool Map::empty() const
{
    //if head points to nullptr, you know it's empty
    if (head->next == nullptr)
    {
        return true;
    }
    return false;
}

inline
bool Map::contains(const KeyType& key) const
{
    if (head->next == nullptr)
    {
        return false;
    }
    else
    {
        Node *p;
        p = head;
        while (p!= nullptr)
        {
            if (p->MapValues.m_key == key)
            {
                return true;
            }
            p = p->next;
        }
        return false;
    }
}
inline
bool Map::update(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, false /* no insert */, true /* update */);
}

#endif // MAP_INCLUDED
