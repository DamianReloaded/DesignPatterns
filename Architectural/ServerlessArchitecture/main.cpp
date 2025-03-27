/**
 * @brief
 * The Serverless Architecture design pattern abstracts away the management of servers and focuses purely on the application logic.
 * 
 * Key Concepts:
 * - Serverless Computing: The developer writes business logic while the cloud provider manages the infrastructure.
 * - Event-Driven: Functions are triggered by events (e.g., HTTP requests, database changes).
 * - Focus on Application Logic: Developers are relieved from managing servers and only focus on writing code.
 * 
 * Benefits:
 * - Reduced operational overhead: No need to provision, manage, or scale servers.
 * - Cost-effective: Pay only for the execution time of the function, instead of maintaining idle server resources.
 * - Auto-scaling: The cloud provider handles scaling automatically based on demand.
 * - Simplifies Deployment: The developer focuses on deploying functions without worrying about infrastructure.
 */

 #include <iostream>
 #include <functional>
 #include <memory>
 #include <string>
 #include <unordered_map>
 #include <cassert>
 
 /**
  * @brief A base class representing a serverless function in the system.
  * 
  * This abstract class defines the interface for any serverless function. The concrete function implementations will define
  * the application logic in the `execute` method.
  */
 class ServerlessFunction
 {
 public:
     virtual ~ServerlessFunction() = default;
 
     /**
      * @brief Executes the function logic. Derived classes should implement the specific logic.
      */
     virtual void execute() = 0;
 };
 
 /**
  * @brief A concrete implementation of a serverless function for a "UserService" that handles user requests.
  */
 class UserServiceFunction : public ServerlessFunction
 {
 public:
     /**
      * @brief Executes the logic for handling a user request.
      */
     void execute() override
     {
         std::cout << "Executing UserService logic: Handling user-related requests!" << std::endl;
     }
 };
 
 /**
  * @brief A concrete implementation of a serverless function for an "OrderService" that handles order requests.
  */
 class OrderServiceFunction : public ServerlessFunction
 {
 public:
     /**
      * @brief Executes the logic for handling an order request.
      */
     void execute() override
     {
         std::cout << "Executing OrderService logic: Handling order-related requests!" << std::endl;
     }
 };
 
 /**
  * @brief A manager that triggers serverless functions based on events.
  * 
  * This class acts as a serverless function orchestrator. It maps event names to specific serverless functions and 
  * executes the function when an event occurs.
  */
 class ServerlessOrchestrator
 {
 public:
     /**
      * @brief Registers a serverless function for a given event name.
      * 
      * @param eventName The name of the event.
      * @param function The serverless function to execute for the event.
      */
     void registerFunction(const std::string &eventName, std::shared_ptr<ServerlessFunction> function)
     {
         m_functions[eventName] = function;
     }
 
     /**
      * @brief Triggers the execution of the registered function for a given event.
      * 
      * @param eventName The name of the event that should trigger the function.
      */
     void triggerEvent(const std::string &eventName)
     {
         auto it = m_functions.find(eventName);
         if (it != m_functions.end())
         {
             std::cout << "Triggering event: " << eventName << std::endl;
             it->second->execute();
         }
         else
         {
             std::cout << "No function registered for event: " << eventName << std::endl;
         }
     }
 
 private:
     std::unordered_map<std::string, std::shared_ptr<ServerlessFunction>> m_functions;
 };
 
 /**
  * @brief The entry point for the application, demonstrating the use of serverless functions in the system.
  */
 int main()
 {
     // Create a serverless orchestrator instance
     ServerlessOrchestrator orchestrator;
 
     // Register serverless functions
     orchestrator.registerFunction("userEvent", std::make_shared<UserServiceFunction>());
     orchestrator.registerFunction("orderEvent", std::make_shared<OrderServiceFunction>());
 
     // Simulate triggering events
     orchestrator.triggerEvent("userEvent"); // Should call UserServiceFunction
     orchestrator.triggerEvent("orderEvent"); // Should call OrderServiceFunction
     orchestrator.triggerEvent("paymentEvent"); // No function registered for paymentEvent
 
     return 0;
 }
 