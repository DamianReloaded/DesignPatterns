/**
 * @brief Mediator Pattern example for a Chatroom system.
 *
 * **Key Concepts:**
 * 1. **Mediator Interface (`ChatMediator`)**: Defines communication rules between participants.
 * 2. **Concrete Mediator (`Chatroom`)**: Handles message passing between users.
 * 3. **Colleagues (`User`)**: Participants who communicate through the mediator.
 *
 * **Benefits:**
 * - Decouples communication logic from individual objects.
 * - Centralizes communication to simplify object interaction.
 * - Makes it easier to modify communication rules without changing participants.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <vector>
 #include <unordered_map>
 
 /**
  * @brief Forward declaration of User.
  */
 class User;
 
 /**
  * @brief Interface for chatroom mediators.
  */
 class ChatMediator
 {
 public:
     virtual ~ChatMediator() = default;
 
     /**
      * @brief Registers a user in the chatroom.
      * @param user The user to register.
      */
     virtual void registerUser(std::shared_ptr<User> user) = 0;
 
     /**
      * @brief Sends a message from one user to all others.
      * @param sender The user sending the message.
      * @param message The message to send.
      */
     virtual void sendMessage(const std::string& sender, const std::string& message) = 0;
 };
 
 /**
  * @brief Represents a user in the chatroom.
  */
 class User
 {
 public:
     User(std::string name, std::shared_ptr<ChatMediator> mediator)
         : m_name(std::move(name)), m_mediator(std::move(mediator)) {}
 
     /**
      * @brief Sends a message through the mediator.
      * @param message The message content.
      */
     void send(const std::string& message)
     {
         m_mediator->sendMessage(m_name, message);
     }
 
     /**
      * @brief Receives a message from the chatroom.
      * @param sender The name of the sender.
      * @param message The message content.
      */
     void receive(const std::string& sender, const std::string& message)
     {
         std::cout << "[" << m_name << "] received from " << sender << ": " << message << "\n";
     }
 
     /**
      * @brief Gets the user's name.
      * @return The user's name.
      */
     std::string getName() const
     {
         return m_name;
     }
 
 private:
     std::string m_name; ///< The name of the user.
     std::shared_ptr<ChatMediator> m_mediator; ///< Mediator for communication.
 };
 
 /**
  * @brief Concrete mediator implementing a chatroom.
  */
 class Chatroom : public ChatMediator
 {
 public:
     /**
      * @brief Registers a user in the chatroom.
      * @param user The user to register.
      */
     void registerUser(std::shared_ptr<User> user) override
     {
         m_users[user->getName()] = user;
     }
 
     /**
      * @brief Sends a message from one user to all others.
      * @param sender The user sending the message.
      * @param message The message to send.
      */
     void sendMessage(const std::string& sender, const std::string& message) override
     {
         for (auto& [name, user] : m_users)
         {
             if (name != sender)
             {
                 user->receive(sender, message);
             }
         }
     }
 
 private:
     std::unordered_map<std::string, std::shared_ptr<User>> m_users; ///< Registered users.
 };
 
 /**
  * @brief Demonstrates the chatroom system using the Mediator Pattern.
  */
 int main()
 {
     auto chatroom = std::make_shared<Chatroom>();
 
     auto alice = std::make_shared<User>("Alice", chatroom);
     auto bob = std::make_shared<User>("Bob", chatroom);
     auto charlie = std::make_shared<User>("Charlie", chatroom);
 
     chatroom->registerUser(alice);
     chatroom->registerUser(bob);
     chatroom->registerUser(charlie);
 
     alice->send("Hello, everyone!");
     bob->send("Hey Alice!");
     charlie->send("Hi all!");
 
     return 0;
 }
 