#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Service Interface for the Dependency Injection pattern.
 * 
 * The `Service` interface defines the contract for services that can be injected.
 */
class Service
{
public:
    virtual ~Service() = default;

    /**
     * @brief Perform some action defined by the service.
     *
     * This function should be implemented by concrete services to perform an operation.
     */
    virtual void performAction() const = 0;
};

/**
 * @brief Concrete implementation of the Service interface.
 * 
 * `ConcreteService` is a specific implementation of the `Service` interface. It provides
 * the actual behavior for `performAction()`.
 */
class ConcreteService : public Service
{
public:
    /**
     * @brief Perform a specific action.
     *
     * This implementation prints a message when the action is performed.
     */
    void performAction() const override
    {
        std::cout << "ConcreteService is performing an action." << std::endl;
    }
};

/**
 * @brief Another concrete implementation of the Service interface.
 * 
 * `AnotherService` is another service that provides its own implementation of `performAction()`.
 */
class AnotherService : public Service
{
public:
    /**
     * @brief Perform a different action.
     *
     * This implementation prints a different message when the action is performed.
     */
    void performAction() const override
    {
        std::cout << "AnotherService is performing a different action." << std::endl;
    }
};

/**
 * @brief Client class that uses dependency injection to receive its dependencies.
 * 
 * The `Client` class depends on the `Service` interface. The service is injected via the
 * constructor, allowing the client to interact with any concrete implementation of `Service`.
 */
class Client
{
public:
    /**
     * @brief Constructor that accepts a shared pointer to a Service.
     * 
     * @param service A shared pointer to an object that implements the `Service` interface.
     */
    Client(std::shared_ptr<Service> service) : m_service(service) {}

    /**
     * @brief Perform the action using the injected service.
     *
     * This method calls the `performAction()` method of the injected service.
     */
    void executeAction() const
    {
        m_service->performAction();
    }

private:
    std::shared_ptr<Service> m_service;  ///< The service dependency that is injected into the client.
};

/**
 * @brief Main function demonstrating Dependency Injection.
 * 
 * In this example, we create different services and inject them into the `Client` class.
 * This allows the client to work with different behaviors without being tightly coupled
 * to any specific service implementation.
 */
int main()
{
    // Inject ConcreteService into Client
    std::shared_ptr<Service> service1 = std::make_shared<ConcreteService>();
    Client client1(service1);
    client1.executeAction();  // Output: ConcreteService is performing an action.

    // Inject AnotherService into Client
    std::shared_ptr<Service> service2 = std::make_shared<AnotherService>();
    Client client2(service2);
    client2.executeAction();  // Output: AnotherService is performing a different action.

    return 0;
}
