/**
 * @brief Builder pattern example for creating different types of pizzas.
 *
 * **Key Concepts:**
 * 1. **Product (`Pizza`)**: Represents the complex object that is being built.
 * 2. **Abstract Builder (`PizzaBuilder`)**: Defines the abstract interface for constructing the parts of the product.
 * 3. **Concrete Builder (`VeggiePizzaBuilder`, `CheesePizzaBuilder`)**: Implements the construction steps for a specific type of pizza.
 * 4. **Director (`PizzaDirector`)**: Uses the builder to construct the pizza step by step without knowing the exact details of how the pizza is built.
 *
 * **How it works:**
 * 1. We have an abstract `PizzaBuilder` class with methods for building different parts of the pizza (`dough`, `sauce`, and `toppings`).
 * 2. `VeggiePizzaBuilder` and `CheesePizzaBuilder` are concrete builders that implement the `PizzaBuilder` interface and define specific details for building a Veggie Pizza and Cheese Pizza.
 * 3. The `PizzaDirector` takes a builder object and coordinates the construction process, ensuring the pizza is assembled step by step.
 * 4. Finally, the client code constructs different pizzas using the builder pattern and describes the resulting pizzas.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <vector>
 
 /**
  * @brief Product class representing a pizza.
  *
  * The `Pizza` class represents the complex object that is being built. It has methods for setting
  * its dough, sauce, and toppings, as well as for describing the pizza.
  */
 class Pizza
 {
 public:
     /**
      * @brief Set the dough for the pizza.
      * 
      * @param dough The type of dough for the pizza (e.g., "Whole Wheat", "Regular").
      */
     void setDough(const std::string &dough)
     {
         dough_ = dough;
     }
 
     /**
      * @brief Set the sauce for the pizza.
      * 
      * @param sauce The type of sauce for the pizza (e.g., "Tomato", "Cream").
      */
     void setSauce(const std::string &sauce)
     {
         sauce_ = sauce;
     }
 
     /**
      * @brief Set the toppings for the pizza.
      * 
      * @param toppings A list of toppings for the pizza (e.g., "Olives", "Cheese").
      */
     void setToppings(const std::vector<std::string> &toppings)
     {
         toppings_ = toppings;
     }
 
     /**
      * @brief Describe the pizza.
      * 
      * This method prints out a description of the pizza, including its dough, sauce, and toppings.
      */
     void describe() const
     {
         std::cout << "Pizza with " << dough_ << " dough, "
                   << sauce_ << " sauce, and toppings: ";
         for (const auto &topping : toppings_)
         {
             std::cout << topping << " ";
         }
         std::cout << "\n";
     }
 
 private:
     std::string dough_; ///< Dough type for the pizza
     std::string sauce_; ///< Sauce type for the pizza
     std::vector<std::string> toppings_; ///< List of toppings for the pizza
 };
 
 /**
  * @brief Abstract Builder class for constructing pizzas.
  *
  * The `PizzaBuilder` class defines the abstract interface for constructing the different parts of a pizza,
  * such as the dough, sauce, and toppings. Concrete builders implement this interface to build specific types of pizzas.
  */
 class PizzaBuilder
 {
 public:
     virtual ~PizzaBuilder() = default;
 
     /**
      * @brief Build the dough for the pizza.
      * 
      * Concrete builders must implement this method to define how the dough is built.
      */
     virtual void buildDough() = 0;
 
     /**
      * @brief Build the sauce for the pizza.
      * 
      * Concrete builders must implement this method to define how the sauce is built.
      */
     virtual void buildSauce() = 0;
 
     /**
      * @brief Build the toppings for the pizza.
      * 
      * Concrete builders must implement this method to define how the toppings are built.
      */
     virtual void buildToppings() = 0;
 
     /**
      * @brief Get the constructed pizza.
      * 
      * This method returns the pizza object after it has been fully constructed.
      * 
      * @return A shared pointer to the constructed pizza.
      */
     virtual std::shared_ptr<Pizza> getPizza() = 0;
 };
 
 /**
  * @brief Concrete builder class for creating Veggie pizza.
  *
  * The `VeggiePizzaBuilder` class is a concrete implementation of the `PizzaBuilder` interface. It builds
  * a Veggie pizza by specifying the dough, sauce, and toppings.
  */
 class VeggiePizzaBuilder : public PizzaBuilder
 {
 public:
     VeggiePizzaBuilder() : pizza_(std::make_shared<Pizza>()) {}
 
     /**
      * @brief Build the dough for the Veggie pizza.
      * 
      * Sets the dough to "Whole Wheat".
      */
     void buildDough() override
     {
         pizza_->setDough("Whole Wheat");
     }
 
     /**
      * @brief Build the sauce for the Veggie pizza.
      * 
      * Sets the sauce to "Tomato".
      */
     void buildSauce() override
     {
         pizza_->setSauce("Tomato");
     }
 
     /**
      * @brief Build the toppings for the Veggie pizza.
      * 
      * Adds "Olives", "Bell Peppers", and "Mushrooms" as toppings.
      */
     void buildToppings() override
     {
         pizza_->setToppings({"Olives", "Bell Peppers", "Mushrooms"});
     }
 
     /**
      * @brief Get the constructed Veggie pizza.
      * 
      * Returns the fully constructed Veggie pizza.
      * 
      * @return A shared pointer to the constructed Veggie pizza.
      */
     std::shared_ptr<Pizza> getPizza() override
     {
         return pizza_;
     }
 
 private:
     std::shared_ptr<Pizza> pizza_; ///< The pizza object being constructed
 };
 
 /**
  * @brief Concrete builder class for creating Cheese pizza.
  *
  * The `CheesePizzaBuilder` class is a concrete implementation of the `PizzaBuilder` interface. It builds
  * a Cheese pizza by specifying the dough, sauce, and toppings.
  */
 class CheesePizzaBuilder : public PizzaBuilder
 {
 public:
     CheesePizzaBuilder() : pizza_(std::make_shared<Pizza>()) {}
 
     /**
      * @brief Build the dough for the Cheese pizza.
      * 
      * Sets the dough to "Regular".
      */
     void buildDough() override
     {
         pizza_->setDough("Regular");
     }
 
     /**
      * @brief Build the sauce for the Cheese pizza.
      * 
      * Sets the sauce to "Cream".
      */
     void buildSauce() override
     {
         pizza_->setSauce("Cream");
     }
 
     /**
      * @brief Build the toppings for the Cheese pizza.
      * 
      * Adds "Cheese" as the only topping.
      */
     void buildToppings() override
     {
         pizza_->setToppings({"Cheese"});
     }
 
     /**
      * @brief Get the constructed Cheese pizza.
      * 
      * Returns the fully constructed Cheese pizza.
      * 
      * @return A shared pointer to the constructed Cheese pizza.
      */
     std::shared_ptr<Pizza> getPizza() override
     {
         return pizza_;
     }
 
 private:
     std::shared_ptr<Pizza> pizza_; ///< The pizza object being constructed
 };
 
 /**
  * @brief Director class that constructs pizzas using a builder.
  *
  * The `PizzaDirector` class coordinates the construction of a pizza by using a `PizzaBuilder` object. 
  * It controls the steps of pizza creation without needing to know the details of the pizza.
  */
 class PizzaDirector
 {
 public:
     /**
      * @brief Constructor that accepts a builder.
      * 
      * @param builder A shared pointer to a `PizzaBuilder` object used to construct the pizza.
      */
     PizzaDirector(std::shared_ptr<PizzaBuilder> builder)
         : builder_(builder) {}
 
     /**
      * @brief Construct a pizza using the builder.
      * 
      * This method uses the builder to construct the pizza step by step (dough, sauce, toppings).
      * 
      * @return A shared pointer to the constructed pizza.
      */
     std::shared_ptr<Pizza> construct()
     {
         builder_->buildDough();
         builder_->buildSauce();
         builder_->buildToppings();
         return builder_->getPizza();
     }
 
 private:
     std::shared_ptr<PizzaBuilder> builder_; ///< The builder used to construct the pizza
 };
 
 /**
  * @brief Main function demonstrating the Builder pattern.
  *
  * This function demonstrates the use of the Builder pattern to construct different types of pizzas
  * (Veggie and Cheese) using respective builders and a director.
  */
 int main()
 {
     // Use VeggiePizzaBuilder
     auto veggieBuilder = std::make_shared<VeggiePizzaBuilder>();
     PizzaDirector director(veggieBuilder);
 
     auto veggiePizza = director.construct();
     veggiePizza->describe();
 
     // Use CheesePizzaBuilder
     auto cheeseBuilder = std::make_shared<CheesePizzaBuilder>();
     PizzaDirector director2(cheeseBuilder);
 
     auto cheesePizza = director2.construct();
     cheesePizza->describe();
 
     return 0;
 }
 