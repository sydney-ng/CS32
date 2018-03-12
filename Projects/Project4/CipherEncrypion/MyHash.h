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
        KeyType key;
        ValueType value;
    };
    
    //private member variables
        //The pointer to the first entry of the hash table
        Node * m_HashTable;
        //how much you're going to increase size by
        int m_IncreaseFactor;
        int m_HashSize;
        int m_NumAssociations;
    
    //private functions
    void generateHash();
    
};

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
 {
 return std::hash<int>()(i);
 }
 
unsigned int hash(const char& c)
 {
 return std::hash<char>()(c);
 }

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
{
    m_HashTable = nullptr;
    m_IncreaseFactor = 1;
    m_HashSize = 0;
    m_NumAssociations = 0;
    generateHash();
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::generateHash()
{
    m_HashTable = new Node[100 * m_IncreaseFactor];
    m_IncreaseFactor = m_IncreaseFactor *2;
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
        Node* current = *m_HashTable[i];
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
    double LF = (m_NumAssociations/m_HashSize)/2;
    return LF;
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    
}

