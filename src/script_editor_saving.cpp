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

	// Compose directory path
	const string directoryPath = (Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
								  ("projects\\" + _currentProjectID)) + "\\scripts\\");

	// Delete all text files containing deleted scripts
	for(const auto& fileName : _scriptFilenamesToDelete)
	{
		const string finalPath = directoryPath + fileName + ".fe3d";

		// Check if file exists
		if(Tools::isFileExisting(finalPath))
		{
			DeleteFile(LPCSTR(finalPath.c_str()));
		}
	}
	_scriptFilenamesToDelete.clear();

	// Write every script to a text file
	for(const auto& scriptID : _script.getAllScriptFileIDs())
	{
		// Create or overwrite script file
		ofstream file;
		file.open(directoryPath + scriptID + ".fe3d");

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