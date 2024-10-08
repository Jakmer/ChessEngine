#include "Client.hpp"
#include "MsgTypes.hpp"
#include <memory>

int main(int argc, char *argv[])
{
    spdlog::set_level(spdlog::level::info);
    spdlog::info("ClientStarter: Client initialization ...");

    // default parameters
    std::string port = "8080";
    std::string host = "localhost";

    try
    {
        if (argc > 1)
        {
            host = argv[1];
        }

        if (argc > 2)
        {
            port = argv[2];
        }

        Client::Client client(host, port);

        client.connect();
        client.start();

    }
    catch (const std::exception &e)
    {
        spdlog::error("ClientStarter: Exception: {}", e.what());
    }

    spdlog::shutdown();

    return 0;
}
