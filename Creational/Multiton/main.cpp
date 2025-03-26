/**
 * @brief Multiton pattern example that manages multiple instances identified by unique keys.
 *
 * The `Multiton` pattern is similar to the Singleton pattern but allows multiple instances to exist,
 * each identified by a unique key. It ensures that only one instance per key is created and accessed.
 * This pattern is useful for managing global resources that can be identified by a unique key.
 *
 * **Key Concepts:**
 * 1. **Multiton (`Multiton`)**: The class that manages instances of itself, each mapped by a unique key.
 * 2. **Private Constructor**: The constructor of `Multiton` is private to prevent direct instantiation.
 * 3. **Factory Method (`getInstance`)**: A static method that provides access to a shared instance based on a given key.
 * 4. **Storage (`instances_`)**: A static map to hold the shared instances of `Multiton`, indexed by the unique keys.
 */

 #include <iostream>
 #include <memory>
 #include <unordered_map>
 #include <string>
 
 /**
  * @brief Multiton class that manages instances identified by unique keys.
  * 
  * The `Multiton` class ensures that only one instance is created for each unique key.
  * It manages instances via a static `std::unordered_map` and provides access
  * to these instances using a static `getInstance` method.
  */
 class Multiton
 {
 public:
     /**
      * @brief Get the instance of Multiton identified by the given key.
      * 
      * If the instance with the given key doesn't exist, it will be created.
      * 
      * @param key The unique key used to identify the instance.
      * @return A shared pointer to the `Multiton` instance associated with the key.
      */
     static std::shared_ptr<Multiton> getInstance(const std::string& key)
     {
         // If no instance exists for the given key, create one
         if (instances_.find(key) == instances_.end())
         {
             instances_[key] = std::shared_ptr<Multiton>(new Multiton(key)); // Pass key to constructor
         }
 
         return instances_[key];
     }
 
     /**
      * @brief Example method to demonstrate functionality.
      * 
      * Prints out the key that identifies this specific instance.
      */
     void printKey() const
     {
         std::cout << "Instance with key: " << key_ << std::endl;
     }
 
 private:
     /**
      * @brief Private constructor to prevent direct instantiation.
      * 
      * The constructor is private to ensure that instances can only be created via the `getInstance` method.
      * 
      * @param key The unique key used to identify this instance.
      */
     Multiton(const std::string& key) : key_(key) {}
 
     std::string key_; ///< Key that identifies this particular instance
 
     /**
      * @brief Static map to hold the instances of Multiton, indexed by unique keys.
      */
     static std::unordered_map<std::string, std::shared_ptr<Multiton>> instances_;
 };
 
 // Initialize the static member
 std::unordered_map<std::string, std::shared_ptr<Multiton>> Multiton::instances_;
 
 int main()
 {
     // Get instances of Multiton with different keys
     auto instanceA = Multiton::getInstance("A");
     instanceA->printKey();
 
     auto instanceB = Multiton::getInstance("B");
     instanceB->printKey();
 
     auto instanceC = Multiton::getInstance("A");
     instanceC->printKey(); // Should print the same key "A" as instanceA
 
     // Demonstrating that instances "A" and "B" are different
     std::cout << (instanceA == instanceC ? "Same instance" : "Different instance") << std::endl;
 
     return 0;
 }
 