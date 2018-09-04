#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pizza
{
protected:
    string name;
    string dough;
    string sauce;
    vector<string> toppings;

public:
    virtual ~Pizza(){}
    void prepare();
    void bake();
    virtual void cut();
    void box();
    string getName();
};

class NYStyleCheesePizza: public Pizza
{
public:
    NYStyleCheesePizza();
};

class ChicagoStyleCheesePizza: public Pizza
{
public:
    ChicagoStyleCheesePizza();
    void cut();
};

void Pizza::prepare()
{
    cout << "Preparing " << name << endl
        << "Tossing dough..." << endl
        << "Adding sauce..." << endl
        << "Adding toppings..." << endl;
    for(int i = 0; i < toppings.size(); i++)
    {
        cout << " " << toppings[i] << endl;
    }
}

void Pizza::bake()
{
    cout << "Bake for 25 minutes at 350" << endl;
}

void Pizza::cut()
{
    cout << "Cutting the pizza into diagonal slices" << endl;
}

void Pizza::box()
{
    cout << "Place pizza in official PizzaStore box" << endl;
}

string Pizza::getName()
{
    return name;
}

NYStyleCheesePizza::NYStyleCheesePizza()
{
    name = "NY Style Sauce and Cheese Pizza";
    dough = "Thin Crust Dough";
    sauce = "Marinara Sauce";

    toppings.push_back("Grated Reggiano Cheese");
}

ChicagoStyleCheesePizza::ChicagoStyleCheesePizza()
{
    name = "Chicago Style Deep Dish Cheese Pizza";
    dough = "Extra Thick Crust Dough";
    sauce = "Plum Tomato Sauce";

    toppings.push_back("Shredded Mozzarella Cheese");
}

void ChicagoStyleCheesePizza::cut()
{
    cout << "Cutting the pizza into square slices" << endl;
}

class Pizza;

class PizzaStore
{
public:
    virtual ~PizzaStore(){}
    Pizza* orderPizza(const string &type);

protected:
    virtual Pizza* createPizza(const string &type) = 0;
};

class NYPizzaStore: public PizzaStore
{
protected:
    Pizza* createPizza(const string &type);
};

class ChicagoPizzaStore: public PizzaStore
{
protected:
    Pizza* createPizza(const string &type);
};

class CaliforniaPizzaStore: public PizzaStore
{
protected:
    Pizza* createPizza(const string &type);
};


Pizza* PizzaStore::orderPizza(const string &type)
{
    Pizza *pizza = createPizza(type);
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    return pizza;
}

Pizza* NYPizzaStore::createPizza(const string &type)
{
    if(type == "cheese")
    {
        return new NYStyleCheesePizza();
    }
//    else if(type == "veggie")
//    {
//        return new NYStyleVeggiePizza();
//    }
//    else if(type == "clam")
//    {
//        return new NYStyleClamPizza();
//    }
//    else if(type == "pepperoni")
//    {
//        return new NYStylePepperoniPizza();
//    }
    else
    {
        return NULL;
    }
}

Pizza* ChicagoPizzaStore::createPizza(const string &type)
{
    if(type == "cheese")
    {
        return new ChicagoStyleCheesePizza();
    }
//    else if(type == "veggie")
//    {
//        return new ChicagoStyleVeggiePizza();
//    }
//    else if(type == "clam")
//    {
//        return new ChicagoStyleClamPizza();
//    }
//    else if(type == "pepperoni")
//    {
//        return new ChicagoStylePepperoniPizza();
//    }
    else
    {
        return NULL;
    }
}

Pizza* CaliforniaPizzaStore::createPizza(const string &type)
{
    if(type == "cheese")
    {
//        return new CaliforniaStyleCheesePizza();
    }
//    else if(type == "veggie")
//    {
//        return new CaliforniaStyleVeggiePizza();
//    }
//    else if(type == "clam")
//    {
//        return new CaliforniaStyleClamPizza();
//    }
//    else if(type == "pepperoni")
//    {
//        return new CaliforniaStylePepperoniPizza();
//    }
    else
    {
        return NULL;
    }
}
/**
 * FACTORY METHOD: Define an interface for creating an object, but let subclasses decide
 * which class to instantiate. Factory method lets a class defer instantiation to the subclasses.
 */

int main()
{
    PizzaStore *nyStore = new NYPizzaStore();
    PizzaStore *chicagoStore = new ChicagoPizzaStore();

    Pizza *pizza = nyStore->orderPizza("cheese");
    cout << "Ethan ordered a " << pizza->getName() << endl << endl;

    delete pizza;

    pizza = chicagoStore->orderPizza("cheese");
    cout << "Joel ordered a " << pizza->getName() << endl << endl;

    delete nyStore;
    delete chicagoStore;
    delete pizza;

    return 0;
}

