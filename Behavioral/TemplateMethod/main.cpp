/**
 * @brief Template Method Design Pattern Example.
 *
 * **Key Concepts:**
 * 1. **Abstract Class (`Meal`)**: Defines a template method that outlines the steps of an algorithm.
 * 2. **Concrete Classes (`VegetarianMeal`, `NonVegetarianMeal`)**: Implement the steps defined by the abstract class.
 * 3. **Template Method**: Defines the skeleton of the algorithm but allows the subclasses to override specific steps.
 *
 * **Benefits:**
 * - Promotes code reuse by implementing common steps in the base class while allowing customization in subclasses.
 * - Provides a clear structure for algorithms with common steps and customizable parts.
 * - Avoids code duplication by allowing specific steps to be overridden without modifying the algorithm structure.
 */

 #include <iostream>
 #include <memory>
 
 /**
  * @brief Abstract class defining the template method for preparing a meal.
  */
 class Meal
 {
 public:
     // Template method defines the sequence of steps to prepare the meal.
     void prepareMeal()
     {
         cookMainIngredient();
         addCondiments();
         serve();
     }
 
     virtual ~Meal() = default;
 
 private:
     /**
      * @brief Abstract method for cooking the main ingredient, must be implemented by subclasses.
      */
     virtual void cookMainIngredient() = 0;
 
     /**
      * @brief Abstract method for adding condiments, must be implemented by subclasses.
      */
     virtual void addCondiments() = 0;
 
     /**
      * @brief Concrete method for serving the meal. This step is common to all meals.
      */
     void serve()
     {
         std::cout << "Meal is served!" << std::endl;
     }
 };
 
 /**
  * @brief Concrete class implementing the vegetarian meal preparation.
  */
 class VegetarianMeal : public Meal
 {
 private:
     void cookMainIngredient() override
     {
         std::cout << "Cooking vegetarian main ingredient (tofu)." << std::endl;
     }
 
     void addCondiments() override
     {
         std::cout << "Adding vegetarian condiments (soy sauce, spices)." << std::endl;
     }
 };
 
 /**
  * @brief Concrete class implementing the non-vegetarian meal preparation.
  */
 class NonVegetarianMeal : public Meal
 {
 private:
     void cookMainIngredient() override
     {
         std::cout << "Cooking non-vegetarian main ingredient (chicken)." << std::endl;
     }
 
     void addCondiments() override
     {
         std::cout << "Adding non-vegetarian condiments (garlic, pepper)." << std::endl;
     }
 };
 
 /**
  * @brief Demonstrates the Template Method pattern for preparing meals.
  */
 int main()
 {
     // Create a shared pointer to a VegetarianMeal and prepare it.
     std::shared_ptr<Meal> vegetarianMeal = std::make_shared<VegetarianMeal>();
     std::cout << "Preparing Vegetarian Meal:" << std::endl;
     vegetarianMeal->prepareMeal();
     std::cout << std::endl;
 
     // Create a shared pointer to a NonVegetarianMeal and prepare it.
     std::shared_ptr<Meal> nonVegetarianMeal = std::make_shared<NonVegetarianMeal>();
     std::cout << "Preparing Non-Vegetarian Meal:" << std::endl;
     nonVegetarianMeal->prepareMeal();
 
     return 0;
 }
 