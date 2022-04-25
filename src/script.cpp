#include "script.hpp"

void Script::createScriptFile(const string & id)
{
	if(isScriptFileExisting(id))
	{
		abort();
	}

	_scriptFiles.insert({id, make_shared<ScriptFile>(id)});
}

void Script::renameScriptFile(const string & id, const string & newId)
{
	if(!isScriptFileExisting(id))
	{
		abort();
	}

	const auto cursorLineIndex = getScriptFile(id)->getCursorLineIndex();
	const auto cursorCharacterIndex = getScriptFile(id)->getCursorCharacterIndex();
	const auto lines = getScriptFile(id)->getLines();

	deleteScriptFile(id);
	createScriptFile(newId);

	getScriptFile(newId)->setCursorLineIndex(cursorLineIndex);
	getScriptFile(newId)->setCursorCharacterIndex(cursorCharacterIndex);
	getScriptFile(newId)->setLines(lines);
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

const unsigned int Script::getScriptFileCount() const
{
	return static_cast<unsigned int>(_scriptFiles.size());
}

const unsigned int Script::getTotalLineCount() const
{
	unsigned int total = 0;

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		total += scriptFile->getLineCount();
	}

	return total;
}

const bool Script::isScriptFileExisting(const string & id) const
{
	return (_scriptFiles.find(id) != _scriptFiles.end());
}

const bool Script::isEmpty()
{
	return (getScriptFileCount() == 0);
}

const shared_ptr<ScriptFile> Script::getScriptFile(const string & id) const
{
	if(!isScriptFileExisting(id))
	{
		abort();
	}

	return _scriptFiles.at(id);
}

const vector<string> Script::getScriptFileIds() const
{
	vector<string> result;

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		result.push_back(scriptFileId);
	}

	return result;
}

const unordered_map<string, unsigned int> Script::findKeyword(const string & keyword) const
{
	unordered_map<string, unsigned int> result;

	for(const auto & [scriptFileId, scriptFile] : _scriptFiles)
	{
		for(unsigned int lineNumber = 0; lineNumber < static_cast<unsigned int>(scriptFile->getLines().size()); lineNumber++)
		{
			const auto line = scriptFile->getLines()[lineNumber];

			for(unsigned int index = 0; index < static_cast<unsigned int>(line.size()); index++)
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