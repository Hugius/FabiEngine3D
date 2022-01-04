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
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ScriptEditor::loadScriptsFromFile");
	}

	_script.reset();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "scripts\\");

	if(!Tools::isDirectoryExisting(directoryPath))
	{
		if(isLoggingEnabled)
		{
			Logger::throwWarning("Project corrupted: directory `scripts\\` missing!");
		}
		return false;
	}

	for(const auto& fileName : Tools::getFilesFromDirectory(directoryPath))
	{
		const auto extension = fileName.substr(fileName.size() - 5, 5);
		if(extension != ".fe3d")
		{
			continue;
		}

		const auto filePath = string(directoryPath + fileName);
		auto file = ifstream(filePath);
		if(!file)
		{
			continue;
		}

		const auto scriptFileID = fileName.substr(0, fileName.size() - 5);
		_script.createScriptFile(scriptFileID);

		unsigned int cursorLineIndex, cursorCharIndex;
		string line;
		getline(file, line);
		istringstream iss(line);
		iss >> cursorLineIndex >> cursorCharIndex;
		_script.getScriptFile(scriptFileID)->setCursorLineIndex(cursorLineIndex);
		_script.getScriptFile(scriptFileID)->setCursorCharIndex(cursorCharIndex);

		unsigned int lineIndex = 0;
		while(getline(file, line))
		{
			_script.getScriptFile(scriptFileID)->insertNewLine(lineIndex, line);
			lineIndex++;
		}

		file.close();
	}

	if(isLoggingEnabled)
	{
		Logger::throwInfo("Script data loaded!");
	}

	_isScriptLoadedFromFile = true;

	return true;
}