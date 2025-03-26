/**
 * @brief Facade pattern example for simplifying complex subsystem interactions.
 *
 * The **Facade** pattern provides a simplified interface to a complex subsystem, 
 * making it easier to use. It hides the complexities of the subsystem and provides 
 * a unified interface for the client.
 *
 * **Key Concepts:**
 * 1. **Facade (`HomeTheaterFacade`)**: The facade class that provides a simplified interface to the subsystem.
 * 2. **Subsystem Classes (`Amplifier`, `DVDPlayer`, `Projector`, `Screen`, `Lights`)**: The individual classes representing components of the subsystem.
 * 3. **Client**: The client interacts with the facade, which simplifies the interactions with the complex subsystem.
 *
 * **How it works:**
 * 1. The `HomeTheaterFacade` class simplifies the process of using a home theater system by hiding the complexity of 
 *    interacting with the individual components (`Amplifier`, `DVDPlayer`, etc.).
 * 2. The client can use the facade to easily control the home theater system without needing to interact directly 
 *    with each individual component.
 */

 #include <iostream>
 #include <memory>
 
 /**
  * @brief Class representing an amplifier in a home theater system.
  *
  * The `Amplifier` class is a subsystem component responsible for amplifying audio signals.
  */
 class Amplifier
 {
 public:
     /**
      * @brief Turn on the amplifier.
      */
     void on() const
     {
         std::cout << "Amplifier is on\n";
     }
 
     /**
      * @brief Turn off the amplifier.
      */
     void off() const
     {
         std::cout << "Amplifier is off\n";
     }
 
     /**
      * @brief Set the volume of the amplifier.
      *
      * @param level The volume level to set.
      */
     void setVolume(int level) const
     {
         std::cout << "Setting amplifier volume to " << level << "\n";
     }
 };
 
 /**
  * @brief Class representing a DVD player in a home theater system.
  *
  * The `DVDPlayer` class is a subsystem component responsible for playing DVDs.
  */
 class DVDPlayer
 {
 public:
     /**
      * @brief Turn on the DVD player.
      */
     void on() const
     {
         std::cout << "DVD Player is on\n";
     }
 
     /**
      * @brief Turn off the DVD player.
      */
     void off() const
     {
         std::cout << "DVD Player is off\n";
     }
 
     /**
      * @brief Play a DVD.
      */
     void play() const
     {
         std::cout << "DVD is playing\n";
     }
 
     /**
      * @brief Stop the DVD player.
      */
     void stop() const
     {
         std::cout << "DVD stopped\n";
     }
 };
 
 /**
  * @brief Class representing a projector in a home theater system.
  *
  * The `Projector` class is a subsystem component responsible for displaying video.
  */
 class Projector
 {
 public:
     /**
      * @brief Turn on the projector.
      */
     void on() const
     {
         std::cout << "Projector is on\n";
     }
 
     /**
      * @brief Turn off the projector.
      */
     void off() const
     {
         std::cout << "Projector is off\n";
     }
 
     /**
      * @brief Set the projector to 16:9 aspect ratio.
      */
     void setAspectRatio16_9() const
     {
         std::cout << "Setting projector aspect ratio to 16:9\n";
     }
 };
 
 /**
  * @brief Class representing a screen in a home theater system.
  *
  * The `Screen` class is a subsystem component responsible for controlling the screen.
  */
 class Screen
 {
 public:
     /**
      * @brief Lower the screen.
      */
     void down() const
     {
         std::cout << "Screen is down\n";
     }
 
     /**
      * @brief Raise the screen.
      */
     void up() const
     {
         std::cout << "Screen is up\n";
     }
 };
 
 /**
  * @brief Class representing the lights in a home theater system.
  *
  * The `Lights` class is a subsystem component responsible for controlling the lights.
  */
 class Lights
 {
 public:
     /**
      * @brief Dim the lights.
      *
      * @param level The level to dim the lights to.
      */
     void dim(int level) const
     {
         std::cout << "Dimming the lights to " << level << "%\n";
     }
 
     /**
      * @brief Turn on the lights.
      */
     void on() const
     {
         std::cout << "Lights are on\n";
     }
 };
 
 /**
  * @brief Facade class that simplifies interaction with the home theater system.
  *
  * The `HomeTheaterFacade` class provides a simplified interface for the client to interact with 
  * the various components of a home theater system, such as the `Amplifier`, `DVDPlayer`, `Projector`, 
  * `Screen`, and `Lights`.
  */
 class HomeTheaterFacade
 {
 public:
     /**
      * @brief Constructor that accepts the subsystem components.
      *
      * @param amplifier A shared pointer to the `Amplifier` object.
      * @param dvdPlayer A shared pointer to the `DVDPlayer` object.
      * @param projector A shared pointer to the `Projector` object.
      * @param screen A shared pointer to the `Screen` object.
      * @param lights A shared pointer to the `Lights` object.
      */
     HomeTheaterFacade(std::shared_ptr<Amplifier> amplifier, 
                       std::shared_ptr<DVDPlayer> dvdPlayer, 
                       std::shared_ptr<Projector> projector, 
                       std::shared_ptr<Screen> screen, 
                       std::shared_ptr<Lights> lights)
         : m_amplifier(amplifier), m_dvdPlayer(dvdPlayer), 
           m_projector(projector), m_screen(screen), m_lights(lights)
     {
     }
 
     /**
      * @brief Prepare the home theater for a movie.
      *
      * This method sets the projector, screen, and lights, and starts playing the DVD.
      */
     void watchMovie() const
     {
         m_lights->dim(10);
         m_screen->down();
         m_projector->on();
         m_projector->setAspectRatio16_9();
         m_amplifier->on();
         m_amplifier->setVolume(5);
         m_dvdPlayer->on();
         m_dvdPlayer->play();
     }
 
     /**
      * @brief End the movie and turn off all components.
      */
     void endMovie() const
     {
         m_lights->on();
         m_screen->up();
         m_projector->off();
         m_amplifier->off();
         m_dvdPlayer->off();
     }
 
 private:
     std::shared_ptr<Amplifier> m_amplifier;  ///< The amplifier component
     std::shared_ptr<DVDPlayer> m_dvdPlayer;  ///< The DVD player component
     std::shared_ptr<Projector> m_projector;  ///< The projector component
     std::shared_ptr<Screen> m_screen;       ///< The screen component
     std::shared_ptr<Lights> m_lights;       ///< The lights component
 };
 
 /**
  * @brief Main function demonstrating the Facade pattern.
  *
  * This function demonstrates how the `HomeTheaterFacade` class simplifies the usage of 
  * a complex home theater system by hiding the interactions with individual components.
  */
 int main()
 {
     // Create the subsystem components
     std::shared_ptr<Amplifier> amplifier = std::make_shared<Amplifier>();
     std::shared_ptr<DVDPlayer> dvdPlayer = std::make_shared<DVDPlayer>();
     std::shared_ptr<Projector> projector = std::make_shared<Projector>();
     std::shared_ptr<Screen> screen = std::make_shared<Screen>();
     std::shared_ptr<Lights> lights = std::make_shared<Lights>();
 
     // Create the facade
     HomeTheaterFacade homeTheater(amplifier, dvdPlayer, projector, screen, lights);
 
     // Watch a movie using the facade
     homeTheater.watchMovie();
 
     // End the movie and turn off everything
     homeTheater.endMovie();
 
     return 0;
 }
 