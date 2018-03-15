#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//TO DO MAKE THE FILE NAME GLOBAL
class DecrypterImpl
{
public:
    DecrypterImpl();
    ~DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList * m_WL;
    Translator * m_TranslatorP;
    Tokenizer * m_TokenizerP;
    vector<string> allWords;
    vector<string> seenWords;
    
    string ChooseWordToCrack();
};

DecrypterImpl::DecrypterImpl()
{
    m_WL = new WordList;
    m_WL->loadWordList("/Users/J/Desktop/CS32/Projects/Project4/CipherEncrypion/wordlist.txt");
    //STEP 1: create an empty mapping
    m_TranslatorP = new Translator;
    m_TokenizerP = new Tokenizer (",;:.!()[]{}-\"#$%^&");
}

DecrypterImpl::~DecrypterImpl()
{
    delete m_WL;
    delete m_TranslatorP;
    delete m_TokenizerP;
}

bool DecrypterImpl::load(string filename)
{
    return m_WL->loadWordList(filename);  //delegate to loadWordList
}

string DecrypterImpl::ChooseWordToCrack()
{
    if (allWords.size() == seenWords.size())
    {
        return "";
    }
    
    //set it equal to the first index and set curr number of question marks
    string toChooseWord = allWords[0];
    int currMaxQuestionmarks = 0;
    for (int k = 0; k < toChooseWord.size(); k++)
    {
        if (toChooseWord[k] == '?')
        {
            currMaxQuestionmarks ++;
        }
    }
    
    for (int i = 0; i < allWords.size(); i++)
    {
        //check if it's in seen words
        bool flag = true;
        for (int j = 0; j < seenWords.size(); j++)
        {
            if (allWords[i] == seenWords[j])
            {
                flag = false;
                break;
            }
        }
        //if it wasn't in seen words
        if (flag == true)
        {
            //count the number of ?
            int questionmarkCounter = 0;
            for (int k = 0; k < allWords[i].size(); k++)
            {
                if (allWords[i][k] == '?')
                {
                    questionmarkCounter ++;
                }
            }
            
            if (questionmarkCounter > currMaxQuestionmarks)
            {
                currMaxQuestionmarks = questionmarkCounter;
                toChooseWord = allWords[i];
            }
            //if its more than the number of ? in the chooseword, set this equal to choose word
                //append that word to seenwords
        }
    }
    return toChooseWord;
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    //STEP 2: tokenize & choose a word to crack
    allWords = m_TokenizerP->tokenize(ciphertext);
    cerr << "allwords size is: " << allWords.size();
    for (int i = 0; i <allWords.size(); i ++)
    {
        cerr << allWords[i]; 
    }    
    string crackWord = ChooseWordToCrack();
    
    //STEP 3: get translation for that word
    string CrackWordTranslation = m_TranslatorP->getTranslation(crackWord);
    //associate that translation with crackWord
    
    
    //STEP 4: getCandidates, a vec of strings of all possibilities
    vector<string> CandidateVector = m_WL->findCandidates(crackWord, CrackWordTranslation);
    for (int i =0; i < CandidateVector.size(); i ++)
    {
        cerr << CandidateVector[i] << endl;
    }
    
    //STEP 5: pop map & restart if it's empty
    if (CandidateVector.empty() == true)
    {
        m_TranslatorP->popMapping();
        crack(ciphertext);
    }
    
    //STEP 6: there are results, create a mapping for each
    else
    {
        for (int i =0; i < CandidateVector.size(); i ++)
        {
            //try to create a mapping for crackword + that possibility
            bool createdCharTranslation = m_TranslatorP->pushMapping(crackWord, CandidateVector[i]);
            if (createdCharTranslation == false)
            {
                //get rid of that mapping, will automatically move to the next word in vector
                m_TranslatorP->popMapping();
            }
            else
            {
                cerr << " a possibility is : " << CandidateVector[i] << endl;
            }
        }
    }
    return vector<string>();  // This compiles, but may not be correct
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
