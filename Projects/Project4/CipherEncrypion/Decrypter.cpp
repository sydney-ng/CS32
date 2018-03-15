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
    bool testTranslation();
    bool AtLeastOneWordTranslated (string possibleTranslation);
    string CrackHelperFunction(string ciphertext_message, vector<string>& output);
    int numFullyTranslated();
    void StepSix();

};

DecrypterImpl::DecrypterImpl()
{
    m_WL = new WordList;
    m_WL->loadWordList("/Users/J/Desktop/CS32/Projects/Project4/CipherEncrypion/wordlist.txt");
    //STEP 1: create an empty mapping
    m_TranslatorP = new Translator;
    m_TokenizerP = new Tokenizer (",;:.!()[]{}-\"#$%^& ");
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
    
    //string ctw = allCipherTextWords[0];
    string toChooseWord = allCipherTextWords[0];
    //set it equal to the first index and set curr number of question marks
//    cerr << "allciphertextwords size is in choosewordtocrack: " << allCipherTextWords.size();
    for (int a = 0; a < allCipherTextWords.size(); a++)
    {
        bool flag = true;
        for (int j = 0; j < seenWords.size(); j++)
        {
            if (allCipherTextWords[a] == seenWords[j])
            {
                flag = false;
                break;
            }
        }
        //if it wasn't in seen words
        if (flag == true)
        {
            cerr << "let's use " << allCipherTextWords [a] << endl;
            toChooseWord = allCipherTextWords[a];
        }
    }
    string translatedPivot = m_TranslatorP->getTranslation(allCipherTextWords[0]);
    int currMaxQuestionmarks = 0;
    for (int k = 0; k < translatedPivot.size(); k++)
    {
        if (translatedPivot[k] == '?')
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
                toChooseWord = allCipherTextWords[i];
                cerr << "let's use " << allCipherTextWords [i] << endl;

            }
            //if its more than the number of ? in the chooseword, set this equal to choose word
                //append that word to seenwords
        }
    }
    seenWords.push_back(toChooseWord);
    return toChooseWord;
}

bool DecrypterImpl::AtLeastOneWordTranslated (string possibleTranslation)
{
    return false;
}

int DecrypterImpl::numFullyTranslated()
{
    int numFullWords = 0;
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
            //check if it's in wordlist, it must be!!! or return false
            if (m_WL->contains(translated) == true)
            {
                numFullWords++;
            }
        }
    }
    
    return numFullWords;
}

bool DecrypterImpl::testTranslation()
{
    
    //use most updated map to translate ciphertext -> plaintext message
    for (int i = 0; i < allCipherTextWords.size(); i++)
    {
        string x = allCipherTextWords[i];
        cerr << "cipher text is : " << x << endl;
        string translated = m_TranslatorP->getTranslation(allCipherTextWords[i]);
        cerr << "cipher text translated is: " << translated << endl;
        //STEP 6C: check if translated is a complete word
        bool flag = true;
        for (int k = 0; k < translated.size(); k++)
        {
            char translatedChar = translated[k];
            if (translated[k] == '?')
            {
                flag = false;
                break;
            }
        }
        //this is a complete word, proceed to step 6c.
        if (flag == true)
        {
            //check if it's in wordlist, it must be!!! or return false
            if (m_WL->contains(translated) == false)
            {
                return false;
            }
        }
        else{
            continue;
        }
    }
    
    return true;
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector <string> AnswerVector;
    CrackHelperFunction (ciphertext, AnswerVector);
    //sort the result
    //return that big Crack
    return AnswerVector;
}

void DecrypterImpl::StepSix();

string DecrypterImpl::CrackHelperFunction(string ciphertext, vector<string>& answer)
{
    //STEP 2A: tokenize
    allCipherTextWords = m_TokenizerP->tokenize(ciphertext);
    cerr << "allciphertextwords size is in choosewordtocrack: " << allCipherTextWords.size();

        for (int i =0; i < allCipherTextWords.size(); i ++)
        {
            cerr << allCipherTextWords[i] << endl;
        }
    //STEP 2B: choose word to crack
    string crackWord = ChooseWordToCrack();
    cerr << "crackword is: " <<  crackWord << endl;
    if (crackWord.size () < 1)
    {
        return "";
    }
    
    //STEP 3: get translation for that word
    string CrackWordTranslation = m_TranslatorP->getTranslation(crackWord);
    
    //STEP 4: getCandidates, a vec of strings of all possibilities
    vector<string> CandidateVector = m_WL->findCandidates(crackWord, CrackWordTranslation);
    
//    for (int i =0; i < CandidateVector.size(); i ++)
//    {
//        cerr << CandidateVector[i] << endl;
//    }
    
    //STEP 5: pop map & restart if it's empty
    if (CandidateVector.empty() == true)
    {
        m_TranslatorP->popMapping();
        return CrackHelperFunction(ciphertext, answer);
    }
    
    //STEP 6: there are results, create a mapping for each
    else
    {
        //for each candidate
        for (int i =0; i < CandidateVector.size(); i ++)
        {
            //STEP 6A: creating a temporary mapping
            //try to create a mapping for crackword + that possibility
            bool createdCharTranslation = m_TranslatorP->pushMapping(crackWord, CandidateVector[i]);
            if (createdCharTranslation == false)
            {
                //get rid of that mapping, will automatically move to the next word in vector
                m_TranslatorP->popMapping();
            }
            //you were able to push & make the association
            else
            {
                //STEP 6B: try to translate the entire cipher text using this
//                string possibleTranslation = m_TranslatorP->getTranslation(crackWord);
                //put allcipher words to see how many are matches
                bool noDiscrepancies = testTranslation ();
                
                //if no words were translated
                if (noDiscrepancies == false)
                {
                    //pop map & it will automatically continue with step six
                    m_TranslatorP->popMapping();
                }
                //else, there were no discrepancies for any fully translated words
                else
                {
                    string CorrectTranslation = m_TranslatorP->getTranslation(ciphertext);
                    cerr << "our current translation is: " << CorrectTranslation <<endl;
                    cerr << "we have fully translated " << numFullyTranslated() << " words " << endl;
                    //if this is a full, correct solution
                    if (numFullyTranslated() == allCipherTextWords.size())
                    {
                        //put cipher text through get translation & add it to the vector
                        string CorrectTranslation = m_TranslatorP->getTranslation(ciphertext);
                        cerr << CorrectTranslation << " is a valid solution " << endl;
                        answer.push_back(CorrectTranslation);
                        m_TranslatorP->popMapping();
                    }
                    
                    //this is not a full,correct solution, keep trying!
                    else
                    {
                        return CrackHelperFunction(ciphertext, answer);
                    }
                }
            }
        }
    }
    
    //at the very end, no matter what,
    //create a new translator and set a new one (delete old)
    Translator * new_translatorPointer = new Translator();
    delete m_TranslatorP;
    m_TranslatorP = new_translatorPointer;
    return "";
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
