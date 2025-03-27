/**
 * @brief Command Pattern example for a Game Input System.
 *
 * **Key Concepts:**
 * 1. **Command Interface (`GameCommand`)** - Defines an interface for executing actions.
 * 2. **Concrete Commands (`JumpCommand`, `ShootCommand`, `CrouchCommand`)** - Implement specific player actions.
 * 3. **Receiver (`Player`)** - The game entity that performs actions.
 * 4. **Invoker (`InputHandler`)** - Maps keys to commands and executes them.
 *
 * **Benefits:**
 * - **Decouples** input handling from game logic.
 * - Allows **dynamic keybinding** without modifying core logic.
 * - Supports **macro recording and replays**.
 */

 #include <iostream>
 #include <memory>
 #include <unordered_map>
 
 /**
  * @brief Represents a player that can perform actions.
  */
 class Player
 {
 public:
     void jump() const
     {
         std::cout << "Player jumps!\n";
     }
 
     void shoot() const
     {
         std::cout << "Player shoots!\n";
     }
 
     void crouch() const
     {
         std::cout << "Player crouches!\n";
     }
 };
 
 /**
  * @brief Abstract command interface for game actions.
  */
 class GameCommand
 {
 public:
     virtual ~GameCommand() = default;
     virtual void execute() = 0;
 };
 
 /**
  * @brief Command for making the player jump.
  */
 class JumpCommand : public GameCommand
 {
 public:
     explicit JumpCommand(std::shared_ptr<Player> player) : m_player(player) {}
 
     void execute() override
     {
         m_player->jump();
     }
 
 private:
     std::shared_ptr<Player> m_player; ///< Reference to the player.
 };
 
 /**
  * @brief Command for making the player shoot.
  */
 class ShootCommand : public GameCommand
 {
 public:
     explicit ShootCommand(std::shared_ptr<Player> player) : m_player(player) {}
 
     void execute() override
     {
         m_player->shoot();
     }
 
 private:
     std::shared_ptr<Player> m_player; ///< Reference to the player.
 };
 
 /**
  * @brief Command for making the player crouch.
  */
 class CrouchCommand : public GameCommand
 {
 public:
     explicit CrouchCommand(std::shared_ptr<Player> player) : m_player(player) {}
 
     void execute() override
     {
         m_player->crouch();
     }
 
 private:
     std::shared_ptr<Player> m_player; ///< Reference to the player.
 };
 
 /**
  * @brief Handles player input and executes mapped commands.
  */
 class InputHandler
 {
 public:
     /**
      * @brief Binds a key to a command.
      * @param key The input key.
      * @param command The command to execute.
      */
     void bindCommand(char key, std::shared_ptr<GameCommand> command)
     {
         m_keyBindings[key] = command;
     }
 
     /**
      * @brief Executes the command mapped to the given key.
      * @param key The input key.
      */
     void handleInput(char key)
     {
         if (m_keyBindings.contains(key))
         {
             m_keyBindings[key]->execute();
         }
         else
         {
             std::cout << "No action bound to key: " << key << "\n";
         }
     }
 
 private:
     std::unordered_map<char, std::shared_ptr<GameCommand>> m_keyBindings; ///< Maps keys to commands.
 };
 
 /**
  * @brief Demonstrates the Game Input System using the Command Pattern.
  */
 int main()
 {
     auto player = std::make_shared<Player>();
     auto inputHandler = std::make_shared<InputHandler>();
 
     // Bind keys to commands
     inputHandler->bindCommand('w', std::make_shared<JumpCommand>(player));
     inputHandler->bindCommand('s', std::make_shared<CrouchCommand>(player));
     inputHandler->bindCommand('f', std::make_shared<ShootCommand>(player));
 
     // Simulated user input
     std::cout << "Press 'w' to Jump, 's' to Crouch, 'f' to Shoot, 'x' for an unbound key.\n";
     for (char input : {'w', 's', 'f', 'x'})  // Example key presses
     {
         inputHandler->handleInput(input);
     }
 
     return 0;
 }
 