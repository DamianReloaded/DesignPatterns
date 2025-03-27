/**
 * @brief Domain Event Pattern Example
 *
 * **Key Concepts:**
 * 1. **Domain Event**: Represents a state change in the domain model.
 * 2. **CQRS**: Used in Command Query Responsibility Segregation systems to distinguish between command and query models.
 * 3. **Event-driven Architecture**: The system reacts to events that signify important changes in state.
 *
 * **Benefits:**
 * - Improves system modularity by decoupling the components that handle events from those that change the state.
 * - Enables auditing, logging, and tracking of important changes in the system.
 * - Can be used to trigger other actions or workflows asynchronously.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 #include <string>
 #include <chrono>
 #include <thread>
 #include <functional>
 
 /**
  * @brief Represents a domain event that signifies a state change in the domain.
  */
 class DomainEvent
 {
 public:
     /**
      * @brief Constructs a domain event with a description.
      * @param description A string describing the event.
      */
     DomainEvent(std::string description)
         : m_description(std::move(description)), m_timestamp(std::chrono::system_clock::now())
     {
     }
 
     /**
      * @brief Gets the description of the domain event.
      * @return The event description.
      */
     const std::string &getDescription() const
     {
         return m_description;
     }
 
     /**
      * @brief Gets the timestamp when the event was created.
      * @return The timestamp of the event.
      */
     const std::chrono::system_clock::time_point &getTimestamp() const
     {
         return m_timestamp;
     }
 
 private:
     std::string m_description; ///< Description of the event.
     std::chrono::system_clock::time_point m_timestamp; ///< Time the event was created.
 };
 
 /**
  * @brief Represents an event handler that reacts to domain events.
  */
 class EventHandler
 {
 public:
     /**
      * @brief Handles the domain event by printing the event description.
      * @param event The domain event to handle.
      */
     void handleEvent(const DomainEvent &event)
     {
         std::cout << "Handling event: " << event.getDescription() << " at " 
                   << std::chrono::system_clock::to_time_t(event.getTimestamp()) << std::endl;
     }
 };
 
 /**
  * @brief Represents a domain service that generates domain events.
  */
 class DomainService
 {
 public:
     /**
      * @brief Simulates the occurrence of a state change and triggers a domain event.
      * @param description Description of the state change.
      * @param handler The event handler that processes the event.
      */
     void triggerEvent(const std::string &description, EventHandler &handler)
     {
         DomainEvent event(description);
         handler.handleEvent(event);
     }
 };
 
 /**
  * @brief Main function demonstrating the Domain Event pattern.
  */
 int main()
 {
     EventHandler eventHandler; ///< Event handler that processes domain events.
     DomainService domainService; ///< Domain service that triggers domain events.
 
     // Simulating the occurrence of domain events
     domainService.triggerEvent("User created", eventHandler);
     std::this_thread::sleep_for(std::chrono::seconds(1));
     domainService.triggerEvent("User updated", eventHandler);
     std::this_thread::sleep_for(std::chrono::seconds(1));
     domainService.triggerEvent("User deleted", eventHandler);
 
     return 0;
 }
 