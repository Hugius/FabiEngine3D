#include "engine_controller.hpp"

#include <iostream>
#include <conio.h>

using std::endl;
using std::cout;

int main(int argc, char* argv[])
{
	// Create engine
	EngineController controller;

	// Start engine
	controller.application_start();

	// Initiate new scope so engine can end
	if (controller.mustPromptOnExit())
	{
		cout << endl;
		cout << "Press a key to continue...";
		auto temp = _getch();
	}

	return 0;
}