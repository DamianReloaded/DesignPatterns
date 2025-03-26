/**
 * @brief Abstract Factory pattern example.
 *
 * **Key Concepts:**
 * 1. **Abstract Product Interfaces**: Defines a set of related products that the factory will create. In this case, `Button` and `Checkbox` are abstract interfaces for GUI components.
 * 2. **Concrete Product Classes**: Implements the concrete classes for each product, such as `WinButton`, `MacButton`, `WinCheckbox`, and `MacCheckbox`.
 * 3. **Abstract Factory Interface**: Declares methods for creating abstract products. The `GUIFactory` is the abstract factory that defines the interface for creating buttons and checkboxes.
 * 4. **Concrete Factory Classes**: Implements the abstract factory interface for specific platforms. `WinFactory` creates Windows-specific products, while `MacFactory` creates Mac-specific products.
 * 5. **Client Code**: Uses the factory pattern to create platform-specific UI elements (buttons and checkboxes) and render them. The client code remains agnostic to the specific platform and interacts with the abstract interfaces.
 *
 * **New C++23 Features (Used Here):**
 * - **`std::ranges`**: Although not directly applied in a complex way in this example, it could be used to apply operations over ranges of products or components.
 * - **`std::span`**: Would be useful when handling fixed-size arrays of products or components, though we simulate platform detection and factory creation here.
 *
 * **How it works:**
 * - The abstract factory `GUIFactory` provides methods to create abstract products (buttons and checkboxes).
 * - `WinFactory` and `MacFactory` are concrete factories that implement these methods and create platform-specific products.
 * - The client code interacts with the abstract factory and its products without needing to know which platform the products are from.
 * - This allows for easy extension if new platforms are added, as the client code remains unchanged while new concrete factories are created.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <vector>
 #include <ranges>   // C++23 feature
 #include <span>     // C++23 feature
 
 /**
  * @brief Abstract class for buttons.
  *
  * The `Button` class defines the interface for button objects in the GUI. It declares
  * the `render` method which will be implemented by concrete button classes.
  */
 class Button
 {
 public:
     /**
      * @brief Render the button.
      * 
      * This method is responsible for rendering the button. It will be overridden by concrete button classes.
      */
     virtual void render() const = 0;
 
     virtual ~Button() = default; ///< Virtual destructor for proper cleanup of derived objects
 };
 
 /**
  * @brief Abstract class for checkboxes.
  *
  * The `Checkbox` class defines the interface for checkbox objects in the GUI. It declares
  * the `render` method which will be implemented by concrete checkbox classes.
  */
 class Checkbox
 {
 public:
     /**
      * @brief Render the checkbox.
      * 
      * This method is responsible for rendering the checkbox. It will be overridden by concrete checkbox classes.
      */
     virtual void render() const = 0;
 
     virtual ~Checkbox() = default; ///< Virtual destructor for proper cleanup of derived objects
 };
 
 /**
  * @brief Concrete class for a Windows-specific button.
  *
  * The `WinButton` class implements the `Button` interface and provides the Windows-specific
  * rendering logic for a button.
  */
 class WinButton : public Button
 {
 public:
     /**
      * @brief Render a Windows button.
      * 
      * This method overrides the `render` method to provide a Windows-specific button rendering.
      */
     void render() const override
     {
         std::cout << "Rendering Windows button\n";
     }
 };
 
 /**
  * @brief Concrete class for a Mac-specific button.
  *
  * The `MacButton` class implements the `Button` interface and provides the Mac-specific
  * rendering logic for a button.
  */
 class MacButton : public Button
 {
 public:
     /**
      * @brief Render a Mac button.
      * 
      * This method overrides the `render` method to provide a Mac-specific button rendering.
      */
     void render() const override
     {
         std::cout << "Rendering Mac button\n";
     }
 };
 
 /**
  * @brief Concrete class for a Windows-specific checkbox.
  *
  * The `WinCheckbox` class implements the `Checkbox` interface and provides the Windows-specific
  * rendering logic for a checkbox.
  */
 class WinCheckbox : public Checkbox
 {
 public:
     /**
      * @brief Render a Windows checkbox.
      * 
      * This method overrides the `render` method to provide a Windows-specific checkbox rendering.
      */
     void render() const override
     {
         std::cout << "Rendering Windows checkbox\n";
     }
 };
 
 /**
  * @brief Concrete class for a Mac-specific checkbox.
  *
  * The `MacCheckbox` class implements the `Checkbox` interface and provides the Mac-specific
  * rendering logic for a checkbox.
  */
 class MacCheckbox : public Checkbox
 {
 public:
     /**
      * @brief Render a Mac checkbox.
      * 
      * This method overrides the `render` method to provide a Mac-specific checkbox rendering.
      */
     void render() const override
     {
         std::cout << "Rendering Mac checkbox\n";
     }
 };
 
 /**
  * @brief Abstract factory interface for creating GUI components.
  *
  * The `GUIFactory` class declares methods to create abstract products: buttons and checkboxes.
  */
 class GUIFactory
 {
 public:
     /**
      * @brief Create a button.
      * 
      * This method is responsible for creating platform-specific buttons. The actual button creation
      * is delegated to the concrete factories.
      * 
      * @return A unique pointer to a `Button` object.
      */
     virtual std::unique_ptr<Button> createButton() const = 0;
 
     /**
      * @brief Create a checkbox.
      * 
      * This method is responsible for creating platform-specific checkboxes. The actual checkbox creation
      * is delegated to the concrete factories.
      * 
      * @return A unique pointer to a `Checkbox` object.
      */
     virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
 
     virtual ~GUIFactory() = default; ///< Virtual destructor for proper cleanup of derived factories
 };
 
 /**
  * @brief Concrete factory for creating Windows-specific GUI components.
  *
  * The `WinFactory` class implements the `GUIFactory` interface and creates Windows-specific buttons
  * and checkboxes.
  */
 class WinFactory : public GUIFactory
 {
 public:
     /**
      * @brief Create a Windows button.
      * 
      * This method overrides the `createButton` method to return a Windows-specific `WinButton` object.
      * 
      * @return A unique pointer to a `WinButton` object.
      */
     std::unique_ptr<Button> createButton() const override
     {
         return std::make_unique<WinButton>();
     }
 
     /**
      * @brief Create a Windows checkbox.
      * 
      * This method overrides the `createCheckbox` method to return a Windows-specific `WinCheckbox` object.
      * 
      * @return A unique pointer to a `WinCheckbox` object.
      */
     std::unique_ptr<Checkbox> createCheckbox() const override
     {
         return std::make_unique<WinCheckbox>();
     }
 };
 
 /**
  * @brief Concrete factory for creating Mac-specific GUI components.
  *
  * The `MacFactory` class implements the `GUIFactory` interface and creates Mac-specific buttons
  * and checkboxes.
  */
 class MacFactory : public GUIFactory
 {
 public:
     /**
      * @brief Create a Mac button.
      * 
      * This method overrides the `createButton` method to return a Mac-specific `MacButton` object.
      * 
      * @return A unique pointer to a `MacButton` object.
      */
     std::unique_ptr<Button> createButton() const override
     {
         return std::make_unique<MacButton>();
     }
 
     /**
      * @brief Create a Mac checkbox.
      * 
      * This method overrides the `createCheckbox` method to return a Mac-specific `MacCheckbox` object.
      * 
      * @return A unique pointer to a `MacCheckbox` object.
      */
     std::unique_ptr<Checkbox> createCheckbox() const override
     {
         return std::make_unique<MacCheckbox>();
     }
 };
 
 /**
  * @brief Render the UI using the provided factory.
  *
  * This function accepts a `GUIFactory` object and uses it to create and render platform-specific
  * buttons and checkboxes.
  * 
  * @param factory The factory used to create the GUI components.
  */
 void renderUI(const GUIFactory& factory)
 {
     auto button = factory.createButton();
     auto checkbox = factory.createCheckbox();
 
     button->render();
     checkbox->render();
 }
 
 /**
  * @brief Create and render UI using multiple factories with `std::span`.
  *
  * This function demonstrates how to use `std::span` to handle a collection of factories and render
  * the UI using all the available factories.
  * 
  * @param factories A span containing the list of factories to be used.
  */
 void createAndRenderUI(const std::span<const std::unique_ptr<GUIFactory>>& factories)
 {
     for (const auto& factory : factories)
     {
         renderUI(*factory);
     }
 }
 
 /**
  * @brief Main function to demonstrate the Abstract Factory pattern.
  *
  * This function simulates platform detection and creates appropriate factories to generate platform-specific
  * GUI components (buttons and checkboxes). It also demonstrates the use of `std::span` to handle multiple factories.
  */
 int main()
 {
     // Using factory based on platform choice
     bool isWindows = true; // Simulate platform detection
 
     std::unique_ptr<GUIFactory> factory;
     if (isWindows)
     {
         factory = std::make_unique<WinFactory>();
     }
     else
     {
         factory = std::make_unique<MacFactory>();
     }
 
     renderUI(*factory);
 
     // C++23 Example with std::span (Handling multiple factories)
     std::vector<std::unique_ptr<GUIFactory>> factoryList;
     factoryList.push_back(std::make_unique<WinFactory>());
     factoryList.push_back(std::make_unique<MacFactory>());
     
     std::span<const std::unique_ptr<GUIFactory>> factorySpan(factoryList);
     createAndRenderUI(factorySpan);
     
     return 0;
 }
 