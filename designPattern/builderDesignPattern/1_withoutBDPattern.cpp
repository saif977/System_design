#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==== ENUM =========
enum class Bread
{
    Toast,
    HotdogBun,
    BurgerBun
};
enum class Protein
{
    ChickenPatty,
    Aloo,
    Bacon
};
enum class Side
{
    Lettuce,
    Tomato,
    Onions,
    Cheese
};
enum class Sauce
{
    Mayo,
    Ketchup,
    YumYum,
    Mustard
};
enum class Wrapper
{
    Paper,
    Box,
    Plastic
};
// ===============

// ================== Function to convert enums to string for readable output =========
string breadToString(Bread b)
{
    switch (b)
    {
    case Bread::Toast:
        return "Toast";
    case Bread::HotdogBun:
        return "Hotdog Bun";
    case Bread::BurgerBun:
        return "Burger Bun";
    default:
        return "Unknown Bread";
    }
}

string proteinToString(Protein p)
{
    switch (p)
    {
    case Protein::ChickenPatty:
        return "Chicken Patty";
    case Protein::Aloo:
        return "Aloo";
    case Protein::Bacon:
        return "Bacon";
    default:
        return "Unknown Protein";
    }
}

string sideToString(Side s)
{
    switch (s)
    {
    case Side::Lettuce:
        return "Lettuce";
    case Side::Tomato:
        return "Tomato";
    case Side::Onions:
        return "Onions";
    case Side::Cheese:
        return "Cheese";
    default:
        return "Unknown Side";
    }
}

string sauceToString(Sauce s)
{
    switch (s)
    {
    case Sauce::Mayo:
        return "Mayo";
    case Sauce::Ketchup:
        return "Ketchup";
    case Sauce::YumYum:
        return "YumYum";
    case Sauce::Mustard:
        return "Mustard";
    default:
        return "Unknown Sauce";
    }
}

string wrapperToString(Wrapper w)
{
    switch (w)
    {
    case Wrapper::Paper:
        return "Paper";
    case Wrapper::Box:
        return "Box";
    case Wrapper::Plastic:
        return "Plastic";
    default:
        return "Unknown Wrapper";
    }
}

//==============================================

// Class Sandwich
class Sandwich
{
public:
    Bread b;
    Protein p;
    vector<Side> side;
    vector<Sauce> sauce;
    Wrapper w;
    Sandwich(Bread b, Protein p, vector<Side> side, vector<Sauce> sauce, Wrapper w) : b{b}, p{p}, side{side}, sauce{sauce}, w{w}
    {
        cout << "Sandwich is constructed with following items:" << endl;
        cout << "Bread: " << breadToString(b) << endl;
        cout << "Protein: " << proteinToString(p) << endl;
        cout << "Sides: ";
        for (Side s : side)
        {
            cout << sideToString(s) << " ";
        }
        cout << endl;

        cout << "Sauces: ";
        for (Sauce s : sauce)
        {
            cout << sauceToString(s) << " ";
        }
        cout << endl;

        cout << "Wrapper: " << wrapperToString(w) << endl;
    }
};

int main()
{
    // Building Diiferent Sandwiches

    // Chicken HotDog
    Sandwich chickenHotDog = Sandwich(Bread::HotdogBun,Protein::ChickenPatty,{Side::Onions,Side::Cheese},{Sauce::Mayo,Sauce::Ketchup},Wrapper::Box);
    
    // Config Error (Want to build veg burger, But build burger with Chicken patty instead)
    Sandwich vegAlooPatty = Sandwich(Bread::BurgerBun,Protein::ChickenPatty,{Side::Onions,Side::Cheese},{Sauce::Mayo,Sauce::Ketchup},Wrapper::Box); 
    return 0;
}