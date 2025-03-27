/**
 * @brief Data Mapper Pattern Example: Separates in-memory objects from the database schema, allowing objects to remain unaware of the database structure.
 *
 * **Key Concepts:**
 * 1. **Data Mapper**: The Data Mapper pattern is used to keep in-memory objects and the database schema separated. The mapper layer handles the conversion between the two.
 * 2. **Persistence Layer**: The data mapper is responsible for saving, retrieving, and deleting data in the database without exposing the database details to the objects.
 * 3. **In-Memory Objects**: The in-memory objects (also known as domain objects) are independent of the database schema and do not require any knowledge of the persistence layer.
 *
 * **Benefits:**
 * - Enables better separation of concerns, keeping the domain logic separate from the persistence logic.
 * - Allows for easier changes to the database schema without impacting the business logic.
 * - Enhances testability by making the domain objects simpler to test.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 #include <string>
 
 /**
  * @brief A simple User model that represents a user in-memory.
  */
 class User
 {
 public:
     /**
      * @brief Constructs a User object.
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
     int m_id;          ///< The ID of the user.
     std::string m_name;///< The name of the user.
 };
 
 /**
  * @brief Interface for a Data Mapper that handles the persistence logic for the User object.
  */
 class IUserDataMapper
 {
 public:
     virtual ~IUserDataMapper() = default;
 
     /**
      * @brief Saves a user to the database.
      * @param user The user to save.
      */
     virtual void save(const std::shared_ptr<User>& user) = 0;
 
     /**
      * @brief Retrieves a user by ID from the database.
      * @param id The ID of the user.
      * @return A shared pointer to the user if found, nullptr otherwise.
      */
     virtual std::shared_ptr<User> findById(int id) const = 0;
 };
 
 /**
  * @brief Concrete implementation of IUserDataMapper that uses a simple in-memory "database".
  */
 class InMemoryUserDataMapper : public IUserDataMapper
 {
 public:
     /**
      * @brief Saves a user to the in-memory database.
      * @param user The user to save.
      */
     void save(const std::shared_ptr<User>& user) override
     {
         m_users.push_back(user);
         std::cout << "User saved: " << user->getName() << std::endl;
     }
 
     /**
      * @brief Finds a user by ID in the in-memory database.
      * @param id The ID of the user.
      * @return A shared pointer to the user if found, nullptr otherwise.
      */
     std::shared_ptr<User> findById(int id) const override
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
 
 private:
     std::vector<std::shared_ptr<User>> m_users; ///< In-memory storage for users.
 };
 
 /**
  * @brief A service class that interacts with the Data Mapper to manage user data.
  */
 class UserService
 {
 public:
     /**
      * @brief Constructs the UserService with a given data mapper.
      * @param dataMapper The data mapper for accessing the user data.
      */
     UserService(const std::shared_ptr<IUserDataMapper>& dataMapper)
         : m_dataMapper(dataMapper)
     {}
 
     /**
      * @brief Saves a user to the database via the data mapper.
      * @param id The ID of the user.
      * @param name The name of the user.
      */
     void saveUser(int id, const std::string& name)
     {
         auto user = std::make_shared<User>(id, name);
         m_dataMapper->save(user);
     }
 
     /**
      * @brief Retrieves a user by ID from the database via the data mapper.
      * @param id The ID of the user.
      * @return A shared pointer to the user, or nullptr if the user is not found.
      */
     std::shared_ptr<User> getUserById(int id) const
     {
         return m_dataMapper->findById(id);
     }
 
 private:
     std::shared_ptr<IUserDataMapper> m_dataMapper; ///< The data mapper for user data.
 };
 
 /**
  * @brief Main function that demonstrates the Data Mapper pattern.
  */
 int main()
 {
     // Create the data mapper and service.
     auto userDataMapper = std::make_shared<InMemoryUserDataMapper>();
     UserService userService(userDataMapper);
 
     // Save some users.
     userService.saveUser(1, "Alice");
     userService.saveUser(2, "Bob");
 
     // Retrieve a user by ID.
     auto user = userService.getUserById(1);
     if (user)
     {
         std::cout << "Found user: " << user->getName() << std::endl;
     }
     else
     {
         std::cout << "User not found" << std::endl;
     }
 
     return 0;
 }
 