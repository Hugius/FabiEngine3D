#include "script.hpp"
#include "logger.hpp"

Script::Script(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d)
{

}

void Script::createScriptFile(const string& ID)
{
	// Check if non-existent
	for(const auto& file : _scriptFiles)
	{
		if(file->getID() == ID)
		{
			Logger::throwError("Script::createScriptFile");
		}
	}

	// Add new script file
	_scriptFiles.push_back(make_shared<ScriptFile>(_fe3d, ID));
}

void Script::renameScriptFile(const string& ID, const string& newID)
{
	for(const auto& file : _scriptFiles)
	{
		if(file->getID() == ID)
		{
			file->changeID(newID);
			return;
		}
	}

	Logger::throwError("Script::renameScriptFile");
}

void Script::removeScriptFile(const string& ID)
{
	for(size_t i = 0; i < _scriptFiles.size(); i++)
	{
		if(_scriptFiles[i]->getID() == ID)
		{
			_scriptFiles.erase(_scriptFiles.begin() + i);
			return;
		}
	}

	Logger::throwError("Script::removeScriptFile");
}

void Script::reset()
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

const bool Script::isScriptFileExisting(const string& ID) const
{
	for(const auto& file : _scriptFiles)
	{
		if(file->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

shared_ptr<ScriptFile> Script::getScriptFile(const string& ID) const
{
	for(const auto& file : _scriptFiles)
	{
		if(file->getID() == ID)
		{
			return file;
		}
	}

	Logger::throwError("Script::getScriptFile");
}

const vector<string> Script::getScriptFileIDs() const
{
	vector<string> result;

	for(const auto& file : _scriptFiles)
	{
		result.push_back(file->getID());
	}

	sort(result.begin(), result.end());

	return result;
}

const vector<pair<string, unsigned int>> Script::findKeyword(const string& keyword) const
{
	// Temporary values
	vector<pair<string, unsigned int>> result;

	// Iterate through script files
	for(const auto& file : _scriptFiles)
	{
		// Iterate through lines
		for(unsigned int lineNumber = 0; lineNumber < file->getLines().size(); lineNumber++)
		{
			// Temporary values
			string line = file->getLines()[lineNumber];

			// Iterate through lines
			for(size_t i = 0; i < line.size(); i++)
			{
				// Check if keyword occurs
				if(line.substr(i, keyword.size()) == keyword)
				{
					result.push_back(make_pair(file->getID(), lineNumber + 1));
					break;
				}
			}
		}
	}

	// Return
	return result;
}