#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;



void Car_test1()
{
    CarMap Car;
    Car.addCar("ABC");
    Car.addCar("ABCA");
    Car.addCar("ABCE");
    Car.addCar("ABC");
    assert(Car.fleetSize() ==3);
    
    Car.addGas("ABC", 10);
    Car.addGas("ABC", -2);
    assert(Car.gas("ABC") ==10);
    
    Car.useGas("ABC", 2);
    assert(Car.gas("ABC") ==8);

}

int main ()
{
    Car_test1();
    cerr << "passed all test cases";
    return 0;
}
