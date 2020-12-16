//
//  main.cpp
//  CS32_Project3
//
//  Created by Super on 1/24/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#include <iostream>
#include "Map.h"
#include "testInsertUpdateFunctions.h"
#include "testBasicFunctions.h"
#include "testGetFunctions.h"
#include "testCombineSubtract.h"
#include "testSubtract.h"
#include <iostream>
#include <cassert>
#include <string>

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void professor_case2();

int main ()
{
    Map A, B;
    testSubtractfunct(A,B);
    testCombine(A,B);
    testSwap (A,B);
    test_SizeEmptyContains(A);
    testInsert(A);
    testUpdate(A);
    testInsertOrUpdate ( A);
    testGet1(A);
    testGet2(A);
    testErase(A);
    professor_case2();
    
}
void professor_case2()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    ValueType v = 42;
    assert(!m.get("Lucy", v)  &&  v == 42);
    assert(m.get("Fred", v)  &&  v == 123);
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v)  &&
           ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
           x != x2);
    cerr << "professor test case() --> passed" << endl;
}

/*PROFESSOR'S TEST CASE: #include "Map.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
              "Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
              "Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
    CHECKTYPE(&Map::size,           int  (Map::*)() const);
    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
    
    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
}

int main()
{}
*/
