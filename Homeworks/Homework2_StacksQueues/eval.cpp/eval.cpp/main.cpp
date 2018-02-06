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
bool CheckFormation (string infix);
string getPostfixForm(string infix);
bool CorrectLetters (const Map& values, const string infix);
bool PEMDAS(char currChar, char stackTop);
int Calculate (int num1, int num2, char postfix_char, bool& flag);

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
           pf == "ae+"  &&  answer == -6);
    answer = 999;
    /*assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    
    int a = evaluate("a*b", m, pf, answer);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    /*assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3); */
    cout << "Passed all tests" << endl;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    if (CheckFormation(infix) == false)
    {
        cerr <<"there are upper case values" << endl;
        return 1;
    }
    if (CorrectLetters(values, infix) == false)
    {
        cerr <<"there are values that are not in map" << endl;
        return 2;
    }
    
    
    postfix = getPostfixForm(infix);
    cerr << "postfix notation is: " << postfix << endl;
    stack <char> evaluateStack;
    for (int i = 0; i < postfix.length(); i++)
    {
        //if it's a number
        if (isalpha(postfix[i]))
        {
            cerr << "we are currently looking at the value of: " << postfix[i] << endl;
            //get the corresponding value
            int num;
            values.get(postfix[i], num);
            evaluateStack.push(num);
        }
        //it must be an operator
        else
        {
            int num1 = evaluateStack.top();
            evaluateStack.pop();
            
            int num2 = evaluateStack.top();
            evaluateStack.pop();
            
            bool flag = true;
            int tempAnswer = Calculate (num1, num2, postfix[i], flag);
            
            //check if we divided by 0
            if (flag == false)
            {
                return 3;
            }
            else
            {
                evaluateStack.push (tempAnswer);

            }
        }
    }
    result = evaluateStack.top();
    cerr << result;
    
    return 0;
}


int Calculate (int num1, int num2, char postfix_char, bool& flag)
{
    int answer = 0;
    
    cerr << "num 1: " << num2 << " num 2 : " << num1 << endl;
    if (postfix_char == '*')
    {
        cerr << "multiply num 1 & 2: ";
        answer = num1 * num2;
        cerr << answer << endl;
    }
    else if (postfix_char == '/')
    {
        if (num2 == 0)
        {
            flag = false;
            answer = 0;
        }
        else
        {
          cerr << "divide " << num1 << " by " << num2 << endl;

          answer = num2 / num1;
          cerr << answer << endl;

        }

    }
    else if (postfix_char == '+')
    {

        cerr << "add num 1 & 2: ";
        answer = num1 + num2;
        cerr << answer << endl;


    }
    else if (postfix_char == '-')
    {
        cerr << "subtract num 1 & 2: ";
        answer = num2 - num1;
        cerr << answer << endl;


    }
    
    return answer;
}

bool CorrectLetters (const Map& values, const string infix)
{
    for (int i=0; i < infix.length(); i++)
    {
        if (infix[i] != '*' && infix[i] != '/' && infix[i] != '-' && infix[i] != '+' && infix[i] != ' ')
        {
            if (values.contains(infix[i]) == false)
            {
                return false;
            }
        }
    }
    return true;
}

bool CheckFormation (string infix)
{
    int o_count = 0;
    int paren_r = 0;
    int paren_l = 0;
    int num_alpha = 0;
    //empty string
    if (infix.length() == 0)
    {
        cerr << "string with length 0, fail" << endl;
        return false;
    }
    
    //or if it's only 1 letter, it must be lower case alphabet letter
    
    if (infix.length() == 1)
    {
        if (isalpha(infix[0]) && islower(infix[0]))
        {
            cerr << "string with length 1, isn't a number, fail" << endl;
            return true;
        }
    }

    //make sure that they're only lower case letters
    for (int i = 0; i < infix.length()-1; i++)
    {
        if (infix[i] != '*' && infix[i] != '/' && infix[i] != '-' && infix[i] != '+' && infix[i] != ' ')
        {
            if (islower (infix[i]) == false)
            {
                cerr << infix [i] << " is not lower case, fail" << endl;
                return false;
            }
            
            if (isalpha(infix[i]))
            {
                num_alpha +=1;
            }

        }
        else if (infix[i] == '*' && infix[i] == '/' && infix[i] == '-' && infix[i] == '+')
        {
            o_count +=1;
        }
        
        else if (infix[i] == '(')
        {
            paren_l +=1;
        }
        else if (infix[i] == ')')
        {
            paren_r +=1;
        }
    }
    
    //check the number of ()
    if (paren_r != paren_l)
    {
        cerr << "paren !matching, fail" << endl;

        return false;
    }
    
    if ( o_count != (num_alpha-1))
    {
        cerr << "number&operator !matchin, fail" << endl;
        return false;
    }
    return true;
}

string getPostfixForm(string infix)
{
    //change postfix to postfix notation of expression
    stack <char> postfixStack;
    string postfixString = "";
    
    //iterate through the entire infix
    for (int k = 0; k < infix.length(); k++)
    {
        //if it's a letter just append it
        if (isalpha(infix[k])==true)
        {
            postfixString += (infix[k]);
        }
        
        //if it's an operator
        else
        {
            //add to stack if it's (
            if (infix[k] == '(')
            {
                postfixStack.push(infix[k]);
            }
            //keep popping things off stack & add to postfix until you see a (
            else if (infix[k] == ')')
            {
                    while (postfixStack.top() != '(' && postfixStack.empty() == false)
                    {
                        postfixString += postfixStack.top();
                        postfixStack.pop();
                    }
                
                    postfixStack.pop();
            }
            
            //check if it's an operator
            else if (infix[k] == '*' || infix[k] == '/' || infix[k] == '+' || infix[k] == '-')
            {
                //make sure it's a * or /
                while (postfixStack.empty() == false && postfixStack.top() != '(' && PEMDAS(infix[k], postfixStack.top()) == true)
                {
                    postfixString += postfixStack.top();
                    postfixStack.pop();
                }
                postfixStack.push(infix[k]);
            }
        }
    }
    while (postfixStack.empty() == false)	//pop each operator and append to postfix string
    {
        postfixString += postfixStack.top();
        postfixStack.pop();
    }
    cerr << "our string is now: " << postfixString << endl;
    return postfixString;
}

bool PEMDAS(char currChar, char stackTop)
{
    if (currChar == '*' || currChar == '/')
    {
        if (stackTop == '+' || stackTop == '+')
        {
            return false;
        }
    }
    return true;
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
