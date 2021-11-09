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
		if(Config::getInst().isApplicationExported())
		{
			// Compose file path
			const string filePath = string(Tools::getRootDirectoryPath() + "scripts\\" + fileName + ".fe3d");

			// Check if file exists
			if(Tools::isFileExisting(filePath))
			{
				Tools::deleteFile(filePath);
			}
		}
		else
		{
			// Compose file path
			const string filePath = string(Tools::getRootDirectoryPath() + "game\\" + _currentProjectID + "scripts\\" + fileName + ".fe3d");

			// Check if file exists
			if(Tools::isFileExisting(filePath))
			{
				Tools::deleteFile(filePath);
			}
		}

		// Check if file exists

	}
	_scriptFileNamesToDelete.clear();

	// Write every script to a text file
	for(const auto& scriptID : _script.getAllScriptFileIDs())
	{
		// Create or overwrite file
		ofstream file;
		if(Config::getInst().isApplicationExported())
		{
			file.open(Tools::getRootDirectoryPath() + "scripts\\" + scriptID + ".fe3d");
		}
		else
		{
			file.open(Tools::getRootDirectoryPath() + "game\\" + _currentProjectID + "scripts\\" + scriptID + ".fe3d");
		}

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
	Logger::throwInfo("Script data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}