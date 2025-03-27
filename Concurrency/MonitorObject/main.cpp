/**
 * @brief Monitor Object Pattern Example: Thread-Safe Bank Account with Blocking Withdrawals
 *
 * **Key Concepts:**
 * 1. **Encapsulation**: Synchronization and condition handling are inside `BankAccount`.
 * 2. **Thread Safety**: Uses a mutex and condition variable for safe transactions.
 * 3. **Synchronization**: `withdraw` waits until enough funds are available.
 *
 * **Benefits:**
 * - Prevents race conditions in concurrent transactions.
 * - Ensures fairness by suspending insufficient withdrawals instead of failing.
 * - Encapsulates all synchronization logic within the object.
 */

 #include <iostream>
 #include <thread>
 #include <mutex>
 #include <memory>
 #include <vector>
 #include <condition_variable>
 #include <chrono>
 
 /**
  * @brief Thread-safe bank account with blocking withdrawals.
  */
 class BankAccount
 {
 public:
     /**
      * @brief Constructs a bank account with an initial balance.
      * @param initialBalance The starting balance.
      */
     explicit BankAccount(double initialBalance) : m_balance(initialBalance) {}
 
     /**
      * @brief Deposits money into the account safely and notifies waiting withdrawals.
      * @param amount The amount to deposit.
      */
     void deposit(double amount)
     {
         {
             std::lock_guard lock(m_mutex);
             m_balance += amount;
             std::cout << "Deposited: $" << amount << " | Balance: $" << m_balance << std::endl;
         }
         m_cv.notify_all(); // Notify waiting threads
     }
 
     /**
      * @brief Withdraws money safely, blocking if insufficient funds.
      * @param amount The amount to withdraw.
      */
     void withdraw(double amount)
     {
         std::unique_lock lock(m_mutex);
         if (m_balance<amount) std::cout << "Not enough funds. Awaiting for a deposit..." << std::endl;
         m_cv.wait(lock, [&] { return m_balance >= amount; }); // Wait until enough balance
 
         m_balance -= amount;
         std::cout << "Withdrawn: $" << amount << " | Balance: $" << m_balance << std::endl;
     }
 
     /**
      * @brief Retrieves the current balance safely.
      * @return The current balance.
      */
     double getBalance()
     {
         std::lock_guard lock(m_mutex);
         return m_balance;
     }
 
 private:
     double m_balance; ///< The bank account balance.
     std::mutex m_mutex; ///< Mutex for synchronizing access.
     std::condition_variable m_cv; ///< Condition variable to manage waiting withdrawals.
 };
 
 /**
  * @brief Demonstrates the Monitor Object pattern with a bank account.
  */
 int main()
 {
     auto account = std::make_shared<BankAccount>(50.0);
 
     std::cout << "Initial Balance: $" << account->getBalance() << std::endl;

     std::vector<std::thread> threads;
 
     // Attempt to withdraw more than the available balance (this will block)
     std::cout << "Attempting to withdraw 100..." << std::endl;
     threads.emplace_back([&] { account->withdraw(100.0); });
 
     // Simulate delay before deposit
     std::this_thread::sleep_for(std::chrono::seconds(2));
 
     // Deposit enough money to unblock the withdrawal
     threads.emplace_back([&] { account->deposit(100.0); });
 
     for (auto& thread : threads)
     {
         thread.join();
     }
 
     std::cout << "Final Balance: $" << account->getBalance() << std::endl;
     return 0;
 }
 