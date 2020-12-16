//
//// MyHash.h
//
//// Skeleton for the MyHash class template.  You must implement the first seven
//// member functions; we have implemented the eighth.
////REMOVE:
//#include <iostream>
//using namespace std;
//
//template<typename KeyType, typename ValueType>
//class MyHash
//{
//public:
//    MyHash(double maxLoadFactor = 0.5);
//    ~MyHash()
//    {
//        for (int i = 0; i < m_HashSize; i++)
//        {
//            Node* current = m_HashTable[i];
//            if (current != nullptr)
//            {
//                deleteNodes(current);
//            }
//        }
//        delete [] m_HashTable;
//    }
//    
//    void reset();
//    void associate(const KeyType& key, const ValueType& value);
//    int getNumItems() const;
//    double getLoadFactor() const;
//
//      // for a map that can't be modified, return a pointer to const ValueType
//    const ValueType* find(const KeyType& key) const;
//
//      // for a modifiable map, return a pointer to modifiable ValueType
//    ValueType* find(const KeyType& key)
//    {
//        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
//    }
//
//      // C++11 syntax for preventing copying and assignment
//    MyHash(const MyHash&) = delete;
//    MyHash& operator=(const MyHash&) = delete;
//private:
//    struct Node
//    {
//        Node * nextEntry;
//        ValueType value;
//        KeyType key;
//    };
//    
//    //private member variables
//        //The pointer to the first entry of the hash table
//        Node ** m_HashTable;
//        //how much you're going to increase size by
//        //int m_IncreaseFactor;
//        int m_HashSize;
//        int m_NumAssociations;
//        double m_MaxLoadFator;
//    
//    //private functions
//    void PossiblyResize();
//    void GenerateAHashTable();
//    void CopyEntriesOver(Node ** oldHash);
//    unsigned int getBucketNumber(const KeyType &key) const;
//    bool CheckIfExists(const KeyType& key);
//    void AddNewEntry(const KeyType& key, const ValueType& value, int bucketNum);
//    void UpdateEntry(const KeyType& key, const ValueType& value, unsigned int bucketNum);
//    void deleteNodes(Node * node)
//    {
//        if (node == nullptr)
//        {
//            return;
//        }
//        if (node->nextEntry != nullptr)
//        {
//            deleteNodes(node->nextEntry);
//        }
//        delete node;
//        return;
//    };
//};
//
//template<typename KeyType, typename ValueType>
//MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
//{
//    m_MaxLoadFator = maxLoadFactor >2 ? 2.0 : 0.5;
//    
//    m_HashTable = new Node * [100];
//    for (int i = 0; i < 100; i ++)
//    {
//        m_HashTable [i] = nullptr; 
//    }
//    m_HashSize = 100;
//    m_NumAssociations = 0;
//}
//
//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::GenerateAHashTable()
//{
//    Node **oldHash = m_HashTable;
//    m_HashTable = new Node  *[m_HashSize];
//    CopyEntriesOver(oldHash);
//}
//
//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::CopyEntriesOver(Node ** oldHash)
//{
//    //iterate through everything in the hash
//    for (int i = 0; i < m_HashSize/2; i++)
//    {
//        //if the bucket isn't null
//        if (oldHash[i] != nullptr)
//        {
//            //copy everything over to the new hash
//            Node * iterator = oldHash[i];
//            while(iterator != nullptr)
//            {
//                associate(iterator->key, iterator->value);
//                iterator = iterator->nextEntry;
//            }
//        }
//    }
//    
//    //delete everything in the oldHash now
//    delete [] oldHash;
//}
//
//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::PossiblyResize()
//{
//    if (getLoadFactor() >= m_MaxLoadFator)
//    {
//        //m_IncreaseFactor++;
//        m_HashSize *=2;
//        GenerateAHashTable();
//    }
//
//}
//
//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::reset()
//{
//    for (int i = 0; i < m_HashSize; i++)
//    {
//        Node* current = m_HashTable[i];
//        if (current != nullptr)
//        {
//            deleteNodes(current);
//        }
//    }
//    delete [] m_HashTable;
//    
//    m_HashSize = 100;
//    m_NumAssociations = 0;
//    
//    m_HashTable = new Node *[m_HashSize];
//    for (int i =0; i < m_HashSize; i++)
//    {
//        m_HashTable[i] = nullptr;
//    }
//}
//
////returns # of buckets being used
//template<typename KeyType, typename ValueType>
//int MyHash<KeyType, ValueType>::getNumItems() const
//{
//    return m_NumAssociations;
//}
//
//template<typename KeyType, typename ValueType>
//double MyHash<KeyType, ValueType>::getLoadFactor() const
//{
//    double HashSize = m_HashSize * 1.0;
//    double LF = (m_NumAssociations+1/HashSize);
//    //cerr << "LF IS : " << LF << endl;
//    return LF;
//}
//
//template<typename KeyType, typename ValueType>
//const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
//{
//    //hash the key
//    unsigned int buckNum = getBucketNumber(key);
//    //search that bucket
//    Node * iterator = m_HashTable[buckNum];
//    while (iterator != nullptr)
//    {
//        if (iterator->key == key)
//        {
//            ValueType * ValTypePointer;
//            ValTypePointer = &(iterator->value);
//            return ValTypePointer;
//        }
//        iterator = iterator->nextEntry;
//    }
//    return nullptr;
//    //return pointer to value NOT THE KEY
//}
//
//template<typename KeyType, typename ValueType>
//unsigned int MyHash<KeyType, ValueType>:: getBucketNumber(const KeyType &key) const
//{
//    //hash the word, determine which bucket it will go in
//    unsigned int hash(const KeyType &k);
//    unsigned int numHash = hash(key) % m_HashSize;
//    return numHash;
//}
//
//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::AddNewEntry(const KeyType& key, const ValueType& value, int bucketNum)
//{
//    Node * newNode = new Node();
//    newNode->key = key;
//    newNode->value = value;
//    newNode->nextEntry = nullptr;
//    
//    if (m_HashTable[bucketNum] == nullptr)
//    {
//        m_HashTable[bucketNum] = newNode;
//    }
//    
//    else
//    {
//        //traverse to the end of this linked list
//        Node * iterateNode = m_HashTable[bucketNum];
//        while (iterateNode->nextEntry!= nullptr)
//        {
//            if (iterateNode->value == value)
//            {
//                return;
//            }
//            iterateNode = iterateNode->nextEntry;
//        }
//        //you have made it to the end, make the next entry that node
//        iterateNode->nextEntry = newNode;
//    }
//    m_NumAssociations++;
//}
//
//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::UpdateEntry(const KeyType& key, const ValueType& value, unsigned int bucketNum)
//{
//    Node * iterateNode = m_HashTable[bucketNum];
//    while (iterateNode != nullptr)
//    {
//        if (iterateNode->key == key)
//        {
//            iterateNode->value = value;
//        }
//        iterateNode = iterateNode->nextEntry;
//    }
//}
//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
//{
//    //depending on the number, add it to the hash table
//    unsigned int bucketNum = getBucketNumber(key);
//    
//    //if it's not there
//    if (CheckIfExists(key) == false)
//    {
//        PossiblyResize();
//        AddNewEntry(key, value, bucketNum);
//    }
//
//    //this already exists, so overwrite it
//    else
//    {
//        UpdateEntry(key, value, bucketNum);
//    }
//}
//
//template<typename KeyType, typename ValueType>
//bool MyHash<KeyType, ValueType>::CheckIfExists(const KeyType& key)
//{
//    ValueType * valTypePointer = find(key);
//    if (valTypePointer == nullptr)
//    {
//        return false;
//    }
//    return true;
//}





// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
private:
    struct Node
    {
    public:
        Node * nextEntry;
        ValueType value;
        KeyType key;
    };

    //private member variables
        //The pointer to the first entry of the hash table
        Node ** m_HashTable;
        //how much you're going to increase size by
        //int m_IncreaseFactor;
        int m_HashSize;
        int m_NumAssociations;
        int m_MaxLoadFator;

    //private functions
    void PossiblyResize();
    void GenerateAHashTable();
    void CopyEntriesOver(Node ** oldHash);
    unsigned int getBucketNumber(const KeyType &key) const;
    bool CheckIfExists(const KeyType& key);
    void AddNewEntry(const KeyType& key, const ValueType& value, int bucketNum);
    void UpdateEntry(const KeyType& key, const ValueType& value, int bucketNum);
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
{
    //m_IncreaseFactor = 1;
    if (maxLoadFactor > 2)
    {
        m_MaxLoadFator = 2;
    }
    else
    {
        m_MaxLoadFator = 0.5;

    }
    m_HashTable = new Node * [100];
    for (int i = 0; i < 100; i ++)
    {
        m_HashTable [i] = nullptr;
    }
    m_HashSize = 100;
    m_NumAssociations = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::GenerateAHashTable()
{
    Node **oldHash = m_HashTable;
    m_HashTable = new Node  *[m_HashSize];
    CopyEntriesOver(oldHash);
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::CopyEntriesOver(Node ** oldHash)
{
    //iterate through everything in the hash
    for (int i = 0; i < m_HashSize/2; i++)
    {
        //if the bucket isn't null
        if (oldHash[i] != nullptr)
        {
            //copy everything over to the new hash
            Node * iterator = oldHash[i];
            while(iterator != nullptr)
            {
                associate(iterator->key, iterator->value);
                iterator = iterator->nextEntry;
            }
        }
    }

    //delete everything in the oldHash now
    delete [] oldHash;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::PossiblyResize()
{
    if (getLoadFactor() >= m_MaxLoadFator)
    {
        //m_IncreaseFactor++;
        m_HashSize *=2;
        GenerateAHashTable();
    }
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
    reset();
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    for (int i = 0; i < m_HashSize; i++)
    {
        Node* current = m_HashTable[i];
        while (current->nextEntry != nullptr)
        {
            Node * deleteMe = current;
            current = deleteMe->nextEntry;
            delete deleteMe;
        }
        delete m_HashTable[i];
    }
}

//returns # of buckets being used
template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_NumAssociations;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    double LF = 1 + (m_NumAssociations/(m_HashSize/2));
    return LF;
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    //hash the key
    unsigned int buckNum = getBucketNumber(key);
    //search that bucket
    Node * iterator = m_HashTable[buckNum];
    while (iterator != nullptr)
    {
        if (iterator->key == key)
        {
            ValueType * ValTypePointer;
            ValTypePointer = &(iterator->value);
            return ValTypePointer;
        }
        iterator = iterator->nextEntry;
    }
    return nullptr;
    //return pointer to value NOT THE KEY
}

template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>:: getBucketNumber(const KeyType &key) const
{
    //hash the word, determine which bucket it will go in
    unsigned int hash(const KeyType &k);
    unsigned int numHash = hash(key) % m_HashSize;
    return numHash;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::AddNewEntry(const KeyType& key, const ValueType& value, int bucketNum)
{
    Node * newNode = new Node();
    newNode->key = key;
    newNode->value = value;
    newNode->nextEntry = nullptr;

    if (m_HashTable[bucketNum] == nullptr)
    {
        m_HashTable[bucketNum] = newNode;
    }

    else
    {
        //traverse to the end of this linked list
        Node * iterateNode = m_HashTable[bucketNum];
        while (iterateNode->nextEntry!= nullptr)
        {
            iterateNode = iterateNode->nextEntry;
        }
        //you have made it to the end, make the next entry that node
        iterateNode->nextEntry = newNode;
    }
    m_NumAssociations++;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::UpdateEntry(const KeyType& key, const ValueType& value, int bucketNum)
{
    Node * iterateNode = m_HashTable[bucketNum];
    while (iterateNode != nullptr)
    {
        if (iterateNode->key == key)
        {
            iterateNode->value = value;
        }
    }
}
template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    //depending on the number, add it to the hash table
    int bucketNum = getBucketNumber(key);

    //if it's not there
    if (CheckIfExists(key) == false)
    {
        PossiblyResize();
        AddNewEntry(key, value, bucketNum);
    }

    //this already exists, so overwrite it
    else
    {
        UpdateEntry(key, value, bucketNum);
    }
}

template<typename KeyType, typename ValueType>
bool MyHash<KeyType, ValueType>::CheckIfExists(const KeyType& key)
{
    ValueType * valTypePointer = find(key);
    if (valTypePointer == nullptr)
    {
        return false;
    }
    return true;
}
