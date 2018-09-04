#include <iostream>
#include <string>
 
using namespace std;

/* Abstract base class */
// The abstract Coffee class defines the functionality of Coffee implemented by decorator
struct Coffee {
    virtual double getCost() = 0; // Returns the cost of the coffee
    virtual std::string getIngredients() = 0; // Returns the ingredients of the coffee
    virtual ~Coffee() = 0;
};
inline Coffee::~Coffee() { }
 
struct CondimentDecorator: public Coffee {
    CondimentDecorator(Coffee *inner) { wrappee=inner; }
    virtual ~CondimentDecorator() { delete wrappee; }
    virtual double getCost() { return wrappee->getCost(); }
    virtual string getIngredients() { return wrappee->getIngredients(); }
private:
    Coffee *wrappee;
};
/* SimpleCoffee class. */
// Extension of a simple coffee without any extra ingredients
struct SimpleCoffee : public Coffee {
    virtual double getCost() { return 1.0; }
    virtual std::string getIngredients() { return "Simple Coffee"; }
    ~SimpleCoffee() { cout << "::SimpleCoffee dctor::" << endl;  }
};
struct DarkRoast : public Coffee {
    virtual double getCost() { return .99; }
    virtual std::string getIngredients() { return "Dark Roast"; }
    ~DarkRoast() { cout << "::DarkRoast dctor::" << endl;  }
};
struct HouseBlend : public Coffee {
    virtual double getCost() { return .89; }
    virtual std::string getIngredients() { return "House Blend"; }
    ~HouseBlend() { cout << "::HouseBlend dctor::" << endl;  }
};


/* Decorators */
// Decorator Milk that adds milk to coffee.
struct MilkDecorator : Coffee {
    MilkDecorator (Coffee *basicCoffee)
      : basicCoffee(basicCoffee) {
    }
    ~MilkDecorator() { cout << "::MilkDecorator dctor::";  delete basicCoffee; }

    virtual double getCost() { // Providing methods defined in the abstract superclass
      return basicCoffee->getCost() + 0.5;
    }

    virtual std::string getIngredients() {
      return basicCoffee->getIngredients() + ", " + "Milk";
    }
private:
    Coffee *basicCoffee;
};

// Decorator Whip that adds whip to coffee
struct WhipDecorator : Coffee {
    WhipDecorator (Coffee *basicCoffee)
      : basicCoffee(basicCoffee) {
    }
    // The wikipedia does not work to call delete in destructor, so do not stack
    ~WhipDecorator() { cout << "::WhipDecorator dctor::"; /* missing delete */ }

  virtual double getCost() {
    return basicCoffee->getCost() + 0.7;
  }

  virtual std::string getIngredients() {
    return basicCoffee->getIngredients() + ", " + "Whip";
  }
private:
    Coffee *basicCoffee;
};

/* Decorators */
// Decorator Milk that adds milk to coffee.
struct Milk : public CondimentDecorator {
    Milk (Coffee *basicCoffee): CondimentDecorator(basicCoffee) {}
    ~Milk() { cout << "::Milk dctor::";  }

    virtual double getCost() { // Providing methods defined in the abstract superclass
      return CondimentDecorator::getCost() + 0.1;
    }
  
    virtual std::string getIngredients() {
      return CondimentDecorator::getIngredients() + ", " + "Milk";
    }
};
 
// Decorator Whip that adds whip to coffee
struct Whip : CondimentDecorator {
    Whip (Coffee *basicCoffee)
      : CondimentDecorator(basicCoffee) {
    }
    ~Whip() { cout << "::Whip dctor::";  }
  
    virtual double getCost() {
      return CondimentDecorator::getCost() + 0.1;
    }
  
    virtual std::string getIngredients() {
      return CondimentDecorator::getIngredients() + ", " + "Whip";
    }
};
struct Soy : CondimentDecorator {
    Soy (Coffee *basicCoffee)
    : CondimentDecorator(basicCoffee) {
    }
    ~Soy() { cout << "::Soy dctor::" ;  }

    virtual double getCost() {
      return CondimentDecorator::getCost() + 0.15;
    }

    virtual std::string getIngredients() {
      return CondimentDecorator::getIngredients() + ", " + "Whip";
    }
};

// The wikipedia does not work to call delete in destructor, so do not stack
struct Mocha : Coffee {
    Mocha (Coffee *basicCoffee): basicCoffee(basicCoffee) {}
    ~Mocha() { cout << "::Mocha dctor::"; delete basicCoffee; }

    virtual double getCost() {
      return basicCoffee->getCost() + 0.2;
    }

    virtual std::string getIngredients() {
      return basicCoffee->getIngredients() + ", " + "Mocha";
    }
private:
  Coffee *basicCoffee;
};
 
/* DECORATOR: Attach additional responsibilities to an object dynamically. Decorators
 * provide a flexible alternative for subclassing for extending functionality.
 */
int main() 
{
    Coffee *c = new Mocha(new Mocha(new Milk(new DarkRoast)));
    cout << "Cost: " << c->getCost() << "; Ingredients: " << c->getIngredients() << endl;
    delete c;
    Coffee *d = new Soy(new Mocha(new Whip(new HouseBlend)));
    cout << "Cost: " << d->getCost() << "; Ingredients: " << d->getIngredients() << endl;
    delete d;
}
