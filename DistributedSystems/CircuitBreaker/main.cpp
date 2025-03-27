/**
 * @brief Circuit Breaker Pattern Example: Prevents a system from repeatedly attempting 
 *        to execute an operation that's likely to fail, improving system resilience.
 *
 * **Key Concepts:**
 * 1. **Circuit Breaker**: Monitors the system for failures and prevents repeated execution of failing operations.
 * 2. **Failure Threshold**: Defines a threshold after which the circuit is considered "open" and prevents further attempts.
 * 3. **Resilience**: Allows the system to recover by temporarily stopping the failing operation and reducing the system load.
 *
 * **Benefits:**
 * - Improves system stability by avoiding repeated failures.
 * - Allows fallback mechanisms or retries.
 * - Helps prevent cascading failures in distributed systems.
 */

 #include <iostream>
 #include <memory>
 #include <chrono>
 #include <thread>
 #include <atomic>
 #include <functional>
 
 class CircuitBreaker
 {
 public:
     /**
      * @brief Constructs a circuit breaker with a given failure threshold and timeout.
      * @param failureThreshold The number of consecutive failures before opening the circuit.
      * @param timeoutSeconds The time (in seconds) to wait before attempting to reset the circuit after it has opened.
      */
     CircuitBreaker(int failureThreshold, int timeoutSeconds)
         : m_failureThreshold(failureThreshold), m_timeoutSeconds(timeoutSeconds), m_failureCount(0), m_circuitOpen(false)
     {}
 
     /**
      * @brief Attempts to execute an operation. If the circuit is open or failures exceed the threshold, it will prevent execution.
      * @param operation The operation to execute, represented as a callable (e.g., function, lambda).
      * @return `true` if the operation is successfully executed, `false` otherwise.
      */
     bool execute(std::function<bool()> operation)
     {
         if (m_circuitOpen)
         {
             std::cout << "Circuit is open. Operation will not be executed.\n";
             return false;
         }
 
         bool success = operation();
         
         if (!success)
         {
             m_failureCount++;
             std::cout << "Operation failed. Failure count: " << m_failureCount << "/" << m_failureThreshold << "\n";
             
             if (m_failureCount >= m_failureThreshold)
             {
                 openCircuit();
             }
         }
         else
         {
             m_failureCount = 0;  // Reset failure count on success.
         }
 
         return success;
     }
 
     /**
      * @brief Resets the circuit after the timeout period if the circuit is open.
      */
     void resetCircuit()
     {
         if (m_circuitOpen)
         {
             std::cout << "Circuit is open, waiting for reset...\n";
             std::this_thread::sleep_for(std::chrono::seconds(m_timeoutSeconds));
             std::cout << "Resetting circuit...\n";
             m_circuitOpen = false;
             m_failureCount = 0;  // Reset failure count after resetting the circuit.
         }
     }
 
 private:
     int m_failureThreshold; ///< The number of consecutive failures before the circuit is opened.
     int m_timeoutSeconds;   ///< The timeout period before attempting to reset the circuit.
     int m_failureCount;     ///< The current count of consecutive failures.
     bool m_circuitOpen;     ///< A flag indicating if the circuit is open (i.e., no more attempts allowed).
     
     /**
      * @brief Opens the circuit, preventing further operation attempts until reset.
      */
     void openCircuit()
     {
         std::cout << "Circuit opened due to failure threshold reached.\n";
         m_circuitOpen = true;
     }
 };
 
 /**
  * @brief Simulates an operation that may fail intermittently.
  * @return `true` for success, `false` for failure.
  */
 bool riskyOperation()
 {
     static int attempt = 0;
     attempt++;
     if (attempt % 6 == 0)
     {
         std::cout << "Operation succeeded.\n";
         return true;
     }
     else
     {
         std::cout << "Operation failed.\n";
         return false;
     }
 }
 
 /**
  * @brief Demonstrates the usage of the Circuit Breaker pattern.
  */
 int main()
 {
     // Create a circuit breaker that opens after 3 consecutive failures and has a 5-second timeout before resetting.
     auto circuitBreaker = std::make_shared<CircuitBreaker>(3, 5);
 
     // Try to execute the risky operation multiple times
     for (int i = 0; i < 10; ++i)
     {
         if (!circuitBreaker->execute(riskyOperation))
         {
             std::cout << "Retrying...\n";
         }
 
         // If the circuit is open, wait before retrying.
         if (i % 5 == 0)
         {
             circuitBreaker->resetCircuit();
         }
     }
 
     return 0;
 }
 