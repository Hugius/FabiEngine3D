#include "script_editor.hpp"

#include <fstream>
#include <sstream>

void ScriptEditor::_loadScriptFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Clear last script
	_unloadScript();

	// Compose full script folder path
	string filePath = _fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\script.fe3d";

	// Check if script file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Create new script to be filled from savefile
		_script = make_shared<Script>(_fe3d);

		// Load script file
		std::ifstream file(filePath);
		string line;

		// Read script data
		while (std::getline(file, line))
		{

		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectName + "\" loaded!");
	}
	else
	{
		// Create new empty script
		//_script = make_shared<Script>();
	}

	// Inject into script executor
	_scriptExecutor = make_shared<ScriptExecutor>(_script);
}

void ScriptEditor::_saveScriptToFile()
{
	// Check if project is loaded properly
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\script.fe3d");

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectName + "\" saved!");
	}
}