//
//  investment.cpp
//  PortfolioManagement
//
//  Created by Super on 2/7/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
#include <string> 
using namespace std;

//////////////////IMPLEMENTATION FOR INVESTMENT//////////////////////////////

class Investment
{
public:
    
    //Constructor & Destructor
    Investment(string input_name, int input_val);
    virtual ~Investment();
    
    //return values of the private variables
    string name() const;
    int purchasePrice() const;
    
    //things for the each of the types
    virtual string description() const = 0;
    virtual bool fungible() const;
    
    //bool fungible();
    //void output() const ;
    
private:
    int m_value;
    string m_name;
};

Investment:: Investment(string input_name, int input_val)
{
    m_name = input_name;
    m_value = input_val;
}

Investment:: ~Investment()
{
}

string Investment::name() const
{
    return m_name;
}

int Investment::purchasePrice() const
{
    return m_value;
}

string Investment:: description() const
{
    return "";
}

bool Investment::fungible() const
{
    return false;
}

//////////////////IMPLEMENTATION FOR STOCK//////////////////////////////

class Stock: public Investment
{
public:
    //Constructor & Destructor
    Stock (string input_name, int input_value, string input_nickname);
    virtual ~Stock();
    virtual string description() const;
    virtual bool fungible() const;
    
private:
    string nickname;
    
};

Stock:: Stock (string input_name, int input_value, string input_nickname)
: Investment(input_name, input_value), nickname(input_nickname)
{
}

Stock:: ~Stock()
{
    cout << "Destroying " << name() << ", a stock holding" << endl;
}
string Stock::description() const
{
    string stock_description = "stock trading as " + nickname;
    return stock_description;
}

bool Stock:: fungible() const
{
    return true;
}

//////////////////IMPLEMENTATION FOR PAINTING//////////////////////////////

class Painting: public Investment
{
public:
    //Constructor & Destructor
    Painting(string input_name, int input_val);
    virtual ~Painting();
    virtual string description() const;
    virtual bool fungible() const;
};

Painting:: Painting(string input_name, int input_val)
:Investment(input_name,input_val)
{
}

Painting::~Painting()
{
    cout << "Destroying " << name() << ", a painting" << endl;
}

string Painting:: description() const
{
    string stock_description = "painting";
    return stock_description;
}

bool Painting:: fungible() const
{
    return false;
}

//////////////////IMPLEMENTATION FOR HOUSE/////////////////////////////////
class House: public Investment
{
public:
    //Constructor & Destructor
    House(string input_name, int input_val);
    virtual ~House();
    virtual string description() const;
    virtual bool fungible() const;

};

House:: House(string input_name, int input_val)
:Investment(input_name,input_val)
{
    
}
House::~House (){
    cout << "Destroying the house " << name() << endl;
}

string House::description() const
{
   return "house";
}

bool House:: fungible() const
{
    return false;
}
