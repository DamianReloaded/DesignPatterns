/**
 * @brief Servant Pattern example in C++23.
 *
 * **Key Concepts:**
 * 1. **Servant Interface (`Servant`)**: Defines the interface that provides the core functionality.
 * 2. **Concrete Servants (`RealServant`)**: Implements the actual functionality of the servant.
 * 3. **Invoker (`Client`)**: Calls the service provided by the servant.
 * 4. **Proxy (`ProxyServant`)**: Controls access to the real servant, adding additional functionality if needed.
 *
 * **Benefits:**
 * - Encapsulates complex logic within a servant, while providing a simple interface.
 * - Enables separation of concerns by allowing different servicer implementations.
 * - Can be extended to include proxy behavior or add additional functionality without altering the client code.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 /**
  * @brief Abstract servant interface that defines a method to serve a request.
  */
 class Servant
 {
 public:
     virtual ~Servant() = default;
 
     /**
      * @brief Serves the request.
      * 
      * This is the core method of the servant interface.
      */
     virtual void serve() const = 0;
 };
 
 /**
  * @brief Concrete implementation of the Servant interface.
  */
 class RealServant : public Servant
 {
 public:
     /**
      * @brief Performs the actual work to serve the request.
      */
     void serve() const override
     {
         std::cout << "RealServant is serving the request." << std::endl;
     }
 };
 
 /**
  * @brief Proxy implementation of the Servant interface that controls access to the real servant.
  */
 class ProxyServant : public Servant
 {
 public:
     ProxyServant(std::shared_ptr<Servant> realServant)
         : m_realServant(realServant) {}
 
     /**
      * @brief Performs a check or additional logic before delegating the work to the real servant.
      */
     void serve() const override
     {
         std::cout << "ProxyServant: Performing checks before serving the request." << std::endl;
         m_realServant->serve();
         std::cout << "ProxyServant: Post-processing after the request." << std::endl;
     }
 
 private:
     std::shared_ptr<Servant> m_realServant; ///< The real servant that actually performs the work.
 };
 
 /**
  * @brief Client code that interacts with the servant (through proxy or real servant).
  */
 class Client
 {
 public:
     /**
      * @brief Sets the servant that will handle the request.
      * @param servant The servant to set.
      */
     void setServant(std::shared_ptr<Servant> servant)
     {
         m_servant = servant;
     }
 
     /**
      * @brief Calls the serve method of the servant.
      */
     void makeRequest() const
     {
         m_servant->serve();
     }
 
 private:
     std::shared_ptr<Servant> m_servant; ///< The servant that will handle the request.
 };
 
 /**
  * @brief Main function demonstrating the use of the Servant Pattern.
  */
 int main()
 {
     auto realServant = std::make_shared<RealServant>();
     auto proxyServant = std::make_shared<ProxyServant>(realServant);
 
     Client client;
 
     // Using the real servant directly
     client.setServant(realServant);
     std::cout << "Client making request using RealServant:\n";
     client.makeRequest();
 
     // Using the proxy servant
     client.setServant(proxyServant);
     std::cout << "Client making request using ProxyServant:\n";
     client.makeRequest();
 
     return 0;
 }
 