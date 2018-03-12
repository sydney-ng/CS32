#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    string m_Delims;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    m_Delims = separators;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    for (int i = 0; i < s.size(); i++)
    {
        cout << s[i] << endl;
//        for (int j = 0; j< m_Delims.size(); j++)
//        {
//
//        }
    }
    return vector<string>();  // This compiles, but may not be correct
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
