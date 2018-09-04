/*
 * Tadej_test.cpp
 *
 *  Created on: 30. jan. 2015
 *      Author: Tadej
 */
#include <iostream>
#include <vector>
#include "strategy.h"

using namespace std;

class base
{

public:
    base(){cout<<"Base Constructor Called\n";}
    virtual ~base(){cout<<"Base Destructor called\n";}

};
class derived1:public base
{

public:
    derived1(){cout<<"Derived constructor called\n";}
    ~derived1(){cout<<"Derived destructor called\n";}

};

/*
 * STRATEGY defines a family of algorithms, encapsulates each one, and make them interchangeable.
 * Strategy lets the algorithm vary independently from clients that use it.
 */
int main()
{
    FlyBehavior *f;
    f = new FlyRocketPowered;
    FlyRocketPowered fr;
//    f->fly();

    Duck *md = new MallardDuck;
    Duck *mo = new ModelDuck;
    mo->performFly();
    mo->performQuack();
    mo->display();
//    mo->setFlyBehavior(fr); // works, but is better to work with pointers
    mo->setFlyBehavior2(f);
    mo->performFly();
}
