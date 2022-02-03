#include "engine_core.hpp"
#include "engine_interface.hpp"
#include "engine_controller.hpp"

int main(int argc, char* argv[])
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	auto engineCore = make_shared<EngineCore>();
	auto engineInterface = make_shared<EngineInterface>();
	auto engineController = make_shared<EngineController>();

	engineCore->inject(engineInterface);
	engineCore->inject(engineController);
	engineInterface->inject(engineCore);
	engineController->inject(engineInterface);

	engineInterface->application_start();

	return 0;
}