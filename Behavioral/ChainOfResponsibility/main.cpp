/**
 * @brief Chain of Responsibility Pattern in C++23 using shared_ptr.
 *
 * **Key Concepts:**
 * 1. **Handler (Abstract Base Class)**: Defines the interface for handling requests and passing them to the next handler.
 * 2. **Concrete Handlers**: Implement specific request handling behavior and decide whether to process or pass the request.
 * 3. **Chaining Mechanism**: Each handler holds a reference to the next handler in the chain.
 *
 * **How it Works:**
 * - A request starts at the first handler.
 * - Each handler either processes the request or passes it to the next handler.
 * - The request propagates until a handler processes it or the chain ends.
 *
 * **Benefits:**
 * - **Decouples Senders and Receivers**: Request senders don't need to know which handler will process the request.
 * - **Flexible Request Handling**: Easily add or remove handlers without modifying existing code.
 * - **Reduces Conditional Complexity**: Eliminates long `if-else` chains.
 */

 #include <iostream>
 #include <memory>
 
 /**
  * @brief Abstract base class representing a request handler.
  */
 class Handler
 {
 public:
     virtual ~Handler() = default;
 
     /**
      * @brief Sets the next handler in the chain.
      * @param nextHandler Shared pointer to the next handler.
      */
     void setNext(std::shared_ptr<Handler> nextHandler)
     {
         m_nextHandler = nextHandler;
     }
 
     /**
      * @brief Handles a request, processing it or passing it to the next handler.
      * @param request The request integer value.
      */
     virtual void handleRequest(int request)
     {
         if (m_nextHandler)
         {
             m_nextHandler->handleRequest(request);
         }
         else
         {
             std::cout << "No handler available for request: " << request << std::endl;
         }
     }
 
 protected:
     std::shared_ptr<Handler> m_nextHandler; ///< Pointer to the next handler in the chain.
 };
 
 /**
  * @brief Concrete handler for low-priority requests.
  */
 class LowPriorityHandler : public Handler
 {
 public:
     /**
      * @brief Processes low-priority requests or passes them further.
      * @param request The request integer value.
      */
     void handleRequest(int request) override
     {
         if (request < 10)
         {
             std::cout << "LowPriorityHandler processing request: " << request << std::endl;
         }
         else if (m_nextHandler)
         {
             m_nextHandler->handleRequest(request);
         }
     }
 };
 
 /**
  * @brief Concrete handler for medium-priority requests.
  */
 class MediumPriorityHandler : public Handler
 {
 public:
     /**
      * @brief Processes medium-priority requests or passes them further.
      * @param request The request integer value.
      */
     void handleRequest(int request) override
     {
         if (request >= 10 && request < 20)
         {
             std::cout << "MediumPriorityHandler processing request: " << request << std::endl;
         }
         else if (m_nextHandler)
         {
             m_nextHandler->handleRequest(request);
         }
     }
 };
 
 /**
  * @brief Concrete handler for high-priority requests.
  */
 class HighPriorityHandler : public Handler
 {
 public:
     /**
      * @brief Processes high-priority requests.
      * @param request The request integer value.
      */
     void handleRequest(int request) override
     {
         if (request >= 20)
         {
             std::cout << "HighPriorityHandler processing request: " << request << std::endl;
         }
         else if (m_nextHandler)
         {
             m_nextHandler->handleRequest(request);
         }
     }
 };
 
 /**
  * @brief Main function demonstrating the Chain of Responsibility pattern.
  */
 int main()
 {
     // Create handlers
     std::shared_ptr<Handler> lowPriority = std::make_shared<LowPriorityHandler>();
     std::shared_ptr<Handler> mediumPriority = std::make_shared<MediumPriorityHandler>();
     std::shared_ptr<Handler> highPriority = std::make_shared<HighPriorityHandler>();
 
     // Set up the chain
     lowPriority->setNext(mediumPriority);
     mediumPriority->setNext(highPriority);
 
     // Process different requests
     lowPriority->handleRequest(5);  // Handled by LowPriorityHandler
     lowPriority->handleRequest(15); // Handled by MediumPriorityHandler
     lowPriority->handleRequest(25); // Handled by HighPriorityHandler
     lowPriority->handleRequest(30); // Handled by HighPriorityHandler
 
     return 0;
 }
 