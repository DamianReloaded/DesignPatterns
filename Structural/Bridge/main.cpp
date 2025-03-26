/**
 * @brief Bridge pattern example that separates abstraction and implementation into distinct class hierarchies.
 *
 * The **Bridge** pattern is used to separate an abstraction from its implementation so that both can evolve independently. 
 * It decouples the abstraction (interface) and the implementation (concrete functionality) into separate class hierarchies.
 * 
 * **Key Concepts:**
 * 1. **Abstraction (`Shape`)**: The high-level abstraction that delegates tasks to the implementation.
 * 2. **Refined Abstraction (`Circle`, `Square`)**: The concrete implementations of the abstraction.
 * 3. **Implementor (`DrawingAPI`)**: The interface for the implementation classes.
 * 4. **Concrete Implementor (`OpenGLAPI`, `DirectXAPI`)**: The actual implementation classes for the drawing.
 * 
 * **How it works:**
 * 1. `Shape` provides a high-level interface to draw shapes.
 * 2. `DrawingAPI` is the interface that defines the drawing methods.
 * 3. `OpenGLAPI` and `DirectXAPI` provide concrete implementations of the drawing methods.
 * 4. `Circle` and `Square` extend the `Shape` abstraction and call the drawing methods from `DrawingAPI` to perform the actual rendering.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 
 /**
  * @brief Interface for drawing shapes.
  *
  * The `DrawingAPI` interface defines the methods for drawing shapes. Concrete implementations of this interface
  * provide different ways to render shapes, such as OpenGL or DirectX.
  */
 class DrawingAPI
 {
 public:
     virtual ~DrawingAPI() = default;
 
     /**
      * @brief Draw a circle.
      * 
      * This method will be implemented by concrete classes like OpenGLAPI or DirectXAPI.
      *
      * @param radius The radius of the circle.
      * @param x The x-coordinate of the center of the circle.
      * @param y The y-coordinate of the center of the circle.
      */
     virtual void drawCircle(double radius, double x, double y) const = 0;
 
     /**
      * @brief Draw a square.
      * 
      * This method will be implemented by concrete classes like OpenGLAPI or DirectXAPI.
      *
      * @param side The side length of the square.
      * @param x The x-coordinate of the top-left corner of the square.
      * @param y The y-coordinate of the top-left corner of the square.
      */
     virtual void drawSquare(double side, double x, double y) const = 0;
 };
 
 /**
  * @brief Concrete implementor for OpenGL rendering.
  *
  * The `OpenGLAPI` class provides an OpenGL-specific implementation for drawing shapes, such as circles and squares.
  */
 class OpenGLAPI : public DrawingAPI
 {
 public:
     void drawCircle(double radius, double x, double y) const override
     {
         std::cout << "Drawing Circle with OpenGL: radius = " << radius 
                   << ", center = (" << x << ", " << y << ")\n";
     }
 
     void drawSquare(double side, double x, double y) const override
     {
         std::cout << "Drawing Square with OpenGL: side = " << side 
                   << ", top-left corner = (" << x << ", " << y << ")\n";
     }
 };
 
 /**
  * @brief Concrete implementor for DirectX rendering.
  *
  * The `DirectXAPI` class provides a DirectX-specific implementation for drawing shapes, such as circles and squares.
  */
 class DirectXAPI : public DrawingAPI
 {
 public:
     void drawCircle(double radius, double x, double y) const override
     {
         std::cout << "Drawing Circle with DirectX: radius = " << radius 
                   << ", center = (" << x << ", " << y << ")\n";
     }
 
     void drawSquare(double side, double x, double y) const override
     {
         std::cout << "Drawing Square with DirectX: side = " << side 
                   << ", top-left corner = (" << x << ", " << y << ")\n";
     }
 };
 
 /**
  * @brief Abstraction class for shapes.
  *
  * The `Shape` class defines the abstraction for geometric shapes. It delegates the drawing task to the `DrawingAPI` interface.
  */
 class Shape
 {
 public:
     virtual ~Shape() = default;
 
     /**
      * @brief Set the drawing API for the shape.
      * 
      * This method allows us to assign a specific drawing API to the shape, like OpenGL or DirectX.
      *
      * @param drawingAPI A shared pointer to the `DrawingAPI` implementation.
      */
     void setDrawingAPI(std::shared_ptr<DrawingAPI> drawingAPI)
     {
         m_drawingAPI = drawingAPI;
     }
 
     /**
      * @brief Draw the shape.
      * 
      * This is a high-level method that delegates the drawing task to the drawing API.
      */
     virtual void draw() const = 0;
 
 protected:
     std::shared_ptr<DrawingAPI> m_drawingAPI; ///< The drawing API used to render the shape
 };
 
 /**
  * @brief Refined abstraction for Circle shape.
  *
  * The `Circle` class is a concrete implementation of the `Shape` abstraction. It uses the drawing API to draw a circle.
  */
 class Circle : public Shape
 {
 public:
     Circle(double radius, double x, double y)
         : m_radius(radius), m_x(x), m_y(y) {}
 
     /**
      * @brief Draw the circle by delegating to the drawing API.
      */
     void draw() const override
     {
         m_drawingAPI->drawCircle(m_radius, m_x, m_y);
     }
 
 private:
     double m_radius; ///< The radius of the circle
     double m_x;      ///< The x-coordinate of the circle's center
     double m_y;      ///< The y-coordinate of the circle's center
 };
 
 /**
  * @brief Refined abstraction for Square shape.
  *
  * The `Square` class is a concrete implementation of the `Shape` abstraction. It uses the drawing API to draw a square.
  */
 class Square : public Shape
 {
 public:
     Square(double side, double x, double y)
         : m_side(side), m_x(x), m_y(y) {}
 
     /**
      * @brief Draw the square by delegating to the drawing API.
      */
     void draw() const override
     {
         m_drawingAPI->drawSquare(m_side, m_x, m_y);
     }
 
 private:
     double m_side; ///< The side length of the square
     double m_x;    ///< The x-coordinate of the square's top-left corner
     double m_y;    ///< The y-coordinate of the square's top-left corner
 };
 
 /**
  * @brief Main function demonstrating the Bridge pattern.
  *
  * The function demonstrates how the abstraction (`Shape`) is decoupled from the implementation (`DrawingAPI`).
  * The same shape (e.g., Circle or Square) can be drawn using different implementations (e.g., OpenGL or DirectX).
  */
 int main()
 {
     // Create OpenGL and DirectX drawing APIs
     std::shared_ptr<DrawingAPI> openGLAPI = std::make_shared<OpenGLAPI>();
     std::shared_ptr<DrawingAPI> directXAPI = std::make_shared<DirectXAPI>();
 
     // Create shapes and associate them with drawing APIs
     Circle circle(5.0, 10.0, 15.0);
     circle.setDrawingAPI(openGLAPI);
 
     Square square(4.0, 20.0, 25.0);
     square.setDrawingAPI(directXAPI);
 
     // Draw shapes using OpenGL and DirectX
     std::cout << "Drawing shapes with OpenGL and DirectX:\n";
     circle.draw();  // Uses OpenGL
     square.draw();  // Uses DirectX
 
     return 0;
 }
 