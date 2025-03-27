/**
 * @brief Strategy Pattern example for a Game Character's Attack System.
 *
 * **Key Concepts:**
 * 1. **Strategy Interface (`AttackStrategy`)** - Defines a common interface for attack behaviors.
 * 2. **Concrete Strategies (`MeleeAttack`, `RangedAttack`)** - Implement specific attack types.
 * 3. **Context (`Character`)** - Holds a strategy and delegates attack execution.
 *
 * **Benefits:**
 * - **Encapsulates algorithm variations** inside separate classes.
 * - **Allows dynamic strategy selection** at runtime.
 * - **Follows Open/Closed Principle** (new attack types can be added without modifying `Character`).
 */

 #include <iostream>
 #include <memory>
 
 /**
  * @brief Abstract strategy interface defining attack behavior.
  */
 class AttackStrategy
 {
 public:
     virtual ~AttackStrategy() = default;
 
     /**
      * @brief Executes an attack.
      */
     virtual void attack() const = 0;
 };
 
 /**
  * @brief Concrete strategy for melee attacks.
  */
 class MeleeAttack : public AttackStrategy
 {
 public:
     void attack() const override
     {
         std::cout << "Performs a melee attack with a sword!\n";
     }
 };
 
 /**
  * @brief Concrete strategy for ranged attacks.
  */
 class RangedAttack : public AttackStrategy
 {
 public:
     void attack() const override
     {
         std::cout << "Shoots an arrow from a bow!\n";
     }
 };
 
 /**
  * @brief Represents a game character that can switch attack strategies.
  */
 class Character
 {
 public:
     /**
      * @brief Sets the attack strategy for the character.
      * @param strategy The new attack strategy.
      */
     void setAttackStrategy(std::shared_ptr<AttackStrategy> strategy)
     {
         m_attackStrategy = strategy;
     }
 
     /**
      * @brief Executes the currently set attack strategy.
      */
     void performAttack() const
     {
         if (m_attackStrategy)
         {
             m_attackStrategy->attack();
         }
         else
         {
             std::cout << "No attack strategy set!\n";
         }
     }
 
 private:
     std::shared_ptr<AttackStrategy> m_attackStrategy; ///< Current attack strategy.
 };
 
 /**
  * @brief Demonstrates the Strategy Pattern in a game character's attack system.
  */
 int main()
 {
     auto player = std::make_shared<Character>();
 
     auto melee = std::make_shared<MeleeAttack>();
     auto ranged = std::make_shared<RangedAttack>();
 
     player->setAttackStrategy(melee);
     player->performAttack(); // Melee attack
 
     player->setAttackStrategy(ranged);
     player->performAttack(); // Ranged attack
 
     return 0;
 }
 