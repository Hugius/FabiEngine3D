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

	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = (rootPath + "projects\\" + getCurrentProjectId() + "\\scripts\\");

	for(const auto& fileName : Tools::getFileNamesFromDirectory(directoryPath))
	{
		const auto extension = fileName.substr(fileName.size() - 5, 5);
		if(extension != ".fe3d")
		{
			continue;
		}

		if(Tools::isFileExisting(directoryPath + fileName))
		{
			Tools::deleteFile(directoryPath + fileName);
		}
	}

	for(const auto& scriptId : _script->getScriptFileIds())
	{
		auto file = ofstream(directoryPath + scriptId + ".fe3d");

		file
			<< _script->getScriptFile(scriptId)->getCursorLineIndex()
			<< " "
			<< _script->getScriptFile(scriptId)->getCursorCharacterIndex()
			<< endl;

		for(unsigned int lineIndex = 0; lineIndex < _script->getScriptFile(scriptId)->getLineCount(); lineIndex++)
		{
			file << _script->getScriptFile(scriptId)->getLine(lineIndex) << endl;
		}

		file.close();
	}

	Logger::throwInfo("Script editor data saved");

	return true;
}