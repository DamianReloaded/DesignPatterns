/**
 * @brief CQRS (Command Query Responsibility Segregation) Pattern Example: Customer Management System
 *
 * **Key Concepts:**
 * 1. **Command**: Responsible for making changes (modifications) to the system.
 * 2. **Query**: Responsible for reading data from the system.
 * 3. **Separation of Concerns**: Commands and Queries are handled by different models, which optimizes performance and scalability.
 *
 * **Benefits:**
 * - Improved scalability: Command operations are optimized for writing, while query operations are optimized for reading.
 * - Separation of responsibilities: Enables a more maintainable and scalable system.
 * - Enhanced performance: Each side (Command and Query) can be optimized independently.
 */

 #include <iostream>
 #include <string>
 #include <vector>
 #include <memory>
 #include <unordered_map>
 
 /**
  * @brief Command interface for modifying customer data.
  */
 class ICommand
 {
 public:
     virtual ~ICommand() = default;
 
     /**
      * @brief Executes the command.
      */
     virtual void execute() = 0;
 };
 
 /**
  * @brief Command to add a new customer.
  */
 class AddCustomerCommand : public ICommand
 {
 public:
     AddCustomerCommand(std::unordered_map<int, std::string>& customers, int id, const std::string& name)
         : m_customers(customers), m_id(id), m_name(name) {}
 
     void execute() override
     {
         m_customers[m_id] = m_name;
         std::cout << "Customer added: " << m_name << " with ID: " << m_id << std::endl;
     }
 
 private:
     std::unordered_map<int, std::string>& m_customers; ///< Customer database.
     int m_id; ///< Customer ID.
     std::string m_name; ///< Customer name.
 };
 
 /**
  * @brief Command to remove a customer.
  */
 class RemoveCustomerCommand : public ICommand
 {
 public:
     RemoveCustomerCommand(std::unordered_map<int, std::string>& customers, int id)
         : m_customers(customers), m_id(id) {}
 
     void execute() override
     {
         auto it = m_customers.find(m_id);
         if (it != m_customers.end())
         {
             std::cout << "Customer removed: " << it->second << " with ID: " << m_id << std::endl;
             m_customers.erase(it);
         }
         else
         {
             std::cout << "Customer with ID: " << m_id << " not found." << std::endl;
         }
     }
 
 private:
     std::unordered_map<int, std::string>& m_customers; ///< Customer database.
     int m_id; ///< Customer ID.
 };
 
 /**
  * @brief Query interface for reading customer data.
  */
 class IQuery
 {
 public:
     virtual ~IQuery() = default;
 
     /**
      * @brief Executes the query.
      */
     virtual void execute() const = 0;
 };
 
 /**
  * @brief Query to retrieve customer details by ID.
  */
 class GetCustomerQuery : public IQuery
 {
 public:
     GetCustomerQuery(const std::unordered_map<int, std::string>& customers, int id)
         : m_customers(customers), m_id(id) {}
 
     void execute() const override
     {
         auto it = m_customers.find(m_id);
         if (it != m_customers.end())
         {
             std::cout << "Customer found: " << it->second << " with ID: " << m_id << std::endl;
         }
         else
         {
             std::cout << "Customer with ID: " << m_id << " not found." << std::endl;
         }
     }
 
 private:
     const std::unordered_map<int, std::string>& m_customers; ///< Customer database.
     int m_id; ///< Customer ID.
 };
 
 /**
  * @brief Manages command and query operations for customer data.
  */
 class CustomerService
 {
 public:
     /**
      * @brief Executes a command to modify customer data.
      * @param command The command to execute.
      */
     void executeCommand(std::shared_ptr<ICommand> command)
     {
         command->execute();
     }
 
     /**
      * @brief Executes a query to retrieve customer data.
      * @param query The query to execute.
      */
     void executeQuery(std::shared_ptr<IQuery> query)
     {
         query->execute();
     }
 
     /**
      * @brief Getter for customers data.
      * @return A reference to the customers map.
      */
     std::unordered_map<int, std::string>& getCustomers()
     {
         return m_customers;
     }
 
 private:
     std::unordered_map<int, std::string> m_customers; ///< Customer database.
 };
 
 /**
  * @brief Demonstrates the CQRS pattern by separating commands and queries in a customer management system.
  */
 int main()
 {
     // Instantiate the customer service
     CustomerService customerService;
 
     // Adding customers via command
     customerService.executeCommand(std::make_shared<AddCustomerCommand>(customerService.getCustomers(), 1, "John Doe"));
     customerService.executeCommand(std::make_shared<AddCustomerCommand>(customerService.getCustomers(), 2, "Jane Smith"));
 
     // Querying customer data
     customerService.executeQuery(std::make_shared<GetCustomerQuery>(customerService.getCustomers(), 1));
     customerService.executeQuery(std::make_shared<GetCustomerQuery>(customerService.getCustomers(), 2));
 
     // Removing a customer via command
     customerService.executeCommand(std::make_shared<RemoveCustomerCommand>(customerService.getCustomers(), 1));
 
     // Querying customer data again
     customerService.executeQuery(std::make_shared<GetCustomerQuery>(customerService.getCustomers(), 1));
     customerService.executeQuery(std::make_shared<GetCustomerQuery>(customerService.getCustomers(), 2));
 
     return 0;
 }
 