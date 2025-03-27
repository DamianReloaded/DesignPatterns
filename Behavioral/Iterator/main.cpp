/**
 * @brief Iterator Pattern example for traversing a collection.
 *
 * **Key Concepts:**
 * 1. **Iterator Interface (`Iterator`)**: Defines methods for traversal.
 * 2. **Concrete Iterator (`WordIterator`)**: Implements iteration over a collection.
 * 3. **Aggregate Interface (`IterableCollection`)**: Provides a method to create an iterator.
 * 4. **Concrete Collection (`WordCollection`)**: Stores words and provides an iterator.
 *
 * **Benefits:**
 * - Encapsulates iteration logic, separating it from the collection.
 * - Allows multiple ways to iterate over a collection.
 * - Supports variations like reverse iteration or filtering.
 */

 #include <iostream>
 #include <vector>
 #include <memory>
 #include <string>
 
 /**
  * @brief Iterator interface for traversing a collection.
  */
 class Iterator
 {
 public:
     virtual ~Iterator() = default;
     virtual bool hasNext() const = 0;
     virtual std::string next() = 0;
 };
 
 /**
  * @brief Concrete iterator for iterating over words in a collection.
  */
 class WordIterator : public Iterator
 {
 public:
     WordIterator(const std::vector<std::string>& words)
         : m_words(words), m_index(0) {}
 
     bool hasNext() const override
     {
         return m_index < m_words.size();
     }
 
     std::string next() override
     {
         return hasNext() ? m_words[m_index++] : "";
     }
 
 private:
     const std::vector<std::string>& m_words; ///< Reference to the word list.
     size_t m_index; ///< Current position in the collection.
 };
 
 /**
  * @brief Interface for a collection that can create an iterator.
  */
 class IterableCollection
 {
 public:
     virtual ~IterableCollection() = default;
     virtual std::shared_ptr<Iterator> createIterator() const = 0;
 };
 
 /**
  * @brief Concrete collection storing words and providing an iterator.
  */
 class WordCollection : public IterableCollection
 {
 public:
     void addWord(const std::string& word)
     {
         m_words.push_back(word);
     }
 
     std::shared_ptr<Iterator> createIterator() const override
     {
         return std::make_shared<WordIterator>(m_words);
     }
 
 private:
     std::vector<std::string> m_words; ///< Storage for words.
 };
 
 /**
  * @brief Demonstrates iteration over a word collection using the Iterator pattern.
  */
 int main()
 {
     auto collection = std::make_shared<WordCollection>();
     collection->addWord("Hello");
     collection->addWord("World");
     collection->addWord("!");
 
     auto iterator = collection->createIterator();
     while (iterator->hasNext())
     {
         std::cout << iterator->next() << " ";
     }
     std::cout << "\n";
 
     return 0;
 }
 