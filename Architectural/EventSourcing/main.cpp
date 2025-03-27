/**
 * @brief Event Sourcing Pattern Example: Banking Transaction System
 *
 * **Key Concepts:**
 * 1. **Event Storage**: Instead of storing the current state, all state changes are recorded as events.
 * 2. **Reconstructing State**: The current state is derived by replaying past events.
 * 3. **Auditable History**: Complete traceability of all changes.
 *
 * **Benefits:**
 * - Provides a complete, immutable history of system state changes.
 * - Enables event replay for debugging, auditing, or rebuilding system state.
 * - Improves traceability and debugging in distributed systems.
 */

 #include <iostream>
 #include <vector>
 #include <memory>
 #include <string>
 
 /**
  * @brief Abstract base class for all transaction events.
  */
 class Event
 {
 public:
     virtual ~Event() = default;
 
     /**
      * @brief Applies the event to reconstruct account state.
      * @param balance Reference to the account balance.
      */
     virtual void apply(int& balance) const = 0;
 
     /**
      * @brief Returns a string representation of the event.
      * @return Event description.
      */
     virtual std::string toString() const = 0;
 };
 
 /**
  * @brief Event representing a deposit transaction.
  */
 class DepositEvent : public Event
 {
 public:
     explicit DepositEvent(int amount) : m_amount(amount) {}
 
     void apply(int& balance) const override
     {
         balance += m_amount;
     }
 
     std::string toString() const override
     {
         return "Deposit: +" + std::to_string(m_amount);
     }
 
 private:
     int m_amount; ///< Amount deposited.
 };
 
 /**
  * @brief Event representing a withdrawal transaction.
  */
 class WithdrawEvent : public Event
 {
 public:
     explicit WithdrawEvent(int amount) : m_amount(amount) {}
 
     void apply(int& balance) const override
     {
         balance -= m_amount;
     }
 
     std::string toString() const override
     {
         return "Withdraw: -" + std::to_string(m_amount);
     }
 
 private:
     int m_amount; ///< Amount withdrawn.
 };
 
 /**
  * @brief Manages the list of transaction events and reconstructs account state.
  */
 class Account
 {
 public:
     /**
      * @brief Adds an event (transaction) to the history.
      * @param event The event to record.
      */
     void addEvent(std::shared_ptr<Event> event)
     {
         m_events.push_back(event);
     }
 
     /**
      * @brief Computes the account balance by replaying all stored events.
      * @return The reconstructed account balance.
      */
     int getBalance() const
     {
         int balance = 0;
         for (const auto& event : m_events)
         {
             event->apply(balance);
         }
         return balance;
     }
 
     /**
      * @brief Displays all recorded transactions.
      */
     void printEventHistory() const
     {
         std::cout << "Transaction History:\n";
         for (const auto& event : m_events)
         {
             std::cout << "  " << event->toString() << std::endl;
         }
     }
 
 private:
     std::vector<std::shared_ptr<Event>> m_events; ///< List of recorded events.
 };
 
 /**
  * @brief Demonstrates the Event Sourcing pattern with a simple banking system.
  */
 int main()
 {
     auto account = std::make_shared<Account>();
 
     account->addEvent(std::make_shared<DepositEvent>(100));
     account->addEvent(std::make_shared<WithdrawEvent>(40));
     account->addEvent(std::make_shared<DepositEvent>(50));
 
     account->printEventHistory();
     std::cout << "Final Balance: " << account->getBalance() << " USD\n";
 
     return 0;
 }
 