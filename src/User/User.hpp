#ifndef USER_HPP
#define USER_HPP

#include <string>

namespace User
{
    class User  // User is going to be a class that will be used to store user data
    {
    public:
        User(const std::string &username);
        ~User();
        std::string getUsername();
        std::string getUserID();

    private:
        std::string username;
        std::string userID;
    };

} // namespace User

#endif // USER_HPP
