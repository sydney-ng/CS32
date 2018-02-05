//
//  main.cpp
//  eval.cpp
//
//  Created by Super on 2/4/18.
//  Copyright © 2018 Sydney. All rights reserved.
//


#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;
int evaluate(string infix, const Map& values, string& postfix, int& result);


int main ()
{
    
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    evaluate("abcdefg", m, pf, answer);
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    //make sure that they're only lower case letters
    for (int i = 0; i < infix.length()-1; i++)
    {

        if (islower (infix[i]) == false)
        {
            return 1;

        }
    }
    cout << "finished evaluate";
    return 0;
}
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.
