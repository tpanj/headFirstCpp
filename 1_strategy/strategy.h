/*
 * Tadej.h
 *
 *  Created on: 30. jan. 2015
 *      Author: Tadej
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

class FlyBehavior {
public: virtual void fly() = 0;
};

class FlyWithWings: public FlyBehavior {
public: virtual void fly();
};

class FlyNoWay: public FlyBehavior {
public: virtual void fly();
};
class FlyRocketPowered: public FlyBehavior {
public: virtual void fly();
};
class QuackBehavior {
public: virtual void quack() = 0;
};

class Quack: public QuackBehavior {
public: virtual void quack();
};

class MuteQuack: public QuackBehavior {
public: virtual void quack();
};

class Squeak: public QuackBehavior {
public: virtual void quack();
};


class Duck {
protected:
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;
public:
    virtual void display()=0;
    void performFly() { flyBehavior->fly(); }
    void performQuack() { quackBehavior->quack(); }
//  void setFlyBehavior( FlyBehavior &fb) { flyBehavior = &fb; }
    void setFlyBehavior2( FlyBehavior *fb) { flyBehavior = fb; }
    void setQuackBehavior( QuackBehavior *quackb) { quackBehavior = quackb; }
};

class MallardDuck: public Duck {
public:
    MallardDuck() { flyBehavior = new FlyWithWings; quackBehavior = new Quack;}
    virtual void display();
};

class ModelDuck: public Duck {
public:
    ModelDuck() { flyBehavior = new FlyNoWay; quackBehavior = new Quack;}
    virtual void display();
};

/**
 *  STRATEGY PATTERN: define a family of algorithms, encapsulates each one, and make
 *  them interchangeable. Strategy lets the algorithm vary independently from cluents that use it.
 */

#endif /* STRATEGY_H_ */
