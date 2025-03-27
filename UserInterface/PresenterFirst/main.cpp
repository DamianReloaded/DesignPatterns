/**
 * @brief Presenter-First (MVP) Pattern Example: A simple system to manage and display user information in a UI context.
 *
 * **Key Concepts:**
 * 1. **Model**: Holds the application's data and logic.
 * 2. **View**: Displays the data to the user and forwards user actions to the Presenter.
 * 3. **Presenter**: Acts as the middleman between the Model and View, handling business logic and communication.
 *
 * **Benefits:**
 * - Separation of concerns between data (Model), UI (View), and business logic (Presenter).
 * - Promotes testability and flexibility in UI changes, as the Presenter does not directly depend on a specific UI framework.
 * - Facilitates maintenance by isolating the logic of the UI from the data representation.
 */

 #include <iostream>
 #include <string>
 #include <memory>
 
 /**
  * @brief Represents the model in the MVP pattern. Manages the user's data.
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
 
 private:
     std::string m_name; ///< The name of the user.
 };
 
 /**
  * @brief Represents the view in the MVP pattern. Displays the data to the user.
  */
 class UserView
 {
 public:
     /**
      * @brief Displays the formatted user data.
      * @param data The data to display.
      */
     void displayUser(const std::string& data) const
     {
         std::cout << "User Data: " << data << std::endl;
     }
 
     /**
      * @brief Sets the presenter to interact with.
      * @param presenter The presenter that controls the view.
      */
     void setPresenter(std::shared_ptr<class UserPresenter> presenter)
     {
         m_presenter = presenter;
     }
 
 private:
     std::shared_ptr<class UserPresenter> m_presenter; ///< The presenter that interacts with this view.
 };
 
 /**
  * @brief Represents the presenter in the MVP pattern. Acts as a middleman between the Model and the View.
  */
 class UserPresenter : public std::enable_shared_from_this<UserPresenter>
 {
 public:
     /**
      * @brief Constructs the presenter, taking the model and view.
      * @param model The model that holds user data.
      * @param view The view that displays the data.
      */
     UserPresenter(std::shared_ptr<UserModel> model, std::shared_ptr<UserView> view)
         : m_model(model), m_view(view)
     {
         // The presenter is constructed, but we will delay calling shared_from_this().
     }
 
     /**
      * @brief Initializes the view by setting the presenter after construction.
      */
     void initializeView()
     {
         m_view->setPresenter(shared_from_this());
     }
 
     /**
      * @brief Updates the view with the current user data from the model.
      */
     void updateView()
     {
         std::string data = "Name: " + m_model->getName();
         m_view->displayUser(data);
     }
 
     /**
      * @brief Sets the user's name in the model.
      * @param name The name of the user.
      */
     void setUserName(const std::string& name)
     {
         m_model->setName(name);
         updateView(); // Update the view after setting the name.
     }
 
 private:
     std::shared_ptr<UserModel> m_model; ///< The model that holds user data.
     std::shared_ptr<UserView> m_view; ///< The view that displays the data.
 };
 
 /**
  * @brief Main function demonstrating the Presenter-First (MVP) design pattern.
  */
 int main()
 {
     // Create the model and set some initial data
     auto model = std::make_shared<UserModel>();
     model->setName("John Doe");
 
     // Create the view
     auto view = std::make_shared<UserView>();
 
     // Create the presenter, passing the model and view
     auto presenter = std::make_shared<UserPresenter>(model, view);
 
     // Initialize the view by setting the presenter after the object is fully constructed
     presenter->initializeView();
 
     // Update the view with the current data
     presenter->updateView();
 
     // Change the user's name and update the view again
     presenter->setUserName("Jane Smith");
 
     return 0;
 }
 