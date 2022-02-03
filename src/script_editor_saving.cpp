#include "script_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool ScriptEditor::saveScriptFiles()
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		abort();
	}

	for(const auto& fileName : _scriptFileNamesToDelete)
	{
		const auto rootPath = Tools::getRootDirectoryPath();
		const auto filePath = string(rootPath + "projects\\" + getCurrentProjectId() + "\\scripts\\" + fileName + ".fe3d");

		if(Tools::isFileExisting(filePath))
		{
			Tools::deleteFile(filePath);
		}
	}
	_scriptFileNamesToDelete.clear();

	for(const auto& scriptId : _script->getScriptFileIds())
	{
		const auto rootPath = Tools::getRootDirectoryPath();
		ofstream file(rootPath + "projects\\" + getCurrentProjectId() + "\\scripts\\" + scriptId + ".fe3d");

		file << _script->getScriptFile(scriptId)->getCursorLineIndex() << " " << _script->getScriptFile(scriptId)->getCursorCharIndex() << endl;

		for(unsigned int lineIndex = 0; lineIndex < _script->getScriptFile(scriptId)->getLineCount(); lineIndex++)
		{
			file << _script->getScriptFile(scriptId)->getLineText(lineIndex) << endl;
		}

		file.close();
	}

	Logger::throwInfo("Script editor data saved");

	return true;
}