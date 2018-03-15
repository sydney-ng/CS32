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
    vector<string> allCipherTextWords;
    vector<string> seenWords;
    
    string ChooseWordToCrack();
    int testTranslation();
    bool AtLeastOneWordTranslated (string possibleTranslation);
    void CrackHelperFunction(string ciphertext_message, vector<string>& output);

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
    if (allCipherTextWords.size() == seenWords.size())
    {
        return "";
    }
    string ctw = allCipherTextWords[0];
    //set it equal to the first index and set curr number of question marks
    string toChooseWordTranslation = m_TranslatorP->getTranslation(allCipherTextWords[0]);
    int currMaxQuestionmarks = 0;
    for (int k = 0; k < toChooseWordTranslation.size(); k++)
    {
        if (toChooseWordTranslation[k] == '?')
        {
            currMaxQuestionmarks ++;
        }
    }
    
    for (int i = 1; i < allCipherTextWords.size(); i++)
    {
        string compare = allCipherTextWords[i];
        //check if it's in seen words
        bool flag = true;
        for (int j = 0; j < seenWords.size(); j++)
        {
            if (allCipherTextWords[i] == seenWords[j])
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
            string ctw_Translated = m_TranslatorP->getTranslation(allCipherTextWords[i]);
            for (int k = 0; k < ctw_Translated.size(); k++)
            {
                if (ctw_Translated[k] == '?')
                {
                    questionmarkCounter ++;
                }
            }
            
            if (questionmarkCounter > currMaxQuestionmarks)
            {
                currMaxQuestionmarks = questionmarkCounter;
                toChooseWordTranslation = allCipherTextWords[i];
            }
            //if its more than the number of ? in the chooseword, set this equal to choose word
                //append that word to seenwords
        }
    }
    return toChooseWordTranslation;
}

bool DecrypterImpl::AtLeastOneWordTranslated (string possibleTranslation)
{
    return false;
}

int DecrypterImpl::testTranslation()
{
    
    //set a counter that tracks the number completed words that are in word list
    int numCorrectWords = 0;
    //use most updated map to translate ciphertext -> plaintext message
    for (int i = 0; i < allCipherTextWords.size(); i++)
    {
        string translated = m_TranslatorP->getTranslation(allCipherTextWords[i]);
        //STEP 6C: check if translated is a complete word
        bool flag = true;
        for (int k = 0; k < translated.size(); k++)
        {
            if (translated[k] == '?')
            {
                flag = false;
                break;
            }
        }
        //this is a complete word, proceed to step 6c.
        if (flag == true)
        {
            //check if it's in wordlist
            if (m_WL->contains(allCipherTextWords[i]) == true)
            {
                numCorrectWords ++;
            }
        }
    }
    return numCorrectWords;
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector <string> AnswerVector;
    CrackHelperFunction (ciphertext, AnswerVector);
    //sort the result
    //return that big Crack
    return AnswerVector;
}

void DecrypterImpl::CrackHelperFunction(string ciphertext, vector<string>& answer)
{
    //STEP 2: tokenize & choose a word to crack
    allCipherTextWords = m_TokenizerP->tokenize(ciphertext);
    
    string crackWord = ChooseWordToCrack();
    
//    //STEP 3: get translation for that word
//    string CrackWordTranslation = m_TranslatorP->getTranslation(crackWord);
//    
//    //STEP 4: getCandidates, a vec of strings of all possibilities
//    vector<string> CandidateVector = m_WL->findCandidates(crackWord, CrackWordTranslation);
////    for (int i =0; i < CandidateVector.size(); i ++)
////    {
////        cerr << CandidateVector[i] << endl;
////    }
//    
//    //STEP 5: pop map & restart if it's empty
//    if (CandidateVector.empty() == true)
//    {
//        m_TranslatorP->popMapping();
//        CrackHelperFunction(ciphertext, answer);
//    }
//    
//    //STEP 6: there are results, create a mapping for each
//    else
//    {
//        //counter here
//        for (int i =0; i < CandidateVector.size(); i ++)
//        {
//            //STEP 6A: creating a temporary mapping
//            //try to create a mapping for crackword + that possibility
//            bool createdCharTranslation = m_TranslatorP->pushMapping(crackWord, CandidateVector[i]);
//            if (createdCharTranslation == false)
//            {
//                //get rid of that mapping, will automatically move to the next word in vector
//                m_TranslatorP->popMapping();
//            }
//            else
//            {
//                //STEP 6B: TRY TO USE THIS TRANSLATION TO GET
//                string possibleTranslation = m_TranslatorP->getTranslation(crackWord);
//                //put allcipher words to see how many are matches
//                int numTranslatedWords = testTranslation ();
//                
//                //if no words were translated
//                if (numTranslatedWords <= 0)
//                {
//                    //pop map & it will automatically continue with step six
//                    m_TranslatorP->popMapping();
//                }
//                else
//                {
//                    if (numTranslatedWords == allCipherTextWords.size())
//                    {
//                        //put cipher text through get translation & add it to the vector
//                        string CorrectTranslation = m_TranslatorP->getTranslation(ciphertext);
//                        answer.push_back(CorrectTranslation);
//                    }
//                }
//                //IF TRUE -> CHECK IF NUMBER OF TRANSLATED WORDS == SIZE OF ALL CIPHER WORDS
//                //put cipher text through gettranslation
//                //OTHERWISE JUST CALL CRACK
//            }
//        }
//    }
//    
//    //at the very end, no matter what,
//    //create a new translator and set a new one (delete old)
//    Translator * new_translatorPointer = new Translator();
//    delete m_TranslatorP;
//    m_TranslatorP = new_translatorPointer;
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
