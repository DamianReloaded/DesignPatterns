/**
 * @brief
 * The Pipeline pattern is a specific case of the Chain of Responsibility pattern where a series of processing steps
 * (or functions) are applied to a piece of data sequentially. Each function in the pipeline processes the data and
 * passes it to the next one. This is typically used for operations that involve multiple steps, such as data transformations
 * or processing chains in data workflows.
 *
 * Key concepts:
 * - Chain of Responsibility: A sequence of handlers (functions) is responsible for handling the data.
 * - Sequential Processing: Each handler in the chain processes the data and passes it to the next handler.
 * - Flexibility: The pipeline can be dynamically extended or changed without affecting the overall system.
 *
 * Benefits:
 * - Improved maintainability: Each function (step) in the pipeline has a single responsibility.
 * - Easy extensibility: New functions can be added to the pipeline easily.
 * - Decoupling: Each function is independent of others in terms of logic.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <functional>
 #include <vector>
 
 /**
  * @brief
  * Pipeline class that processes data through a sequence of functions.
  */
 class Pipeline
 {
 public:
     /**
      * @brief Add a processing step to the pipeline.
      * @param step Function that processes a string and returns the processed string.
      */
     void addStep(const std::function<std::string(const std::string &)> &step)
     {
         m_steps.push_back(step);
     }
 
     /**
      * @brief Execute the pipeline on the provided input data.
      * @param input Data to be processed.
      * @return Processed data after applying each step in the pipeline.
      */
     std::string execute(const std::string &input)
     {
         std::string result = input;
         for (auto &step : m_steps)
         {
             result = step(result);
         }
         return result;
     }
 
 private:
     std::vector<std::function<std::string(const std::string &)>> m_steps; ///< List of processing steps in the pipeline.
 };
 
 /**
  * @brief Example of a concrete processing step.
  * Converts a string to uppercase.
  * @param input Data to be converted.
  * @return Uppercase string.
  */
 std::string toUpperCase(const std::string &input)
 {
     std::string result = input;
     for (auto &ch : result)
     {
         ch = std::toupper(ch);
     }
     return result;
 }
 
 /**
  * @brief Example of another concrete processing step.
  * Reverses the string.
  * @param input Data to be reversed.
  * @return Reversed string.
  */
 std::string reverseString(const std::string &input)
 {
     return std::string(input.rbegin(), input.rend());
 }
 
 int main()
 {
     // Create a pipeline
     Pipeline pipeline;
 
     // Add steps to the pipeline
     pipeline.addStep(toUpperCase);
     pipeline.addStep(reverseString);
 
     // Execute the pipeline with input data
     std::string input = "hello world";
     std::string output = pipeline.execute(input);
 
     std::cout << "Processed Output: " << output << std::endl;
 
     return 0;
 }
 