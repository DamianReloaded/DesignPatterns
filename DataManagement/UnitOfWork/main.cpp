#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cassert>
#include <unordered_map>
#include <functional>

/**
 * @brief
 * The Unit of Work design pattern manages a set of operations on a data source and ensures that all operations are completed
 * successfully before committing them as a single transaction. It prevents partial updates to the data source, ensuring
 * atomicity and consistency.
 * 
 * Key Concepts:
 * - Unit of Work: Represents a single transaction that handles a series of operations on objects.
 * - Transactional Integrity: Ensures that all changes are committed together, and if an error occurs, all changes can be rolled back.
 * - Data Persistence: The Unit of Work pattern helps in keeping track of data that is being modified, so that these modifications
 *   can be committed or rolled back as part of a single unit.
 * 
 * Benefits:
 * - Atomicity: Changes are committed as a whole, ensuring consistency and preventing partial updates.
 * - Easy Rollback: If an error occurs, all changes can be undone in a single operation.
 * - Centralized Management: Operations are managed in a centralized fashion, reducing the complexity of managing data updates.
 */

class Customer
{
public:
    Customer(int id, const std::string &name) : m_id(id), m_name(name) {}

    /**
     * @brief Gets the customer ID.
     * @return The customer ID.
     */
    int getId() const { return m_id; }

    /**
     * @brief Gets the customer name.
     * @return The customer name.
     */
    std::string getName() const { return m_name; }

    /**
     * @brief Sets the customer name.
     * @param name The new name for the customer.
     */
    void setName(const std::string &name) { m_name = name; }

private:
    int m_id;               ///< Customer ID
    std::string m_name;     ///< Customer Name
};

class IRepository
{
public:
    virtual ~IRepository() = default;

    virtual void add(const std::shared_ptr<Customer> &entity) = 0;
    virtual void update(const std::shared_ptr<Customer> &entity) = 0;
    virtual void remove(const std::shared_ptr<Customer> &entity) = 0;
    virtual void commit() = 0;
    virtual void rollback() = 0;
};

class CustomerRepository : public IRepository
{
public:
    void add(const std::shared_ptr<Customer> &entity) override
    {
        m_customers[entity->getId()] = entity;
        m_rollbackOperations.push_back([this, entity]() {
            m_customers.erase(entity->getId());
            std::cout << "Rollback: Removed customer " << entity->getName() << " (ID: " << entity->getId() << ")\n";
        });
        std::cout << "Added customer: " << entity->getName() << " (ID: " << entity->getId() << ")\n";
    }

    void update(const std::shared_ptr<Customer> &entity) override
    {
        auto it = m_customers.find(entity->getId());
        if (it != m_customers.end())
        {
            int id = entity->getId();
            m_rollbackOperations.push_back([this, id, oldName = it->second->getName()]() {
                m_customers[id]->setName(oldName);
                std::cout << "Rollback: Restored name to " << oldName << " (ID: " << id << ")\n";
            });
            m_customers[it->first]->setName(entity->getName());
            std::cout << "Updated customer name to: " << entity->getName() << " (ID: " << entity->getId() << ")\n";
        }
    }

    void remove(const std::shared_ptr<Customer> &entity) override
    {
        auto it = m_customers.find(entity->getId());
        if (it != m_customers.end())
        {
            m_rollbackOperations.push_back([this, entity]() {
                m_customers[entity->getId()] = entity;
                std::cout << "Rollback: Re-added customer " << entity->getName() << " (ID: " << entity->getId() << ")\n";
            });
            m_customers.erase(entity->getId());
            std::cout << "Removed customer: " << entity->getName() << " (ID: " << entity->getId() << ")\n";
        }
    }

    void commit() override
    {
        std::cout << "Committing changes to the repository...\n";
        // Execute only the commit actions
        for (auto &operation : m_commitOperations)
        {
            operation();
        }
        m_commitOperations.clear();
        std::cout << "Commit successful.\n";
    }

    void rollback() override
    {
        std::cout << "Rolling back changes...\n";
        // Execute only the rollback actions
        for (auto &operation : m_rollbackOperations)
        {
            operation();
        }
        m_rollbackOperations.clear();
        std::cout << "Rollback successful.\n";
    }

private:
    std::unordered_map<int, std::shared_ptr<Customer>> m_customers;
    std::vector<std::function<void()>> m_commitOperations;        ///< Operations to commit
    std::vector<std::function<void()>> m_rollbackOperations;      ///< Operations to rollback
};

class UnitOfWork
{
public:
    void registerRepository(std::shared_ptr<IRepository> repository)
    {
        m_repository = repository;
    }

    void commit()
    {
        m_repository->commit();
    }

    void rollback()
    {
        m_repository->rollback();
    }

private:
    std::shared_ptr<IRepository> m_repository;
};

int main()
{
    // Create a Unit of Work
    UnitOfWork unitOfWork;

    // Create a repository
    auto repository = std::make_shared<CustomerRepository>();

    // Register the repository in the unit of work
    unitOfWork.registerRepository(repository);

    // Create some customers
    auto customer1 = std::make_shared<Customer>(1, "John Doe");
    auto customer2 = std::make_shared<Customer>(2, "Jane Smith");

    // Add, update, and remove customers (simulating a set of operations)
    repository->add(customer1);
    repository->add(customer2);
    customer2->setName("Jane Johnson");
    repository->update(customer2);
    repository->remove(customer1);

    // Now commit or rollback
    // Simulate a successful commit
    unitOfWork.commit();

    // Simulate rolling back changes (uncomment to test rollback)
    // unitOfWork.rollback();

    return 0;
}
