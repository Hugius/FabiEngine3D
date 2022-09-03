#include "script.hpp"

#include <regex>

using std::regex;

void Script::createScriptFile(const string & scriptId)
{
	if(isScriptFileExisting(scriptId))
	{
		abort();
	}

	_scriptFiles.insert({scriptId, make_shared<ScriptFile>(scriptId)});
}

void Script::renameScriptFile(const string & scriptId, const string & newScriptId)
{
	if(!isScriptFileExisting(scriptId))
	{
		abort();
	}

	const auto cursorLineIndex = getScriptFile(scriptId)->getCursorLineIndex();
	const auto cursorCharacterIndex = getScriptFile(scriptId)->getCursorCharacterIndex();
	const auto lines = getScriptFile(scriptId)->getLines();

	deleteScriptFile(scriptId);
	createScriptFile(newScriptId);

	getScriptFile(newScriptId)->setCursorLineIndex(cursorLineIndex);
	getScriptFile(newScriptId)->setCursorCharacterIndex(cursorCharacterIndex);
	getScriptFile(newScriptId)->setLines(lines);
}

void Script::deleteScriptFile(const string & id)
{
	if(!isScriptFileExisting(id))
	{
		abort();
	}

	_scriptFiles.erase(id);
}

void Script::replaceKeyword(const string & oldKeyword, const string & newKeyword)
{
	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		auto lines = scriptFile->getLines();

		for(auto & line : lines)
		{
			for(int index = 0; index < static_cast<int>(line.size()); index++)
			{
				if(line.substr(index, oldKeyword.size()) == oldKeyword)
				{
					const auto firstPart = line.substr(0, index);
					const auto secondPart = line.substr(index + oldKeyword.size());

					line = (firstPart + newKeyword + secondPart);

					break;
				}
			}
		}

		scriptFile->setLines(lines);

		const auto cursorLineLength = static_cast<int>(scriptFile->getLine(scriptFile->getCursorLineIndex()).size());

		if(scriptFile->getCursorCharacterIndex() > cursorLineLength)
		{
			scriptFile->setCursorCharacterIndex(cursorLineLength);
		}
	}
}

void Script::clear()
{
	_scriptFiles.clear();
}

const int Script::getScriptFileCount() const
{
	return static_cast<int>(_scriptFiles.size());
}

const int Script::getTotalLineCount() const
{
	int result = 0;

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		result += scriptFile->getLineCount();
	}

	return result;
}

const bool Script::isScriptFileExisting(const string & scriptId) const
{
	return (_scriptFiles.find(scriptId) != _scriptFiles.end());
}

const bool Script::isEmpty()
{
	return (getScriptFileCount() == 0);
}

const shared_ptr<ScriptFile> Script::getScriptFile(const string & scriptId) const
{
	if(!isScriptFileExisting(scriptId))
	{
		abort();
	}

	return _scriptFiles.at(scriptId);
}

const vector<string> Script::getScriptFileIds() const
{
	vector<string> result = {};

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		result.push_back(scriptFileId);
	}

	return result;
}

const unordered_map<string, vector<int>> Script::searchKeyword(const string & keyword) const
{
	unordered_map<string, vector<int>> result = {};

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		result.insert({scriptFileId, {}});

		for(int lineNumber = 0; lineNumber < static_cast<int>(scriptFile->getLines().size()); lineNumber++)
		{
			const auto line = scriptFile->getLines()[lineNumber];

			for(int index = 0; index < static_cast<int>(line.size()); index++)
			{
				if(line.substr(index, keyword.size()) == keyword)
				{
					result.at(scriptFileId).push_back(lineNumber + 1);

					break;
				}
			}
		}
	}

	return result;
}