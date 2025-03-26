/**
 * @brief Composite pattern example where objects are composed into tree structures to represent part-whole hierarchies.
 *
 * The **Composite** pattern allows you to compose objects into tree structures and treat individual objects and 
 * compositions of objects uniformly. This pattern is particularly useful for representing hierarchies of objects 
 * where leaf nodes and composite nodes are treated the same way.
 *
 * **Key Concepts:**
 * 1. **Component (`Graphic`)**: An abstract class that represents both leaf and composite objects.
 * 2. **Leaf (`Circle`, `Rectangle`)**: Concrete classes that represent leaf nodes in the tree (i.e., individual shapes).
 * 3. **Composite (`Group`)**: A composite object that holds other `Graphic` objects (both leaf and composite).
 *
 * **How it works:**
 * 1. `Graphic` defines the common interface for both `Circle` and `Rectangle`, allowing them to be treated uniformly.
 * 2. `Circle` and `Rectangle` are leaf objects that implement the `Graphic` interface and provide their own drawing behavior.
 * 3. `Group` is a composite object that holds multiple `Graphic` objects (either `Circle`, `Rectangle`, or other `Group` objects).
 * 4. The client can call the same interface (`draw()`) on both individual objects and composite objects.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 
 /**
  * @brief Abstract Component class representing graphical objects.
  *
  * The `Graphic` class defines the interface for all concrete objects in the composition, both leaf and composite.
  */
 class Graphic
 {
 public:
     virtual ~Graphic() = default;
 
     /**
      * @brief Draw the graphic.
      *
      * This method must be implemented by both leaf and composite objects. For leaf objects, it draws a single object. 
      * For composite objects, it delegates the drawing task to their child components.
      */
     virtual void draw() const = 0;
 };
 
 /**
  * @brief Leaf class representing a circle.
  *
  * The `Circle` class is a leaf node in the composite structure. It represents an individual graphical object 
  * (a circle in this case).
  */
 class Circle : public Graphic
 {
 public:
     /**
      * @brief Constructor to initialize circle properties.
      *
      * @param x The x-coordinate of the circle's center.
      * @param y The y-coordinate of the circle's center.
      * @param radius The radius of the circle.
      */
     Circle(double x, double y, double radius)
         : m_x(x), m_y(y), m_radius(radius) {}
 
     /**
      * @brief Draw the circle.
      *
      * This method draws the circle by printing its properties to the console.
      */
     void draw() const override
     {
         std::cout << "Drawing Circle at (" << m_x << ", " << m_y << ") with radius " << m_radius << std::endl;
     }
 
 private:
     double m_x;      ///< The x-coordinate of the circle's center
     double m_y;      ///< The y-coordinate of the circle's center
     double m_radius; ///< The radius of the circle
 };
 
 /**
  * @brief Leaf class representing a rectangle.
  *
  * The `Rectangle` class is a leaf node in the composite structure. It represents an individual graphical object 
  * (a rectangle in this case).
  */
 class Rectangle : public Graphic
 {
 public:
     /**
      * @brief Constructor to initialize rectangle properties.
      *
      * @param x The x-coordinate of the rectangle's top-left corner.
      * @param y The y-coordinate of the rectangle's top-left corner.
      * @param width The width of the rectangle.
      * @param height The height of the rectangle.
      */
     Rectangle(double x, double y, double width, double height)
         : m_x(x), m_y(y), m_width(width), m_height(height) {}
 
     /**
      * @brief Draw the rectangle.
      *
      * This method draws the rectangle by printing its properties to the console.
      */
     void draw() const override
     {
         std::cout << "Drawing Rectangle at (" << m_x << ", " << m_y << ") with width " << m_width 
                   << " and height " << m_height << std::endl;
     }
 
 private:
     double m_x;      ///< The x-coordinate of the rectangle's top-left corner
     double m_y;      ///< The y-coordinate of the rectangle's top-left corner
     double m_width;  ///< The width of the rectangle
     double m_height; ///< The height of the rectangle
 };
 
 /**
  * @brief Composite class representing a group of graphical objects.
  *
  * The `Group` class is a composite that contains other `Graphic` objects. It is capable of adding, removing,
  * and drawing all its child components (which can be both leaf and other composite objects).
  */
 class Group : public Graphic
 {
 public:
     /**
      * @brief Add a graphic to the group.
      *
      * Adds a `Graphic` object (either leaf or composite) to the group's collection of child components.
      *
      * @param graphic A shared pointer to a `Graphic` object.
      */
     void add(const std::shared_ptr<Graphic>& graphic)
     {
         m_graphics.push_back(graphic);
     }
 
     /**
      * @brief Draw all the graphics in the group.
      *
      * This method delegates the drawing task to all its child components.
      */
     void draw() const override
     {
         std::cout << "Drawing Group:" << std::endl;
         for (const auto& graphic : m_graphics)
         {
             graphic->draw();
         }
     }
 
 private:
     std::vector<std::shared_ptr<Graphic>> m_graphics; ///< The list of child components (either leaf or composite)
 };
 
 /**
  * @brief Main function demonstrating the Composite pattern.
  *
  * The function demonstrates how individual graphical objects (`Circle`, `Rectangle`) and composite objects (`Group`) 
  * can be treated uniformly. A group of shapes can be drawn using the same `draw()` method.
  */
 int main()
 {
     // Create leaf objects (circle and rectangle)
     std::shared_ptr<Graphic> circle1 = std::make_shared<Circle>(5.0, 10.0, 15.0);
     std::shared_ptr<Graphic> rectangle1 = std::make_shared<Rectangle>(1.0, 1.0, 4.0, 6.0);
 
     // Create a group and add the shapes to it
     std::shared_ptr<Group> group1 = std::make_shared<Group>();
     group1->add(circle1);
     group1->add(rectangle1);
 
     // Create another group and add a shape and another group
     std::shared_ptr<Group> group2 = std::make_shared<Group>();
     group2->add(group1);
     group2->add(std::make_shared<Circle>(20.0, 25.0, 10.0));
 
     // Draw the entire structure (groups and individual shapes)
     std::cout << "Drawing all shapes:" << std::endl;
     group2->draw(); // Drawing group2 (which includes group1 and another circle)
 
     return 0;
 }
 