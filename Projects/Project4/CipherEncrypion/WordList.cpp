#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
using namespace std;
//I added these:
#include <iostream>
#include <fstream>
using namespace std;
class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash <string, std::vector<string>> * m_WLIHash;
    string createPattern (string readLine) const;
    bool InputValidation (string readLine);
};

string WordListImpl::createPattern (string readLine) const
{
    //look @ the word & determine a word pattern from it
    char patternLetter = 'a';
    string returnPattern;
    for (int j = 0; j < readLine.size(); j++)
    {
        returnPattern = returnPattern + '@';
    }
    
    //iterate through everything in readLine
    for (int currRPindex = 0; currRPindex < returnPattern.size(); currRPindex++)
    {
        bool flag = true;
        //loop through the entire pattern
        for (int previousRPindex = 0; previousRPindex < currRPindex; previousRPindex++)
        {
            //if we haven't seen it before
            if (returnPattern[previousRPindex] == returnPattern[currRPindex])
            {
                returnPattern [currRPindex] = returnPattern[previousRPindex];
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            returnPattern [currRPindex] = patternLetter;
            patternLetter++;
        }
    }
    return returnPattern;
}

bool WordListImpl::InputValidation(string readLine)
{
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
    return flag;
}
bool WordListImpl::loadWordList(string filename)
{
    cerr << "in loadWordlist" << endl;
    string a = "baby";
    string b = createPattern(a);
    return true;
//    string pattern;
//    vector<string> answer;
//    ifstream infile(filename);    // infile is a name of our choosing
//    if (infile)		        // Did opening the file fail?
//    {
//        cerr << "you opened word list" << endl;
//
//        //create a new hash
//        m_WLIHash = new MyHash<string, vector<string>>::MyHash();
//        string readLine;
//        while (getline(infile,readLine))
//        {
//            //create the pattern
//            if (InputValidation (readLine) == true)
//            {
//                pattern = createPattern (readLine);
//                if (contains(pattern) == false)
//                {
//                    //findCandidates(string cipherWord, <#string currTranslation#>)
//                    m_WLIHash->associate(pattern, answer);
//                }
//            }
//        }
//        return true; //means you were able to open the file
//    }
//    return false;  //unable to open file
}

bool WordListImpl::contains(string word) const
{

    //patternize the word
    string pattern = createPattern(word);
    //check if it's in a bucket of the hash table
    vector<string> * PossibleWords = m_WLIHash->find(pattern);
    
    if (PossibleWords == nullptr)
    {
        return false;
    }

    else
    {
        //iterate through that bucket to check if it's in the value of something
        for(std::vector<string>::iterator it = PossibleWords->begin(); it != PossibleWords->end(); ++it)
        {
            //check if the
            if (*it == word)
            {
                return true;
            }
        }
    }
    return false; //right bucket num, but not there :(
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    //check parameters for cipherWord & currTranslation
    //user pattern to get bucket, look at what's in the bucket
        //if all the conditions are met, then return the vector
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
