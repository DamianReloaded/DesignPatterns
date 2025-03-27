/**
 * @brief Aggregate Pattern Example: Represents a group of related objects that are treated as a unit for data changes.
 *
 * **Key Concepts:**
 * 1. **Aggregate**: An aggregate is a collection or group of objects that can be treated as a single unit for operations. It ensures that operations on individual objects can be done through the aggregate, making the group behave as a cohesive unit.
 * 2. **Composition**: Aggregates typically consist of multiple objects that form a logical unit. They allow for easier management and modification of related objects.
 * 3. **Encapsulation**: The aggregate class hides the internal complexity and presents a simplified interface for interacting with the group of objects.

 * **Benefits:**
 * - **Simplifies Data Management**: Aggregate pattern simplifies the management of related objects by treating them as a cohesive unit.
 * - **Encapsulation**: Keeps individual objects hidden from the outside, providing controlled access to their data.
 * - **Reduced Complexity**: Operations on multiple related objects can be done through a single interface, reducing the complexity for the client code.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 
 /**
  * @brief Represents an individual item in the aggregate.
  */
 class Item
 {
 public:
     /**
      * @brief Constructs an Item with a given ID and value.
      * @param id The ID of the item.
      * @param value The value of the item.
      */
     Item(int id, int value)
         : m_id(id), m_value(value)
     {}
 
     /**
      * @brief Gets the ID of the item.
      * @return The ID of the item.
      */
     int getId() const { return m_id; }
 
     /**
      * @brief Gets the value of the item.
      * @return The value of the item.
      */
     int getValue() const { return m_value; }
 
     /**
      * @brief Sets the value of the item.
      * @param value The new value to set.
      */
     void setValue(int value) { m_value = value; }
 
 private:
     int m_id;      ///< The ID of the item.
     int m_value;   ///< The value of the item.
 };
 
 /**
  * @brief Represents an aggregate that groups multiple items.
  */
 class Aggregate
 {
 public:
     /**
      * @brief Adds an item to the aggregate.
      * @param item The item to add.
      */
     void addItem(const std::shared_ptr<Item>& item)
     {
         m_items.push_back(item);
     }
 
     /**
      * @brief Gets the item by index from the aggregate.
      * @param index The index of the item to retrieve.
      * @return The item at the specified index.
      */
     std::shared_ptr<Item> getItem(int index)
     {
         if (index < 0 || index >= static_cast<int>(m_items.size()))
         {
             return nullptr;
         }
         return m_items[index];
     }
 
     /**
      * @brief Updates the value of an item in the aggregate by index.
      * @param index The index of the item.
      * @param newValue The new value to set.
      */
     void updateItemValue(int index, int newValue)
     {
         if (auto item = getItem(index))
         {
             item->setValue(newValue);
         }
     }
 
     /**
      * @brief Displays all items in the aggregate.
      */
     void displayItems() const
     {
         for (const auto& item : m_items)
         {
             std::cout << "Item ID: " << item->getId() << ", Value: " << item->getValue() << std::endl;
         }
     }
 
 private:
     std::vector<std::shared_ptr<Item>> m_items; ///< List of items in the aggregate.
 };
 
 /**
  * @brief Main function demonstrating the Aggregate pattern.
  */
 int main()
 {
     // Create individual items
     auto item1 = std::make_shared<Item>(1, 10);
     auto item2 = std::make_shared<Item>(2, 20);
     auto item3 = std::make_shared<Item>(3, 30);
 
     // Create an aggregate and add items to it
     Aggregate aggregate;
     aggregate.addItem(item1);
     aggregate.addItem(item2);
     aggregate.addItem(item3);
 
     // Display all items in the aggregate
     std::cout << "Before update:" << std::endl;
     aggregate.displayItems();
 
     // Update the value of the second item
     aggregate.updateItemValue(1, 50);
 
     // Display all items after the update
     std::cout << "After update:" << std::endl;
     aggregate.displayItems();
 
     return 0;
 }
 