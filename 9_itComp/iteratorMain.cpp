#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;


class MenuItem
{
private:
    string name;
    string description;
    bool vegetarian;
    double price;

public:
    MenuItem(const string &name, const string &description,
            bool vegetarian, double price);
    string getName();
    string getDescription();
    bool isVegetarian();
    double getPrice();
};

class Iterator
{
public:
    virtual ~Iterator(){}
    virtual bool hasNext() = 0;
    virtual MenuItem* next() = 0;
};

class DinerMenuIterator: public Iterator
{
private:
    MenuItem **items;
    int position;
    int length;
public:
    DinerMenuIterator(MenuItem *items[], int length);
    MenuItem* next();
    bool hasNext();
};

class PancakeHouseMenuIterator: public Iterator
{
private:
    vector<MenuItem*> items;
    vector<MenuItem*>::iterator iter;
public:
    PancakeHouseMenuIterator(vector<MenuItem*> &items);
    MenuItem* next();
    bool hasNext();
};

class CafeMenuIterator: public Iterator
{
private:
    map<string, MenuItem*> items;
    map<string, MenuItem*>::iterator iter;
public:
    CafeMenuIterator(map<string, MenuItem*> &items);
    MenuItem* next();
    bool hasNext();
};

//
DinerMenuIterator::DinerMenuIterator(MenuItem *items[], int length)
{
    this->items = items;
    this->length = length;
    position = 0;
}

MenuItem* DinerMenuIterator::next()
{
    MenuItem *menuItem = items[position];
    position++;
    return menuItem;
}

