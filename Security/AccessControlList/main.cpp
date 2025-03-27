/**
 * @brief Access Control List (ACL) Pattern Example: Defines permissions for various users or groups to access resources in the system.
 *
 * **Key Concepts:**
 * 1. **Access Control List (ACL)**: An ACL is a list of permissions attached to an object that specifies who or what can access the object and what actions they are allowed to perform.
 * 2. **Users and Roles**: ACLs are typically associated with users or user groups and define what actions those users or groups can take on resources.
 * 3. **Resources**: Resources can be files, services, or any other object in the system that requires access control.
 *
 * **Benefits:**
 * - Provides fine-grained control over who can access specific resources in a system.
 * - Helps improve system security by defining precise permissions for different users or groups.
 * - Simplifies management of access controls by centralizing permission definitions.
 */

 #include <iostream>
 #include <memory>
 #include <unordered_map>
 #include <string>
 #include <vector>
 #include <optional>
 
 /**
  * @brief A class representing a user in the system.
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
     int m_id;          ///< The ID of the user.
     std::string m_name;///< The name of the user.
 };
 
 /**
  * @brief A class representing a resource in the system.
  */
 class Resource
 {
 public:
     /**
      * @brief Constructs a Resource object.
      * @param id The ID of the resource.
      * @param name The name of the resource.
      */
     Resource(int id, const std::string& name)
         : m_id(id), m_name(name)
     {}
 
     /**
      * @brief Gets the ID of the resource.
      * @return The ID of the resource.
      */
     int getId() const { return m_id; }
 
     /**
      * @brief Gets the name of the resource.
      * @return The name of the resource.
      */
     const std::string& getName() const { return m_name; }
 
 private:
     int m_id;          ///< The ID of the resource.
     std::string m_name;///< The name of the resource.
 };
 
 /**
  * @brief A class representing a permission (read, write, delete, etc.) associated with a resource.
  */
 class Permission
 {
 public:
     enum class Type
     {
         READ,
         WRITE,
         DELETE
     };
 
     /**
      * @brief Constructs a Permission object.
      * @param type The type of permission (e.g., READ, WRITE, DELETE).
      */
     Permission(Type type)
         : m_type(type)
     {}
 
     /**
      * @brief Gets the type of permission.
      * @return The type of permission.
      */
     Type getType() const { return m_type; }
 
 private:
     Type m_type; ///< The type of permission.
 };
 
 /**
  * @brief A class that implements the Access Control List (ACL) pattern.
  */
 class AccessControlList
 {
 public:
     /**
      * @brief Adds a permission for a user on a specific resource.
      * @param user The user who will be granted the permission.
      * @param resource The resource on which the user is granted the permission.
      * @param permission The permission granted to the user on the resource.
      */
     void addPermission(const std::shared_ptr<User>& user, const std::shared_ptr<Resource>& resource, const Permission& permission)
     {
         m_permissions[user->getId()][resource->getId()].push_back(permission);
     }
 
     /**
      * @brief Checks if a user has a specific permission on a resource.
      * @param user The user to check.
      * @param resource The resource to check.
      * @param permission The permission to check.
      * @return true if the user has the permission, false otherwise.
      */
     bool hasPermission(const std::shared_ptr<User>& user, const std::shared_ptr<Resource>& resource, const Permission& permission)
     {
         auto userPermissions = m_permissions.find(user->getId());
         if (userPermissions != m_permissions.end())
         {
             auto resourcePermissions = userPermissions->second.find(resource->getId());
             if (resourcePermissions != userPermissions->second.end())
             {
                 for (const auto& p : resourcePermissions->second)
                 {
                     if (p.getType() == permission.getType())
                     {
                         return true;
                     }
                 }
             }
         }
         return false;
     }
 
 private:
     std::unordered_map<int, std::unordered_map<int, std::vector<Permission>>> m_permissions; ///< A map of user IDs to resource IDs to permissions.
 };
 
 /**
  * @brief Main function demonstrating the Access Control List (ACL) pattern.
  */
 int main()
 {
     // Create users
     auto user1 = std::make_shared<User>(1, "Alice");
     auto user2 = std::make_shared<User>(2, "Bob");
 
     // Create resources
     auto resource1 = std::make_shared<Resource>(1, "Document1");
     auto resource2 = std::make_shared<Resource>(2, "Document2");
 
     // Create ACL and add permissions
     AccessControlList acl;
     acl.addPermission(user1, resource1, Permission(Permission::Type::READ));
     acl.addPermission(user1, resource1, Permission(Permission::Type::WRITE));
     acl.addPermission(user2, resource2, Permission(Permission::Type::READ));
 
     // Check permissions
     std::cout << "Alice has READ access to Document1: " << acl.hasPermission(user1, resource1, Permission(Permission::Type::READ)) << std::endl;
     std::cout << "Alice has DELETE access to Document1: " << acl.hasPermission(user1, resource1, Permission(Permission::Type::DELETE)) << std::endl;
     std::cout << "Bob has READ access to Document2: " << acl.hasPermission(user2, resource2, Permission(Permission::Type::READ)) << std::endl;
 
     return 0;
 }
 