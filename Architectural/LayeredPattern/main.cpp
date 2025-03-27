/**
 * @brief Layered Pattern Example: A simple layered architecture for a user management system.
 *
 * **Key Concepts:**
 * 1. **Separation of Concerns**: Separates the system into distinct layers such as presentation, business, and data access layers.
 * 2. **Modular Design**: Each layer has a clear responsibility, making the system easier to maintain and scale.
 * 3. **Testability**: Each layer can be tested independently, and mock objects can be used for testing purposes.
 * 4. **Loose Coupling**: The presentation layer does not depend on the data access layer directly. Instead, it interacts with the business layer.
 *
 * **Benefits:**
 * - Improved maintainability due to clear separation of concerns.
 * - Easier to scale and modify individual layers without affecting others.
 * - Allows for independent testing of each layer.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <vector>
 #include <algorithm>
 
 /**
  * @brief The Data Access Layer: Manages interactions with the database (simulated here with an in-memory collection).
  */
 class UserRepository
 {
 public:
     /**
      * @brief Adds a new user to the repository.
      * @param userName The name of the user to add.
      */
     void addUser(const std::string& userName)
     {
         m_users.push_back(userName);
     }
 
     /**
      * @brief Retrieves all users from the repository.
      * @return A list of all user names.
      */
     std::vector<std::string> getUsers() const
     {
         return m_users;
     }
 
 private:
     std::vector<std::string> m_users; ///< In-memory list of users.
 };
 
 /**
  * @brief The Business Layer: Provides the logic for user-related operations.
  */
 class UserService
 {
 public:
     /**
      * @brief Constructor.
      * @param repository The UserRepository instance.
      */
     UserService(std::shared_ptr<UserRepository> repository)
         : m_repository(repository)
     {}
 
     /**
      * @brief Adds a new user to the system.
      * @param userName The name of the user.
      */
     void addUser(const std::string& userName)
     {
         m_repository->addUser(userName);
     }
 
     /**
      * @brief Retrieves a list of all users.
      * @return A list of user names.
      */
     std::vector<std::string> getUsers() const
     {
         return m_repository->getUsers();
     }
 
 private:
     std::shared_ptr<UserRepository> m_repository; ///< User repository instance.
 };
 
 /**
  * @brief The Presentation Layer: Interacts with the user and displays information.
  */
 class UserController
 {
 public:
     /**
      * @brief Constructor.
      * @param service The UserService instance.
      */
     UserController(std::shared_ptr<UserService> service)
         : m_service(service)
     {}
 
     /**
      * @brief Displays the list of users.
      */
     void showUsers() const
     {
         auto users = m_service->getUsers();
         if (users.empty())
         {
             std::cout << "No users found.\n";
         }
         else
         {
             std::cout << "Users:\n";
             for (const auto& user : users)
             {
                 std::cout << "- " << user << '\n';
             }
         }
     }
 
     /**
      * @brief Adds a user.
      * @param userName The name of the user to add.
      */
     void addUser(const std::string& userName)
     {
         m_service->addUser(userName);
         std::cout << "User \"" << userName << "\" added successfully.\n";
     }
 
 private:
     std::shared_ptr<UserService> m_service; ///< User service instance.
 };
 
 /**
  * @brief Main function demonstrating the use of a layered architecture.
  */
 int main()
 {
     // Data Access Layer: The repository where user data is stored.
     auto userRepository = std::make_shared<UserRepository>();
 
     // Business Layer: The service that handles business logic.
     auto userService = std::make_shared<UserService>(userRepository);
 
     // Presentation Layer: The controller that interacts with the user.
     auto userController = std::make_shared<UserController>(userService);
 
     // Add some users
     userController->addUser("Alice");
     userController->addUser("Bob");
     userController->addUser("Charlie");
 
     // Show all users
     userController->showUsers();
 
     return 0;
 }
 