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
    Node *newNode = new Node;

    //this is our first time adding something to the linked list
    if (head == nullptr)
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
    Node *Killme = head;
    //make sure list isn't empty
    if (head == nullptr)
    {
        return false;
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
        tail = Killme->previous;
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
                Killme = iterator->next;
                iterator->next = Killme->next;
                Killme->next->previous = iterator;
                m_size--;
                delete Killme;
                return true;
            }
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
    //NEED TO WRITE THE CHECKING PART
    //make sure that i is within range
    if (i<0 || i >= size())
    {
        return false; 
    }
    
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

