#include "engine_controller.hpp"

bool startEngine()
{
	// Create engine
	EngineController fe3dController;

	// Start engine
	fe3dController.application_start();

	// Return
	return fe3dController.mustPromptOnExit();
}

int main(int argc, char* argv[])
{
	// Initiate new scope so engine can end
	if (startEngine())
	{
		std::cout << std::endl << "Press a key to continue...";
		auto temp = _getch();
	}

	return 0;
}