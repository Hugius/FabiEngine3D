#include "engine_controller.hpp"

bool startEngine()
{
	// Create engine
	EngineController fe3dController;

	// Start engine
	fe3dController.engine_start();

	return fe3dController.mustPromptOnExit();
}

int main(int argc, char* argv[])
{
	// Initiate new scope so engine can endwd
	if (startEngine())
	{
		std::cout << std::endl << "Type something to continue...";
		auto temp = _getch();
	}

	return 0;
}