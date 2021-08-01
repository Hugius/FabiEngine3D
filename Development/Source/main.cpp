#include "engine_controller.hpp"

#include <iostream>
#include <conio.h>

using std::endl;
using std::cout;

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
		cout << endl << "Press a key to continue...";
		auto temp = _getch();
	}

	return 0;
}