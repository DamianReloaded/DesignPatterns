/**
 * @brief Guarded Suspension Pattern Example: Safe Data Retrieval in Multithreading
 *
 * **Key Concepts:**
 * 1. **Synchronization**: The consumer waits (suspends) until a condition is met.
 * 2. **Thread Safety**: Uses a mutex and condition variable to prevent race conditions.
 * 3. **Efficient Waiting**: The consumer does not busy-wait; it suspends until notified.
 *
 * **Benefits:**
 * - Prevents unnecessary CPU usage in multithreading.
 * - Ensures data is accessed only when available.
 * - Avoids race conditions with proper locking mechanisms.
 */

 #include <iostream>
 #include <thread>
 #include <mutex>
 #include <condition_variable>
 #include <queue>
 #include <memory>
 #include <chrono>
 
 /**
  * @brief A thread-safe queue implementing the Guarded Suspension pattern.
  */
 class GuardedQueue
 {
 public:
     /**
      * @brief Adds data to the queue and notifies the consumer.
      * @param value The integer value to add.
      */
     void addData(int value)
     {
         {
             std::lock_guard lock(m_mutex);
             m_dataQueue.push(value);
         }
         m_cv.notify_one();
     }
 
     /**
      * @brief Retrieves and removes data from the queue, suspending if empty.
      * @return The retrieved integer value.
      */
     int getData()
     {
         std::unique_lock lock(m_mutex);
         m_cv.wait(lock, [this] { return !m_dataQueue.empty(); }); // Suspend if queue is empty
 
         int value = m_dataQueue.front();
         m_dataQueue.pop();
         return value;
     }
 
 private:
     std::queue<int> m_dataQueue; ///< Queue storing integer values.
     std::mutex m_mutex;          ///< Mutex for thread safety.
     std::condition_variable m_cv; ///< Condition variable for synchronization.
 };
 
 /**
  * @brief Simulates a data producer that generates values and adds them to the queue.
  * @param queue Shared queue instance.
  */
 void producer(std::shared_ptr<GuardedQueue> queue)
 {
     for (int i = 1; i <= 5; ++i)
     {
         std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate delay
         queue->addData(i);
         std::cout << "Produced: " << i << std::endl;
     }
 }
 
 /**
  * @brief Simulates a data consumer that retrieves values from the queue.
  * @param queue Shared queue instance.
  */
 void consumer(std::shared_ptr<GuardedQueue> queue)
 {
     for (int i = 1; i <= 5; ++i)
     {
         int value = queue->getData();
         std::cout << "Consumed: " << value << std::endl;
     }
 }
 
 /**
  * @brief Demonstrates the Guarded Suspension pattern with producer-consumer threads.
  */
 int main()
 {
     auto queue = std::make_shared<GuardedQueue>();
 
     std::thread producerThread(producer, queue);
     std::thread consumerThread(consumer, queue);
 
     producerThread.join();
     consumerThread.join();
 
     return 0;
 }
 