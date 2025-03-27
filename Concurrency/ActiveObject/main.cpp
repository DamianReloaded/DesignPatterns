/**
 * @brief Active Object Pattern Example: Asynchronous Logging System
 *
 * **Key Concepts:**
 * 1. **Active Object (`Logger`)**: Decouples logging requests from actual log writing.
 * 2. **Thread Safety**: Uses a mutex and condition variable for safe communication.
 * 3. **Non-Blocking Execution**: Logging requests return immediately, avoiding performance bottlenecks.
 *
 * **Benefits:**
 * - Prevents logging from blocking the main application flow.
 * - Improves responsiveness in real-time or high-throughput systems.
 * - Automatically processes logs in the background.
 */

 #include <iostream>
 #include <queue>
 #include <string>
 #include <memory>
 #include <thread>
 #include <mutex>
 #include <condition_variable>
 #include <atomic>
 #include <chrono>
 
 /**
  * @brief Manages an asynchronous logging system using the Active Object pattern.
  */
 class Logger
 {
 public:
     /**
      * @brief Constructs the Logger and starts the worker thread.
      */
     Logger()
     {
         m_worker = std::make_unique<std::thread>(&Logger::processLogs, this);
     }
 
     /**
      * @brief Destroys the Logger and ensures all logs are processed.
      */
     ~Logger()
     {
         {
             std::lock_guard lock(m_mutex);
             m_running = false;
         }
         m_cv.notify_one();
         if (m_worker->joinable())
         {
             m_worker->join();
         }
     }
 
     /**
      * @brief Asynchronously logs a message.
      * @param message The message to log.
      */
     void logMessage(const std::string& message)
     {
         {
             std::lock_guard lock(m_mutex);
             m_logQueue.push(message);
         }
         m_cv.notify_one();
     }
 
     /**
      * @brief Waits for all log messages to be processed before exiting.
      */
     void waitForCompletion()
     {
         while (true)
         {
             std::lock_guard lock(m_mutex);
             if (m_logQueue.empty())
             {
                 break;
             }
             std::this_thread::sleep_for(std::chrono::milliseconds(100));
         }
     }
 
 private:
     std::queue<std::string> m_logQueue; ///< Queue of log messages.
     std::mutex m_mutex;                 ///< Protects access to the queue.
     std::condition_variable m_cv;       ///< Notifies the worker thread.
     std::unique_ptr<std::thread> m_worker; ///< Worker thread processing logs.
     std::atomic<bool> m_running{true};  ///< Flag to control worker execution.
 
     /**
      * @brief Processes log messages asynchronously.
      */
     void processLogs()
     {
         while (true)
         {
             std::unique_lock lock(m_mutex);
             m_cv.wait(lock, [this] { return !m_logQueue.empty() || !m_running; });
 
             if (!m_running && m_logQueue.empty())
             {
                 break;
             }
 
             while (!m_logQueue.empty())
             {
                 std::cout << "Log: " << m_logQueue.front() << std::endl;
                 m_logQueue.pop();
                 // Simulate a slow logging operation
                 std::this_thread::sleep_for(std::chrono::milliseconds(2000));
             }
         }
     }
 };
 
 /**
  * @brief Demonstrates the Active Object pattern with an asynchronous logger.
  */
 int main()
 {
     auto logger = std::make_shared<Logger>();
 
     auto startTime = std::chrono::high_resolution_clock::now();
 
     // All calls return immediately without blocking the main thread, even though logging takes 2 sec per log
     logger->logMessage("Starting application...");
     logger->logMessage("User logged in");
     logger->logMessage("Data processing started");
     logger->logMessage("Data processing finished");
     logger->logMessage("User logged out");
 
     auto endTime = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
 
     std::cout << " --------------------\n"<< "Time taken to queue all log messages: " << duration << " ms\n--------------------\n";
 
     // Ensure all logs are processed before program exits
     logger->waitForCompletion();
 
     return 0;
 }
 