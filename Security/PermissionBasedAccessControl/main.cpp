/**
 * @brief
 * The Permission-based Access Control (PBAC) design pattern provides a method for controlling access to system resources
 * based on a user's role and permissions. The pattern helps ensure that users can only access resources or perform actions
 * they are authorized for, thereby improving system security.
 * 
 * Key Concepts:
 * - Roles: Represent categories or groups that users belong to (e.g., "Admin", "User", "Manager").
 * - Permissions: Define what actions a role can perform on specific resources (e.g., "read", "write").
 * - Access Control: Ensures that only authorized users can access resources based on their roles and permissions.
 * 
 * Benefits:
 * - Fine-Grained Security: Allows precise control over who can access what resources.
 * - Flexible: Permissions can be easily added or removed from roles, making it adaptable to changing security requirements.
 * - Centralized Management: Permissions are managed centrally, simplifying security management and auditing.
 */

 #include <iostream>
 #include <memory>
 #include <string>
 #include <unordered_map>
 #include <vector>
 
 /**
  * @brief Represents a permission in the system.
  * 
  * A permission defines an action that can be performed on a resource (e.g., "read", "write").
  */
 class Permission
 {
 public:
     Permission(const std::string &action) : m_action(action) {}
 
     /**
      * @brief Gets the action associated with the permission.
      * @return The action as a string.
      */
     std::string getAction() const { return m_action; }
 
 private:
     std::string m_action; ///< The action (e.g., "read", "write")
 };
 
 /**
  * @brief Represents a role in the system.
  * 
  * A role groups permissions together and assigns them to users.
  */
 class Role
 {
 public:
     Role(const std::string &roleName) : m_roleName(roleName) {}
 
     /**
      * @brief Adds a permission to the role.
      * @param permission The permission to add to the role.
      */
     void addPermission(const std::shared_ptr<Permission> &permission)
     {
         m_permissions.push_back(permission);
     }
 
     /**
      * @brief Checks if the role has the given permission.
      * @param permission The permission to check.
      * @return True if the role has the permission, otherwise false.
      */
     bool hasPermission(const std::shared_ptr<Permission> &permission) const
     {
         for (const auto &perm : m_permissions)
         {
             if (perm->getAction() == permission->getAction())
             {
                 return true;
             }
         }
         return false;
     }
 
     /**
      * @brief Gets the role name.
      * @return The name of the role.
      */
     std::string getRoleName() const { return m_roleName; }
 
 private:
     std::string m_roleName;                             ///< The name of the role (e.g., "Admin")
     std::vector<std::shared_ptr<Permission>> m_permissions; ///< Permissions assigned to the role
 };
 
 /**
  * @brief Represents a user in the system.
  * 
  * A user has a role, and the permissions granted to the user are based on their role.
  */
 class User
 {
 public:
     User(const std::string &userName, const std::shared_ptr<Role> &role)
         : m_userName(userName), m_role(role) {}
 
     /**
      * @brief Checks if the user has a specific permission based on their role.
      * @param permission The permission to check.
      * @return True if the user has the permission, otherwise false.
      */
     bool hasPermission(const std::shared_ptr<Permission> &permission) const
     {
         return m_role->hasPermission(permission);
     }
 
     /**
      * @brief Gets the username.
      * @return The username.
      */
     std::string getUserName() const { return m_userName; }
 
 private:
     std::string m_userName;           ///< The username
     std::shared_ptr<Role> m_role;     ///< The role assigned to the user
 };
 
 /**
  * @brief Main function to demonstrate the PBAC design pattern.
  * 
  * In this example, we create roles, assign permissions to them, and then check if users have those permissions.
  */
 int main()
 {
     // Create permissions
     auto readPermission = std::make_shared<Permission>("read");
     auto writePermission = std::make_shared<Permission>("write");
 
     // Create roles
     auto adminRole = std::make_shared<Role>("Admin");
     adminRole->addPermission(readPermission);
     adminRole->addPermission(writePermission);
 
     auto userRole = std::make_shared<Role>("User");
     userRole->addPermission(readPermission);
 
     // Create users
     auto adminUser = std::make_shared<User>("admin_user", adminRole);
     auto normalUser = std::make_shared<User>("normal_user", userRole);
 
     // Check permissions for admin user
     std::cout << adminUser->getUserName() << " has read permission: "
               << (adminUser->hasPermission(readPermission) ? "Yes" : "No") << "\n";
     std::cout << adminUser->getUserName() << " has write permission: "
               << (adminUser->hasPermission(writePermission) ? "Yes" : "No") << "\n";
 
     // Check permissions for normal user
     std::cout << normalUser->getUserName() << " has read permission: "
               << (normalUser->hasPermission(readPermission) ? "Yes" : "No") << "\n";
     std::cout << normalUser->getUserName() << " has write permission: "
               << (normalUser->hasPermission(writePermission) ? "Yes" : "No") << "\n";
 
     return 0;
 }
 