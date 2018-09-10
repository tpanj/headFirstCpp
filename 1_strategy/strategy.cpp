#include "strategy.h"
#include <iostream>

using namespace std;


void FlyWithWings::fly() { cout << "I'm flying" << "\n"; return; }
void FlyNoWay::fly() { cout << "I can't fly" << "\n"; return; }
void FlyRocketPowered::fly() { cout << "I am flying with a rocket" << "\n"; return; }
void Quack::quack() { cout << "Quack" << "\n"; return; }
void MuteQuack::quack() { cout << "<<Silence>>" << "\n"; return; }
void Squeak::quack() { cout << "Squeak" << "\n"; return; }

void MallardDuck::display() { cout << "I'm a real Mallar Duck" << "\n"; return; }
void ModelDuck::display() { cout << "I'm a model Duck" << "\n"; return; }
