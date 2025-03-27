/**
 * @brief Abstract Factory Pattern Example
 * 
 * The Abstract Factory Pattern provides an interface for creating families of related or 
 * dependent objects without specifying their concrete classes. This pattern allows clients 
 * to work with abstract classes, instead of the concrete class implementations, 
 * which promotes loose coupling.
 * 
 * Key Concepts:
 * - Defines an interface for creating related objects.
 * - Allows clients to work with abstract interfaces rather than concrete implementations.
 * - Helps manage complex object creation by organizing it into families of products.
 * 
 * Benefits:
 * - Provides flexibility to change the concrete classes of the products.
 * - Enhances maintainability by abstracting object creation.
 * - Allows for easy extension by adding new products without affecting client code.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 // Abstract Product: A family of related products
 class Button
 {
 public:
     virtual void render() = 0; ///< Pure virtual method to render the button
     virtual ~Button() = default; ///< Virtual destructor
 };
 
 class Label
 {
 public:
     virtual void render() = 0; ///< Pure virtual method to render the label
     virtual ~Label() = default; ///< Virtual destructor
 };
 
 // Concrete Product A1
 class WindowsButton : public Button
 {
 public:
     void render() override
     {
         std::cout << "Rendering Windows Button" << std::endl;
     }
 };
 
 // Concrete Product A2
 class LinuxButton : public Button
 {
 public:
     void render() override
     {
         std::cout << "Rendering Linux Button" << std::endl;
     }
 };
 
 // Concrete Product B1
 class WindowsLabel : public Label
 {
 public:
     void render() override
     {
         std::cout << "Rendering Windows Label" << std::endl;
     }
 };
 
 // Concrete Product B2
 class LinuxLabel : public Label
 {
 public:
     void render() override
     {
         std::cout << "Rendering Linux Label" << std::endl;
     }
 };
 
 // Abstract Factory: Defines an interface for creating related products
 class GUIFactory
 {
 public:
     virtual std::shared_ptr<Button> createButton() = 0; ///< Pure virtual method to create a button
     virtual std::shared_ptr<Label> createLabel() = 0; ///< Pure virtual method to create a label
     virtual ~GUIFactory() = default; ///< Virtual destructor
 };
 
 // Concrete Factory 1
 class WindowsFactory : public GUIFactory
 {
 public:
     std::shared_ptr<Button> createButton() override
     {
         return std::make_shared<WindowsButton>(); ///< Create Windows button
     }
 
     std::shared_ptr<Label> createLabel() override
     {
         return std::make_shared<WindowsLabel>(); ///< Create Windows label
     }
 };
 
 // Concrete Factory 2
 class LinuxFactory : public GUIFactory
 {
 public:
     std::shared_ptr<Button> createButton() override
     {
         return std::make_shared<LinuxButton>(); ///< Create Linux button
     }
 
     std::shared_ptr<Label> createLabel() override
     {
         return std::make_shared<LinuxLabel>(); ///< Create Linux label
     }
 };
 
 // Client code that uses the abstract factory to get products
 int main()
 {
     // Choose the factory based on the operating system (this can be dynamic at runtime)
     std::shared_ptr<GUIFactory> m_factory;
 
     std::string os = "Windows"; // Assume the OS is Windows for this example
 
     if (os == "Windows")
     {
         m_factory = std::make_shared<WindowsFactory>(); ///< Use Windows factory
     }
     else
     {
         m_factory = std::make_shared<LinuxFactory>(); ///< Use Linux factory
     }
 
     // Create a button and a label using the factory
     auto m_button = m_factory->createButton();
     auto m_label = m_factory->createLabel();
 
     // Render the button and label
     m_button->render();
     m_label->render();
 
     return 0;
 }
 