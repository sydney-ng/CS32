#include "provided.h"
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    bool InputValidationPushMapping (string ciphertext, string plaintext);
    std::unordered_map<char,char> mymap;
};

TranslatorImpl::TranslatorImpl()
{
    char alpha = 'a';
    for (int i = 0; i < 26; i ++)
    {
        mymap.insert({alpha, '?'});
        alpha++;
    }
    
//    for ( auto it = mymap.begin(); it != mymap.end(); ++it )
//        std::cout << " " << it->first << ":" << it->second;
//    std::cout << std::endl;
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

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    //input validation
    if (InputValidationPushMapping (ciphertext,plaintext) == false)
    {
        return false;
    }
    
    //TranslatorMap tm;
    
    for (int i = 0; i < ciphertext.size(); i++)
    {
        
    }
    //check if there's already that table in the hash (most updated copy)
        //return false
    
    //else, it's valide
        //create a new map, combined with the old features
        //create the new associations (using hash)
    //return true
    return false;  // This compiles, but may not be correct
}

bool TranslatorImpl::popMapping()
{
    return false;  // This compiles, but may not be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    //make a string called temp
    
    //for each letter in cipher text
        //if it maps to a plaintext letter, add that letter to temp
    
        //else if it maps to nothing, add a ? to temp
    
        //else if it's not a letter, add that character to temp (apostrophe??)
    //return temp
    
    return ""; // This compiles, but may not be correct
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
