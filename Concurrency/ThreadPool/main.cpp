/**
 * @brief Thread Pool Pattern Example: Efficient Task Execution with a Fixed Thread Pool
 *
 * **Key Concepts:**
 * 1. **Thread Management**: Uses a fixed number of threads to execute tasks.
 * 2. **Task Queueing**: Incoming tasks are queued and processed by available threads.
 * 3. **Efficient Resource Utilization**: Threads are reused instead of frequently creating/destroying them.
 *
 * **Benefits:**
 * - Reduces overhead from thread creation and destruction.
 * - Ensures parallel execution of tasks with limited resources.
 * - Improves responsiveness in applications requiring frequent task execution.
 */

 #include <iostream>
 #include <vector>
 #include <queue>
 #include <thread>
 #include <mutex>
 #include <condition_variable>
 #include <functional>
 #include <memory>
 #include <atomic>
 
 /**
  * @brief Manages a pool of worker threads that execute queued tasks.
  */
 class ThreadPool
 {
 public:
     /**
      * @brief Constructs a thread pool with the given number of worker threads.
      * @param threadCount Number of worker threads.
      */
     explicit ThreadPool(size_t threadCount) : m_running(true)
     {
         for (size_t i = 0; i < threadCount; ++i)
         {
             m_workers.emplace_back([this]
             {
                 while (true)
                 {
                     std::function<void()> task;
                     {
                         std::unique_lock lock(m_mutex);
                         m_condition.wait(lock, [this] { return !m_tasks.empty() || !m_running; });
 
                         if (!m_running && m_tasks.empty())
                         {
                             return;
                         }
 
                         task = std::move(m_tasks.front());
                         m_tasks.pop();
                     }
                     task(); // Execute the task
                 }
             });
         }
     }
 
     /**
      * @brief Destroys the thread pool, ensuring all tasks complete before shutdown.
      */
     ~ThreadPool()
     {
         {
             std::lock_guard lock(m_mutex);
             m_running = false;
         }
         m_condition.notify_all();
 
         for (auto& worker : m_workers)
         {
             if (worker.joinable())
             {
                 worker.join();
             }
         }
     }
 
     /**
      * @brief Adds a new task to the queue for execution by a worker thread.
      * @param task The function to execute asynchronously.
      */
     void enqueueTask(std::function<void()> task)
     {
         {
             std::lock_guard lock(m_mutex);
             m_tasks.push(std::move(task));
         }
         m_condition.notify_one();
     }
 
 private:
     std::vector<std::thread> m_workers; ///< Worker threads.
     std::queue<std::function<void()>> m_tasks; ///< Task queue.
     std::mutex m_mutex; ///< Synchronizes access to task queue.
     std::condition_variable m_condition; ///< Notifies workers of new tasks.
     std::atomic<bool> m_running; ///< Controls worker execution.
 };
 
 /**
  * @brief Demonstrates the Thread Pool pattern with multiple tasks.
  */
 int main()
 {
     constexpr size_t threadCount = 4;
     auto pool = std::make_shared<ThreadPool>(threadCount);
 
     for (int i = 0; i < 10; ++i)
     {
         pool->enqueueTask([i]
         {
             std::cout << "Task " << i << " is executing on thread " << std::this_thread::get_id() << std::endl;
             std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
         });
     }
 
     std::this_thread::sleep_for(std::chrono::seconds(3)); // Allow time for tasks to finish
     return 0;
 }
 