/**
 * @brief Visitor Design Pattern Example for Shapes.
 *
 * **Key Concepts:**
 * 1. **Visitor Interface (`ShapeVisitor`)**: Defines a visit method for each type of shape.
 * 2. **Element Interface (`Shape`)**: Defines an accept method that allows the visitor to visit it.
 * 3. **Concrete Elements (`Circle`, `Rectangle`)**: Implement the accept method, which calls the appropriate visit method on the visitor.
 * 4. **Concrete Visitors (`AreaCalculator`, `PerimeterCalculator`)**: Implement the visit methods for specific operations (calculating area and perimeter).
 *
 * **Benefits:**
 * - Separates algorithm (visitor) from the object structure (elements).
 * - Allows adding new operations on shapes without modifying their classes.
 * - Facilitates performing operations on a set of related elements in a clean and extendable way.
 */

#include <iostream>
#include <memory>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
 
 /**
  * @brief Abstract visitor class that declares visit methods for each concrete element.
  */
 class ShapeVisitor
 {
 public:
     virtual ~ShapeVisitor() = default;
 
     /**
      * @brief Visit method for Circle.
      * @param circle The Circle to visit.
      */
     virtual void visit(class Circle& circle) = 0;
 
     /**
      * @brief Visit method for Rectangle.
      * @param rectangle The Rectangle to visit.
      */
     virtual void visit(class Rectangle& rectangle) = 0;
 };
 
 /**
  * @brief Abstract element class that defines the accept method for the visitor.
  */
 class Shape
 {
 public:
     virtual ~Shape() = default;
 
     /**
      * @brief Accept a visitor to perform an operation on this shape.
      * @param visitor The visitor to accept.
      */
     virtual void accept(ShapeVisitor& visitor) = 0;
 };
 
 /**
  * @brief Concrete element class that represents a Circle.
  */
 class Circle : public Shape
 {
 public:
     Circle(double radius) : m_radius(radius) {}
 
     /**
      * @brief Accept a visitor and call its visit method for Circle.
      * @param visitor The visitor to accept.
      */
     void accept(ShapeVisitor& visitor) override
     {
         visitor.visit(*this);
     }
 
     /**
      * @brief Returns the radius of the Circle.
      * @return The radius of the Circle.
      */
     double getRadius() const
     {
         return m_radius;
     }
 
 private:
     double m_radius; ///< The radius of the Circle.
 };
 
 /**
  * @brief Concrete element class that represents a Rectangle.
  */
 class Rectangle : public Shape
 {
 public:
     Rectangle(double width, double height) : m_width(width), m_height(height) {}
 
     /**
      * @brief Accept a visitor and call its visit method for Rectangle.
      * @param visitor The visitor to accept.
      */
     void accept(ShapeVisitor& visitor) override
     {
         visitor.visit(*this);
     }
 
     /**
      * @brief Returns the width of the Rectangle.
      * @return The width of the Rectangle.
      */
     double getWidth() const
     {
         return m_width;
     }
 
     /**
      * @brief Returns the height of the Rectangle.
      * @return The height of the Rectangle.
      */
     double getHeight() const
     {
         return m_height;
     }
 
 private:
     double m_width; ///< The width of the Rectangle.
     double m_height; ///< The height of the Rectangle.
 };
 
 /**
  * @brief Concrete visitor class that calculates the area of shapes.
  */
 class AreaCalculator : public ShapeVisitor
 {
 public:
     /**
      * @brief Visit method for Circle, calculating its area.
      * @param circle The Circle to visit.
      */
     void visit(Circle& circle) override
     {
         double area = M_PI * std::pow(circle.getRadius(), 2);
         std::cout << "Area of Circle: " << area << std::endl;
     }
 
     /**
      * @brief Visit method for Rectangle, calculating its area.
      * @param rectangle The Rectangle to visit.
      */
     void visit(Rectangle& rectangle) override
     {
         double area = rectangle.getWidth() * rectangle.getHeight();
         std::cout << "Area of Rectangle: " << area << std::endl;
     }
 };
 
 /**
  * @brief Concrete visitor class that calculates the perimeter of shapes.
  */
 class PerimeterCalculator : public ShapeVisitor
 {
 public:
     /**
      * @brief Visit method for Circle, calculating its perimeter.
      * @param circle The Circle to visit.
      */
     void visit(Circle& circle) override
     {
         double perimeter = 2 * M_PI * circle.getRadius();
         std::cout << "Perimeter of Circle: " << perimeter << std::endl;
     }
 
     /**
      * @brief Visit method for Rectangle, calculating its perimeter.
      * @param rectangle The Rectangle to visit.
      */
     void visit(Rectangle& rectangle) override
     {
         double perimeter = 2 * (rectangle.getWidth() + rectangle.getHeight());
         std::cout << "Perimeter of Rectangle: " << perimeter << std::endl;
     }
 };
 
 /**
  * @brief Demonstrates the Visitor pattern by calculating the area and perimeter of shapes.
  */
 int main()
 {
     auto circle = std::make_shared<Circle>(5.0);  // Circle with radius 5.0
     auto rectangle = std::make_shared<Rectangle>(4.0, 6.0);  // Rectangle with width 4.0 and height 6.0
 
     AreaCalculator areaCalculator;
     PerimeterCalculator perimeterCalculator;
 
     // Accepting the visitors to calculate area and perimeter
     std::cout << "Calculating Area:" << std::endl;
     circle->accept(areaCalculator);
     rectangle->accept(areaCalculator);
 
     std::cout << std::endl;
 
     std::cout << "Calculating Perimeter:" << std::endl;
     circle->accept(perimeterCalculator);
     rectangle->accept(perimeterCalculator);
 
     return 0;
 }
 