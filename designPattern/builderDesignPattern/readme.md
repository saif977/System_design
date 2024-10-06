# Builder design pattern 
- The core of the Builder Pattern is to replace a constructor call overfilled with parameters with a step by step instruction on how to build and assemble the product.
- For example, instead of instantiating a burger object by calling it’s parameterized constructor:
- ```
  Burger(BurgerBun, BeefPatty, Onions, Lettuce, Cheese, Ketchup, Mayo);
  ```
- we decompose the process into steps to construct the burger such as:
- ```
  Burger.AddBread()
  Burger.AddProtein()
  Burger.AddSides()
  Burger.AddSauce()
  ```
-  This is mainly used while making  config files.
- Lets create a Sandwich, which can be represented as Sandwich Class
- ```
  enum class Bread {Toast, HotdogBun, BurgerBun};
  enum class Protein {ChickenPatty, Aloo, Bacon};
  enum class Side{Lettuce, Tomato, Onions, Cheese};
  enum class Sauce {Mayo, Ketchup, YumYum, Mustard};
  enum class Wrapper {Paper, Box, Plastic};

  class Sandwich {
  public:
    Sandwich(Bread b, Protein p, std::vector<Side> sides, std::vector<Sauce> sauces, Wrapper w) :
    b{b}, p{p}, sides{sides}, sauces{sauces}, w{w} {
        std::cout << "A Sandwich is Constructed" << std::endl;
    }
    Bread b;
    Protein p;
    std::vector<Side> sides;
    std::vector<Sauce> sauces;
    Wrapper w;
   };
``
 - Now, to construct a sandwich, we would need to pass in all the different parameters to make the specific type of sandwich:

- ```
    int main() { 

    Sandwich burger(Bread::BurgerBun, Protein::BeefPatty, 
      std::vector<Side>{Side::Lettuce,Side::Cheese,Side::Tomato}, 
      std::vector<Sauce>{Sauce::YumYum}, Wrapper::Paper);

    Sandwich hotdog(Bread::HotdogBun, Protein::Dog, 
      std::vector<Side>{Side::Onions}, 
      std::vector<Sauce>{Sauce::Ketchup, Sauce::Mustard}, Wrapper::Box);

    Sandwich BLT(Bread::Toast, Protein::Bacon, 
      std::vector<Side>{Side::Tomato, Side::Lettuce}, 
      std::vector<Sauce>{Sauce::Mayo}, Wrapper::Plastic);
    
    return 0;  }

- Here the issue is that, The customer can send wrong config and the code still works, for example the customer selected the `bread : toast` and `patty : chicken` instead of `patty : aloo`. So here the sandwich will still be made and customer is served with wrong sandwich.
- Here the issue is also that, We have to create a lot constructor overloading if there are more number of member variables present in a Class.
- To avoid this we will use a Builder Class which will take care of the  members of the class.
- Example if we want to make 2 types of sandwitches then we make 2 types of sandwich builders.
- These 2 types of sandwich builders will inherit the abstract sandwich builder class.
- ``` 
    class SandwichBuilder {
     public:
      virtual void AddBread() = 0;
      virtual void AddProtein() = 0;
      void AddSide(Side s) {product.sides.push_back(s);}
      void AddSauce(Sauce s) {product.sauces.push_back(s);}
      virtual void AddWrapper() = 0;
      Sandwich ReturnProduct() {return product;} // Note that this should be   decalred in concrete builders if returned products are different.
      Sandwich product; 
    }; 
- 1 type of sandwich is HotDog
- ```
   class HotdogBuilder : public SandwichBuilder {
    public:
    void AddBread() {
        std::cout << "Steaming up the buns" << std::endl;
        product.b = Bread::HotdogBun;
    }
    void AddProtein() {
        std::cout << "Boiling the hotdog in brine" << std::endl;
        product.p = Protein::Dog;
    }
    void AddWrapper() {
        std::cout << "Placing hotdog into box" << std::endl;
        product.w = Wrapper::Box;
    }
  };
- 2 type of sandwich is burger
- ```
  class BurgerBuilder : public SandwichBuilder {
   public:
    void AddBread() {
        std::cout << "Heating up the Seasame Sprinked Bun" << std::endl;
        product.b = Bread::BurgerBun;
    }
    void AddProtein() {
        std::cout << "Grilling the Wagyu" << std::endl;
        product.p = Protein::BeefPatty;
    }
    void AddWrapper() {
        std::cout << "Wrapping with 100% recycled paper" << std::endl;
        product.w = Wrapper::Paper;
    }
  };  
- Now we will create methods , which will help us to make these burgers. 
- ```
  Sandwich BuildBurger() {
    BurgerBuilder builder;
    builder.AddBread();
    builder.AddProtein();
    builder.AddSide(Side::Lettuce);
    builder.AddSide(Side::Tomato);
    builder.AddSauce(Sauce::YumYum);
    builder.AddWrapper();
    return builder.ReturnProduct();
  }

  Sandwich BuildHotdog() {
    HotdogBuilder builder;
    builder.AddBread();
    builder.AddProtein();
    builder.AddSide(Side::Onions);
    builder.AddSauce(Sauce::Ketchup);
    builder.AddSauce(Sauce::Mustard);
    builder.AddWrapper();
    return builder.ReturnProduct();
  }

  int main() {
    Sandwich burger = BuildBurger();
    Sandwich hotdog = BuildHotdog();
    Sandwich BLT = BuildBLT();
    return 0;
  }

