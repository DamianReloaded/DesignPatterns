/**
 * @brief Lazy Load Pattern Example: Demonstrates deferring the loading of an object until it's actually needed.
 *
 * **Key Concepts:**
 * 1. **Lazy Loading**: Defers the creation or initialization of an object until the point where it is accessed for the first time.
 * 2. **Object Initialization**: Objects are only initialized when they are needed, saving resources and potentially improving startup time.
 * 3. **Delayed Computation**: The object or resource is not loaded until it's explicitly requested, which can reduce unnecessary computations.
 *
 * **Benefits:**
 * - Saves resources by deferring the initialization until necessary.
 * - Can improve performance in scenarios where not all objects are used immediately.
 * - Useful in databases and ORM systems where not all data is required upfront.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 /**
  * @brief A class that simulates the loading of user data lazily from a database.
  */
 class User
 {
 public:
     /**
      * @brief Constructor for the User class.
      * @param id The unique identifier for the user.
      */
     User(int id)
         : m_id(id)
     {
     }
 
     /**
      * @brief Gets the user data.
      * 
      * Lazy loads the user data the first time it is accessed.
      * @return A string representing the user data.
      */
     std::string getUserData()
     {
         if (!m_data)
         {
             loadData();
         }
         return *m_data;
     }
 
 private:
     int m_id;                          ///< The unique ID of the user.
     std::shared_ptr<std::string> m_data; ///< Holds user data, initialized lazily.
 
     /**
      * @brief Simulates loading user data from a database.
      * This is a private method that simulates the lazy loading of user data.
      */
     void loadData()
     {
         // Simulate a delay for loading data (e.g., database query).
         std::cout << "Loading data for user " << m_id << " from the database..." << std::endl;
         m_data = std::make_shared<std::string>("User Data for ID: " + std::to_string(m_id));
     }
 };
 
 /**
  * @brief A class that demonstrates the lazy loading pattern by interacting with the User class.
  */
 class UserManager
 {
 public:
     /**
      * @brief Creates a new User instance.
      * @param id The unique identifier for the user.
      * @return A shared pointer to the created user.
      */
     std::shared_ptr<User> createUser(int id)
     {
         return std::make_shared<User>(id);
     }
 };
 
 /**
  * @brief Main function demonstrating Lazy Load pattern.
  */
 int main()
 {
     UserManager userManager;
 
     // Create a new user.
     auto user = userManager.createUser(1);
 
     // At this point, the user data is not loaded yet.
     std::cout << "User created. Data not loaded yet.\n";
 
     // Accessing user data for the first time triggers the lazy loading.
     std::cout << "User Data: " << user->getUserData() << std::endl;
 
     // On subsequent calls, the data is already loaded.
     std::cout << "User Data (second access): " << user->getUserData() << std::endl;
 
     return 0;
 }
 