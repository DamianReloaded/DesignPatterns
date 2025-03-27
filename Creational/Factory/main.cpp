/**
 * @brief Factory Pattern Example
 * 
 * The Factory Pattern provides a way to encapsulate the object creation logic. 
 * It allows for creating instances of a class without exposing the exact instantiation logic 
 * to the client. This pattern is useful when you want to manage the creation of objects 
 * without tightly coupling the client to the class's concrete implementation.
 * 
 * Key Concepts:
 * - Encapsulation of object creation logic.
 * - Separation of object construction from client code.
 * - Simplifies object creation when multiple variations exist.
 * 
 * Benefits:
 * - Simplifies the client code by abstracting away object creation.
 * - Allows for flexibility in how objects are created.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 // Abstract Component: A base class for various UI elements
 class Component
 {
 public:
     virtual void render() = 0; ///< Pure virtual method to render the component
     virtual ~Component() = default; ///< Virtual destructor
 };
 
 // Concrete Component: Button
 class Button : public Component
 {
 public:
     void render() override
     {
         std::cout << "Rendering Button" << std::endl;
     }
 };
 
 // Concrete Component: Label
 class Label : public Component
 {
 public:
     void render() override
     {
         std::cout << "Rendering Label" << std::endl;
     }
 };
 
 // Factory: A class that creates components based on certain conditions
 class ComponentFactory
 {
 public:
     /**
      * @brief Creates a component based on the specified type.
      * 
      * This factory method returns a shared pointer to the requested component type.
      * 
      * @param type The type of component to create (e.g., "Button" or "Label").
      * @return A shared pointer to the created component.
      */
     static std::shared_ptr<Component> createComponent(const std::string &type)
     {
         if (type == "Button")
         {
             return std::make_shared<Button>(); ///< Create and return a Button instance
         }
         else if (type == "Label")
         {
             return std::make_shared<Label>(); ///< Create and return a Label instance
         }
         return nullptr; ///< Return nullptr if type is unknown
     }
 };
 
 // Client code using the Factory to create components
 int main()
 {
     // Create a Button using the factory
     auto m_button = ComponentFactory::createComponent("Button");
     if (m_button)
     {
         m_button->render(); ///< Renders the Button
     }
 
     // Create a Label using the factory
     auto m_label = ComponentFactory::createComponent("Label");
     if (m_label)
     {
         m_label->render(); ///< Renders the Label
     }
 
     return 0;
 }
 