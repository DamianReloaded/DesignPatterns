/**
 * @brief Blackboard Pattern Example for coordinating subsystems in problem solving.
 *
 * **Key Concepts:**
 * 1. **Blackboard**: A shared memory space where data is stored and processed incrementally.
 * 2. **Subsystems (Agents)**: Independent agents that process the data on the blackboard.
 * 3. **Collaborative Processing**: Agents read from and write back to the blackboard, contributing to solving the problem.
 *
 * **Benefits:**
 * - Provides a centralized data repository.
 * - Allows for multiple subsystems to contribute to the solution incrementally.
 * - Facilitates extensibility and modification as new agents can be added without modifying existing ones.
 */

 #include <iostream>
 #include <memory>
 #include <vector>
 #include <string>
 #include <algorithm>
 
 /// @brief Blackboard class serves as the shared memory space for data.
 class Blackboard
 {
 public:
     void addData(const std::string& data)
     {
         m_data.push_back(data);
     }
 
     const std::vector<std::string>& getData() const
     {
         return m_data;
     }
 
     void clearData()
     {
         m_data.clear();
     }
 
 private:
     std::vector<std::string> m_data; ///< Stores the data on the blackboard.
 };
 
 /// @brief Subsystem (Agent) class that reads from and writes to the blackboard.
 class Agent
 {
 public:
     virtual ~Agent() = default;
 
     /// @brief Performs processing on the blackboard data.
     /// @param blackboard The blackboard to read from and write to.
     virtual void process(std::shared_ptr<Blackboard> blackboard) = 0;
 };
 
 /// @brief Example of a concrete agent that processes text data on the blackboard.
 class TextProcessingAgent : public Agent
 {
 public:
     void process(std::shared_ptr<Blackboard> blackboard) override
     {
         for (auto& data : blackboard->getData())
         {
             std::string uppercased = data;
             std::transform(uppercased.begin(), uppercased.end(), uppercased.begin(), ::toupper);
             std::cout << "TextProcessingAgent processed: " << uppercased << std::endl;
         }
     }
 };
 
 /// @brief Example of another concrete agent that processes numeric data on the blackboard.
 class NumericProcessingAgent : public Agent
 {
 public:
     void process(std::shared_ptr<Blackboard> blackboard) override
     {
         for (auto& data : blackboard->getData())
         {
             try
             {
                 int number = std::stoi(data);
                 std::cout << "NumericProcessingAgent processed: " << (number * 2) << std::endl;
             }
             catch (const std::exception&)
             {
                 std::cout << "NumericProcessingAgent couldn't process non-numeric data: " << data << std::endl;
             }
         }
     }
 };
 
 /// @brief Orchestrator that controls the flow of data through agents on the blackboard.
 class Orchestrator
 {
 public:
     Orchestrator(std::shared_ptr<Blackboard> blackboard) : m_blackboard(blackboard) {}
 
     /// @brief Executes all the agents to process data on the blackboard.
     void executeAgents()
     {
         for (auto& agent : m_agents)
         {
             agent->process(m_blackboard);
         }
     }
 
     /// @brief Adds agents to be executed.
     void addAgent(std::shared_ptr<Agent> agent)
     {
         m_agents.push_back(agent);
     }
 
 private:
     std::shared_ptr<Blackboard> m_blackboard; ///< Shared memory for all agents.
     std::vector<std::shared_ptr<Agent>> m_agents; ///< List of agents to process data.
 };
 
 int main()
 {
     // Create the blackboard
     auto blackboard = std::make_shared<Blackboard>();
 
     // Add some data to the blackboard
     blackboard->addData("hello");
     blackboard->addData("42");
     blackboard->addData("world");
 
     // Create agents
     auto textAgent = std::make_shared<TextProcessingAgent>();
     auto numericAgent = std::make_shared<NumericProcessingAgent>();
 
     // Create the orchestrator and add agents
     Orchestrator orchestrator(blackboard);
     orchestrator.addAgent(textAgent);
     orchestrator.addAgent(numericAgent);
 
     // Execute all agents to process data on the blackboard
     orchestrator.executeAgents();
 
     return 0;
 }
 