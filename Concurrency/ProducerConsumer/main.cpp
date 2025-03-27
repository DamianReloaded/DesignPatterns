/**
 * @brief
 * The Producer-Consumer design pattern solves problems related to shared data access 
 * by ensuring proper synchronization between producer and consumer threads. 
 * It typically involves two types of threads: producers that generate data and consumers 
 * that process the data. A buffer (or queue) is used to temporarily hold the data 
 * until the consumer can process it. This pattern ensures that the producers and consumers 
 * operate in synchronization, avoiding race conditions and data inconsistencies.
 * 
 * Key Concepts:
 * - Producer: A thread responsible for generating data.
 * - Consumer: A thread responsible for consuming or processing the data.
 * - Shared Queue: A common data structure used by both producers and consumers for synchronization.
 * - Synchronization: Ensures that only one thread can access the shared data at a time.
 * 
 * Benefits:
 * - Prevents race conditions: Ensures proper synchronization between producer and consumer threads.
 * - Efficient data processing: Producers and consumers can operate concurrently, improving throughput.
 * - Simple and effective for multithreading: Makes handling shared data and synchronization easy.
 */

 #include <iostream>
 #include <thread>
 #include <queue>
 #include <condition_variable>
 #include <memory>
 #include <chrono>
 
 class ProducerConsumer
 {
 public:
     ProducerConsumer()
         : m_done(false) {}
 
     /**
      * @brief Adds data to the shared queue (Producer).
      * @param data The data to be added.
      */
     void produce(int data)
     {
         std::unique_lock<std::mutex> lock(m_mutex);
         m_queue.push(data);
         std::cout << "Produced: " << data << std::endl;
         m_condVar.notify_one();  // Notify the consumer that data is available.
     }
 
     /**
      * @brief Consumes data from the shared queue (Consumer).
      */
     void consume()
     {
         while (!m_done)
         {
             std::unique_lock<std::mutex> lock(m_mutex);
             m_condVar.wait(lock, [this] { return !m_queue.empty() || m_done; });  // Wait until there's data or the task is done.
 
             if (!m_queue.empty())
             {
                 int data = m_queue.front();
                 m_queue.pop();
                 std::cout << "Consumed: " << data << std::endl;
             }
         }
     }
 
     /**
      * @brief Stops the producer and consumer after finishing work.
      */
     void stop()
     {
         std::unique_lock<std::mutex> lock(m_mutex);
         m_done = true;
         m_condVar.notify_all();  // Notify all waiting threads to exit.
     }
 
 private:
     std::queue<int> m_queue; ///< The shared queue to hold data for the consumer.
     std::mutex m_mutex; ///< Mutex to synchronize access to the queue.
     std::condition_variable m_condVar; ///< Condition variable to synchronize the threads.
     bool m_done; ///< Flag to indicate when to stop the consumer thread.
 };
 
 /**
  * @brief A function to simulate a producer's work.
  * @param producerConsumer Shared pointer to the ProducerConsumer object.
  */
 void producerTask(std::shared_ptr<ProducerConsumer> producerConsumer)
 {
     for (int i = 0; i < 10; ++i)
     {
         std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
         producerConsumer->produce(i);
     }
 }
 
 /**
  * @brief A function to simulate a consumer's work.
  * @param producerConsumer Shared pointer to the ProducerConsumer object.
  */
 void consumerTask(std::shared_ptr<ProducerConsumer> producerConsumer)
 {
     producerConsumer->consume();
 }
 
 int main()
 {
     std::shared_ptr<ProducerConsumer> producerConsumer = std::make_shared<ProducerConsumer>();
 
     std::thread producer(producerTask, producerConsumer);
     std::thread consumer(consumerTask, producerConsumer);
 
     // Wait for the producer to finish producing
     producer.join();
 
     // Stop the consumer and allow it to exit the loop
     producerConsumer->stop();
 
     // Wait for the consumer to finish
     consumer.join();
 
     return 0;
 }
 