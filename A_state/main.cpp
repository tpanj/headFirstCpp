#include <iostream>

#include "State.h"
#include "GumballMachine.h"

using namespace std;

/* 
 * The State Pattern allows an object to alter its behavior
 * when its internal state changes. The object will appear to
 * change its class.
 */
int main()
{
    GumballMachine *gumballMachine = new GumballMachine(5);

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    cout << endl;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    cout << endl;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    cout << endl;

    delete gumballMachine;

    return 0;
}

