/**
 * @brief Lazy initialization example
 * 
 * This example demonstrates lazy initialization, where an object is only created when it is actually needed.
 * The `ExpensiveResource` class simulates an expensive operation (e.g., loading a file, making a network request),
 * and the resource is only created when accessed for the first time. This avoids unnecessary resource creation
 * until it is absolutely required.
 * 
 * Key Concepts:
 * 1. **Lazy Initialization**: The object `ExpensiveResource` is created only when it is first accessed.
 * 2. **Delayed Creation**: The first access to the `ExpensiveResource` introduces a simulated delay (e.g., file loading or network call).
 * 3. **Efficient Resource Usage**: The object is not created at program startup, thus saving resources if not used.
 */
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

/**
 * @brief A class that simulates an expensive resource.
 *
 * The `ExpensiveResource` class simulates an expensive operation, such as loading a large file or making a network call.
 * The object is only created once it is accessed for the first time.
 */
class ExpensiveResource
{
public:
    /**
     * @brief Constructor simulating an expensive operation
     *
     * The constructor introduces a delay to simulate an expensive initialization task
     * (e.g., loading a large file, database query).
     */
    ExpensiveResource() 
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));  // Simulating an expensive operation
        std::cout << "ExpensiveResource initialized!" << std::endl;
    }

    /**
     * @brief Simulates some operation with the resource
     *
     * This method simulates using the initialized `ExpensiveResource` after it has been created.
     */
    void doSomething() const
    {
        std::cout << "Performing some operation with ExpensiveResource..." << std::endl;
    }
};

/**
 * @brief Manages the lazy initialization of the `ExpensiveResource`.
 *
 * The `ResourceManager` class ensures that the `ExpensiveResource` is initialized only when it is first needed.
 * It manages access to the resource and prevents redundant initialization.
 */
class ResourceManager
{
public:
    /**
     * @brief Accesses the `ExpensiveResource` object, initializing it lazily.
     *
     * The `getResource` method lazily initializes the `ExpensiveResource` only when it's first accessed.
     * The resource is then available for future use without delay.
     * 
     * @return Reference to the `ExpensiveResource` object.
     */
    ExpensiveResource& getResource()
    {
        if (!resource_)
        {
            resource_ = std::make_unique<ExpensiveResource>();  // Lazy initialization
        }
        return *resource_;
    }

private:
    std::unique_ptr<ExpensiveResource> resource_;  ///< Holds the lazy-initialized resource
};

/**
 * @brief Main function demonstrating lazy initialization.
 *
 * The `main` function demonstrates the lazy initialization of the `ExpensiveResource` class via the `ResourceManager` class.
 * The first access to the resource introduces a simulated delay, but subsequent accesses are instant.
 * 
 * @return int Return status code.
 */
int main()
{
    std::cout << "Program started." << std::endl;

    ResourceManager manager;
    
    // Lazy initialization of ExpensiveResource happens here
    std::cout << "Accessing resource for the first time..." << std::endl;
    manager.getResource().doSomething();  // Simulates the delay during the first access

    // No delay in subsequent accesses
    std::cout << "Accessing resource again..." << std::endl;
    manager.getResource().doSomething();  // No delay now

    return 0;
}