- We can also use chaining in the above methods, for that we have return the object in each of the methods in builder classes.
- Ex Now hotDog builder will look like 
- ``` 
   class HotdogBuilder : public SandwichBuilder {
    public:
    void AddBread() {
        std::cout << "Steaming up the buns" << std::endl;
        product.b = Bread::HotdogBun;
        return *this;
    }
    void AddProtein() {
        std::cout << "Boiling the hotdog in brine" << std::endl;
        product.p = Protein::Dog;
        return *this;
    }
    void AddWrapper() {
        std::cout << "Placing hotdog into box" << std::endl;
        product.w = Wrapper::Box;
        return *this;
    }
  };

- Now we can use this builder as 
-     Sandwich BuildHotdog() {
      HotdogBuilder builder;
      builder.AddBread().AddProtein().AddSide(Side::Onions).AddSauce(Sauce::Ketchup).AddSauce(Sauce::Mustard).AddWrapper();
      return builder.ReturnProduct();
      }

- Here We can also make an common way to build burgers. By adding the defaultSides and defaultSauces method in each sandwich builder type.
- Now the builder interface will look like 
- ```
  class SandwichBuilder {
   public:
    virtual void AddBread() = 0;
    virtual void AddProtein() = 0;
    void AddSide(Side s) {product.sides.push_back(s);}
    void AddSauce(Sauce s) {product.sauces.push_back(s);}
    virtual void AddWrapper() = 0;
    void addDefaultSides()  = 0;
    void addDefaultSauces() = 0;
    Sandwich ReturnProduct() {return product;} // Note that this should be   decalred in concrete builders if returned products are different.
    Sandwich product; 
  };
 - Now we can update the hotDog Builder as
 - ```
   class HotdogBuilder : public SandwichBuilder {
    public:
    void AddBread() {
      std::cout << "Steaming up the buns" << std::endl;
      product.b = Bread::HotdogBun;

    }
    void AddProtein() {
      std::cout << "Boiling the hotdog in brine" << std::endl;
      product.p = Protein::Dog;

    }
    void AddWrapper() {
      std::cout << "Placing hotdog into box" << std::endl;
      product.w = Wrapper::Box;
 
    }
    void addDefaultSides(){
        this->AddSide(Side::Onions);
  
    }
    void addDefaultSauces(){
        this->AddSauce(Sauce::Ketchup);
        this->AddSauce(Sauce::Mustard)
    }
   };
   
- Now we have to make a common method instead of different methods.
- Ex - one common method  to create Sandwich is buildSandwich instead of buildHotdog,buildBurger.
- ```
  Sandwich CreateSandwich(SandwichBuilder* builder) {
    builder->AddBread();
    builder->AddProtein();
    builder->addDefaultSides();
    builder->addDefaultSauces();
    builder->AddWrapper();
    return builder->ReturnProduct();
  }

  int main(){
    Sandwich burger = CreateSandwich(new BurgerBuilder());
    Sandwich hotDog = CreateSandwich(new HotdogBuilder());
    return 0;
  }

 - The scalability of our Sandwich shop will amplify when we introduce the Director class. 
 - The role of Director class is to direct the execution on the building process.
 - Lets take example of building process of sandwich at different scenarious
 - ```
   Dine In Order: AddBread -> AddProtein -> addDefaultSides -> addDefaultSauces
   Takeout Order: Steps from Dine In Order -> AddWrapper
   Order No Sides: AddBread -> AddProtein -> addDefaultSauces
   Order without Sauces: AddBread -> AddProtein -> addDefaultSides
- Ex :
- ``` 
  Class Director{

    public:

     Sandwich dineIn(Sandwich *builder){
        builder->AddBread();
        builder->AddProtein();
        builder->addDefaultSides();
        builder->addDefaultSauces;
        return builder;
     }

      Sandwich takeOut(Sandwich *builder){
        builder->AddBread();
        builder->AddProtein();
           builder->addDefaultSides();
        builder->addDefaultSauces;
        builder->AddWrapper();
        return builder;
     } 

    Sandwich noSauce(Sandwich *builder){
        builder->AddBread();
        builder->AddProtein();
        builder->addDefaultSides();
        return builder;
     }  

    Sandwich noSides(Sandwich *builder){
        builder->AddBread();
        builder->AddProtein();
        builder->addDefaultSauces;
        return builder;
     }  
  }   

  int main()
  {
    Director d = new Director();
    Sandwich t_o = d.TakeoutOrder(new hotDogBuilder());
    Sandwich d_i = d.DineInOrder(new hotDogBuilder());
    Sandwich no_sauce = d.noSauce(new burgerBuilder());
    Sandwich no_sides = d.noSides(new burgerBuilder);
    return 0;
  }



