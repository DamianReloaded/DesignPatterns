/**
 * @brief Null Object Pattern example in C++23.
 *
 * **Key Concepts:**
 * 1. **Abstract Class (`Shape`)**: Defines the common interface for all concrete objects.
 * 2. **Concrete Objects (`Circle`, `Rectangle`)**: Implement actual behavior of objects.
 * 3. **Null Object (`NullShape`)**: A special object that does nothing, representing the absence of an object.
 *
 * **Benefits:**
 * - Avoids null pointer checks by providing a default object that implements the interface.
 * - Helps avoid errors due to the use of null references or pointers.
 * - Simplifies code by reducing conditional logic for null handling.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 /**
  * @brief Abstract class defining a common interface for shapes.
  */
 class Shape
 {
 public:
     virtual ~Shape() = default;
 
     /**
      * @brief Draws the shape.
      */
     virtual void draw() const = 0;
 };
 
 /**
  * @brief Concrete class representing a Circle.
  */
 class Circle : public Shape
 {
 public:
     /**
      * @brief Draws a Circle.
      */
     void draw() const override
     {
         std::cout << "Drawing a Circle." << std::endl;
     }
 };
 
 /**
  * @brief Concrete class representing a Rectangle.
  */
 class Rectangle : public Shape
 {
 public:
     /**
      * @brief Draws a Rectangle.
      */
     void draw() const override
     {
         std::cout << "Drawing a Rectangle." << std::endl;
     }
 };
 
 /**
  * @brief Null Object class implementing the Shape interface, representing no object.
  */
 class NullShape : public Shape
 {
 public:
     /**
      * @brief Does nothing when draw is called.
      */
     void draw() const override
     {
         // No operation (null behavior)
     }
 };
 
 /**
  * @brief Client code that uses the Shape interface.
  */
 class ShapeClient
 {
 public:
     /**
      * @brief Sets the current shape.
      * @param shape The shape to set.
      */
     void setShape(std::shared_ptr<Shape> shape)
     {
         m_shape = shape;
     }
 
     /**
      * @brief Draws the current shape.
      */
     void drawShape() const
     {
         if (m_shape)
         {
             m_shape->draw();
         }
         else
         {
             std::cout << "No shape to draw." << std::endl;
         }
     }
 
 private:
     std::shared_ptr<Shape> m_shape = std::make_shared<NullShape>();  ///< Default to NullShape (avoiding null checks).
 };
 
 /**
  * @brief Main function demonstrating the use of the Null Object Pattern.
  */
 int main()
 {
     ShapeClient client;
 
     // Draw with NullShape (default)
     client.drawShape();
 
     // Set and draw a Circle
     client.setShape(std::make_shared<Circle>());
     client.drawShape();
 
     // Set and draw a Rectangle
     client.setShape(std::make_shared<Rectangle>());
     client.drawShape();
 
     // Set and draw with NullShape again (after use of real shapes)
     client.setShape(std::make_shared<NullShape>());
     client.drawShape();
 
     return 0;
 }
 