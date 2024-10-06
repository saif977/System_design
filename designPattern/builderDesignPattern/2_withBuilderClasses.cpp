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
};

//======== Abstract Sandwich builder class ================
class SandwichBuilder
{
public:
    virtual void addBread() = 0;   // Making it pure virtual function, So that the Specific builder class is forced to define these functions which will add specific bread for that specific sandwich.
    virtual void addProtein() = 0; // Making it pure virtual function, So that the Specific builder class is forced to define these functions which will add specific protein for that specific sandwich.
    void addSide(Side s)
    {
        cout<<"Adding Side : "<<sideToString(s)<<endl;
        sandwich.side.push_back(s);
    }
    void addSauce(Sauce s)
    {
        cout<<"Adding Sauce : "<<sauceToString(s)<<endl;
        sandwich.sauce.push_back(s);
    }
    virtual void addWrapper() = 0; // Making it pure virtual function, So that the Specific builder class is forced to define these functions which will add specific wrapper for that specific sandwich.
    Sandwich getSandwich(){return sandwich;}
    Sandwich sandwich;
};
//==========================================================

//=================== HotDog chicken Sandwich builder class ================
class HotDogSandwich : public SandwichBuilder{
    public:
     void addBread(){
        cout<<"Adding Bread : "<<breadToString(Bread::HotdogBun)<<endl;
        sandwich.b = Bread::HotdogBun;
     }
     void addProtein(){
        cout<<"Adding Protien : "<<proteinToString(Protein::ChickenPatty)<<endl;
        sandwich.p = Protein::ChickenPatty;
     }
     void addWrapper(){
        cout<<"Adding Wrapper : "<<wrapperToString(Wrapper::Box)<<endl;
        sandwich.w = Wrapper::Box; 
     }; 
};
//==================================================================

//=================== Veg Burger Aloo Sandwich builder class ================
class VegBurgerSandwich : public SandwichBuilder{
    public:
     void addBread(){
        cout<<"Adding Bread : "<<breadToString(Bread::BurgerBun)<<endl;
        sandwich.b = Bread::HotdogBun;
     }
     void addProtein(){
        cout<<"Adding Protien : "<<proteinToString(Protein::Aloo)<<endl;
        sandwich.p = Protein::ChickenPatty;
     }
     void addWrapper(){
        cout<<"Adding Wrapper : "<<wrapperToString(Wrapper::Paper)<<endl;
        sandwich.w = Wrapper::Box; 
     }; 
};
//==================================================================

//================= Method to build HotDog chicken sandwich ================
Sandwich buildHotDogSandwich(){
    HotDogSandwich sandwich;
    sandwich.addBread();
    sandwich.addProtein();
    sandwich.addSide(Side::Cheese);
    sandwich.addSauce(Sauce::Mayo);
    sandwich.addWrapper();
    return sandwich.getSandwich();
}
//==========================================================================

//================= Method to build Veg Burger sandwich ================
Sandwich buildVegBurgerSandwich(){
    VegBurgerSandwich sandwich;
    sandwich.addBread();
    sandwich.addProtein();
    sandwich.addSide(Side::Onions);
    sandwich.addSauce(Sauce::Ketchup);
    sandwich.addWrapper();
    return sandwich.getSandwich();
}
//==========================================================================



int main()
{
    // Building Diiferent Sandwiches

    // ================  Earlier without Builder classes ===============
    // Chicken HotDog
    //Sandwich chickenHotDog = Sandwich(Bread::HotdogBun, Protein::ChickenPatty, {Side::Onions, Side::Cheese}, {Sauce::Mayo, Sauce::Ketchup}, Wrapper::Box);

    // Config Error (Want to build veg burger, But build burger with Chicken patty instead)
    //Sandwich vegAlooPatty = Sandwich(Bread::BurgerBun, Protein::ChickenPatty, {Side::Onions, Side::Cheese}, {Sauce::Mayo, Sauce::Ketchup}, Wrapper::Box);
    //===================================================================


    // ========  With Builder classes ===========
    //chicken Hotdog
    Sandwich chickenHotDog = buildHotDogSandwich();

    cout<<"============="<<endl;

    //VegBurger
    // Here the user need not to pass any configs which is less error prone.
    Sandwich vegBurger = buildVegBurgerSandwich();
    //===========================================
    
    return 0;
}