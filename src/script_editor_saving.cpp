#include "script_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool ScriptEditor::saveScriptFiles()
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("ScriptEditor::saveScriptsToFile");
	}

	for(const auto& fileName : _scriptFileNamesToDelete)
	{
		const auto rootPath = Tools::getRootDirectoryPath();
		const auto filePath = string(rootPath + "projects\\" + _currentProjectID + "\\scripts\\" + fileName + ".fe3d");

		if(Tools::isFileExisting(filePath))
		{
			Tools::deleteFile(filePath);
		}
	}
	_scriptFileNamesToDelete.clear();

	for(const auto& scriptID : _script->getScriptFileIDs())
	{
		const auto rootPath = Tools::getRootDirectoryPath();
		ofstream file(rootPath + "projects\\" + _currentProjectID + "\\scripts\\" + scriptID + ".fe3d");

		file << _script->getScriptFile(scriptID)->getCursorLineIndex() << " " << _script->getScriptFile(scriptID)->getCursorCharIndex() << endl;

		for(unsigned int lineIndex = 0; lineIndex < _script->getScriptFile(scriptID)->getLineCount(); lineIndex++)
		{
			file << _script->getScriptFile(scriptID)->getLineText(lineIndex) << endl;
		}

		file.close();
	}

	Logger::throwInfo("Script editor data saved!");

	return true;
}