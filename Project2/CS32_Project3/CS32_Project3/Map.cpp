                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        // Map.cpp
#include "Map.h"
//TAKE THIS OUT BEFORE TURNING IN

//do I initialize the MapValues????
Map::Map()
: m_size(0), tail(nullptr), head (nullptr)
{
}

Map::~Map()
{
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
    Node *newFirstNode = new Node;
    
    //get first node in other
    newFirstNode->MapValues = other.head->MapValues;
    newFirstNode->previous = nullptr;
    newFirstNode->next = nullptr;
    head = newFirstNode;
    Node *other_iterator = other.head->next;
    
    while (other_iterator != nullptr)
    {
        //create a new node
        Node *newNode = new Node;
        
        //give it the values of map
        newNode->MapValues = other_iterator->MapValues;
        //set previous/next
        newNode->next = nullptr;
        newNode->previous = newFirstNode;
        
        //set the next of the node before it
        newNode->previous->next = newNode;
        
        newFirstNode = newFirstNode->next;
        other_iterator = other_iterator->next;
        
    }
    
    tail = newFirstNode;
    m_size = other.size();
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
    //CASE IF THERE'S ONLY ONE NODE
    
    Node *Killme = head;
    //make sure list isn't empty
    if (empty() == true)
    {
        return false;
    }
    
    if(Killme->next == nullptr)
    {
        head = nullptr;
        delete Killme; 
        m_size--;
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
        cout << "cool beans" << endl;
        cerr << "made it here" << endl;
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
    KeyType empty_result_key;
    ValueType empty_result_val;
    if (result.size() > 0)
    {
        for (int result_iter1 = 0; result_iter1 < result.size(); result_iter1 ++)
        {
            result.get(result_iter1, empty_result_key, empty_result_val);
            cerr << "empty result key: " << empty_result_key << endl;
            cerr << "empty result value: " << empty_result_val << endl;
            result.erase(empty_result_key);
        }
    }
    
    else{
        cout << "it's empty" << endl;
    }
   
    return true;

   /* KeyType my_key;
    ValueType my_val;
    
    //loop through map 1
    for (int map1_iter = 0; map1_iter < m1.size(); map1_iter ++)
    {
        //make sure that get returns true (aka there is something to return)
        if (result.get(map1_iter, my_key, my_val))
        {
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
    }
    
    KeyType my_key2;
    ValueType my_val2;
    
    //find unique entries in map2, you don't need to do the ones in both
    //that was satisfied by first for loop
    for (int map2_iter = 0; map2_iter < m2.size(); map2_iter ++)
    {
        //make sure that get returns true (aka there is something to return)
        if (result.get(map2_iter, my_key2, my_val2))
        {
            //if it's not in m1
            if (m1.contains(my_key2) == false)
            {
                result.insert(my_key2, my_val2);
            }
    
        }
    }
    return flag; */
}

//PREVENT ALIASING
void subtract(const Map& m1, const Map& m2, Map& result)
{
    //empty result
    KeyType empty_result_key;
    ValueType empty_result_val;
    for (int result_iter1 = 0; result_iter1 < result.size(); result_iter1 ++)
    {
        result.get(result_iter1, empty_result_key, empty_result_val);
        result.erase(empty_result_key);
    }
    
    KeyType my_key;
    ValueType my_val;
    
    for (int map1_iter = 0; map1_iter < m1.size(); map1_iter ++)
    {
        //make sure that get returns true (aka there is something to return)
        if (result.get(map1_iter, my_key, my_val))
        {
            //if it's not in m2
            if (m2.contains(my_key) == false)
            {
                result.insert(my_key, my_val);
            }

        }
    }
}
