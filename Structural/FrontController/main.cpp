/**
 * @brief Front Controller Pattern in C++23 using shared_ptr.
 *
 * **Key Concepts:**
 * 1. **Front Controller**: A single handler (`FrontController`) that manages and delegates requests to appropriate handlers.
 * 2. **Handlers (`RequestHandler` and concrete implementations)**: Handle different types of requests.
 * 3. **Centralized Control**: The `FrontController` serves as a centralized access point for request processing.
 *
 * **How it Works:**
 * - Clients send requests to the `FrontController`, which decides which `RequestHandler` should handle them.
 * - The actual request processing is delegated to specific handlers implementing `RequestHandler`.
 *
 * **Benefits:**
 * - **Centralized Request Handling**: One entry point for request management.
 * - **Decoupling**: Clients do not interact with specific request handlers directly.
 * - **Scalability**: New handlers can be added without modifying existing client code.
 */

 #include <iostream>
 #include <memory>
 #include <unordered_map>
 #include <string>
 
 /**
  * @brief Abstract base class for handling requests.
  * 
  * Defines a common interface for all request handlers.
  */
 class RequestHandler
 {
 public:
     virtual ~RequestHandler() = default;
 
     /**
      * @brief Handles a request.
      * @param request The request string to process.
      */
     virtual void handleRequest(const std::string &request) const = 0;
 };
 
 /**
  * @brief Concrete handler for login requests.
  */
 class LoginHandler : public RequestHandler
 {
 public:
     /**
      * @brief Handles a login request.
      * @param request The request string.
      */
     void handleRequest(const std::string &request) const override
     {
         std::cout << "Handling login request: " << request << std::endl;
     }
 };
 
 /**
  * @brief Concrete handler for data retrieval requests.
  */
 class DataHandler : public RequestHandler
 {
 public:
     /**
      * @brief Handles a data request.
      * @param request The request string.
      */
     void handleRequest(const std::string &request) const override
     {
         std::cout << "Handling data retrieval request: " << request << std::endl;
     }
 };
 
 /**
  * @brief Front Controller that manages request handling.
  * 
  * Acts as a central entry point for processing requests and delegates them to appropriate handlers.
  */
 class FrontController
 {
 public:
     /**
      * @brief Constructor that initializes request handlers.
      */
     FrontController()
     {
         m_handlers["login"] = std::make_shared<LoginHandler>();
         m_handlers["data"] = std::make_shared<DataHandler>();
     }
 
     /**
      * @brief Processes a request by delegating to the appropriate handler.
      * @param requestType The type of request (e.g., "login", "data").
      * @param request The actual request data.
      */
     void processRequest(const std::string &requestType, const std::string &request) const
     {
         auto it = m_handlers.find(requestType);
         if (it != m_handlers.end())
         {
             it->second->handleRequest(request);
         }
         else
         {
             std::cout << "Unknown request type: " << requestType << std::endl;
         }
     }
 
 private:
     std::unordered_map<std::string, std::shared_ptr<RequestHandler>> m_handlers; ///< Stores request handlers.
 };
 
 /**
  * @brief Main function demonstrating the Front Controller pattern.
  */
 int main()
 {
     std::shared_ptr<FrontController> controller = std::make_shared<FrontController>();
 
     // Client sends requests through the FrontController
     controller->processRequest("login", "User: Alice");
     controller->processRequest("data", "Fetch user records");
     controller->processRequest("unknown", "Some request");  // No handler for this type
 
     return 0;
 }
 