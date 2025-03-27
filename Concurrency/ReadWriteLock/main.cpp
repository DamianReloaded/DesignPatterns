/**
 * @brief
 * The Read-Write Lock pattern allows multiple threads to read shared data concurrently while providing exclusive 
 * access for a thread when writing data. This improves performance in scenarios where read operations are much more 
 * frequent than write operations.
 * 
 * Key concepts:
 * - Read Access: Allows multiple threads to read data concurrently.
 * - Write Access: Ensures that only one thread can write at a time, preventing other threads from reading or writing during the operation.
 * - Performance: This pattern optimizes performance in read-heavy scenarios by allowing concurrent reads while serializing writes.
 * 
 * Benefits:
 * - Increased concurrency: Multiple threads can read shared data without blocking each other.
 * - Improved performance: By avoiding unnecessary locks during read operations, the overall performance of the system is enhanced.
 * - Fine-grained control: Allows controlling access for reading and writing separately.
 */

 #include <iostream>
 #include <shared_mutex>
 #include <memory>
 #include <string>
 #include <thread>
 #include <vector>
 #include <mutex>
 
 /**
  * @brief
  * A simple Read-Write Lock example that demonstrates the use of read-write locks for thread-safe read and write operations.
  */
 class SharedData
 {
 public:
     /**
      * @brief Sets the data value.
      * Uses a write lock to ensure exclusive access to the data while writing.
      * 
      * @param data The value to set.
      */
     void setData(const std::string &data)
     {
         std::unique_lock<std::shared_mutex> writeLock(m_rwMutex); // Write lock
         m_data = data;
         std::cout << "Data set to: " << m_data << std::endl;
     }
 
     /**
      * @brief Gets the data value.
      * Uses a read lock to allow multiple threads to read the data concurrently.
      * 
      * @return The current data value.
      */
     std::string getData() const
     {
         std::shared_lock<std::shared_mutex> readLock(m_rwMutex); // Read lock
         return m_data;
     }
 
 private:
     mutable std::shared_mutex m_rwMutex; ///< Mutex for read-write locking.
     std::string m_data; ///< Shared data.
 };
 
 /**
  * @brief Simulates a reader thread that reads data.
  * @param sharedData The shared data object to read from.
  */
 void reader(const SharedData &sharedData)
 {
     std::cout << "Reader: " << sharedData.getData() << std::endl;
 }
 
 /**
  * @brief Simulates a writer thread that writes data.
  * @param sharedData The shared data object to write to.
  * @param newData The new data to write.
  */
 void writer(SharedData &sharedData, const std::string &newData)
 {
     sharedData.setData(newData);
 }
 
 int main()
 {
     SharedData sharedData;
 
     // Start a writer thread
     std::thread writerThread(writer, std::ref(sharedData), "Hello, World!");
 
     // Start several reader threads
     std::vector<std::thread> readerThreads;
     for (int i = 0; i < 5; ++i)
     {
         readerThreads.push_back(std::thread(reader, std::cref(sharedData)));
     }
 
     // Join writer and reader threads
     writerThread.join();
     for (auto &t : readerThreads)
     {
         t.join();
     }
 
     return 0;
 }
 