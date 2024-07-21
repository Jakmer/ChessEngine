#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "EngineServer.hpp"

int main()
{

	spdlog::set_level(spdlog::level::info);
	spdlog::info("EngineStarter: Engine initialization ...");

	boost::asio::io_context ioContext;
	short port = 8080;

	try
	{
		EngineServer::EngineServer engineServer(ioContext, port);
		engineServer.Start();

		// Server runs until get isRunning flag is set to false

		spdlog::info("EngineStarter: Engine stopped");
	}
	catch (const std::exception &e)
	{
		spdlog::error("EngineStarter exception: {}", e.what());
	}

	return 0;
}