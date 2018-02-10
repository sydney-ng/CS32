//
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
    assert(evaluate("(u+e)/y", m, pf, answer) == 0  &&  answer == -5 && pf == "ue+y/");
    assert(evaluate("a/y+o", m, pf, answer) == 0  &&  answer == 5 && pf == "ay/o+");
    assert(evaluate("(a/y)+o", m, pf, answer) == 0  &&  answer == 5 && pf == "ay/o+");
    assert(evaluate("i/(a-y)", m, pf, answer) == 0  &&  answer == 3 && pf == "iay-/");
    assert(evaluate("(i/(a-y))", m, pf, answer) == 0  &&  answer == 3 && pf == "iay-/");
    assert(evaluate("((i)/(a-y))", m, pf, answer) == 0  &&  answer == 3 && pf == "iay-/");
    assert(evaluate("a+ e", m, pf, answer) == 0  && pf == "ae+"  &&  answer == -6);
    assert(evaluate("a*i-o", m, pf, answer) == 0  &&  answer == 16 && pf == "ai*o-");
    string pf2 = "";
    answer = 999;
    assert(evaluate("((0)/(a-y))", m, pf, answer) == 1 && answer == 999 && pf2 == "");
    assert(evaluate("(i/(a-a))", m, pf, answer) == 3 && answer == 999 && pf == "iaa-/");
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("  +  ", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("    ", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("A", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a++i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y+()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y+(aa-)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("aE*", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+#e", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+s", m, pf, answer) == 2  &&  answer == 999);
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    if (CheckFormation(infix) == false)
    {
        cerr <<"there are upper case values" << endl;
        return 1;
    }
    
    postfix = getPostfixForm(infix);
    if (CorrectLetters(values, infix) == false)
    {
        cerr <<"there are values that are not in map" << endl;
        return 2;
    }
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
        if (num1 == 0)
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
        if (infix[i] != '*' && infix[i] != '/' && infix[i] != '-' && infix[i] != '+' && infix[i] != ' ' && infix[i] != '(' && infix[i] != ')')
        {
            if (values.contains(infix[i]) == false)
            {
                cerr <<"there's a value that's not in the map" << endl;
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
    
    string temp_Infix = "";
    
    //empty string with no blanks
    for (int i = 0; i < infix.length(); i ++)
    {
        if (infix[i] != ' ')
        {
            temp_Infix += infix[i];
        }
    }
    
    cerr << "temp_Infix is: " << temp_Infix << endl;
    
    if (temp_Infix.length() == 0)
    {
        cerr << "string with length 0, fail" << endl;
        return false;
    }
    
    //or if it's only 1 letter, it must be lower case alphabet letter
    if (temp_Infix.length() == 1)
    {
        if (isalpha(temp_Infix[0]) && islower(temp_Infix[0]))
        {
            cerr << "string with length 1, isn't a number, fail" << endl;
            return true;
        }
    }
    
    //loop through everything and make sure it's valid
    for (int i = 0; i < temp_Infix.length(); i++)
    {
        if (isalpha(temp_Infix[i]) == false && temp_Infix[i] != '*' && temp_Infix[i] != '/' && temp_Infix[i] != '-' && temp_Infix[i] != '+' && temp_Infix[i] != '(' && temp_Infix[i] != ')')
        {
            cerr << "this is not an operator, space, or paren" << endl;
            return false;
        }
        continue;
    }

    //make sure it starts w/ a letter or parentheses
    if (temp_Infix[0] != '(' && (isalpha(temp_Infix[0]) == false))
    {
        cerr << "first thing was not a paren or alphabet char" << endl;
        return false;
    }
    
    //make sure it ends w/ letter or paren
    if (temp_Infix[temp_Infix.length()-1] != ')' && (isalpha(temp_Infix[temp_Infix.length()-1]) == false))
    {
        cerr << "last thing was not a paren or alphabet char" << endl;
        return false;
    }
    
    //check for doubles
    for (int j = 0; j < temp_Infix.length()-1; j++)
    {
        //string w/ adj letters
        if (isalpha(temp_Infix[j]) == true && isalpha(temp_Infix[j+1]) == true)
        {
            cerr << "string with 2 adj letters, fail" << endl;
            return false;
        }
        
        //string with empty paren
        if (temp_Infix[j] == '(' && temp_Infix[j+1] == ')')
        {
            cerr << "string w/ empty paren, fail" << endl;
            return false;
        }
        
        if ((temp_Infix[j] == '*' || temp_Infix[j] == '/' || temp_Infix[j] == '-' || temp_Infix[j] == '+') &&
            (temp_Infix[j+1] == '*' || temp_Infix[j+1] == '/' || temp_Infix[j+1] == '-' || temp_Infix[j+1] == '+'))
        {
                cerr << temp_Infix[j] << " is an operator and " << temp_Infix[j+1] << " is an operator, fail!" << endl;
                return false;
        }
    }
    
    //make sure that they're only lower case letters
    for (int i = 0; i <= temp_Infix.length()-1; i++)
    {
        cerr << "we are currently checking " << temp_Infix[i] << endl;
        //if it's a letter
        if (temp_Infix[i] != '*' && temp_Infix[i] != '/' && temp_Infix[i] != '-' && temp_Infix[i] != '+' && temp_Infix[i] != '(' && temp_Infix[i] != ')')
        {
            if (islower (temp_Infix[i]) == false)
            {
                cerr << temp_Infix [i] << " is not lower case, fail" << endl;
                return false;
            }
            
            if (isalpha(temp_Infix[i]))
            {
                num_alpha +=1;
            }

        }
        //if it's an operator
        if (temp_Infix[i] == '*' || temp_Infix[i] == '/' || temp_Infix[i] == '-' || temp_Infix[i] == '+')
        {
            o_count +=1;
        }
        //if they're paren
        if (temp_Infix[i] == '(')
        {
            paren_l +=1;
        }
        if (temp_Infix[i] == ')')
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

//   Evaluates an integer arithmetic expression
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
