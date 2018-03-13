#include "provided.h"
#include "MyHash.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;

const string WORDLIST_FILE = "wordlist.txt";

string encrypt(string plaintext)
{
	  // Generate a to z
    char plaintextAlphabet[26+1];
	iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
	plaintextAlphabet[26] = '\0';

	  // Generate permutation
	string ciphertextAlphabet(plaintextAlphabet);
	default_random_engine e((random_device()()));
	shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);

	  // Run translator (opposite to the intended direction)
	Translator t;
	t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
	return t.getTranslation(plaintext);
}

bool decrypt(string ciphertext)
{
	Decrypter d;
	if ( ! d.load(WORDLIST_FILE))
	{
		cout << "Unable to load word list file " << WORDLIST_FILE << endl;
		return false;
	}
	for (const auto& s : d.crack(ciphertext))
		cout << s << endl;
	return true;
}
void f();

void f2();
int main(int argc, char* argv[])
{

    
    WordList * wlPointer = new WordList();
    wlPointer->loadWordList("apple"); 
    
//    string * stringPtr2 = exampleHash->find("abc");//('abc');
//    cerr << "cool ben" << endl;
    
    
//    WordList *wl = new WordList();
//    wl->loadWordList("/Users/J/Desktop/CS32/Projects/Project4/skeleton/wordlist.txt");
//    f();
    
//    MyHash<string,string> * biggerHash = new MyHash <string, string>();
    
//	if (argc == 3  &&  argv[1][0] == '-')
//	{
//		switch (tolower(argv[1][1]))
//		{
//		  case 'e':
//			cout << encrypt(argv[2]) << endl;
//			return 0;
//		  case 'd':
//			if (decrypt(argv[2]))
//				return 0;
//			return 1;
//		}
//	}
//
//	cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
//	cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
//	return 1;
}

void f2()
{
    vector<string> v;
    v.push_back("momma");
    v.push_back("dadda");
    MyHash<string, std::vector<string>> * exampleHash = new MyHash<string, std::vector<string>>();
    vector<string> * stringPtr = exampleHash->find("abc");//('abc');
    if (stringPtr == nullptr)
    {
        cerr << "it is null " << endl;
    }
    exampleHash->associate("abc", v);
    stringPtr = exampleHash->find("abc");//('abc');
    
    if (stringPtr == nullptr)
    {
        cerr << "it is null x2" << endl;
    }
}
void f()
{
				Tokenizer	t("	,.!");
				vector<string>	v =	t.tokenize ("This,,	is	a				test!	It's	the...	best!");
        
    //	v	now	contains	"This",	"is",	"a",	"test",	"It's",	"the",	and	"best"
				string	s	=	"!!!!!";
				v	=	t.tokenize(s);
}
