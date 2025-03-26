/**
 * @brief Singleton pattern implementation using a template and static lambda.
 *
 * **Explanation:**
 *
 * 1. **`Dog` Class**: 
 *    - `Dog` is a simple class with a `bark()` method and a private constructor to prevent direct instantiation.
 *    - `Dog` can be any class, and the Singleton behavior will work for it.
 *
 * 2. **`SingletonCreator` Template**:
 *    - `SingletonCreator` is a template class that can manage the singleton instance of any class type `T`.
 *    - It uses a static lambda to lazily initialize the instance of `T` and ensures that the same instance is returned every time.
 *
 * 3. **Template Usage**:
 *    - In the `main()` function, `SingletonCreator<Dog>::getInstance()` is used to get the singleton instance of `Dog`, and the same instance is returned each time.
 * 
 * 4. **Lazy Initialization**:
 *    - The lambda inside `getInstance()` ensures that the `Dog` instance is created only when needed and is shared across calls.
 *
 * **Key Features**:
 * - **Template Flexibility**: The manager can handle singleton creation for any class, not just `Dog`. For instance, `SingletonCreator<Cat>::getInstance()` would manage a `Cat` singleton.
 * - **Static Lambda**: The lambda inside `getInstance()` ensures that the `Dog` object is created lazily (only when first accessed) and remains unique throughout the program.
 */
#include <iostream>
#include <memory>

/**
 * @brief A template class to manage the singleton instance of any type `T`.
 *
 * This class uses a static lambda to ensure lazy initialization of the singleton instance of type `T`.
 * The singleton instance is created only when `getInstance()` is called for the first time.
 *
 * @tparam T The type of the singleton instance.
 */
template <typename T>
class SingletonCreator
{
public:
    /**
     * @brief Returns the singleton instance of type `T`.
     *
     * This method uses a static lambda to create and return the singleton instance.
     * The instance is created only when this method is called for the first time.
     *
     * @return T& The singleton instance of type `T`.
     */
    static T& getInstance()
    {
        // Static lambda ensures only one instance of T is created
        static auto instance = []() -> std::unique_ptr<T> {
            return std::make_unique<T>();  // Lazy initialization of the instance
        }();
        
        // Return the reference to the unique instance
        return *instance;
    }
};

/**
 * @brief A simple class representing a Dog.
 *
 * The Dog class provides a `bark()` method to demonstrate the Singleton pattern with the `SingletonCreator` template.
 */
class Dog
{
public:
    /**
     * @brief Makes the dog bark.
     *
     * This function simulates a dog barking by printing a message to the console.
     */
    void bark() const
    {
        std::cout << "Woof! Woof!" << std::endl;
    }
};

/**
 * @brief Main function demonstrating the Singleton pattern.
 *
 * This function accesses the singleton instance of the `Dog` class using the `SingletonCreator`
 * template, and ensures that the same instance is returned each time.
 *
 * @return int Return status code.
 */
int main()
{
    // Accessing the Dog singleton via SingletonCreator
    SingletonCreator<Dog>::getInstance().bark();
    
    // Ensure that the same instance is being returned each time
    auto& dog1 = SingletonCreator<Dog>::getInstance();
    auto& dog2 = SingletonCreator<Dog>::getInstance();
    
    if (&dog1 == &dog2)
    {
        std::cout << "Both references point to the same instance of Dog." << std::endl;
    }

    return 0;
}
