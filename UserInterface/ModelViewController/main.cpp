/**
 * @brief Model-View-Controller (MVC) Pattern Example: A simple system to manage a list of users.
 *
 * **Key Concepts:**
 * 1. **Model**: Represents the application's data and logic. In this case, it stores user information.
 * 2. **View**: Displays the data to the user. It doesn't know about the model's internal workings.
 * 3. **Controller**: Manages the user input and updates the model. It acts as a mediator between the model and view.
 *
 * **Benefits:**
 * - Separation of concerns: The model, view, and controller can evolve independently.
 * - Increased maintainability: Each layer can be modified without affecting others.
 * - Flexibility: Different views or input methods can be added without changing the model logic.
 */

 #include <iostream>
 #include <string>
 #include <vector>
 #include <memory>
 
 /**
  * @brief Represents the model in the MVC pattern. Manages the list of users.
  */
 class UserModel
 {
 public:
     /**
      * @brief Adds a new user to the model.
      * @param userName The name of the user to add.
      */
     void addUser(const std::string& userName)
     {
         m_users.push_back(userName);
     }
 
     /**
      * @brief Retrieves the list of users.
      * @return A vector containing user names.
      */
     std::vector<std::string> getUsers() const
     {
         return m_users;
     }
 
 private:
     std::vector<std::string> m_users; ///< List of users stored in the model.
 };
 
 /**
  * @brief Represents the view in the MVC pattern. Displays the list of users.
  */
 class UserView
 {
 public:
     /**
      * @brief Displays the users to the console.
      * @param users The list of users to display.
      */
     void showUsers(const std::vector<std::string>& users) const
     {
         if (users.empty())
         {
             std::cout << "No users found.\n";
         }
         else
         {
             std::cout << "Users List:\n";
             for (const auto& user : users)
             {
                 std::cout << "- " << user << '\n';
             }
         }
     }
 };
 
 /**
  * @brief Represents the controller in the MVC pattern. Manages user input and updates the model.
  */
 class UserController
 {
 public:
     /**
      * @brief Constructor for UserController.
      * @param model The model that stores user data.
      * @param view The view that displays the users.
      */
     UserController(std::shared_ptr<UserModel> model, std::shared_ptr<UserView> view)
         : m_model(model), m_view(view)
     {}
 
     /**
      * @brief Adds a new user through the controller and updates the view.
      * @param userName The name of the user to add.
      */
     void addUser(const std::string& userName)
     {
         m_model->addUser(userName); // Update the model
         updateView(); // Update the view with the latest data
     }
 
     /**
      * @brief Displays all users via the view.
      */
     void showUsers() const
     {
         m_view->showUsers(m_model->getUsers());
     }
 
 private:
     /**
      * @brief Updates the view with the current list of users from the model.
      */
     void updateView() const
     {
         m_view->showUsers(m_model->getUsers());
     }
 
     std::shared_ptr<UserModel> m_model; ///< The model that stores data.
     std::shared_ptr<UserView> m_view;   ///< The view that displays the data.
 };
 
 /**
  * @brief Main function demonstrating the MVC design pattern.
  */
 int main()
 {
     // Create the model, view, and controller objects
     auto model = std::make_shared<UserModel>();
     auto view = std::make_shared<UserView>();
     auto controller = std::make_shared<UserController>(model, view);
 
     // Add users through the controller
     controller->addUser("Alice");
     controller->addUser("Bob");
     controller->addUser("Charlie");
 
     // Show all users via the controller (which updates the view)
     controller->showUsers();
 
     return 0;
 }
 