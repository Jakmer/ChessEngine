#include "Client.hpp"

int main()
{
    spdlog::set_level(spdlog::level::info);
    spdlog::info("ClientStarter: Client initialization ...");

    std::string port = "8080";
    std::string host = "localhost";

    try
    {
        // Create a client instance
        Client client(host, port);

        // Connect to the server
        client.connect();

        // Receive a message from the server
        client.receiveMessage();
    }
    catch (const std::exception &e)
    {
        spdlog::error("ClientStarter: Exception: {}", e.what());
    }

    return 0;
}