bool DinerMenuIterator::hasNext()
{
    if(position >= length || items[position] == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

PancakeHouseMenuIterator::PancakeHouseMenuIterator(vector<MenuItem*> &items)
{
    this->items = items;
    iter = this->items.begin();
}

MenuItem* PancakeHouseMenuIterator::next()
{
    MenuItem *menuItem = *iter;
    iter++;
    return menuItem;
}

bool PancakeHouseMenuIterator::hasNext()
{
    if(iter != items.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

CafeMenuIterator::CafeMenuIterator(map<string, MenuItem*> &items)
{
    this->items = items;
    iter = this->items.begin();
}

MenuItem* CafeMenuIterator::next()
{
    MenuItem *menuItem = iter->second;
    iter++;
    return menuItem;
}

bool CafeMenuIterator::hasNext()
{
    if(iter != items.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Menu
{
public:
    virtual ~Menu(){}
    virtual Iterator* createIterator() = 0;
};

class PancakeHouseMenu: public Menu
{
private:
    vector<MenuItem*> menuItems;

public:
    PancakeHouseMenu();
    ~PancakeHouseMenu();
    void addItem(const string &name, const string &description,
            bool vegetarian, double price);
    Iterator* createIterator();
};

class DinerMenu: public Menu
{
private:
    const static int MAX_ITEMS = 6;
    int numberOfItems;
    MenuItem *menuItems[MAX_ITEMS];

public:
    DinerMenu();
    ~DinerMenu();
    void addItem(const string &name, const string &description,
            bool vegetarian, double price);
    Iterator* createIterator();
};

class CafeMenu: public Menu
{
    map<string, MenuItem*> menuItems;

public:
    CafeMenu();
    ~CafeMenu();
    void addItem(const string &name, const string &description,
            bool vegetarian, double price);
    Iterator* createIterator();
};

//
MenuItem::MenuItem(const string &name, const string &description,
        bool vegetarian, double price)
{
    this->name = name;
    this->description = description;
    this->vegetarian = vegetarian;
    this->price = price;
}

string MenuItem::getName()
{
    return name;
}

string MenuItem::getDescription()
{
    return description;
}

bool MenuItem::isVegetarian()
{
    return vegetarian;
}

double MenuItem::getPrice()
{
    return price;
}

PancakeHouseMenu::PancakeHouseMenu()
{
    addItem("K&B's Pancake Breakfast",
            "Pancakes with scrambled eggs, and toast",
            true,
            2.99);

    addItem("Regular Pancake Breakfast",
            "Pancakes with fried eggs, sausage",
            false,
            2.99);

    addItem("Blueberry Pancakes",
            "Pancakes made with fresh blueberries",
            true,
            3.49);

    addItem("Waffles",
            "Waffles, with your choice of blueberries or strawberries",
            true,
            3.59);
}

PancakeHouseMenu::~PancakeHouseMenu()
{
    vector<MenuItem*>::iterator iter;
    for(iter = menuItems.begin();
            iter != menuItems.end();
            iter++)
    {
        delete *iter;
    }
}

void PancakeHouseMenu::addItem(const string &name, const string &description,
         bool vegetarian, double price)
{
    MenuItem *menuItem = new MenuItem(name, description, vegetarian, price);
    menuItems.push_back(menuItem);
}

Iterator* PancakeHouseMenu::createIterator()
{
    return new PancakeHouseMenuIterator(menuItems);
}

DinerMenu::DinerMenu()
{
    numberOfItems = 0;
    for(int i=0; i<MAX_ITEMS; i++)
    {
        menuItems[i] = NULL;
    }

    addItem("Vegetarian BLT",
            "(Fakin') Bacon with lettuce & tomato on whole wheat",
            true,
            2.99);

    addItem("BLT",
            "Bacon with lettuce & tomato on whole wheat",
            false,
            2.99);

    addItem("Soup of the day",
            "Soup of the day, with a side of potato salad",
            false,
            3.29);

    addItem("Hotdog",
            "A hot dog, with saurkraut, relish, onions, topped with cheese",
            false,
            3.05);

    addItem("Steamed Veggies and Brown Rice",
            "Steamed vegetables over brown rice",
            true,
            3.99);

    addItem("Pasta",
            "Spaghetti with Marinara Sauce, and a slice of sourdough bread",
            false,
            3.89);
}

DinerMenu::~DinerMenu()
{
    for(int i=0; i<MAX_ITEMS && menuItems[i]!=NULL; i++)
    {
        delete menuItems[i];
    }
}

void DinerMenu::addItem(const string &name, const string &description,
        bool vegetarian, double price)
{
    MenuItem *menuItem = new MenuItem(name, description, vegetarian, price);
    if(numberOfItems >= MAX_ITEMS)
    {
        cout << "Sorry, menu is full! Can't add item to menu";
    }
    else
    {
        menuItems[numberOfItems] = menuItem;
        numberOfItems++;
    }
}

Iterator* DinerMenu::createIterator()
{
    return new DinerMenuIterator(menuItems, sizeof(menuItems)/sizeof(*menuItems));
}

CafeMenu::CafeMenu()
{
    addItem("Veggie Burger and Air Fries",
            "Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
            true,
            3.99);

    addItem("Soup of the day",
            "A cup of the soup of the day, with a side salad",
            false,
            3.69);

    addItem("Burrito",
            "A large burrito, with whole pinto beans, salsa, guacamole",
            true,
            4.29);
}

CafeMenu::~CafeMenu()
{
    map<string, MenuItem*>::iterator iter;
    for(iter=menuItems.begin(); iter!=menuItems.end(); iter++)
    {
        delete iter->second;
    }
}

void CafeMenu::addItem(const string &name, const string &description,
        bool vegetarian, double price)
{
    MenuItem *menuItem = new MenuItem(name, description, vegetarian, price);
    menuItems.insert(pair<string, MenuItem*>(menuItem->getName(), menuItem));
}

Iterator* CafeMenu::createIterator()
{
    return new CafeMenuIterator(menuItems);
}

//#ifndef __WAITRESS_H__

class Waitress
{
private:
    vector<Menu*> menus;

    void printMenu(Iterator *iterator);

public:
    Waitress(vector<Menu*> &menus);
    void printMenu();
};

//#include "Waitress.h"

Waitress::Waitress(vector<Menu*> &menus)
{
    this->menus = menus;
}

void Waitress::printMenu()
{
    vector<Menu*>::iterator menuIterator;
    for(menuIterator = menus.begin();
            menuIterator != menus.end();
            menuIterator++)
    {
        printMenu((*menuIterator)->createIterator());
    }
}

void Waitress::printMenu(Iterator *iterator)
{
    while(iterator->hasNext())
    {
        MenuItem *menuItem = iterator->next();
        cout << menuItem->getName() << ", "
            << menuItem->getPrice() << " -- "
            << menuItem->getDescription() << endl;
    }
}

/* 
 * THE ITERATOR PATTERN provides a way to access the elements of and aggregate object sequentially 
 * without exposing the underlying representation.
 */
int main()
{
    Menu *pancakeHouseMenu = new PancakeHouseMenu();
    Menu *dinerMenu = new DinerMenu();
    Menu *cafeMenu = new CafeMenu();
    vector<Menu*> menu;

    menu.push_back(pancakeHouseMenu);
    menu.push_back(dinerMenu);
    menu.push_back(cafeMenu);

    Waitress *waitress = new Waitress(menu);

    waitress->printMenu();

    delete pancakeHouseMenu;
    delete dinerMenu;
    delete cafeMenu;
    delete waitress;

    return 0;
}

