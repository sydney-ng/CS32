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
unsigned int MyHash<KeyType, ValueType>:: getBucketNumber(const KeyType &key) const
{
    //hash the word, determine which bucket it will go in
    
    unsigned int hash(const KeyType &k);
    unsigned int numHash = hash(key);
    unsigned int bucketNum = numHash % m_HashSize;
    return bucketNum;
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
