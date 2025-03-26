/**
 * @brief Flyweight pattern example for managing a large number of objects efficiently.
 *
 * The **Flyweight** pattern is used to reduce the memory usage by sharing common parts of 
 * the state between multiple objects. Instead of creating many objects that share common data, 
 * the shared data is stored in a central place, and the individual objects hold references to it.
 *
 * **Key Concepts:**
 * 1. **Flyweight (`Shape`)**: The shared object that stores the common state.
 * 2. **Concrete Flyweight (`Circle`, `Rectangle`)**: Concrete implementations of the Flyweight that store intrinsic data.
 * 3. **Flyweight Factory (`ShapeFactory`)**: The factory that ensures sharing of Flyweight objects.
 * 4. **Client**: The client uses the factory to get shared objects and works with them.
 *
 * **How it works:**
 * 1. The `ShapeFactory` manages the creation and sharing of `Shape` objects.
 * 2. The `Shape` class contains the shared data that is common across all objects.
 * 3. The `Circle` and `Rectangle` classes are concrete flyweights that store only the unique data for each shape (extrinsic data).
 * 4. The client uses the factory to get the shared `Shape` objects and adds unique data as needed.
 */

 #include <iostream>
 #include <memory>
 #include <unordered_map>
 #include <string>
 
 /**
  * @brief Abstract class representing a Shape.
  *
  * The `Shape` class defines the interface for the Flyweight objects. It stores shared data and 
  * provides the common interface for concrete flyweights like `Circle` and `Rectangle`.
  */
 class Shape
 {
 public:
     /**
      * @brief Virtual destructor for the Shape class.
      */
     virtual ~Shape() = default;
 
     /**
      * @brief Draw the shape.
      *
      * Concrete flyweights must implement this method to draw the shape.
      */
     virtual void draw() const = 0;
 
     /**
      * @brief Set the position of the shape.
      *
      * @param x The x-coordinate of the shape.
      * @param y The y-coordinate of the shape.
      */
     void setPosition(int x, int y)
     {
         m_x = x;
         m_y = y;
     }
 
 protected:
     int m_x{0};  ///< The x-coordinate of the shape.
     int m_y{0};  ///< The y-coordinate of the shape.
 };
 
 /**
  * @brief Concrete Flyweight class representing a Circle.
  *
  * The `Circle` class stores the intrinsic data common to all circles (i.e., the color) and 
  * can have different extrinsic data like the position.
  */
 class Circle : public Shape
 {
 public:
     /**
      * @brief Constructor that initializes the color of the circle.
      *
      * @param color The color of the circle.
      */
     Circle(const std::string& color) : m_color(color) {}
 
     /**
      * @brief Draw the circle.
      */
     void draw() const override
     {
         std::cout << "Drawing Circle with color " << m_color 
                   << " at position (" << m_x << ", " << m_y << ")\n";
     }
 
 private:
     std::string m_color;  ///< The color of the circle (intrinsic data).
 };
 
 /**
  * @brief Concrete Flyweight class representing a Rectangle.
  *
  * The `Rectangle` class stores the intrinsic data common to all rectangles (i.e., the color) and 
  * can have different extrinsic data like the position.
  */
 class Rectangle : public Shape
 {
 public:
     /**
      * @brief Constructor that initializes the color of the rectangle.
      *
      * @param color The color of the rectangle.
      */
     Rectangle(const std::string& color) : m_color(color) {}
 
     /**
      * @brief Draw the rectangle.
      */
     void draw() const override
     {
         std::cout << "Drawing Rectangle with color " << m_color 
                   << " at position (" << m_x << ", " << m_y << ")\n";
     }
 
 private:
     std::string m_color;  ///< The color of the rectangle (intrinsic data).
 };
 
 /**
  * @brief Flyweight Factory class that manages shared Flyweight objects.
  *
  * The `ShapeFactory` class is responsible for creating and managing the shared flyweights.
  * It ensures that the same flyweight object is shared across multiple requests with the same intrinsic data.
  */
 class ShapeFactory
 {
 public:
     /**
      * @brief Get a shared Circle or Rectangle based on the color.
      *
      * If a shape with the given color already exists, it returns the existing one. 
      * Otherwise, it creates a new one.
      *
      * @param shapeType The type of shape ("Circle" or "Rectangle").
      * @param color The color of the shape.
      * @return A shared pointer to the Shape object.
      */
     std::shared_ptr<Shape> getShape(const std::string& shapeType, const std::string& color)
     {
         std::string key = shapeType + "_" + color;
         if (m_shapes.find(key) == m_shapes.end())
         {
             if (shapeType == "Circle")
             {
                 m_shapes[key] = std::make_shared<Circle>(color);
             }
             else if (shapeType == "Rectangle")
             {
                 m_shapes[key] = std::make_shared<Rectangle>(color);
             }
         }
         return m_shapes[key];
     }
 
 private:
     std::unordered_map<std::string, std::shared_ptr<Shape>> m_shapes;  ///< A map to store shared Flyweight objects.
 };
 
 /**
  * @brief Main function demonstrating the Flyweight pattern.
  *
  * This function demonstrates how the `ShapeFactory` class can be used to manage the creation
  * and sharing of Flyweight objects, such as `Circle` and `Rectangle`.
  */
 int main()
 {
     // Create the Flyweight Factory
     ShapeFactory shapeFactory;
 
     // Get shared shapes from the factory
     auto redCircle1 = shapeFactory.getShape("Circle", "Red");
     auto redCircle2 = shapeFactory.getShape("Circle", "Red");
     auto blueRectangle = shapeFactory.getShape("Rectangle", "Blue");
 
     // Set positions for each shape (extrinsic data)
     redCircle1->setPosition(1, 2);
     redCircle2->setPosition(3, 4);
     blueRectangle->setPosition(5, 6);
 
     // Draw the shapes
     redCircle1->draw();
     redCircle2->draw();
     blueRectangle->draw();
 
     // Even though both red circles are different instances, they share the same intrinsic data (color).
     // The same applies for the blue rectangle.
     return 0;
 }
 