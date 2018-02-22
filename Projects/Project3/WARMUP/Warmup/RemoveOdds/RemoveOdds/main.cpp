#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOdds(list<int>& li)
{
    std::list<int>::iterator it;
    for (it = li.begin(); it != li.end(); ++it){
        if (*it % 2 != 0)
        {
            li.erase(it);
        }
    }
}

void test()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    list<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    assert(x.size() == 4);
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}
////////////////////////////////////
// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds2(vector<int>& v)
{
    vector <int> v2;
    for (int i = 0; i < v.size(); i ++)
    {
        if (v[i] % 2 == 0)
        {
            v2.push_back(v[i]);
        }
    }
    v= v2;
}

void test2()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds2(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

/////////////////////////////////////////////////////////////////////

vector<int> destroyedOnes10;

class Movie
{
public:
    Movie(int r) : m_rating(r) {}
    ~Movie() { destroyedOnes10.push_back(m_rating); }
    int rating() const { return m_rating; }
private:
    int m_rating;
};

// Remove the movies in li with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator it;
    for (it = li.begin(); it != li.end(); it++)
    {
    }
}

void test3()
{
    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
    list<Movie*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Movie(a[k]));
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes10.size() == 4);
    vector<int> v;
    for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
    {
        Movie* mp = *p;
        v.push_back(mp->rating());
    }
    // Aside:  In C++11, the above loop could be
    //     for (auto p = x.begin(); p != x.end(); p++)
    //     {
    //         Movie* mp = *p;
    //         v.push_back(mp->rating());
    //     }
    // or
    //     for (auto p = x.begin(); p != x.end(); p++)
    //     {
    //         auto mp = *p;
    //         v.push_back(mp->rating());
    //     }
    // or
    //     for (Movie* mp : x)
    //         v.push_back(mp->rating());
    // or
    //     for (auto mp : x)
    //         v.push_back(mp->rating());
    sort(v.begin(), v.end());
    int expect[4] = { 70, 80, 85, 90 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes10.begin(), destroyedOnes10.end());
    int expectGone[4] = { 10, 15, 20, 30 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes10[k] == expectGone[k]);
    for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
        delete *p;
}

/////////////////////////////////////////////////////////////////////

class Movie10
{
public:
    Movie10(int r) : m_rating(r) {}
    ~Movie10() {
        cerr << "here";
        destroyedOnes10.push_back(m_rating); }
    int rating() const { return m_rating; }
private:
    int m_rating;
};

// Remove the movies in v with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original vector.
void removeBad(vector<Movie10*>& v)
{
    vector <Movie10*> v2;
    for (int i = 0; i < v.size(); i ++)
    {
        if(v[i]->rating() > 50)
        {
            v2.push_back(v[i]);
        }
        else
        {
            delete v[i];
        }
    }
    v=v2;

}

void test10()
{
    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
    vector<Movie10*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Movie10(a[k]));
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4);
    assert(x.size() == 4 && destroyedOnes10.size() == 4);
    vector<int> v;
    for (int k = 0; k < 4; k++)
        v.push_back(x[k]->rating());
    sort(v.begin(), v.end());
    int expect[4] = { 70, 80, 85, 90 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes10.begin(), destroyedOnes10.end());
    int expectGone[4] = { 10, 15, 20, 30 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes10[k] == expectGone[k]);
    for (vector<Movie10*>::iterator p = x.begin(); p != x.end(); p++)
        delete *p;
}

int main()
{
    test3();
    
    cout << "Passed" << endl;
}
