/**
 * @brief Decorator pattern example for adding additional functionality to objects.
 *
 * The **Decorator** pattern allows you to add new behavior to an object dynamically 
 * without modifying its structure. This pattern is useful for adding features 
 * to individual objects in a flexible and reusable way.
 *
 * **Key Concepts:**
 * 1. **Component (`Coffee`)**: An abstract class that defines the interface for the object being decorated.
 * 2. **Concrete Component (`SimpleCoffee`)**: A class that implements the basic behavior of the object being decorated.
 * 3. **Decorator (`CoffeeDecorator`)**: An abstract class that wraps a `Coffee` object and adds functionality.
 * 4. **Concrete Decorators (`MilkDecorator`, `SugarDecorator`)**: Concrete classes that add new functionality to the `Coffee` object.
 *
 * **How it works:**
 * 1. The `Coffee` class provides the basic functionality for a coffee object.
 * 2. `SimpleCoffee` is the base class representing a simple coffee without any added ingredients.
 * 3. `CoffeeDecorator` is an abstract decorator that wraps a `Coffee` object, allowing additional functionality.
 * 4. `MilkDecorator` and `SugarDecorator` are concrete decorators that add milk and sugar to the coffee, respectively.
 * 5. The client can dynamically "decorate" the coffee object by wrapping it in various decorators.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 /**
  * @brief Abstract Component class representing the base Coffee object.
  *
  * The `Coffee` class defines the interface for the object being decorated. All concrete objects
  * (like `SimpleCoffee`) and decorators (like `MilkDecorator`) follow this interface.
  */
 class Coffee
 {
 public:
     virtual ~Coffee() = default;
 
     /**
      * @brief Get the description of the coffee.
      *
      * This method returns a description of the coffee.
      *
      * @return A string describing the coffee.
      */
     virtual std::string getDescription() const = 0;
 
     /**
      * @brief Get the cost of the coffee.
      *
      * This method returns the cost of the coffee.
      *
      * @return The cost of the coffee.
      */
     virtual double cost() const = 0;
 };
 
 /**
  * @brief Concrete Component class representing a simple coffee.
  *
  * The `SimpleCoffee` class implements the basic behavior of the `Coffee` interface.
  * It represents a basic coffee without any additions.
  */
 class SimpleCoffee : public Coffee
 {
 public:
     /**
      * @brief Get the description of the simple coffee.
      *
      * @return A string description of the simple coffee ("Simple Coffee").
      */
     std::string getDescription() const override
     {
         return "Simple Coffee";
     }
 
     /**
      * @brief Get the cost of the simple coffee.
      *
      * @return The cost of the simple coffee (5.0).
      */
     double cost() const override
     {
         return 5.0;
     }
 };
 
 /**
  * @brief Abstract Decorator class for adding functionality to a Coffee object.
  *
  * The `CoffeeDecorator` class wraps a `Coffee` object and adds functionality to it.
  * All concrete decorators must extend this class and implement their own behavior.
  */
 class CoffeeDecorator : public Coffee
 {
 public:
     /**
      * @brief Constructor that accepts a `Coffee` object to decorate.
      *
      * @param coffee A shared pointer to the `Coffee` object to be decorated.
      */
     explicit CoffeeDecorator(std::shared_ptr<Coffee> coffee)
         : m_coffee(coffee)
     {
     }
 
     /**
      * @brief Get the description of the decorated coffee.
      *
      * This method delegates to the wrapped `Coffee` object's `getDescription()` method.
      *
      * @return The description of the decorated coffee.
      */
     std::string getDescription() const override
     {
         return m_coffee->getDescription();
     }
 
     /**
      * @brief Get the cost of the decorated coffee.
      *
      * This method delegates to the wrapped `Coffee` object's `cost()` method.
      *
      * @return The cost of the decorated coffee.
      */
     double cost() const override
     {
         return m_coffee->cost();
     }
 
 protected:
     std::shared_ptr<Coffee> m_coffee; ///< The `Coffee` object being decorated
 };
 
 /**
  * @brief Concrete Decorator class for adding milk to the coffee.
  *
  * The `MilkDecorator` class adds milk functionality to the coffee object.
  */
 class MilkDecorator : public CoffeeDecorator
 {
 public:
     /**
      * @brief Constructor that accepts a `Coffee` object to decorate.
      *
      * @param coffee A shared pointer to the `Coffee` object to be decorated.
      */
     explicit MilkDecorator(std::shared_ptr<Coffee> coffee)
         : CoffeeDecorator(coffee)
     {
     }
 
     /**
      * @brief Get the description of the coffee with milk.
      *
      * @return A string description of the coffee with milk ("Simple Coffee with Milk").
      */
     std::string getDescription() const override
     {
         return m_coffee->getDescription() + " with Milk";
     }
 
     /**
      * @brief Get the cost of the coffee with milk.
      *
      * @return The cost of the coffee with milk (cost of the base coffee + 1.0 for milk).
      */
     double cost() const override
     {
         return m_coffee->cost() + 1.0;
     }
 };
 
 /**
  * @brief Concrete Decorator class for adding sugar to the coffee.
  *
  * The `SugarDecorator` class adds sugar functionality to the coffee object.
  */
 class SugarDecorator : public CoffeeDecorator
 {
 public:
     /**
      * @brief Constructor that accepts a `Coffee` object to decorate.
      *
      * @param coffee A shared pointer to the `Coffee` object to be decorated.
      */
     explicit SugarDecorator(std::shared_ptr<Coffee> coffee)
         : CoffeeDecorator(coffee)
     {
     }
 
     /**
      * @brief Get the description of the coffee with sugar.
      *
      * @return A string description of the coffee with sugar ("Simple Coffee with Sugar").
      */
     std::string getDescription() const override
     {
         return m_coffee->getDescription() + " with Sugar";
     }
 
     /**
      * @brief Get the cost of the coffee with sugar.
      *
      * @return The cost of the coffee with sugar (cost of the base coffee + 0.5 for sugar).
      */
     double cost() const override
     {
         return m_coffee->cost() + 0.5;
     }
 };
 
 /**
  * @brief Main function demonstrating the Decorator pattern.
  *
  * This function demonstrates how the Decorator pattern allows you to add new functionality 
  * (milk, sugar) to a coffee object dynamically, without modifying the base `SimpleCoffee` class.
  */
 int main()
 {
     // Create a simple coffee
     std::shared_ptr<Coffee> coffee = std::make_shared<SimpleCoffee>();
 
     // Decorate the coffee with milk
     std::shared_ptr<Coffee> milkCoffee = std::make_shared<MilkDecorator>(coffee);
 
     // Decorate the milk coffee with sugar
     std::shared_ptr<Coffee> milkSugarCoffee = std::make_shared<SugarDecorator>(milkCoffee);
 
     // Output the description and cost of the final coffee
     std::cout << "Description: " << milkSugarCoffee->getDescription() << std::endl;
     std::cout << "Cost: $" << milkSugarCoffee->cost() << std::endl;
 
     return 0;
 }
 