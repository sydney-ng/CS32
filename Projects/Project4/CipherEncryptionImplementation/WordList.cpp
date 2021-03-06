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
    MyHash <string, std::vector<string>> m_WLIHash;
    string createPattern (string readLine) const;
    bool InputValidation (string readLine);
    bool FindCandidateValidation (const string& cipherWord, const string& currTranslation);
    
};

string WordListImpl::createPattern (string readLine) const
{
    string temp ="";
    //make everything lower case
    for (int i = 0; i <readLine.size(); i ++)
    {
        temp += tolower(readLine[i]);
    }
    
    readLine = temp;
    
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
            if (readLine[previousRPindex] == readLine[currRPindex])
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
    //CALL RESET TO DO
    m_WLIHash.reset();
    ifstream ifs(filename);    // infile is a name of our choosing
    if (ifs)		        // Did opening the file fail?
    {
        string readLine;
        while (getline(ifs,readLine))
        {
            //cerr << endl;
            cerr << "we're on " << readLine << " ";
            //make sure that this is is valid
            if (InputValidation (readLine) == true)
            {
                //check to see if you've seen that word in wordlist before
                if (contains(readLine) == false)
                {
//                    cerr << "this is a new word " << endl;
                    //check if the word is new, not already in the list
                    string pattern = createPattern(readLine);
                    cerr << "it's pattern is : " << pattern << endl;

                    if (m_WLIHash.find(pattern) == nullptr)
                    {
                        vector<string> v;
                        v.push_back(readLine);
                        m_WLIHash.associate(pattern, v);
//                        cerr << "haven't seen " << readLine << " yet" << endl;
                    }
                    //if it already exists
                    else
                    {
                        vector<string> * vPointer = m_WLIHash.find(createPattern(readLine));
                        //add the word to that vector (updating the value)
                        vPointer->push_back (readLine);
                        m_WLIHash.associate(pattern, *vPointer);
//                        cerr << "we have seen " << readLine << " already BROOOO" << endl;
                        
                    }

                }
            }
        }
        string patt = createPattern("afpal");
        vector<string> * vPointer = m_WLIHash.find(createPattern (patt));
        for(std::vector<string>::const_iterator it = vPointer->begin(); it != vPointer->end(); ++it)
        {
            cerr << it->data() << endl;
        }
        return true; //means you were able to open the file
    }
    return false;  //unable to open file
}

bool WordListImpl::contains(string word) const
{
    cerr << "checking contains for : " << word << endl;
    //patternize the word
    string pattern = createPattern(word);//(word);
//    cerr << "the pattern for " << word << " is " << pattern << endl;
    //check if it's in a bucket of the hash table
    const std::vector<string>* PossibleWords = m_WLIHash.find(pattern);
    
    if (PossibleWords == nullptr)
    {
        return false;
    }
    
    else
    {
        //iterate through that bucket to check if it's in the value of something
        for(std::vector<string>::const_iterator it = PossibleWords->begin(); it != PossibleWords->end(); ++it)
        {
            string wordInVector = *it;
            bool flag = true;
            for (int i = 0; i < it->size(); i ++)
            {
                if (tolower(wordInVector[i]) != tolower(word[i]))
                {
                    flag = false;
                    break;
                }
            }
            if (flag == true)
            {
                return true; // you found the word
            }
        }
    }
    return false; //right bucket wrong word
}

bool FindCandidateValidation (const string& cipherWord, const string& currTranslation)
{
 
    if (cipherWord.size() != currTranslation.size())
    {
        return false;
    }
    //make sure that every letter is alphabetical
    for (int i = 0; i < cipherWord.size(); i++)
    {
        if (isalpha(cipherWord[i]) == false && cipherWord[i] != '\'')
        {
            return false;
        }
    }
    
    for (int j = 0; j < currTranslation.size(); j++)
    {
        if (isalpha(currTranslation[j]) == false && currTranslation[j] != '\'' && currTranslation[j] != '?')
        {
            return false;
        }
    }
    return true;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    //TO DO: FIX check parameters for cipherWord & currTranslation
    //if (FindCandidateValidation (cipherWord, currTranslation));
    //{return FinalVector; }

    //MAKE EVERYTHING LOWERCASE ->FINISHTHIS
    vector<string> FinalVector;
    //create a pattern for cipherWord;
    string CipherWordPattern = createPattern(cipherWord);
    const vector<string>*  cwMatchesVector = m_WLIHash.find(CipherWordPattern);
    
    if (cwMatchesVector == nullptr)
    {
        return FinalVector;
    }
    
    else
    {
        cerr << "size of vec is : " << cwMatchesVector->size() << endl;
    }
//    for(std::vector<string>::const_iterator it = cwMatchesVector->begin(); it != cwMatchesVector->end(); ++it)
//    {
//        cerr << it->data();
//    }
    
    for(std::vector<string>::const_iterator it = cwMatchesVector->begin(); it != cwMatchesVector->end(); ++it)
    {
        bool flag = true;
        string checkWord = *it;
        for (int i = 0; i < currTranslation.size(); i++)
        {
            //if currTranslation [i] is a letter, it must match
            if (isalpha(tolower(currTranslation[i])) == true)
            {
                //make sure that it's the same letter (upper or lower case)
                if (tolower(currTranslation[i]) != tolower(checkWord[i]))
                {
                    flag = false;
                    break;
                }
            }
            //if currTranslation [i] is a ?, then checkWord[i] must be a letter
            else if (currTranslation[i] == '?' && isalpha(checkWord[i]) == false)
            {
                flag = false;
                break;
            }
            //if currTranslation [i] is a ', then checkWord[i] must be a '
            else if (currTranslation[i] == '\'' && currTranslation[i] != '\'')
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            FinalVector.push_back(checkWord);
        }
    }
    //m_WLIHash->find(const std::basic_string<char> &key)
    //user pattern to get bucket, look at what's in the bucket
        //if all the conditions are met, then return the vector
    return FinalVector;  // This compiles, but may not be correct
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
