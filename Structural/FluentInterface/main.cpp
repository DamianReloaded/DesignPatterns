#include <iostream>
#include <string>

class MyObject
{
private:
    std::string name;

public:
    MyObject& setName(const std::string& newName)
    {
        name = newName;
        return *this;
    }

    MyObject& print() 
    {
        std::cout << "Name: " << name << std::endl;
        return *this;
    }

    MyObject& doSomething()
    {
        std::cout << "Doing something..." << std::endl;
        return *this;
    }
};

int main()
{
    MyObject obj;
    obj.setName("Fluent Example").print().doSomething();

    return 0;
}
