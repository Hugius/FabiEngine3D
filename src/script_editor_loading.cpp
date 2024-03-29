#include "script_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

using std::ifstream;
using std::istringstream;

const bool ScriptEditor::loadScriptFiles(bool isLoggingEnabled)
{
	if(!Tools::isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	_script->clear();

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "scripts\\");

	if(!Tools::isDirectoryExisting(directoryPath))
	{
		if(isLoggingEnabled)
		{
			Logger::throwWarning("Project corrupted: directory `scripts\\` does not exist");
		}

		return false;
	}

	for(const auto & fileName : Tools::getFileNamesFromDirectory(directoryPath))
	{
		const auto extension = fileName.substr(fileName.size() - 5, 5);

		if(extension != ".fe3d")
		{
			continue;
		}

		const auto filePath = (directoryPath + fileName);

		auto file = ifstream(filePath);

		if(!file)
		{
			continue;
		}

		const auto scriptFileId = fileName.substr(0, fileName.size() - 5);

		_script->createScriptFile(scriptFileId);

		string line = "";
		int cursorLineIndex;
		int cursorCharIndex;

		getline(file, line);

		auto iss = istringstream(line);

		iss
			>> cursorLineIndex
			>> cursorCharIndex;

		_script->getScriptFile(scriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(scriptFileId)->setCursorCharacterIndex(cursorCharIndex);

		int lineIndex = 0;

		while(getline(file, line))
		{
			_script->getScriptFile(scriptFileId)->createLine(lineIndex, line);

			lineIndex++;
		}

		file.close();
	}

	if(isLoggingEnabled)
	{
		Logger::throwInfo("Script editor data loaded");
	}

	return true;
}