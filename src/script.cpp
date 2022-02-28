#include "script.hpp"
#include "logger.hpp"

void Script::createScriptFile(const string& id)
{
	for(const auto& file : _scriptFiles)
	{
		if(file->getId() == id)
		{
			abort();
		}
	}

	_scriptFiles.push_back(make_shared<ScriptFile>(id));
}

void Script::renameScriptFile(const string& id, const string& newId)
{
	for(const auto& file : _scriptFiles)
	{
		if(file->getId() == id)
		{
			file->changeId(newId);
			return;
		}
	}

	abort();
}

void Script::deleteScriptFile(const string& id)
{
	for(unsigned int index = 0; index < _scriptFiles.size(); index++)
	{
		if(_scriptFiles[index]->getId() == id)
		{
			_scriptFiles.erase(_scriptFiles.begin() + index);
			return;
		}
	}

	abort();
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

	for(const auto& scriptFile : _scriptFiles)
	{
		total += scriptFile->getLineCount();
	}

	return total;
}

const bool Script::isScriptFileExisting(const string& id) const
{
	for(const auto& file : _scriptFiles)
	{
		if(file->getId() == id)
		{
			return true;
		}
	}

	return false;
}

const bool Script::isEmpty()
{
	return (getScriptFileCount() == 0);
}

shared_ptr<ScriptFile> Script::getScriptFile(const string& id) const
{
	for(const auto& file : _scriptFiles)
	{
		if(file->getId() == id)
		{
			return file;
		}
	}

	abort();
}

const vector<string> Script::getScriptFileIds() const
{
	vector<string> result;

	for(const auto& file : _scriptFiles)
	{
		result.push_back(file->getId());
	}

	sort(result.begin(), result.end());

	return result;
}

const unordered_map<string, unsigned int> Script::findKeyword(const string& keyword) const
{
	unordered_map<string, unsigned int> result;

	for(const auto& file : _scriptFiles)
	{
		for(unsigned int lineNumber = 0; lineNumber < file->getLines().size(); lineNumber++)
		{
			string line = file->getLines()[lineNumber];

			for(unsigned int index = 0; index < line.size(); index++)
			{
				if(line.substr(index, keyword.size()) == keyword)
				{
					result.insert({file->getId(), lineNumber + 1});
					break;
				}
			}
		}
	}

	return result;
}