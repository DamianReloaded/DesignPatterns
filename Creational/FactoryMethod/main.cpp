/**
 * @brief Factory Method pattern example.
 *
 * **Key Concepts:**
 * 1. **Product**: Represents an object created by the factory method.
 * 2. **Creator**: Contains the factory method that creates the product, but does not specify which product is created.
 * 3. **Concrete Creator**: Implements the factory method to create specific types of products.
 *
 * **How it works:**
 * 1. The `Product` class defines the interface that the created objects will follow.
 * 2. The `Creator` class declares a `createProduct` method, which will be overridden by the concrete creators.
 * 3. `ConcreteCreator` classes will implement the `createProduct` method to create specific products.
 *
 * This example uses the Factory Method pattern to create different types of `Animal` objects.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 /**
  * @brief Abstract base class representing an animal.
  * 
  * The `Animal` class defines the interface that all concrete animal classes must implement.
  * Each animal class will have a `speak` method that defines the sound the animal makes.
  */
 class Animal
 {
 public:
     /**
      * @brief Speak the sound of the animal.
      * 
      * This method will be overridden by each concrete animal class to simulate the sound the animal makes.
      */
     virtual void speak() const = 0;
 
     virtual ~Animal() = default; ///< Virtual destructor for proper cleanup of derived objects
 };
 
 /**
  * @brief Concrete class representing a Dog.
  * 
  * The `Dog` class implements the `speak` method to simulate the sound of a dog barking.
  */
 class Dog : public Animal
 {
 public:
     /**
      * @brief Simulate the sound of a dog barking.
      * 
      * This method overrides the `speak` method to simulate the barking of a dog.
      */
     void speak() const override
     {
         std::cout << "Woof! Woof!\n";
     }
 };
 
 /**
  * @brief Concrete class representing a Cat.
  * 
  * The `Cat` class implements the `speak` method to simulate the sound of a cat meowing.
  */
 class Cat : public Animal
 {
 public:
     /**
      * @brief Simulate the sound of a cat meowing.
      * 
      * This method overrides the `speak` method to simulate the meowing of a cat.
      */
     void speak() const override
     {
         std::cout << "Meow! Meow!\n";
     }
 };
 
 /**
  * @brief Abstract base class for animal factories.
  * 
  * The `AnimalFactory` class declares the `createAnimal` method, which must be implemented
  * by all concrete factories to create specific types of animals.
  */
 class AnimalFactory
 {
 public:
     /**
      * @brief Create an animal.
      * 
      * This method must be overridden by concrete factories to create a specific type of animal.
      * 
      * @return A unique pointer to a new `Animal` object.
      */
     virtual std::unique_ptr<Animal> createAnimal() const = 0;
 
     virtual ~AnimalFactory() = default; ///< Virtual destructor for proper cleanup of derived factories
 };
 
 /**
  * @brief Concrete factory for creating Dog objects.
  * 
  * The `DogFactory` class implements the `createAnimal` method to create `Dog` objects.
  */
 class DogFactory : public AnimalFactory
 {
 public:
     /**
      * @brief Create a Dog object.
      * 
      * This method overrides the `createAnimal` method to create and return a new `Dog` object.
      * 
      * @return A unique pointer to a new `Dog` object.
      */
     std::unique_ptr<Animal> createAnimal() const override
     {
         return std::make_unique<Dog>();
     }
 };
 
 /**
  * @brief Concrete factory for creating Cat objects.
  * 
  * The `CatFactory` class implements the `createAnimal` method to create `Cat` objects.
  */
 class CatFactory : public AnimalFactory
 {
 public:
     /**
      * @brief Create a Cat object.
      * 
      * This method overrides the `createAnimal` method to create and return a new `Cat` object.
      * 
      * @return A unique pointer to a new `Cat` object.
      */
     std::unique_ptr<Animal> createAnimal() const override
     {
         return std::make_unique<Cat>();
     }
 };
 
 /**
  * @brief Client code to demonstrate the Factory Method pattern.
  * 
  * The `main` function demonstrates how to use different concrete factories to create
  * specific animal objects (e.g., `Dog` and `Cat`) without directly instantiating them.
  */
 int main()
 {
     std::unique_ptr<AnimalFactory> factory;
 
     // Creating a Dog
     factory = std::make_unique<DogFactory>();
     auto dog = factory->createAnimal();
     dog->speak();  ///< Dog speaks
 
     // Creating a Cat
     factory = std::make_unique<CatFactory>();
     auto cat = factory->createAnimal();
     cat->speak();  ///< Cat speaks
 
     return 0;
 }
 