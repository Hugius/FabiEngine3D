#include "script_editor.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

void ScriptEditor::loadScriptsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> ScriptEditor::loadScriptsFromFile()");
	}

	// Clear last script
	_script.reset();

	// Retrieve all filenames in the scripts folder
	vector<string> scriptFilenames;
	string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\scripts\\";
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
	{
		// Extract filename
		string fileName = string(entry.path().u8string());
		fileName.erase(0, directoryPath.size());

		// Check if script file exists & check if the file extension is correct
		if (_fe3d.misc_isFileExisting(directoryPath + fileName) && (fileName.substr(fileName.size() - 5, 5) == ".fe3d"))
		{
			// Load script file
			std::ifstream file(directoryPath + fileName);
			string line;

			// Add software script file to script
			string scriptName = fileName.substr(0, fileName.size() - 5); // No file extension
			_script.addScriptFile(scriptName);

			// Extract cursor indices
			unsigned int cursorLineIndex, cursorCharIndex;
			std::getline(file, line);
			stringstream iss(line);
			iss >> cursorLineIndex >> cursorCharIndex;
			_script.getScriptFile(scriptName)->setCursorLineIndex(cursorLineIndex);
			_script.getScriptFile(scriptName)->setCursorCharIndex(cursorCharIndex);

			// Extract script lines
			unsigned int lineIndex = 0;
			while (std::getline(file, line))
			{
				// Add new scriptline
				_script.getScriptFile(scriptName)->insertNewLine(lineIndex++, line);
			}

			// Close file
			file.close();
		}
	}

	// Logging
	_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectID + "\" loaded!");

	_isScriptLoadedFromFile = true;
}

void ScriptEditor::saveScriptsToFile()
{
	// Editor must be loaded
	if (_isEditorLoaded)
	{
		// Error checking
		if (_currentProjectID == "")
		{
			_fe3d.logger_throwError("No current project loaded --> ScriptEditor::saveScriptsToFile()");
		}

		string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\scripts\\";

		// Delete all text files containing deleted scripts
		for (auto& scriptName : _scriptFileNamesToDelete)
		{
			string finalPath = directoryPath + scriptName + ".fe3d";

			// Check if file exists
			if (_fe3d.misc_isFileExisting(finalPath))
			{
				DeleteFile(LPCSTR(finalPath.c_str()));
			}
		}
		_scriptFileNamesToDelete.clear();

		// Write every script to a text file
		for (auto& scriptName : _script.getAllScriptFileIDs())
		{
			// Create or overwrite script file
			std::ofstream file;
			file.open(directoryPath + scriptName + ".fe3d");

			// Write cursor indices to file
			file << _script.getScriptFile(scriptName)->getCursorLineIndex() << " " << _script.getScriptFile(scriptName)->getCursorCharIndex() << std::endl;

			// Write every scriptline to file
			for (unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(scriptName)->getLineCount(); lineIndex++)
			{
				file << _script.getScriptFile(scriptName)->getLineText(lineIndex) << std::endl;
			}

			// Close file
			file.close();
		}

		// Logging
		_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectID + "\" saved!");
	}
}