/**
 * @brief Proxy pattern example for controlling access to a resource.
 *
 * **Key Concepts:**
 * 1. **Subject (`RealSubject`)**: Represents the actual object that needs controlled access.
 * 2. **Proxy (`Proxy`)**: Acts as a placeholder for the `RealSubject`, controlling access to it, possibly adding extra behavior like lazy initialization or access control.
 *
 * **How it works:**
 * 1. The `RealSubject` class represents the actual object that performs the core functionality.
 * 2. The `Proxy` class controls access to the `RealSubject`, either delaying its creation (lazy initialization) or providing additional functionality like access control.
 * 3. In this example, the `Proxy` class checks if the `RealSubject` is created and, if not, creates it when needed.
 */

 #include <iostream>
 #include <memory>
 
 /**
  * @brief Abstract Subject class defining common interface.
  *
  * This class defines the common interface for both the `RealSubject` and `Proxy`. 
  * This ensures that the Proxy can be used as a replacement for the RealSubject.
  */
 class Subject
 {
 public:
     virtual ~Subject() = default;
 
     /**
      * @brief Perform an action.
      *
      * This method should be implemented by both the `RealSubject` and `Proxy`.
      */
     virtual void request() const = 0;
 };
 
 /**
  * @brief RealSubject class representing the actual object.
  *
  * The `RealSubject` class is the object that performs the core functionality. 
  * It is accessed directly by the client when needed.
  */
 class RealSubject : public Subject
 {
 public:
     /**
      * @brief Perform the core action.
      *
      * This method simulates the core action the real object is responsible for.
      */
     void request() const override
     {
         std::cout << "RealSubject: Handling request." << std::endl;
     }
 };
 
 /**
  * @brief Proxy class controlling access to the RealSubject.
  *
  * The `Proxy` class is a placeholder for the `RealSubject`. It controls access to the real object, 
  * and in this example, it also adds lazy initialization to delay the creation of the `RealSubject`.
  */
 class Proxy : public Subject
 {
 public:
     Proxy() = default;
 
     /**
      * @brief Perform the action, potentially creating the RealSubject.
      *
      * This method checks if the `RealSubject` is created. If not, it initializes it and then performs the request.
      */
     void request() const override
     {
         if (!m_realSubject)
         {
             m_realSubject = std::make_shared<RealSubject>();
         }
         m_realSubject->request();
     }
 
 private:
     mutable std::shared_ptr<RealSubject> m_realSubject; ///< Shared pointer to the RealSubject instance.
 };
 
 /**
  * @brief Main function demonstrating the Proxy pattern.
  *
  * This function demonstrates how the `Proxy` pattern works by using the `Proxy` class to access 
  * the `RealSubject` through the proxy, controlling access and potentially delaying its creation.
  */
 int main()
 {
     // Create a proxy object
     std::shared_ptr<Subject> proxy = std::make_shared<Proxy>();
 
     // The proxy controls access to the RealSubject
     proxy->request();  // This will create the RealSubject lazily and perform the action.
 
     return 0;
 }
 