/**
 * @brief Value Object Pattern Example
 *
 * **Key Concepts:**
 * 1. **Value Object**: Represents a concept in the domain with no identity. It is immutable, and equality is determined based on its value.
 * 2. **Immutability**: Once created, the value object cannot be modified. This ensures that its state is consistent.
 * 3. **No Identity**: A value object is distinguished by its attributes rather than a unique identity. 
 *
 * **Benefits:**
 * - Improves consistency by ensuring objects cannot be altered after creation.
 * - Enables better comparison between objects since equality is determined by value, not identity.
 * - Helps avoid errors related to shared mutable state.
 */

 #include <iostream>
 #include <string>
 #include <memory>
 
 /**
  * @brief Represents a Value Object that models a Money concept.
  */
 class Money
 {
 public:
     /**
      * @brief Constructs a Money object with a specific amount and currency.
      * @param amount The amount of money.
      * @param currency The currency in which the amount is specified.
      */
     Money(double amount, const std::string& currency)
         : m_amount(amount), m_currency(currency)
     {
     }
 
     /**
      * @brief Gets the amount of money.
      * @return The amount of money.
      */
     double getAmount() const
     {
         return m_amount;
     }
 
     /**
      * @brief Gets the currency of the money.
      * @return The currency of the money.
      */
     const std::string& getCurrency() const
     {
         return m_currency;
     }
 
     /**
      * @brief Compares two Money objects for equality based on amount and currency.
      * @param other Another Money object.
      * @return True if the two Money objects are equal, false otherwise.
      */
     bool operator==(const Money& other) const
     {
         return m_amount == other.m_amount && m_currency == other.m_currency;
     }
 
     /**
      * @brief Displays the money in a readable format.
      */
     void display() const
     {
         std::cout << m_amount << " " << m_currency << std::endl;
     }
 
 private:
     double m_amount; ///< The amount of money.
     std::string m_currency; ///< The currency of the money.
 };
 
 /**
  * @brief Demonstrates the use of Value Object pattern with Money.
  */
 int main()
 {
     auto money1 = std::make_shared<Money>(100.50, "USD");
     auto money2 = std::make_shared<Money>(100.50, "USD");
     auto money3 = std::make_shared<Money>(200.00, "EUR");
 
     // Display money objects
     money1->display();
     money2->display();
     money3->display();
 
     // Check equality
     if (*money1 == *money2)
     {
         std::cout << "Money1 and Money2 are equal." << std::endl;
     }
     else
     {
         std::cout << "Money1 and Money2 are not equal." << std::endl;
     }
 
     if (*money1 == *money3)
     {
         std::cout << "Money1 and Money3 are equal." << std::endl;
     }
     else
     {
         std::cout << "Money1 and Money3 are not equal." << std::endl;
     }
 
     return 0;
 }
 