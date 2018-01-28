
// Map.cpp
#include "Map.h"

Map::Map()
: m_size(0), tail(nullptr), head (nullptr)
{
    
}

Map::~Map()
{
    //empty by iterating through, setting temp & deleting
    Node *p = head;
    while (p != nullptr)
    {
        Node *temp = p->next;
        delete p;
        p = temp;
    }
}

Map::Map(const Map& other)
{
    //set non-node variables
    m_size = 0;
    head = nullptr;
    tail = nullptr;
    
    //populate
    for (int iterator = 0; iterator < other.size(); iterator++)
    {
        KeyType temp_key;
        ValueType temp_val;
        
        other.get(iterator, temp_key, temp_val);
        insert(temp_key, temp_val);
    }
}


Map& Map::operator=(const Map& rhs)
{
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

void Map::swap(Map& other)
{
    // Swap elements.  Since the only elements that matter are those up to
    // m_size and other.m_size, only they have to be moved.

    //exchange the sizes
    int tempMapSize = other.m_size;
    other.m_size = m_size;
    m_size = tempMapSize;
    
    //temp head/tail
    Node *tempHead = head;
    Node *tempTail = tail;

    
    //tail/head for the current map
    head = other.head;
    tail = other.tail;

    //tail/head for other map
    other.head = tempHead;
    other.tail = tempTail;
}

void Map::dump() const
{
    cerr << "size is: " << size() << endl;
    cerr << "head address:" << head << endl;
    cerr << "tail address:" << tail << endl;
    Node *p = head;
    while (p != nullptr)
    {
        cerr << "node is: " << p << endl;
        cerr << "key is: " << p->MapValues.m_key << endl;
        cerr << "value is: " << p->MapValues.m_value << endl;
        cerr << "next is: " << p->next << endl << endl;
        p = p->next;
    }
    cerr << "finished" << endl << endl << endl;
}

//insert to the beginning of linked list
bool Map::insert(const KeyType& key, const ValueType& value)
{
    //check if this value is already in the map
    if (contains(key) == true)
    {
        return false;
    }
    Node *newNode = new Node;

    //this is our first time adding something to the linked list
    if (empty() == true)
    {
        //set the "next" & "previous" values of the new node
        newNode->next = nullptr;
        newNode->previous = nullptr;
        
        //set the values of the new node
        newNode->MapValues.m_key = key;
        newNode->MapValues.m_value = value;
        
        //set the values of the previous one
        head = newNode;

        m_size++;
        return true;
    }
    
    //there's already stuff there, append to end
    else
    {
        //set the values of the new node
        newNode->MapValues.m_key = key;
        newNode->MapValues.m_value = value;
        
        Node *iterator = head;
        
        while (iterator != nullptr)
        {
            //this is how you know it's in the last index
            if (iterator->next == nullptr)
            {
                break;
            }
            iterator = iterator->next;
        }
        
        //set the "next" & "previous" values of the new node
        newNode->next = nullptr;
        newNode->previous = iterator;

        //set the next of iterator to point to new node
        iterator->next = newNode;
        
        m_size ++;
        
        //set tail equal to newNode
        tail = newNode;
        
        return true;
    }
    return false;
}

bool Map::erase(const KeyType& key)
{
    //make sure it's in the map before iterating
    if (contains(key) == false)
    {
        return false;
    }
    Node *Killme = head;
    
    //make sure list isn't empty
    if (empty() == true)
    {
        return false;
    }
    
    //it's the only node
    if(head->next == nullptr && head->MapValues.m_key == key)
    {
        Killme = head;
        head = nullptr;
        delete Killme; 
        m_size--;
        return true;
    }
    
    //check if item is in the front
    else if (head->MapValues.m_key == key)
    {
        head = Killme->next;
        head->previous = nullptr;
        m_size--;
        delete Killme;
        return true;
    }
    
    //check if item is the end
    else if (tail->MapValues.m_key == key)
    {
        Killme = tail;
        tail = tail->previous;
        tail->next = nullptr;
        m_size--;
        delete Killme;
        return true;
    }
    
    //item is somewhere in the middle
    else
    {
        Node *iterator = head;
        while (iterator != nullptr)
        {
            if (iterator->next->MapValues.m_key == key)
            {
                //set the index to delete
                Killme = iterator->next;
                //set the next equal to the one after kill
                iterator->next = iterator->next->next;
                //set the previous of the one after kill to be the iterator
                iterator->next->previous = iterator;
                m_size--;
                delete Killme;
                return true;
            }
            iterator=iterator->next;
        }
    }
    return false;
}


bool Map::get(const KeyType& key, ValueType& value) const
{
    Node *iterator = head;
    int counter = 0;
    while (counter < size())
    {
        if (iterator != nullptr && iterator->MapValues.m_key == key)
        {
            value = iterator->MapValues.m_value;
            return true;
        }
        iterator = iterator->next;
        counter ++;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    //make sure that i is within range
    if (i<0 || i >= size())
    {
        return false; 
    }
    
    Node *iterator = head;
    int counter = 0;
    int iterator_counter = 0;
    while (counter < size())
    {
        if (iterator != nullptr && iterator_counter == i)
        {
            value = iterator->MapValues.m_value;
            key = iterator->MapValues.m_key;
            return true;
        }
        iterator_counter ++;
        iterator = iterator->next;
        counter ++;
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

bool Map::update(const KeyType& key, const ValueType& value)
{
    Node *iterator = head;
    int counter = 0;
    while (counter < size())
    {
        if (iterator != nullptr && iterator->MapValues.m_key == key)
        {
            iterator->MapValues.m_value = value;
            return true;
        }
        iterator = iterator->next;
        counter ++;
    }
    return false;
}

//if a key appears in exactly 1 of m1 and m2, give it to result
//if a key is in both m1 and m2, result will have that pair
bool combine(const Map& m1, const Map& m2, Map& result)
{
    bool flag = true;
    //empty result
    
    if (result.size() > 0)
    {
        while (result.size() > 0)
        {
            KeyType empty_result_key;
            ValueType empty_result_val;
            result.get(0, empty_result_key, empty_result_val);
            result.erase(empty_result_key);
        }
    }
    
    KeyType my_key;
    ValueType my_val;
    
    //loop through map 1
    for (int map1_iter = 0; map1_iter < m1.size(); map1_iter ++)
    {
        //get the value of something in map1
        m1.get(map1_iter, my_key, my_val);
        //if it's not in m2
        if (m2.contains(my_key) == false)
        {
            result.insert(my_key, my_val);
        }
        //it is also in m2
        else
        {
            //check to make sure val in both is the same
            ValueType temp_val;
            m2.get(my_key, temp_val);
            if (temp_val == my_val)
            {
                result.insert(my_key, my_val);
            }
            //same key, different value
            else
            {
                flag = false;
            }
        }
    }
    
    KeyType my_key2;
    ValueType my_val2;
    
    //find unique entries in map2, you don't need to do the ones in both
    //that was satisfied by first for loop
    for (int map2_iter = 0; map2_iter < m2.size(); map2_iter ++)
    {
        //make sure that get returns true (aka there is something to return)
        if (m2.get(map2_iter, my_key2, my_val2))
        {
            //if it's not in m1
            if (m1.contains(my_key2) == false)
            {
                result.insert(my_key2, my_val2);
            }
    
        }
    }
    return flag;
}

//PREVENT ALIASING
void subtract(const Map& m1, const Map& m2, Map& result)
{
    //empty result
    if (result.size() > 0)
    {
        while (result.size() > 0)
        {
            KeyType empty_result_key;
            ValueType empty_result_val;
            result.get(0, empty_result_key, empty_result_val);
            result.erase(empty_result_key);
        }
    }
    
    for (int map1_iter = 0; map1_iter < m1.size(); map1_iter ++)
    {
        KeyType my_key;
        ValueType my_val;
        //make sure that get returns true (aka there is something to return)
        m1.get(map1_iter, my_key, my_val);
        {
            //if it's not in m2
            if (m2.contains(my_key) == false)
            {
                result.insert(my_key, my_val);
            }

        }
    }
    
}
