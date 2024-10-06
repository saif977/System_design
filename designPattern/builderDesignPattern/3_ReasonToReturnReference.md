In the context of your builder pattern implementation, the return type `SandwichBuilder&` (a reference to the builder) is used in the member functions such as `addBread()`, `addProtein()`, `addSide()`, etc. Here’s why you need to return a reference (`&`) rather than returning a value:

### 1. **Enabling Method Chaining**:
   The key feature of the Builder pattern, especially in languages like C++ and Java, is **method chaining**. This allows you to chain calls like:
   ```cpp
   sandwich.addBread().addProtein().addSide(Side::Cheese).addSauce(Sauce::Mayo).addWrapper();
   ```
   For chaining to work, each method in the chain must return the same object (i.e., the current builder instance). Returning a reference (`SandwichBuilder&`) ensures that the same object (the builder instance) is returned and used in subsequent method calls.

   If you return by value (i.e., just `SandwichBuilder`), a **copy** of the object will be returned, and subsequent method calls would operate on different copies of the builder object, breaking the chain and causing unwanted behavior.

### 2. **Efficiency**:
   Returning by reference (`SandwichBuilder&`) avoids copying the object. If you were to return by value, the compiler would create a copy of the builder object each time you call a method, which would be inefficient, especially if the object holds large data structures (like your `Sandwich` object, which contains vectors).

   Here's an example of how returning by value would break the chain:
   ```cpp
   SandwichBuilder sandwich;
   sandwich.addBread();  // A copy of sandwich is returned
   sandwich.addProtein();  // This would operate on the original object, not the copy
   ```

   By returning a reference (`SandwichBuilder&`), both the `addBread()` and `addProtein()` operate on the same `sandwich` object.

### 3. **Consistency**:
   If you return by reference, every method call modifies the same instance of the builder. This maintains consistency across the builder’s state. When all methods modify the same object, the final call to `getSandwich()` returns the sandwich object with all the applied modifications.

### Code Example:

```cpp
class SandwichBuilder
{
public:
    virtual SandwichBuilder& addBread() = 0;
    virtual SandwichBuilder& addProtein() = 0;
    SandwichBuilder& addSide(Side s)
    {
        sandwich.side.push_back(s);
        return *this; // Returning reference to the current builder instance
    }
    SandwichBuilder& addSauce(Sauce s)
    {
        sandwich.sauce.push_back(s);
        return *this; // Returning reference to the current builder instance
    }
    virtual SandwichBuilder& addWrapper() = 0;
    Sandwich getSandwich() { return sandwich; }
protected:
    Sandwich sandwich;
};
```

### Key Benefits of Returning by Reference:
- **Method chaining** is supported.
- **No unnecessary object copies** are made.
- The builder's **internal state** is consistently maintained and modified.

By using `SandwichBuilder&`, you ensure that your builder pattern is both efficient and supports chaining, allowing for easy and flexible construction of complex objects like `Sandwich`.