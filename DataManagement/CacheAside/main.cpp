/**
 * @brief
 * The Cache-Aside design pattern is used to improve data access performance by caching data and ensuring that the application
 * loads data from the cache when possible. If the data is not in the cache, it loads the data from a data source (e.g., a database),
 * stores it in the cache, and then returns it for future use.
 * 
 * Key Concepts:
 * - Cache-Aside: The application code is responsible for interacting with both the cache and the data source.
 * - Lazy Loading: Data is only fetched from the database when it is missing in the cache.
 * - Cache Population: Once data is retrieved from the database, it is stored in the cache for future access.
 * 
 * Benefits:
 * - Improved Performance: Frequently accessed data is cached to reduce database load.
 * - Flexibility: The pattern can work with any cache and data source combination.
 * - Scalability: The application can scale better by offloading some of the database access to the cache.
 * 
 * @note In this example, the cache is simulated using an unordered_map and the database is simulated by a simple function.
 */

 #include <iostream>
 #include <memory>
 #include <unordered_map>
 #include <string>
 
 /**
  * @brief Represents an entity in the system that can be cached.
  * 
  * In this example, we simulate a "Customer" entity with an ID and a name.
  */
 class Customer
 {
 public:
     Customer(int id, const std::string &name) : m_id(id), m_name(name) {}
 
     /**
      * @brief Gets the customer ID.
      * @return The customer ID.
      */
     int getId() const { return m_id; }
 
     /**
      * @brief Gets the customer name.
      * @return The customer name.
      */
     std::string getName() const { return m_name; }
 
 private:
     int m_id;               ///< Customer ID
     std::string m_name;     ///< Customer Name
 };
 
 /**
  * @brief Interface for a cache system.
  * 
  * The cache interface defines methods for retrieving and storing data in the cache.
  */
 class ICache
 {
 public:
     virtual ~ICache() = default;
 
     /**
      * @brief Gets the value from the cache based on the key.
      * @param key The key to retrieve the value.
      * @return A shared pointer to the value if found, nullptr otherwise.
      */
     virtual std::shared_ptr<Customer> get(int key) const = 0;
 
     /**
      * @brief Puts the value into the cache with the given key.
      * @param key The key to store the value under.
      * @param value The value to store in the cache.
      */
     virtual void put(int key, const std::shared_ptr<Customer> &value) = 0;
 };
 
 /**
  * @brief Concrete cache implementation using an unordered_map.
  * 
  * This implementation simulates the behavior of a cache using an unordered_map.
  */
 class Cache : public ICache
 {
 public:
     /**
      * @brief Gets the value from the cache based on the key.
      * @param key The key to retrieve the value.
      * @return A shared pointer to the value if found, nullptr otherwise.
      */
     std::shared_ptr<Customer> get(int key) const override
     {
         auto it = m_cache.find(key);
         if (it != m_cache.end())
         {
             return it->second;
         }
         return nullptr;
     }
 
     /**
      * @brief Puts the value into the cache with the given key.
      * @param key The key to store the value under.
      * @param value The value to store in the cache.
      */
     void put(int key, const std::shared_ptr<Customer> &value) override
     {
         m_cache[key] = value;
     }
 
 private:
     mutable std::unordered_map<int, std::shared_ptr<Customer>> m_cache; ///< Simulated cache storage
 };
 
 /**
  * @brief Interface for a data source, such as a database.
  * 
  * The data source interface defines the method for retrieving data from a storage system.
  */
 class IDataSource
 {
 public:
     virtual ~IDataSource() = default;
 
     /**
      * @brief Retrieves the customer data from the database.
      * @param id The ID of the customer to retrieve.
      * @return A shared pointer to the customer if found, nullptr otherwise.
      */
     virtual std::shared_ptr<Customer> getCustomer(int id) const = 0;
 };
 
 /**
  * @brief Concrete data source implementation simulating a database.
  * 
  * This implementation simulates retrieving a customer from a database.
  */
 class DataSource : public IDataSource
 {
 public:
     /**
      * @brief Retrieves the customer data from the database.
      * @param id The ID of the customer to retrieve.
      * @return A shared pointer to the customer if found, nullptr otherwise.
      */
     std::shared_ptr<Customer> getCustomer(int id) const override
     {
         if (id == 1)
         {
             return std::make_shared<Customer>(1, "John Doe");
         }
         else if (id == 2)
         {
             return std::make_shared<Customer>(2, "Jane Smith");
         }
         return nullptr;
     }
 };
 
 /**
  * @brief Implements the Cache-Aside pattern.
  * 
  * The Cache-Aside pattern ensures that data is retrieved from the cache first, and if not found, it loads from the database
  * and stores the result in the cache for future use.
  */
 class CacheAside
 {
 public:
     /**
      * @brief Constructs a Cache-Aside object with the given cache and data source.
      * @param cache The cache to use for storing and retrieving data.
      * @param dataSource The data source to load data from if not found in the cache.
      */
     CacheAside(std::shared_ptr<ICache> cache, std::shared_ptr<IDataSource> dataSource)
         : m_cache(std::move(cache)), m_dataSource(std::move(dataSource)) {}
 
     /**
      * @brief Retrieves a customer, first checking the cache and then the database.
      * @param id The ID of the customer to retrieve.
      * @return A shared pointer to the customer if found.
      */
     std::shared_ptr<Customer> getCustomer(int id)
     {
         // Try to get customer from cache
         auto customer = m_cache->get(id);
         if (customer)
         {
             std::cout << "Cache hit: Retrieved customer from cache.\n";
             return customer;
         }
 
         // If not found in cache, get it from the data source
         std::cout << "Cache miss: Retrieving customer from database.\n";
         customer = m_dataSource->getCustomer(id);
 
         // Store the retrieved customer in the cache
         if (customer)
         {
             m_cache->put(id, customer);
             std::cout << "Storing customer in cache.\n";
         }
 
         return customer;
     }
 
 private:
     std::shared_ptr<ICache> m_cache;       ///< The cache to store data
     std::shared_ptr<IDataSource> m_dataSource; ///< The data source to load data from
 };
 
 /**
  * @brief Main function to demonstrate the Cache-Aside pattern.
  */
 int main()
 {
     // Initialize the cache and data source
     auto cache = std::make_shared<Cache>();
     auto dataSource = std::make_shared<DataSource>();
 
     // Create the CacheAside object with the cache and data source
     CacheAside cacheAside(cache, dataSource);
 
     // Try to get customers (with cache misses and hits)
     auto customer1 = cacheAside.getCustomer(1); // Should miss the cache and load from the "database"
     auto customer2 = cacheAside.getCustomer(2); // Should miss the cache and load from the "database"
     auto customer3 = cacheAside.getCustomer(1); // Should hit the cache this time
 
     return 0;
 }
 