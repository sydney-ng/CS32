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
    //cerr << "here" << endl;
    vector<string>completeWordsVector;
    string temp = "";
    for (int i =0; i < s.size(); i++)
    {
        //this is a valid word so far
        bool flag = true;
        //cerr << "checking " << s[i] << endl;
        for (int j = 0; j < m_Delims.size(); j++)
        {
            if (s[i] == m_Delims[j])
            {
                if (temp == "")
                {
                    flag = false;
                    break;
                }
                else
                {
                    completeWordsVector.push_back(temp);
                    //cerr << "this is a delim" << endl;
                    temp = "";
                    flag = false;
                    break;
                }
            }
        }
        if (flag == true)
        {
            temp += s[i];
        }
    }
    if (temp != "")
    {
        completeWordsVector.push_back(temp);
    }
//    cerr << "the final vector is: " << endl;
//    for (int i = 0; i < completeWordsVector.size(); i ++)
//    {
//        cerr << completeWordsVector[i] << endl;
//    }
    
    return completeWordsVector;  // This compiles, but may not be correct
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
