/**
 * @brief
 * The Future design pattern simplifies working with asynchronous programming by allowing you to get the result of an operation that may not be complete yet.
 * 
 * Key Concepts:
 * - Asynchronous computation: Enables non-blocking operations, where the computation may occur in the background.
 * - Future: An object that represents the result of an operation that may be in progress, allowing you to retrieve the result later.
 * - Promises: Used to set the result of the computation at some point in the future.
 * 
 * Benefits:
 * - Simplifies concurrency: Allows performing operations in parallel without blocking the main thread.
 * - Synchronizes results: You can retrieve the result once the task is completed without needing to manually manage synchronization.
 * - Suitable for I/O-bound or long-running tasks: Ideal for operations like file reading, network requests, or complex calculations.
 */

 #include <iostream>
 #include <thread>
 #include <future>
 #include <chrono>
 
 /**
  * @brief Simulates a long-running asynchronous operation.
  * 
  * This function simulates a computation by sleeping for a few seconds,
  * then returns the computed result.
  * 
  * @param input The input value for the computation.
  * @return The computed result (input * 2).
  */
 int longRunningComputation(int input)
 {
     std::this_thread::sleep_for(std::chrono::seconds(2));  // Simulate work
     return input * 2;
 }
 
 /**
  * @brief Main function to demonstrate the Future pattern.
  * 
  * In this function, we initiate an asynchronous computation using std::async
  * and then retrieve the result using std::future.
  * 
  * @return int Exit status.
  */
 int main()
 {
     // Create a future that will hold the result of the asynchronous task
     std::future<int> resultFuture = std::async(std::launch::async, longRunningComputation, 10);
 
     // Perform other tasks while the long-running computation is in progress
     std::cout << "Doing some other work while waiting for the result...\n";
 
     // Get the result of the asynchronous operation (this will block until the computation is complete)
     int result = resultFuture.get();  // Blocks here until the result is available
 
     // Output the result of the computation
     std::cout << "The result of the computation is: " << result << "\n";
 
     return 0;
 }
 