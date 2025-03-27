/**
 * @brief Microservices Architecture Example: Simulating Microservices Communication and Coordination
 *
 * **Key Concepts:**
 * 1. **Microservices**: A design pattern where a system is composed of independent, loosely coupled services, each responsible for a specific functionality.
 * 2. **Communication**: Services communicate with each other using APIs or message brokers, typically through HTTP, REST, or messaging queues.
 * 3. **Decentralization**: Each microservice manages its own data, allowing the system to scale independently and avoid tight coupling.
 *
 * **Benefits:**
 * - **Scalability**: Each service can be scaled independently to meet the demands of its specific functionality.
 * - **Fault Isolation**: A failure in one microservice doesn't affect the entire system.
 * - **Flexibility**: Services can be developed and deployed independently, using the most appropriate technologies for each service.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <unordered_map>
 #include <thread>
 #include <chrono>
 #include <mutex>
 #include <future>
 
 /**
  * @brief Simulates a simple Microservice that performs user registration.
  */
 class UserService
 {
 public:
     /**
      * @brief Registers a new user by adding to the "database".
      * @param userId The unique identifier of the user.
      * @param userName The name of the user.
      */
     void registerUser(int userId, const std::string& userName)
     {
         std::lock_guard<std::mutex> lock(m_mutex);
         m_users[userId] = userName;
         std::cout << "User Registered: " << userName << " with ID: " << userId << std::endl;
     }
 
     /**
      * @brief Gets the user information by ID.
      * @param userId The unique identifier of the user.
      * @return The name of the user.
      */
     std::string getUser(int userId)
     {
         std::lock_guard<std::mutex> lock(m_mutex);
         if (m_users.find(userId) != m_users.end())
         {
             return m_users[userId];
         }
         else
         {
             return "User not found!";
         }
     }
 
 private:
     std::unordered_map<int, std::string> m_users; ///< Simulated "database" of users.
     std::mutex m_mutex; ///< Protects access to the user data.
 };
 
 /**
  * @brief Simulates a simple Microservice that performs email notifications.
  */
 class EmailService
 {
 public:
     /**
      * @brief Sends a welcome email to the user after registration.
      * @param userId The unique identifier of the user.
      * @param userName The name of the user.
      */
     void sendWelcomeEmail(int userId, const std::string& userName)
     {
         std::cout << "Sending welcome email to: " << userName << " (ID: " << userId << ")\n";
         // Simulate email sending process
         std::this_thread::sleep_for(std::chrono::seconds(1));
         std::cout << "Email sent to: " << userName << " (ID: " << userId << ")\n";
     }
 };
 
 /**
  * @brief Orchestrates the interaction between the UserService and the EmailService in a microservices architecture.
  */
 class UserRegistrationFacade
 {
 public:
     UserRegistrationFacade(std::shared_ptr<UserService> userService, std::shared_ptr<EmailService> emailService)
         : m_userService(userService), m_emailService(emailService)
     {
     }
 
     /**
      * @brief Registers a user and sends a welcome email asynchronously.
      * @param userId The unique identifier of the user.
      * @param userName The name of the user.
      * @return A future representing the asynchronous email sending task.
      */
     std::future<void> registerUser(int userId, const std::string& userName)
     {
         return std::async(std::launch::async, [this, userId, userName] {
             // First, register the user
             m_userService->registerUser(userId, userName);
 
             // Then, send the welcome email asynchronously
             m_emailService->sendWelcomeEmail(userId, userName);
         });
     }
 
 private:
     std::shared_ptr<UserService> m_userService; ///< The UserService microservice.
     std::shared_ptr<EmailService> m_emailService; ///< The EmailService microservice.
 };
 
 /**
  * @brief Demonstrates a simple microservices architecture using UserService and EmailService.
  */
 int main()
 {
     // Instantiate services and facade
     auto userService = std::make_shared<UserService>();
     auto emailService = std::make_shared<EmailService>();
     UserRegistrationFacade registrationFacade(userService, emailService);
 
     // Register a user asynchronously
     auto registrationFuture = registrationFacade.registerUser(1, "Alice");
 
     // Wait for the email to be sent before exiting
     registrationFuture.get();
 
     // Perform another registration
     registrationFacade.registerUser(2, "Bob").get();
 
     return 0;
 }
 