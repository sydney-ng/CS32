// Map.cpp

#include "Map.h"
//TAKE THIS OUT BEFORE TURNING IN

//do I initialize the MapValues????
Map::Map()
: m_size(0), tail(nullptr), head (nullptr)
{}

Map::~Map()
{
    Node *p;
    p = head;
    while (p != nullptr)
    {
        Node *temp = p->next;
        delete p;
        p = temp;
    }
}

Map::Map(const Map& other)
{
    KeyType temp_key;
    ValueType temp_value;
    m_size = 0;
    head = nullptr;
    tail = nullptr;
    
    //make sure that it's not equal to itself
    if (&other != this)
    {
        //use get function to get everything inside of it
        for (int i =0; i < other.size(); i++)
            {
                other.get (i, temp_key, temp_value);
                //
                //insert(temp_key, temp_value);
                m_size++;
            }
    }
}

/*
Map& Map::operator=(const Map& rhs)
{
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

*/

/*
void Map::swap(Map& other)
{
    // Swap elements.  Since the only elements that matter are those up to
    // m_size and other.m_size, only they have to be moved.
    
    int minSize = (m_size < other.m_size ? m_size : other.m_size);
    for (int k = 0; k < minSize; k++)
    {
        Pair tempPair = m_data[k];
        m_data[k] = other.m_data[k];
        other.m_data[k] = tempPair;
    }
    
    // If the sizes are different, assign the remaining elements from
    // the longer one to the shorter.
    
    if (m_size > minSize)
        for (int k = minSize; k < m_size; k++)
            other.m_data[k] = m_data[k];
    else if (other.m_size > minSize)
        for (int k = minSize; k < other.m_size; k++)
            m_data[k] = other.m_data[k];
    
    // Swap sizes
    
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
}
*/

void Map::dump() const
{
    cout << "head address:" << head << endl;
    Node *p;
    while (p != nullptr)
    {
        cout << "node is: " << p << endl;
        cout << "key is: " << p->MapValues.m_key << endl;
        cout << "value is: " << p->MapValues.m_value << endl;
        cout << "next is: " << p->next << endl;
        p = p->next;
    }
}

//insert to the beginning of linked list
bool Map::insert(const KeyType& key, const ValueType& value)
{
    Node *newNode = new Node;
    newNode->MapValues.m_key = key;
    newNode->MapValues.m_value = value;
    newNode->next = head;
    newNode->previous = nullptr; 
    head = newNode;
    m_size ++;
    return true;
}

bool Map::erase(const KeyType& key)
{
    
    //INSERT SOMETHING TO MAKE SURE IT'S IN DICTIONARY
    Node *ToDelete;
    Node *iterator = head;
    for (int i = 0; i < m_size; i ++)
    {
        if (iterator->MapValues.m_key == key)
        {
            ToDelete = iterator;
            break;
        }
        iterator = iterator->next;
    }
        
        //set the "next" of the element before to the element to the right of ToDelete
        ToDelete->previous->next = ToDelete->next;
        
        //set the "previous" of the element to the right to the "previous" of ToDelete
        ToDelete->next->previous = ToDelete->previous;
        
        //delete ToDelete
        delete ToDelete;
        m_size--;
        return true;
    
}


/*bool Map::get(const KeyType& key, ValueType& value) const
{
    
    return true;
    
} */

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    Node *iterator = head;
    for (int i = 0; i < m_size; i ++)
    {
        if (iterator->MapValues.m_key == key)
        {
            break;
        }
        else
        {
            iterator = iterator->next;
        }
    }
    value = iterator->MapValues.m_value;
    return true;
}
