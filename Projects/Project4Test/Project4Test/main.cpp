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


int main()
{
    MyHash<string, string> * exampleHash = new MyHash<string, string>();
    exampleHash->find("abc");//('abc');
    //string * X = exampleHash.find("cool");
    cout << "nice" << endl;
}
