#include "script_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

using std::ifstream;
using std::istringstream;

const bool ScriptEditor::loadScriptFiles(bool isLoggingEnabled)
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("ScriptEditor::loadScriptsFromFile");
	}

	// Clear last script
	_script.reset();

	// Compose directory path
	const string directoryPath = (Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scripts\\");

	// Warning checking
	if(!Tools::isDirectoryExisting(directoryPath))
	{
		if(isLoggingEnabled)
		{
			Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: directory `scripts\\` missing!");
		}
		return false;
	}

	// Retrieve all fileNames in the scripts directory
	for(const auto& fileName : Tools::getFilesFromDirectory(directoryPath))
	{
		// Extract extension
		const string extension = fileName.substr(fileName.size() - 5, 5);

		// Check if script file exists & check if the file extension is correct
		if(Tools::isFileExisting(directoryPath + fileName) && (extension == ".fe3d"))
		{
			// Load script file
			ifstream file(directoryPath + fileName);
			string line;

			// Add script file to script
			string scriptFileID = fileName.substr(0, fileName.size() - 5); // No file extension
			_script.createScriptFile(scriptFileID);

			// Extract cursor indices
			unsigned int cursorLineIndex, cursorCharIndex;
			getline(file, line);
			istringstream iss(line);
			iss >> cursorLineIndex >> cursorCharIndex;
			_script.getScriptFile(scriptFileID)->setCursorLineIndex(cursorLineIndex);
			_script.getScriptFile(scriptFileID)->setCursorCharIndex(cursorCharIndex);

			// Extract script lines
			unsigned int lineIndex = 0;
			while(getline(file, line))
			{
				// Add new scriptline
				_script.getScriptFile(scriptFileID)->insertNewLine(lineIndex, line);
				lineIndex++;
			}

			// Close file
			file.close();
		}
	}

	// Logging
	if(isLoggingEnabled)
	{
		Logger::throwInfo("Script data from project \"" + _currentProjectID + "\" loaded!");
	}

	// Miscellaneous
	_isScriptLoadedFromFile = true;

	// Return
	return true;
}