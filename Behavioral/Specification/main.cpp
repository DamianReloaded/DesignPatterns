/**
 * @brief Specification Pattern Example for filtering and checking conditions.
 *
 * **Key Concepts:**
 * 1. **Specification Interface**: Defines a method to check if an object meets certain criteria.
 * 2. **Concrete Specifications**: Implement specific criteria (e.g., checking if a person is above a certain age).
 * 3. **Composite Specifications**: Combine multiple specifications using logical operators.
 *
 * **Benefits:**
 * - Allows complex conditions to be expressed in a reusable and composable way.
 * - Decouples the logic from the objects, making it easier to modify or extend.
 * - Promotes maintainability and flexibility in business rule checks.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 #include <functional>
 
 /// @brief Abstract Specification interface that defines the method for checking an object.
 class Specification
 {
 public:
     virtual ~Specification() = default;
 
     /// @brief Checks if the object meets the condition defined by the specification.
     /// @param item The object to be checked.
     /// @return True if the object meets the condition, otherwise false.
     virtual bool isSatisfiedBy(const std::shared_ptr<class Person>& item) const = 0;
 };
 
 /// @brief Concrete Specification that checks if a person is older than a certain age.
 class AgeSpecification : public Specification
 {
 public:
     explicit AgeSpecification(int age) : m_age(age) {}
 
     bool isSatisfiedBy(const std::shared_ptr<class Person>& person) const override;
 
 private:
     int m_age; ///< Minimum age for the specification.
 };
 
 /// @brief Concrete Specification that checks if a person has a certain name.
 class NameSpecification : public Specification
 {
 public:
     explicit NameSpecification(const std::string& name) : m_name(name) {}
 
     bool isSatisfiedBy(const std::shared_ptr<class Person>& person) const override;
 
 private:
     std::string m_name; ///< Name for the specification.
 };
 
 /// @brief Person class to demonstrate the specification pattern.
 class Person
 {
 public:
     Person(const std::string& name, int age) : m_name(name), m_age(age) {}
 
     std::string getName() const { return m_name; }
     int getAge() const { return m_age; }
 
 private:
     std::string m_name; ///< Name of the person.
     int m_age; ///< Age of the person.
 };
 
 /// @brief AgeSpecification implementation that checks if a person is older than the given age.
 bool AgeSpecification::isSatisfiedBy(const std::shared_ptr<Person>& person) const
 {
     return person->getAge() > m_age;
 }
 
 /// @brief NameSpecification implementation that checks if a person's name matches.
 bool NameSpecification::isSatisfiedBy(const std::shared_ptr<Person>& person) const
 {
     return person->getName() == m_name;
 }
 
 /// @brief A helper function to filter persons using a specification.
 void filterPersons(const std::vector<std::shared_ptr<Person>>& persons, const Specification& specification)
 {
     for (const auto& person : persons)
     {
         if (specification.isSatisfiedBy(person))
         {
             std::cout << "Person " << person->getName() << " meets the specification.\n";
         }
         else
         {
             std::cout << "Person " << person->getName() << " does NOT meet the specification.\n";
         }
     }
 }
 
 int main()
 {
     // Creating some persons
     std::vector<std::shared_ptr<Person>> persons;
     persons.push_back(std::make_shared<Person>("Alice", 30));
     persons.push_back(std::make_shared<Person>("Bob", 25));
     persons.push_back(std::make_shared<Person>("Charlie", 35));
 
     // Creating specifications
     AgeSpecification ageSpec(28);
     NameSpecification nameSpec("Alice");
 
     // Filtering persons based on the specifications
     std::cout << "Checking Age Specification:\n";
     filterPersons(persons, ageSpec);
 
     std::cout << "\nChecking Name Specification:\n";
     filterPersons(persons, nameSpec);
 
     return 0;
 }
 