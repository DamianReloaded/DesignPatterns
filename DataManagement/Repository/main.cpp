/**
 * @brief Repository Pattern Example: Encapsulates data access logic and abstracts it from the rest of the application.
 *
 * **Key Concepts:**
 * 1. **Repository**: A pattern used to encapsulate the logic needed to access data sources. The repository provides a collection-like interface for accessing domain objects.
 * 2. **Separation of Concerns**: By using the repository pattern, data access logic is isolated from the rest of the application, making the application easier to maintain and test.
 * 3. **Abstraction**: Provides an abstraction layer over the data access code, whether it interacts with a database, a file system, or an in-memory data structure.
 *
 * **Benefits:**
 * - Promotes the single responsibility principle by separating data access logic from business logic.
 * - Improves code maintainability and testability.
 * - Can easily be extended to support different data sources without modifying other parts of the application.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 #include <string>
 
 /**
  * @brief A simple User model that contains user data.
  */
 class User
 {
 public:
     /**
      * @brief Constructs a User object with an ID and name.
      * @param id The ID of the user.
      * @param name The name of the user.
      */
     User(int id, const std::string& name)
         : m_id(id), m_name(name)
     {}
 
     /**
      * @brief Gets the user's ID.
      * @return The ID of the user.
      */
     int getId() const { return m_id; }
 
     /**
      * @brief Gets the user's name.
      * @return The name of the user.
      */
     const std::string& getName() const { return m_name; }
 
 private:
     int m_id;          ///< The unique ID of the user.
     std::string m_name;///< The name of the user.
 };
 
 /**
  * @brief Interface for a User repository that defines the contract for data access.
  */
 class IUserRepository
 {
 public:
     virtual ~IUserRepository() = default;
 
     /**
      * @brief Adds a user to the repository.
      * @param user The user to add.
      */
     virtual void addUser(const std::shared_ptr<User>& user) = 0;
 
     /**
      * @brief Gets a user by ID.
      * @param id The ID of the user to retrieve.
      * @return A shared pointer to the user if found, nullptr otherwise.
      */
     virtual std::shared_ptr<User> getUserById(int id) const = 0;
 
     /**
      * @brief Lists all users in the repository.
      * @return A list of all users.
      */
     virtual std::vector<std::shared_ptr<User>> getAllUsers() const = 0;
 };
 
 /**
  * @brief A concrete implementation of the IUserRepository that uses an in-memory container for data storage.
  */
 class InMemoryUserRepository : public IUserRepository
 {
 public:
     /**
      * @brief Adds a user to the in-memory repository.
      * @param user The user to add.
      */
     void addUser(const std::shared_ptr<User>& user) override
     {
         m_users.push_back(user);
     }
 
     /**
      * @brief Gets a user by ID from the in-memory repository.
      * @param id The ID of the user to retrieve.
      * @return A shared pointer to the user if found, nullptr otherwise.
      */
     std::shared_ptr<User> getUserById(int id) const override
     {
         for (const auto& user : m_users)
         {
             if (user->getId() == id)
             {
                 return user;
             }
         }
         return nullptr;
     }
 
     /**
      * @brief Lists all users in the in-memory repository.
      * @return A list of all users.
      */
     std::vector<std::shared_ptr<User>> getAllUsers() const override
     {
         return m_users;
     }
 
 private:
     std::vector<std::shared_ptr<User>> m_users; ///< In-memory list of users.
 };
 
 /**
  * @brief A class that demonstrates the use of the Repository pattern for managing users.
  */
 class UserService
 {
 public:
     /**
      * @brief Constructs a UserService with a given repository.
      * @param repository The repository to use for managing users.
      */
     UserService(const std::shared_ptr<IUserRepository>& repository)
         : m_repository(repository)
     {}
 
     /**
      * @brief Adds a user to the repository.
      * @param id The ID of the user.
      * @param name The name of the user.
      */
     void addUser(int id, const std::string& name)
     {
         auto user = std::make_shared<User>(id, name);
         m_repository->addUser(user);
     }
 
     /**
      * @brief Retrieves a user by ID from the repository.
      * @param id The ID of the user.
      * @return A shared pointer to the user, or nullptr if the user is not found.
      */
     std::shared_ptr<User> getUserById(int id) const
     {
         return m_repository->getUserById(id);
     }
 
     /**
      * @brief Retrieves all users from the repository.
      * @return A list of all users.
      */
     std::vector<std::shared_ptr<User>> getAllUsers() const
     {
         return m_repository->getAllUsers();
     }
 
 private:
     std::shared_ptr<IUserRepository> m_repository; ///< The repository for managing users.
 };
 
 /**
  * @brief Main function that demonstrates the Repository pattern in action.
  */
 int main()
 {
     // Create the repository and service.
     auto userRepository = std::make_shared<InMemoryUserRepository>();
     UserService userService(userRepository);
 
     // Add some users.
     userService.addUser(1, "Alice");
     userService.addUser(2, "Bob");
 
     // Retrieve a user by ID.
     auto user = userService.getUserById(1);
     if (user)
     {
         std::cout << "Found user: " << user->getName() << std::endl;
     }
 
     // List all users.
     auto allUsers = userService.getAllUsers();
     std::cout << "All users:\n";
     for (const auto& u : allUsers)
     {
         std::cout << u->getName() << std::endl;
     }
 
     return 0;
 }
 