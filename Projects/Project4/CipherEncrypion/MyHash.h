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
        int m_IncreaseFactor;
        int m_HashSize;
        int m_NumAssociations;
    
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
    m_IncreaseFactor = 1;
    m_HashTable = new Node * [m_IncreaseFactor*100];
    for (int i = 0; i < 100; i ++)
    {
        m_HashTable [i] = nullptr; 
    }
    m_HashSize = 0;
    m_NumAssociations = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::GenerateAHashTable()
{
    Node **oldHash = m_HashTable;
    m_HashTable = new Node  *[m_IncreaseFactor*100];
    CopyEntriesOver(oldHash);
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::CopyEntriesOver(Node ** oldHash)
{
    //iterate through everything in the hash
    //m_HashSize should still be the original number of buckets
    for (int i = 0; i < m_HashSize; i++)
    {
        if (oldHash[i] != nullptr)
        {
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
    if (getLoadFactor() > 0.5 || getLoadFactor() == 0.5)
    {
        m_IncreaseFactor++;
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

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_NumAssociations;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    double LF = (m_NumAssociations/m_HashSize);
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
            *ValTypePointer = iterator->value;
            return ValTypePointer;
        }
    }
    return nullptr;
    //return pointer to value NOT THE KEY
}

template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>:: getBucketNumber(const KeyType &key) const
{
    //hash the word, determine which bucket it will go in
    
    unsigned int hash(const KeyType &k);
    unsigned int numHash = hash(key);
    unsigned int bucketNum = numHash % m_HashSize;
    return bucketNum;
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
        while (iterateNode != nullptr)
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
//
//#ifndef MYHASH_INCLUDED
//#define MYHASH_INCLUDED
//
//#include <unordered_map>  // YOU MUST NOT USE THIS HEADER IN CODE YOU TURN IN
//#include <algorithm>
//
//// In accordance with the spec, YOU MUST NOT TURN IN THIS CLASS TEMPLATE,
//// since you are not allowed to use any STL containers, and this
//// implementation uses std::unordered_map.
//
//// This code is deliberately obfuscated.
//
//// If you can not get your own MyHash class template working, you may use
//// this one during development in order to let you proceed with implementing
//// the other classes for this project; you can then go back to working on
//// fixing your own MyHash class template.
//
//template<typename KeyType, typename ValueType>
//class MyHash
//{
//public:
//    MyHash(const MyHash&) = delete;
//    MyHash& operator=(const MyHash&) = delete;
//    using O=KeyType;using maxloadfactor=float;using O10=int;void reset(){
//        maxloadfactor max_1oad_factor=l01.max_load_factor();l01.clear();l01.
//        max_load_factor(max_1oad_factor);l01.rehash(doub1e+doub1e);}using String=
//    double;using l0=ValueType;using l1O=O10 const;MyHash(String d0uble=doub1e/10):
//    l01(doub1e+doub1e){l01.max_load_factor(std::min<maxloadfactor>(doub1e/5/5,
//                                                                   std::max<maxloadfactor>((double)doub1e/(doub1e+doub1e),d0uble)));}using l10=O
//    const;using Const=MyHash<O,l0>;String getLoadFactor()const{return l01.
//        load_factor();}using ll0=l0 const;O10 getNumItems()const{return l01.size(
//            );}using l00=Const const;void associate(l10&Using,ll0&first){l01[Using]=
//                first;}using l1=std::unordered_map<O,l0>;ll0*find(l10&l11)const{auto first(l01.
//                                                                                           find(l11));return(first!=l01.end()?&first->second:0);}l0*find(l10&l01){return(
//                                                                                                                                                                         l0*)(*(l00*)(this)).find(l01);}private:static l1O doub1e{50};l1 l01;
//};
//
//#endif // MYHASH_INCLUDED