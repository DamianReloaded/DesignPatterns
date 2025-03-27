/**
 * @brief
 * The Thread-Specific Storage (TSS) design pattern is used when you need to store data
 * that is unique to each thread. This pattern ensures that each thread has its own instance
 * of a variable, preventing conflicts between threads accessing the same data.
 * 
 * Explanation:
 * 
 * Thread-Specific Storage: The ThreadSpecificStorage class stores a unique value for each thread using the thread_local keyword. 
 * This allows each thread to have its own instance of m_threadLocalData.
 * 
 * Key Concepts:
 * - Thread-local storage: Data that is only accessible to the thread that created it.
 * - Thread safety: Ensures that each thread can access its own unique data without interference.
 * - Memory isolation: Data is isolated between threads, which can improve concurrency and reduce contention.
 * 
 * Benefits:
 * - Efficient for multi-threaded applications: Avoids the need for mutexes or other synchronization methods to access thread-local data.
 * - Prevents data race conditions: Since each thread has its own copy of the data, no other thread can modify it.
 * - Ideal for thread-local storage like thread IDs, logging, or thread-specific counters.
 */

 #include <iostream>
 #include <thread>
 #include <vector>
 #include <memory>
 #include <mutex>
 
 /**
  * @brief A class representing thread-specific storage.
  * This class demonstrates how to store unique data for each thread.
  */
 class ThreadSpecificStorage
 {
 public:
     /**
      * @brief Sets a value specific to the current thread.
      * @param value The value to store for the current thread.
      */
     void setValue(int value)
     {
         m_threadLocalData = value; // Store value specific to the current thread
     }
 
     /**
      * @brief Gets the value specific to the current thread.
      * @return The value stored for the current thread.
      */
     int getValue() const
     {
         return m_threadLocalData;
     }
 
 private:
     thread_local static int m_threadLocalData; ///< Thread-specific data.
 };
 
 thread_local int ThreadSpecificStorage::m_threadLocalData;

 /**
  * @brief Function that simulates work by each thread, setting and getting its thread-specific data.
  * @param threadId The unique identifier for the thread.
  */
 void threadFunction(int threadId)
 {
     ThreadSpecificStorage threadStorage;
 
     // Set a unique value for each thread
     threadStorage.setValue(threadId);
 
     // Simulate some processing
     std::this_thread::sleep_for(std::chrono::milliseconds(100));
 
     // Get the thread-specific value and print it
     std::cout << "Thread " << threadId << " has value: " << threadStorage.getValue() << std::endl;
 }
 
 /**
  * @brief The main entry point of the program.
  * This function starts multiple threads, each working with thread-specific storage.
  */
 int main()
 {
     std::vector<std::thread> threads;
 
     // Create and start multiple threads
     for (int i = 0; i < 5; ++i)
     {
         threads.push_back(std::thread(threadFunction, i));
     }
 
     // Wait for all threads to complete
     for (auto& t : threads)
     {
         t.join();
     }
 
     return 0;
 }
 