/**
 * @brief Token-Based Authentication Pattern Example: Uses tokens (like JWT) for authenticating users without maintaining server-side sessions.
 *
 * **Key Concepts:**
 * 1. **Token-based Authentication**: The client authenticates using a token (e.g., JWT) rather than a server-maintained session. The token typically encodes user identity and permissions.
 * 2. **Stateless**: The server does not store session data. Authentication is carried out using the token in each request, making the system stateless.
 * 3. **JWT (JSON Web Tokens)**: A common implementation for token-based authentication, which securely transmits information between parties as a JSON object.
 *
 * **Benefits:**
 * - **Scalability**: No server-side session state, which makes it easier to scale horizontally.
 * - **Decentralized**: The client can authenticate itself without relying on session storage on the server.
 * - **Security**: Tokens are often signed and can be encrypted, providing secure communication between client and server.
 * - **Flexibility**: Tokens can contain more information, allowing for richer interactions and fine-grained authorization.
 */

 #include <iostream>
 #include <string>
 #include <memory>
 #include <unordered_map>
 #include <ctime>
 #include <chrono>
 #include <sstream>
 #include <iomanip>
 
 /**
  * @brief Represents a user in the system.
  */
 class User
 {
 public:
     /**
      * @brief Constructs a User object.
      * @param id The ID of the user.
      * @param name The name of the user.
      */
     User(int id, const std::string& name)
         : m_id(id), m_name(name)
     {}
 
     /**
      * @brief Gets the ID of the user.
      * @return The ID of the user.
      */
     int getId() const { return m_id; }
 
     /**
      * @brief Gets the name of the user.
      * @return The name of the user.
      */
     const std::string& getName() const { return m_name; }
 
 private:
     int m_id;            ///< The ID of the user.
     std::string m_name;  ///< The name of the user.
 };
 
 /**
  * @brief A class to represent a token used for authentication.
  */
 class Token
 {
 public:
     /**
      * @brief Constructs a Token object.
      * @param user The user for whom the token is created.
      * @param expirationTime The expiration time for the token.
      */
     Token(const std::shared_ptr<User>& user, const std::chrono::system_clock::time_point& expirationTime)
         : m_user(user), m_expirationTime(expirationTime)
     {
         generateToken();
     }
 
     /**
      * @brief Generates a simple token by encoding user info and expiration time.
      * This is a simplified version, in real systems, it would be signed and possibly encrypted.
      */
     void generateToken()
     {
         std::ostringstream oss;
         oss << m_user->getId() << ":" << m_user->getName() << ":"
             << std::chrono::duration_cast<std::chrono::seconds>(m_expirationTime.time_since_epoch()).count();
         m_token = oss.str();
     }
 
     /**
      * @brief Gets the token string.
      * @return The token string.
      */
     const std::string& getToken() const { return m_token; }
 
     /**
      * @brief Checks if the token is expired.
      * @return true if the token is expired, false otherwise.
      */
     bool isExpired() const
     {
         return std::chrono::system_clock::now() > m_expirationTime;
     }
 
 private:
     std::shared_ptr<User> m_user;              ///< The user associated with the token.
     std::chrono::system_clock::time_point m_expirationTime; ///< The expiration time of the token.
     std::string m_token;                       ///< The generated token string.
 };
 
 /**
  * @brief A class that handles authentication using token-based methods.
  */
 class AuthenticationService
 {
 public:
     /**
      * @brief Authenticates a user and generates a token.
      * @param user The user to authenticate.
      * @return The generated authentication token.
      */
     std::shared_ptr<Token> authenticate(const std::shared_ptr<User>& user)
     {
         auto expirationTime = std::chrono::system_clock::now() + std::chrono::minutes(30);  // Token valid for 30 minutes
         auto token = std::make_shared<Token>(user, expirationTime);
         return token;
     }
 
     /**
      * @brief Verifies if a token is valid.
      * @param token The token to validate.
      * @return true if the token is valid and not expired, false otherwise.
      */
     bool verifyToken(const std::shared_ptr<Token>& token)
     {
         return !token->isExpired();
     }
 };
 
 /**
  * @brief Main function demonstrating Token-Based Authentication.
  */
 int main()
 {
     // Create a user
     auto user = std::make_shared<User>(1, "Alice");
 
     // Create an authentication service
     AuthenticationService authService;
 
     // Authenticate user and generate a token
     auto token = authService.authenticate(user);
     std::cout << "Generated Token: " << token->getToken() << std::endl;
 
     // Verify if the token is still valid
     if (authService.verifyToken(token))
     {
         std::cout << "Token is valid!" << std::endl;
     }
     else
     {
         std::cout << "Token is expired!" << std::endl;
     }
 
     return 0;
 }
 