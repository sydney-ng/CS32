#include "provided.h"
#include <string>
#include <map>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    std::map<char,char> MostCurrentMap;
    vector<map<char,char>> VectorOfMaps;
    std::map<char,char> getMostCurrentMap();
    bool CheckForInconsistency(string i, string ciphertext);
    bool InputValidationPushMapping (string ciphertext, string plaintext);


};

std::map<char,char> TranslatorImpl::getMostCurrentMap()
{
    std::map<char,char> v = VectorOfMaps[VectorOfMaps.size()-1];
    return v;
}

TranslatorImpl::TranslatorImpl()
{
    std::map<char,char> mymap;
    char alpha = 'a';
    for (int i = 0; i < 26; i ++)
    {
        mymap.insert({alpha, '?'});
        alpha++;
    }
    
//    for ( auto it = mymap.begin(); it != mymap.end(); ++it )
//        std::cout << " " << it->first << ":" << it->second;
//    std::cout << std::endl;
    
    VectorOfMaps.push_back(mymap);
}

bool TranslatorImpl::InputValidationPushMapping (string ciphertext, string plaintext)
{
    //parameters not the same length
    if (ciphertext.size() != plaintext.size())
    {
        return false;
    }
    
    //check if either have a non letter
    for (int i = 0; i < ciphertext.size(); i++)
    {
        if (isalpha (ciphertext[i]) == false || isalpha (plaintext[i]) == false)
        {
            return false;
        }
    }
    return true;
}

//ciphertext => dhl
//plaintext = erd
bool TranslatorImpl:: CheckForInconsistency(string plaintext, string ciphertext)
{
    for (int i =0; i < plaintext.size(); i++)
    {
        
        for (auto it = VectorOfMaps[VectorOfMaps.size()-1].begin(); it != VectorOfMaps[VectorOfMaps.size()-1].end(); ++it )
        {
            //if second is erd
            if (it->second == plaintext[i])
            {
                //make sure that it's the cipher text letter that is mapping to it
                if (it-> first != ciphertext[i])
                {
                    return false;
                }
            }
            
        }
    }
    return true;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    //input validation -> checks for non-letter or not same length
    if (InputValidationPushMapping (ciphertext,plaintext) == false)
    {
        return false;
    }
    
    bool inconsistent = CheckForInconsistency(plaintext, ciphertext);
    if (inconsistent == false)
    {
        return false;
    }

    map<char,char> newMap = getMostCurrentMap();
    for (int i = 0; i < ciphertext.size(); i++)
    {
        //TO-DO: CONVERT THIS TO LOWER LATER
        
        std::map<char, char>::iterator it = newMap.find(ciphertext[i]);
        //iterate through the map
        if (it != newMap.end())
        {
            //link that char -> char
            it->second = plaintext[i];
        }
    }
    
    VectorOfMaps.push_back(newMap);
    
    return true;  // This compiles, but may not be correct
}

bool TranslatorImpl::popMapping()
{
    MostCurrentMap = getMostCurrentMap();
    return false;  // This compiles, but may not be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    //make a string called temp
    string temp = "";
    
    //for each letter in cipher text
    for (int i = 0; i < ciphertext.size(); i++)
    {
        //if it maps to a plaintext letter, add that letter to temp
        if (isalpha (ciphertext[i]) == true)
        {
            std::map<char, char>::const_iterator iterator = MostCurrentMap.find(ciphertext[i]);
            //iterate through the map
            if (iterator != MostCurrentMap.end())
            {
                //iterator is now a pointer to that element (with first + second)
                //if the second one is a letter too
                if (isalpha(iterator->second))
                {
                    temp += iterator->second;
                }
                //else if it maps to nothing, add a ? to temp
                else if (iterator->second == '?')
                {
                    temp += iterator->second;
                }
            }
            
        }
        //else if it's not a letter, add that character to temp (apostrophe??)
        else
        {
            temp+= ciphertext[i];
        }

    }
    return "temp"; // This compiles, but may not be correct
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
