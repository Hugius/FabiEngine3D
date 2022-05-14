#include "script.hpp"

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
	int total = 0;

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		total += scriptFile->getLineCount();
	}

	return total;
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

const unordered_map<string, int> Script::findKeyword(const string & keyword) const
{
	unordered_map<string, int> result;

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		for(int lineNumber = 0; lineNumber < static_cast<int>(scriptFile->getLines().size()); lineNumber++)
		{
			const auto line = scriptFile->getLines()[lineNumber];

			for(int index = 0; index < static_cast<int>(line.size()); index++)
			{
				if(line.substr(index, keyword.size()) == keyword)
				{
					result.insert({scriptFileId, lineNumber + 1});

					break;
				}
			}
		}
	}

	return result;
}