#include "script_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool ScriptEditor::saveScriptFiles()
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("ScriptEditor::saveScriptsToFile");
	}

	// Delete all text files containing deleted scripts
	for(const auto& fileName : _scriptFileNamesToDelete)
	{
		// Compose file path
		const string filePath = string(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\scripts\\" + fileName + ".fe3d");

		// Check if file exists
		if(Tools::isFileExisting(filePath))
		{
			Tools::deleteFile(filePath);
		}
	}
	_scriptFileNamesToDelete.clear();

	// Write every script to a text file
	for(const auto& scriptID : _script.getAllScriptFileIDs())
	{
		// Create or overwrite file
		ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\scripts\\" + scriptID + ".fe3d");

		// Write cursor indices to file
		file << _script.getScriptFile(scriptID)->getCursorLineIndex() << " " << _script.getScriptFile(scriptID)->getCursorCharIndex() << endl;

		// Write every scriptline to file
		for(unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(scriptID)->getLineCount(); lineIndex++)
		{
			file << _script.getScriptFile(scriptID)->getLineText(lineIndex) << endl;
		}

		// Close file
		file.close();
	}

	// Logging
	Logger::throwInfo("Script data saved!");

	// Return
	return true;
}