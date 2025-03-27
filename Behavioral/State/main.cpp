/**
 * @brief State Pattern example for a Game Character's Movement.
 *
 * **Key Concepts:**
 * 1. **State Interface (`MovementState`)** - Defines common behavior for different states.
 * 2. **Concrete States (`IdleState`, `RunningState`)** - Implement specific movement behaviors.
 * 3. **Context (`Character`)** - Maintains the current state and delegates behavior.
 *
 * **Benefits:**
 * - **Encapsulates state-specific behavior** inside separate classes.
 * - **Allows state transitions** without modifying the context class.
 * - **Follows Open/Closed Principle** (new states can be added without modifying `Character`).
 */

 #include <iostream>
 #include <memory>
 
 /**
  * @brief Forward declaration of the Character class to avoid circular dependency.
  */
 class Character;
 
 /**
  * @brief Abstract state interface defining movement behavior.
  */
 class MovementState
 {
 public:
     virtual ~MovementState() = default;
 
     /**
      * @brief Handles movement logic for the current state.
      * @param character Reference to the character.
      */
     virtual void handleMovement(std::shared_ptr<Character> character) = 0;
 
     /**
      * @brief Returns the name of the current state.
      * @return State name as a string.
      */
     virtual std::string getStateName() const = 0;
 };
 
 /**
  * @brief Represents a character that can change movement states.
  */
 class Character : public std::enable_shared_from_this<Character>
 {
 public:
     Character() : m_state(std::make_shared<IdleState>()) {}
 
     /**
      * @brief Sets the character's movement state.
      * @param state The new movement state.
      */
     void setState(std::shared_ptr<MovementState> state)
     {
         m_state = state;
     }
 
     /**
      * @brief Executes movement logic based on the current state.
      */
     void move()
     {
         m_state->handleMovement(shared_from_this());
     }
 
     /**
      * @brief Prints the current state of the character.
      */
     void printState() const
     {
         std::cout << "Character is now: " << m_state->getStateName() << "\n";
     }
 
 private:
     std::shared_ptr<MovementState> m_state; ///< Current movement state.
 
     /**
      * @brief Concrete Idle state.
      */
     class IdleState : public MovementState
     {
     public:
         void handleMovement(std::shared_ptr<Character> character) override
         {
             std::cout << "Character is standing still...\n";
             character->setState(std::make_shared<RunningState>());
         }
 
         std::string getStateName() const override
         {
             return "Idle";
         }
     };
 
     /**
      * @brief Concrete Running state.
      */
     class RunningState : public MovementState
     {
     public:
         void handleMovement(std::shared_ptr<Character> character) override
         {
             std::cout << "Character is running...\n";
             character->setState(std::make_shared<IdleState>());
         }
 
         std::string getStateName() const override
         {
             return "Running";
         }
     };
 };
 
 /**
  * @brief Demonstrates the State Pattern in a game character's movement.
  */
 int main()
 {
     auto player = std::make_shared<Character>();
 
     player->printState();
     player->move(); // Transition to Running
     player->printState();
     player->move(); // Transition back to Idle
     player->printState();
 
     return 0;
 }
 