#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
using namespace std;
//I added these:
#include <iostream>
#include <fstream>

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash <int, string> * m_WLIHash;
    
};

bool WordListImpl::loadWordList(string filename)
{
    ifstream infile(filename);    // infile is a name of our choosing
    if (infile)		        // Did opening the file fail?
    {
        cerr << "you opened word list" << endl;

        //create a new hash
        m_WLIHash = new MyHash<int,string>::MyHash();
        string readLine;
        while (getline(infile,readLine))
        {
            //TO-DO: MAKE SURE IT'S NOT ALREADY IN THE HASH
            
            //input validation
            bool flag = true;
            for (int i =0; i < readLine.size(); i++)
            {
                //this is a word that is not part of the word list
                if (isalpha(readLine[i]) == false && readLine[i] != '\'')
                {
                    flag = false;
                    break;
                }
            }
            
            //this is a valid word
            if (flag == true)
            {
                //TO-DO: add it to the Hash
                unsigned int hash (const string &k);
                int hashNum = hash(readLine);
                //TO-DO: change the empty string
                m_WLIHash->associate(hashNum, readLine);
            }
        }
        return true; //means you were able to open the file
    }
    
    return false;  //unable to open file
}

bool WordListImpl::contains(string word) const
{
    
    return false; // This compiles, but may not be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    return vector<string>();  // This compiles, but may not be correct
}

//***** hash functions for string, int, and char *****

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

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
