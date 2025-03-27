/**
 * @brief Observer Pattern example for a Game Event System.
 *
 * **Key Concepts:**
 * 1. **Subject (`GameEvent`)** - Maintains a list of observers and notifies them of changes.
 * 2. **Observer Interface (`GameObserver`)** - Defines an interface for objects that need updates.
 * 3. **Concrete Observers (`HUD`, `Logger`)** - React to game events, such as player health updates.
 *
 * **Benefits:**
 * - **Decouples** event producers from consumers.
 * - Supports **multiple independent observers** reacting to the same event.
 * - Easily **extendable** (new observers can be added without modifying existing code).
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 
 /**
  * @brief Observer interface for game events.
  */
 class GameObserver
 {
 public:
     virtual ~GameObserver() = default;
     virtual void onHealthChanged(int health) = 0;
 };
 
 /**
  * @brief Represents a player that notifies observers of health changes.
  */
 class GameEvent
 {
 public:
     /**
      * @brief Registers an observer.
      * @param observer The observer to add.
      */
     void addObserver(std::shared_ptr<GameObserver> observer)
     {
         m_observers.push_back(observer);
     }
 
     /**
      * @brief Sets player health and notifies observers.
      * @param health The new health value.
      */
     void setHealth(int health)
     {
         m_health = health;
         notifyObservers();
     }
 
 private:
     int m_health{100}; ///< Player's health.
     std::vector<std::shared_ptr<GameObserver>> m_observers; ///< List of observers.
 
     /**
      * @brief Notifies all observers of a health change.
      */
     void notifyObservers()
     {
         for (auto& observer : m_observers)
         {
             observer->onHealthChanged(m_health);
         }
     }
 };
 
 /**
  * @brief Displays player's health on the HUD.
  */
 class HUD : public GameObserver
 {
 public:
     void onHealthChanged(int health) override
     {
         std::cout << "[HUD] Player Health: " << health << "\n";
     }
 };
 
 /**
  * @brief Logs player's health changes.
  */
 class Logger : public GameObserver
 {
 public:
     void onHealthChanged(int health) override
     {
         std::cout << "[Logger] Health changed to: " << health << "\n";
     }
 };
 
 /**
  * @brief Demonstrates the Game Event System using the Observer Pattern.
  */
 int main()
 {
     auto player = std::make_shared<GameEvent>();
     auto hud = std::make_shared<HUD>();
     auto logger = std::make_shared<Logger>();
 
     // Register observers
     player->addObserver(hud);
     player->addObserver(logger);
 
     // Simulated health changes
     player->setHealth(90);
     player->setHealth(75);
     player->setHealth(50);
 
     return 0;
 }
 