/**
 * @brief API Gateway Pattern Example: Acts as a single entry point for multiple microservices,
 *        simplifying client communication in a microservices architecture.
 *
 * **Key Concepts:**
 * 1. **API Gateway**: Acts as a reverse proxy that routes requests to various microservices based on the API endpoint.
 * 2. **Microservices**: A set of small, independently deployable services that each handle a specific part of the application.
 * 3. **Centralized Routing**: The API Gateway is the central point through which all requests pass.
 *
 * **Benefits:**
 * - Simplifies client-side interaction by providing a unified entry point.
 * - Reduces the complexity of handling multiple microservices.
 * - Centralizes authentication, rate-limiting, logging, etc.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <unordered_map>
 #include <functional>
 
 /**
  * @brief Base class for all services. Defines the common interface for all microservices.
  */
 class Service
 {
 public:
     virtual ~Service() = default;
 
     /**
      * @brief Handles the service request.
      * @param id The unique identifier for the resource.
      * @return The result from the service.
      */
     virtual std::string handleRequest(int id) = 0;
 };
 
 /**
  * @brief User service that handles user-related requests.
  */
 class UserService : public Service
 {
 public:
     /**
      * @brief Fetch user details.
      * @param userId The unique identifier for the user.
      * @return The user details.
      */
     std::string handleRequest(int userId) override
     {
         return "User details for user " + std::to_string(userId);
     }
 };
 
 /**
  * @brief Product service that handles product-related requests.
  */
 class ProductService : public Service
 {
 public:
     /**
      * @brief Fetch product details.
      * @param productId The unique identifier for the product.
      * @return The product details.
      */
     std::string handleRequest(int productId) override
     {
         return "Product details for product " + std::to_string(productId);
     }
 };
 
 /**
  * @brief The API Gateway class that routes requests to the appropriate microservices.
  */
 class ApiGateway
 {
 public:
     ApiGateway()
     {
         // Register services
         m_services["user"] = std::make_shared<UserService>();
         m_services["product"] = std::make_shared<ProductService>();
     }
 
     /**
      * @brief Handles the incoming API requests and routes them to the appropriate microservice.
      * @param service The service to call ("user" or "product").
      * @param id The ID parameter to pass to the service.
      * @return The result from the service.
      */
     std::string handleRequest(const std::string& service, int id)
     {
         if (m_services.find(service) != m_services.end())
         {
             return m_services[service]->handleRequest(id);
         }
         return "Service not found";
     }
 
 private:
     std::unordered_map<std::string, std::shared_ptr<Service>> m_services; ///< Map of service names to service instances.
 };
 
 /**
  * @brief Demonstrates the API Gateway pattern by routing requests to various microservices.
  */
 int main()
 {
     auto apiGateway = std::make_shared<ApiGateway>();
 
     // Simulate requests
     std::cout << "API Gateway: " << apiGateway->handleRequest("user", 101) << std::endl;
     std::cout << "API Gateway: " << apiGateway->handleRequest("product", 202) << std::endl;
     std::cout << "API Gateway: " << apiGateway->handleRequest("order", 303) << std::endl; // Invalid service
 
     return 0;
 }
 