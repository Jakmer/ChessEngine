#include "User.hpp"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h>


namespace User
{
    User::User(const std::string &username) : username(username)
    {
        try
        {
            spdlog::info("User: User constructor");
            boost::uuids::random_generator gen;
            boost::uuids::uuid id = gen();
            userID = boost::uuids::to_string(id);
        }
        catch (const std::exception &e)
        {
            spdlog::error("User: Exception: {}", e.what());
        }
    }

    User::~User()
    {
    }

    std::string User::getUsername()
    {
        return username;
    }

    std::string User::getUserID()
    {
        return userID;
    }
} // namespace User