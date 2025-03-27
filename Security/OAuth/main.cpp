/**
 * @brief
 * The OAuth design pattern is a popular method for delegated access to resources. In OAuth, a client application is granted
 * access to a user's data on a server by using a token instead of credentials. OAuth allows third-party applications to
 * request authorization from the user to access resources on their behalf.
 * 
 * Key Concepts:
 * - Client: The application that is requesting access to the user's resources.
 * - Authorization Server: The server that issues tokens after authenticating the user.
 * - Resource Server: The server that holds the user's data and validates the token before granting access.
 * - Access Token: A token issued by the authorization server that allows the client to access the user's resources.
 * 
 * Benefits:
 * - Secure: OAuth allows third-party apps to access user data without exposing user credentials.
 * - Flexible: OAuth tokens can be scoped to specific actions, providing granular access.
 * - Decouples Authentication: Authentication is handled by the authorization server, and the client doesn't need to manage user credentials.
 * 
 * @note This is a simplified example to demonstrate OAuth concepts and does not cover all the complex details of a full OAuth flow.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <unordered_map>
 
 /**
  * @brief Represents an OAuth access token.
  * 
  * The access token is used to authenticate and authorize a client application to access the user's resources.
  */
 class AccessToken
 {
 public:
     AccessToken(const std::string &token, const std::string &scope)
         : m_token(token), m_scope(scope) {}
 
     /**
      * @brief Gets the access token string.
      * @return The access token.
      */
     std::string getToken() const { return m_token; }
 
     /**
      * @brief Gets the scope of the access token.
      * @return The scope of the access token.
      */
     std::string getScope() const { return m_scope; }
 
 private:
     std::string m_token;  ///< Access token string
     std::string m_scope;  ///< Scope of the access token (e.g., "read", "write")
 };
 
 /**
  * @brief Represents an authorization server that issues access tokens.
  * 
  * This server will authenticate the user and issue an access token for the client to access protected resources.
  */
 class AuthorizationServer
 {
 public:
     /**
      * @brief Authenticates the user and issues an access token.
      * @param clientId The client ID requesting authorization.
      * @param clientSecret The client secret for authentication.
      * @param scope The scope for which the access token is issued.
      * @return A shared pointer to the issued access token.
      */
     std::shared_ptr<AccessToken> issueAccessToken(const std::string &clientId, const std::string &clientSecret, const std::string &scope)
     {
         // In a real implementation, clientId and clientSecret would be validated, and user authentication would occur here.
         // This is a simplified example.
         std::cout << "Authenticating client " << clientId << "...\n";
         if (clientId == "trusted-client" && clientSecret == "secret")
         {
             std::cout << "Client authenticated successfully. Issuing access token...\n";
             return std::make_shared<AccessToken>("sample_token_123", scope);  // Simulate issuing an access token.
         }
         std::cout << "Authentication failed for client " << clientId << ".\n";
         return nullptr;
     }
 };
 
 /**
  * @brief Represents a resource server that provides data to the client based on an access token.
  * 
  * The resource server will validate the access token and ensure that the client has the necessary scope to access the data.
  */
 class ResourceServer
 {
 public:
     /**
      * @brief Validates the access token and returns the requested resource if valid.
      * @param token The access token to validate.
      * @param resource The resource to access.
      * @return The requested resource if valid, otherwise an error message.
      */
     std::string accessResource(const std::shared_ptr<AccessToken> &token, const std::string &resource)
     {
         if (token && validateToken(token))
         {
             std::cout << "Token valid. Accessing resource: " << resource << "\n";
             return "Resource Data for " + resource;  // Simulate returning the resource data.
         }
         std::cout << "Invalid token or insufficient scope.\n";
         return "Access Denied";
     }
 
 private:
     /**
      * @brief Validates the provided access token.
      * @param token The access token to validate.
      * @return True if the token is valid, otherwise false.
      */
     bool validateToken(const std::shared_ptr<AccessToken> &token)
     {
         // For simplicity, this example only checks the token's existence and scope.
         return token != nullptr && token->getScope() == "read";
     }
 };
 
 /**
  * @brief Simulates the client application that interacts with the Authorization Server and the Resource Server.
  * 
  * The client will first request an access token from the Authorization Server and then use that token to access a resource
  * from the Resource Server.
  */
 class OAuthClient
 {
 public:
     /**
      * @brief Constructs an OAuth client with the provided authorization and resource servers.
      * @param authServer The authorization server to request access tokens from.
      * @param resourceServer The resource server to access data from.
      */
     OAuthClient(std::shared_ptr<AuthorizationServer> authServer, std::shared_ptr<ResourceServer> resourceServer)
         : m_authServer(std::move(authServer)), m_resourceServer(std::move(resourceServer)) {}
 
     /**
      * @brief Requests an access token from the authorization server and then accesses a resource from the resource server.
      * @param clientId The client ID requesting authorization.
      * @param clientSecret The client secret for authentication.
      * @param scope The scope for the access token.
      * @param resource The resource to access.
      */
     void performOAuthFlow(const std::string &clientId, const std::string &clientSecret, const std::string &scope, const std::string &resource)
     {
         // Request access token from authorization server
         auto token = m_authServer->issueAccessToken(clientId, clientSecret, scope);
         if (token)
         {
             // Use the access token to access the resource
             std::string resourceData = m_resourceServer->accessResource(token, resource);
             std::cout << "Resource data: " << resourceData << "\n";
         }
     }
 
 private:
     std::shared_ptr<AuthorizationServer> m_authServer; ///< The authorization server
     std::shared_ptr<ResourceServer> m_resourceServer;  ///< The resource server
 };
 
 /**
  * @brief Main function to demonstrate the OAuth design pattern.
  */
 int main()
 {
     // Create the authorization server and resource server
     auto authServer = std::make_shared<AuthorizationServer>();
     auto resourceServer = std::make_shared<ResourceServer>();
 
     // Create the OAuth client
     OAuthClient client(authServer, resourceServer);
 
     // Simulate the OAuth flow: Request an access token and access a resource
     client.performOAuthFlow("trusted-client", "secret", "read", "user_profile");
 
     return 0;
 }
 