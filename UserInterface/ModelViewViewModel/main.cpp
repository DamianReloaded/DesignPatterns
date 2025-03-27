/**
 * @brief Model-View-ViewModel (MVVM) Pattern Example: A simple system to manage and display user information in JSON format.
 *
 * **Key Concepts:**
 * 1. **Model**: Represents the application's data and logic. In this case, it stores user information.
 * 2. **ViewModel**: Provides the data in a format (JSON) that the **View** can easily consume.
 * 3. **View**: Displays the data to the user.
 *
 * **Benefits:**
 * - Separation of concerns between the data, logic, and UI.
 * - Enables easy data formatting for various uses (e.g., API response).
 * - Simplifies testing since the **ViewModel** and **Model** can be tested independently.
 */

 #include <iostream>
 #include <string>
 #include <memory>
 
 /**
  * @brief Represents the model in the MVVM pattern. Manages the user's data.
  */
 class UserModel
 {
 public:
     /**
      * @brief Sets the user's name.
      * @param name The name of the user.
      */
     void setName(const std::string& name)
     {
         m_name = name;
     }
 
     /**
      * @brief Retrieves the user's name.
      * @return The name of the user.
      */
     std::string getName() const
     {
         return m_name;
     }
 
     /**
      * @brief Sets the user's email.
      * @param email The email of the user.
      */
     void setEmail(const std::string& email)
     {
         m_email = email;
     }
 
     /**
      * @brief Retrieves the user's email.
      * @return The email of the user.
      */
     std::string getEmail() const
     {
         return m_email;
     }
 
 private:
     std::string m_name; ///< The name of the user.
     std::string m_email; ///< The email of the user.
 };
 
 /**
  * @brief Represents the view model in the MVVM pattern. Transforms the model data into a JSON format.
  */
 class UserViewModel
 {
 public:
     /**
      * @brief Constructor for UserViewModel.
      * @param model The model that stores user data.
      */
     UserViewModel(std::shared_ptr<UserModel> model)
         : m_model(model)
     {}
 
     /**
      * @brief Gets the user data formatted as a JSON string.
      * @return The user data in JSON format.
      */
     std::string getUserAsJson() const
     {
         return "{\"name\": \"" + m_model->getName() + "\", \"email\": \"" + m_model->getEmail() + "\"}";
     }
 
 private:
     std::shared_ptr<UserModel> m_model; ///< The model that stores user data.
 };
 
 /**
  * @brief Represents the view in the MVVM pattern. Displays the data to the user.
  */
 class UserView
 {
 public:
     /**
      * @brief Displays the formatted user data in JSON format from the view model.
      * @param viewModel The view model containing the data to display.
      */
     void displayUserAsJson(const UserViewModel& viewModel)
     {
        std::cout << "User Data (JSON Format): " << viewModel.getUserAsJson() << std::endl;
     }
 };
 
 /**
  * @brief Main function demonstrating the MVVM design pattern with JSON output.
  */
 int main()
 {
     // Create the model and set some data
     std::cout << "Create user John Doe" << std::endl;
     auto model = std::make_shared<UserModel>();
     model->setName("John Doe");
     model->setEmail("john.doe@example.com");
 
     std::cout << "Pass the user model through the viewModel so it gets formatted" << std::endl;
     // Create the view model and bind it to the model
     UserViewModel viewModel(model);
 
     // Create the view and display the formatted user data in JSON format
     UserView view;
     view.displayUserAsJson(viewModel);
 
     return 0;
 }
 