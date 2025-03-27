/**
 * @brief Event-Driven Architecture Example: Demonstrates the concept of systems reacting to events.
 *
 * **Key Concepts:**
 * 1. **Event**: An occurrence or change in state that triggers a reaction in the system.
 * 2. **Event Publisher**: The component that generates and broadcasts events.
 * 3. **Event Listener**: The component that reacts to specific events.
 * 4. **Loose Coupling**: Event-driven systems allow components to be decoupled, with each component focusing on specific actions rather than direct interactions.
 *
 * **Benefits:**
 * - Promotes asynchronous communication between components.
 * - Components can be added or modified independently, improving scalability and maintainability.
 * - Enables real-time processing of events, such as in message queues, real-time analytics, or notifications.
 */

 #include <iostream>
 #include <vector>
 #include <memory>
 #include <functional>
 #include <string>
 
 /**
  * @brief Event class represents an event in the system.
  *        This serves as a base class for specific event types.
  */
 class Event
 {
 public:
     virtual ~Event() = default;
 
     /**
      * @brief Retrieves the type of event.
      * @return A string representing the event type.
      */
     virtual std::string getEventType() const = 0;
 };
 
 /**
  * @brief A specific event that occurs when a user logs in.
  */
 class UserLoginEvent : public Event
 {
 public:
     /**
      * @brief Constructor for UserLoginEvent.
      * @param username The username of the user who logged in.
      */
     UserLoginEvent(const std::string& username)
         : m_username(username)
     {
     }
 
     /**
      * @brief Retrieves the event type.
      * @return A string representing the event type.
      */
     std::string getEventType() const override
     {
         return "UserLoginEvent";
     }
 
     /**
      * @brief Retrieves the username.
      * @return The username of the logged-in user.
      */
     std::string getUsername() const
     {
         return m_username;
     }
 
 private:
     std::string m_username; ///< The username of the user who logged in.
 };
 
 /**
  * @brief A listener that reacts to events.
  */
 class EventListener
 {
 public:
     virtual ~EventListener() = default;
 
     /**
      * @brief Handles an event when it occurs.
      * @param event The event to handle.
      */
     virtual void onEvent(const std::shared_ptr<Event>& event) = 0;
 };
 
 /**
  * @brief A specific listener that reacts to user login events.
  */
 class UserLoginListener : public EventListener
 {
 public:
     /**
      * @brief Handles a user login event.
      * @param event The event to handle.
      */
     void onEvent(const std::shared_ptr<Event>& event) override
     {
         // Check if the event is a UserLoginEvent.
         auto loginEvent = std::dynamic_pointer_cast<UserLoginEvent>(event);
         if (loginEvent)
         {
             std::cout << "User logged in: " << loginEvent->getUsername() << std::endl;
         }
     }
 };
 
 /**
  * @brief EventPublisher publishes events to listeners.
  */
 class EventPublisher
 {
 public:
     /**
      * @brief Adds a listener to the list of listeners.
      * @param listener The listener to add.
      */
     void addListener(const std::shared_ptr<EventListener>& listener)
     {
         m_listeners.push_back(listener);
     }
 
     /**
      * @brief Publishes an event to all listeners.
      * @param event The event to publish.
      */
     void publishEvent(const std::shared_ptr<Event>& event)
     {
         for (const auto& listener : m_listeners)
         {
             listener->onEvent(event);
         }
     }
 
 private:
     std::vector<std::shared_ptr<EventListener>> m_listeners; ///< List of listeners to notify.
 };
 
 /**
  * @brief Demonstrates an event-driven system with an event publisher, event listener, and event handling.
  */
 int main()
 {
     // Create an event publisher and a listener.
     EventPublisher eventPublisher;
     auto userLoginListener = std::make_shared<UserLoginListener>();
     eventPublisher.addListener(userLoginListener);
 
     // Create a user login event.
     auto loginEvent = std::make_shared<UserLoginEvent>("john_doe");
 
     // Publish the event, triggering the listener to handle it.
     eventPublisher.publishEvent(loginEvent);
 
     return 0;
 }
 