/**
 * @brief The Interpreter Pattern is a Behavioral Design Pattern that provides a way to interpret sentences in terms of their grammar.
 *
 * This example demonstrates how to use the Interpreter Pattern with C++23 features such as shared_ptr, auto, and other syntax sugar.
 * It uses member variables prefixed with 'm_' for better readability and maintains ownership through smart pointers.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 
 /**
  * @brief Abstract base class for all expressions.
  */
 class Expression {
 public:
     virtual ~Expression() = default;
     virtual void Interpret() const = 0; // Pure virtual method
 };
 
 /**
  * @brief Concrete implementation of the expression "Number".
  */
 class Number : public Expression {
 private:
     int m_value;
 
 public:
     explicit Number(int value) : m_value(value) {}
 
     void Interpret() const override {
         std::cout << "Number: " << m_value << std::endl;
     }
 };
 
 /**
  * @brief Concrete implementation of the expression "Add".
  */
 class Add : public Expression {
 private:
     std::shared_ptr<Expression> m_left;
     std::shared_ptr<Expression> m_right;
 
 public:
     explicit Add(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
         : m_left(left), m_right(right) {}
 
     void Interpret() const override {
         std::cout << "Adding... ";
         m_left->Interpret();
         m_right->Interpret();
     }
 };
 
 /**
  * @brief Concrete implementation of the expression "Subtract".
  */
 class Subtract : public Expression {
 private:
     std::shared_ptr<Expression> m_left;
     std::shared_ptr<Expression> m_right;
 
 public:
     explicit Subtract(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
         : m_left(left), m_right(right) {}
 
     void Interpret() const override {
         std::cout << "Subtracting... ";
         m_left->Interpret();
         m_right->Interpret();
     }
 };
 
 /**
  * @brief The Client class that builds and executes the expression.
  */
 class Interpreter {
 private:
     std::shared_ptr<Expression> m_expression;
 
 public:
     void SetExpression(std::shared_ptr<Expression> expression) {
         m_expression = expression;
     }
 
     void Interpret() const {
         if (m_expression) {
             m_expression->Interpret();
         } else {
             std::cout << "No expression set to interpret." << std::endl;
         }
     }
 };
 
 int main() {
     // Create the expression: ((5 + 3) - 2)
     auto five = std::make_shared<Number>(5);
     auto three = std::make_shared<Number>(3);
     auto two = std::make_shared<Number>(2);
 
     auto addFiveThree = std::make_shared<Add>(five, three);
     auto subtractResultFromTwo = std::make_shared<Subtract>(addFiveThree, two);
 
     Interpreter interpreter;
     interpreter.SetExpression(subtractResultFromTwo);
     interpreter.Interpret();
 
     return 0;
 }