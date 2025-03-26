/**
 * @brief Prototype pattern example.
 *
 * **Key Concepts:**
 * 1. **Prototype**: The base class that defines the cloning interface.
 * 2. **Concrete Prototype**: Implements the cloning method to create a copy of itself.
 * 3. **Client**: Uses the clone method to create copies of objects.
 *
 * **How it works:**
 * 1. The `Prototype` class defines the `clone` method, which is used to create a copy of an object.
 * 2. The `ConcretePrototype` classes implement the `clone` method to return a new instance that is a copy of the current object.
 * 3. The client uses the `clone` method to create copies of objects without needing to know the details of their creation.
 *
 * This example demonstrates the Prototype pattern where we create and clone `Shape` objects.
 */
#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Abstract base class for shapes.
 * 
 * The `Shape` class defines the `clone` method, which must be implemented by all concrete prototypes.
 * It also includes a virtual `draw` method to be overridden by derived classes.
 */
class Shape
{
public:
    /**
     * @brief Clone the shape object.
     * 
     * Creates a copy of the current object and returns it as a `std::unique_ptr<Shape>`.
     * 
     * @return A unique pointer to a new instance of the same type as the current object.
     */
    virtual std::unique_ptr<Shape> clone() const = 0;

    /**
     * @brief Draw the shape.
     * 
     * This method simulates drawing the shape. Derived classes must implement this to define specific drawing behavior.
     */
    virtual void draw() const = 0;

    virtual ~Shape() = default; ///< Virtual destructor for proper cleanup of derived objects
};

/**
 * @brief Concrete class representing a circle.
 * 
 * The `Circle` class implements the `clone` and `draw` methods. It represents a circle with a given radius.
 */
class Circle : public Shape
{
public:
    /**
     * @brief Constructor for creating a circle with a specific radius.
     * 
     * @param radius The radius of the circle.
     */
    Circle(int radius) : radius_(radius) {}

    /**
     * @brief Clone the circle object.
     * 
     * Creates a new `Circle` object that is a copy of the current one.
     * 
     * @return A unique pointer to a new `Circle` instance.
     */
    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Circle>(*this);
    }

    /**
     * @brief Draw the circle.
     * 
     * This method simulates drawing a circle by printing its radius.
     */
    void draw() const override
    {
        std::cout << "Drawing a Circle with radius: " << radius_ << "\n";
    }

private:
    int radius_; ///< The radius of the circle
};

/**
 * @brief Concrete class representing a rectangle.
 * 
 * The `Rectangle` class implements the `clone` and `draw` methods. It represents a rectangle with a given width and height.
 */
class Rectangle : public Shape
{
public:
    /**
     * @brief Constructor for creating a rectangle with a specific width and height.
     * 
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    Rectangle(int width, int height) : width_(width), height_(height) {}

    /**
     * @brief Clone the rectangle object.
     * 
     * Creates a new `Rectangle` object that is a copy of the current one.
     * 
     * @return A unique pointer to a new `Rectangle` instance.
     */
    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Rectangle>(*this);
    }

    /**
     * @brief Draw the rectangle.
     * 
     * This method simulates drawing a rectangle by printing its width and height.
     */
    void draw() const override
    {
        std::cout << "Drawing a Rectangle with width: " << width_ << " and height: " << height_ << "\n";
    }

private:
    int width_;  ///< The width of the rectangle
    int height_; ///< The height of the rectangle
};

/**
 * @brief Client code to demonstrate the Prototype pattern.
 * 
 * The `main` function demonstrates the use of the Prototype pattern by creating prototype shapes (`Circle`, `Rectangle`) and cloning them.
 */
int main()
{
    // Creating a Circle prototype
    std::unique_ptr<Shape> circlePrototype = std::make_unique<Circle>(5);
    std::unique_ptr<Shape> clonedCircle = circlePrototype->clone();
    clonedCircle->draw();  ///< Drawing the cloned circle

    // Creating a Rectangle prototype
    std::unique_ptr<Shape> rectanglePrototype = std::make_unique<Rectangle>(4, 6);
    std::unique_ptr<Shape> clonedRectangle = rectanglePrototype->clone();
    clonedRectangle->draw();  ///< Drawing the cloned rectangle

    return 0;
}
