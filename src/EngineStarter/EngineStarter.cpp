#include <iostream>
#include <spdlog/spdlog.h>
#include "EngineServer.hpp"

int main() {

	spdlog::set_level(spdlog::level::info);
	spdlog::info("EngineStarter: Engine initialization started");

	try
	{
		EngineServer::EngineServer engineServer;
		engineServer.Start();
		spdlog::info("EngineStarter: Engine started");

		// Server runs until get isRunning flag is set to false

		engineServer.Stop();
		spdlog::info("EngineStarter: Engine stopped");
	}
	catch(const std::exception& e)
	{
		spdlog::error("EngineStarter exception: {}", e.what());
	}
	
	return 0;
}