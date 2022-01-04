#include "engine_controller.hpp"

#include <iostream>
#include <conio.h>

using std::endl;
using std::cout;

int main(int argc, char* argv[])
{
	EngineController controller;

	controller.application_start();

	if(controller.mustPromptOnExit())
	{
		cout << endl;
		cout << "Press a key to continue...";
		auto temp = _getch();
	}

	return 0;
}