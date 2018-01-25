// Map.cpp

#include "Map.h"

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

//using POINTER_THIS RIGHT???
Map::Map(const Map& other)
{
    Node *pointer_other;
    Node *pointer_this;
    //set head equal to the head of the other
    pointer_other = other.head;
    head = other.head;
    
    while (pointer_other != nullptr)
    {
        pointer_this->MapValues.m_key = pointer_other->MapValues.m_key;
        pointer_this->MapValues.m_value = pointer_other->MapValues.m_value;
        pointer_this->next = pointer_other->next;
        pointer_this->previous = pointer_other->previous;
        
        pointer_other = pointer_other->next;
        pointer_this = pointer_this->next;
    }
    tail = other.tail;
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

bool Map::erase(const KeyType& key)
{
    int pos = find(key);
    if (pos == -1)  // not found
        return false;
    
    // Move last array item to replace the one to be erased
    
    m_size--;
    m_data[pos] = m_data[m_size];
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    int pos = find(key);
    if (pos == -1)  // not found
        return false;
    value = m_data[pos].m_value;
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    key = m_data[i].m_key;
    value = m_data[i].m_value;
    return true;
}

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

Node* Map::find(const KeyType& key) const
{
    // Do a linear search through the array.
    
    if (head->next == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node *p;
        p = head;
        while (p != nullptr)
        {
            if (p->MapValues.m_key == key)
            {
                return p;
            }
            p = p->next;
        }
    }
    return nullptr;
    /*for (int pos = 0; pos < m_size; pos++)
        if (m_data[pos].m_key == key)
            return pos;
    return -1;*/
}

bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
                           bool mayInsert, bool mayUpdate)
{
    int pos = find(key);
    if (pos != -1)  // found
    {
        if (mayUpdate)
            m_data[pos].m_value = value;
        return mayUpdate;
    }
    if (!mayInsert)  // not found, and not allowed to insert
        return false;
    if (m_size == DEFAULT_MAX_ITEMS)  // no room to insert
        return false;
    m_data[m_size].m_key = key;
    m_data[m_size].m_value = value;
    m_size++;
    return true;
}
