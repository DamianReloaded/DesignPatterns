/**
 * @brief Object Pool Design Pattern Example
 *
 * The Object Pool pattern provides a way to manage a set of reusable objects that can be used by clients
 * without the need to create and destroy them frequently. The main goal of the object pool is to avoid 
 * expensive resource allocation and deallocation.
 * 
 * In this example, the pool manages reusable `Connection` objects using `std::shared_ptr`. 
 * The pool creates and manages a set number of connections, and clients can acquire and release them.
 */

 #include <iostream>
 #include <memory>
 #include <queue>
 #include <stdexcept>
 
 /**
  * @brief Connection class representing a resource.
  * 
  * The `Connection` class simulates a resource that can be acquired and used.
  */
 class Connection
 {
 public:
     /**
      * @brief Construct a new Connection object.
      * 
      * Initializes the connection and marks it as available.
      */
     Connection()
     {
         std::cout << "Connection created.\n";
     }
 
     /**
      * @brief Simulate a connection usage.
      * 
      * This method simulates the work done while a connection is in use.
      */
     void use()
     {
         std::cout << "Connection is being used.\n";
     }
 
     /**
      * @brief Destruct the Connection object.
      * 
      * Cleans up when the connection is destroyed.
      */
     ~Connection()
     {
         std::cout << "Connection destroyed.\n";
     }
 };
 
 /**
  * @brief ObjectPool class that manages a pool of connections.
  * 
  * The `ObjectPool` class manages a collection of reusable `Connection` objects. Clients can acquire and release
  * connections, and the pool ensures efficient management of resources.
  */
 class ObjectPool
 {
 public:
     /**
      * @brief Construct a new ObjectPool object.
      * 
      * Initializes the pool with a fixed number of connections.
      * 
      * @param size The number of connections to pre-allocate in the pool.
      */
     explicit ObjectPool(size_t size)
     {
         for (size_t i = 0; i < size; ++i)
         {
             pool_.push(std::make_shared<Connection>());
         }
     }
 
     /**
      * @brief Acquire a connection from the pool.
      * 
      * This method returns a `Connection` object if available.
      * If no connections are available, it throws an exception.
      * 
      * @return A shared pointer to a `Connection` object.
      * 
      * @throws std::runtime_error If no connections are available in the pool.
      */
     std::shared_ptr<Connection> acquire()
     {
         if (pool_.empty())
         {
             throw std::runtime_error("No available connections in the pool.");
         }
         auto connection = pool_.front();
         pool_.pop();
         return connection;
     }
 
     /**
      * @brief Release a connection back to the pool.
      * 
      * This method returns a connection object to the pool to be reused.
      * 
      * @param connection A `Connection` object to be returned to the pool.
      */
     void release(std::shared_ptr<Connection> connection)
     {
         pool_.push(connection);
     }
 
     /**
      * @brief Destructor to clean up the pool.
      * 
      * This destructor ensures that any remaining resources are cleaned up when the pool is destroyed.
      */
     ~ObjectPool() = default;
 
 private:
     std::queue<std::shared_ptr<Connection>> pool_; ///< The pool of available connections.
 };
 
 /**
  * @brief Main function to demonstrate the Object Pool pattern.
  * 
  * In the `main` function, an object pool is created with a fixed number of connections.
  * Connections are acquired, used, and released back into the pool.
  */
 int main()
 {
     try
     {
         // Create an ObjectPool with 3 connections
         ObjectPool pool(3);
 
         // Acquire and use a connection
         auto connection1 = pool.acquire();
         connection1->use();
 
         // Acquire and use another connection
         auto connection2 = pool.acquire();
         connection2->use();
 
         // Release connections back to the pool
         pool.release(connection1);
         pool.release(connection2);
 
         // Acquire another connection after releasing
         auto connection3 = pool.acquire();
         connection3->use();
 
     }
     catch (const std::runtime_error &e)
     {
         std::cout << "Error: " << e.what() << std::endl;
     }
 
     return 0;
 }
 