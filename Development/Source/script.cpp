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
	for (const auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			Logger::throwError("Cannot add script file with ID: \"" + ID + "\", already existing!");
		}
	}

	// Add new script file
	_scriptFiles.push_back(make_shared<ScriptFile>(_fe3d, ID));
}

void Script::renameScriptFile(const string& ID, const string& newID)
{
	for (const auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			file->changeID(newID);
			return;
		}
	}

	Logger::throwError("Cannot rename script file with ID: \"" + ID + "\", not existing!");
}

void Script::removeScriptFile(const string& ID)
{
	for (size_t i = 0; i < _scriptFiles.size(); i++)
	{
		if (_scriptFiles[i]->getID() == ID)
		{
			_scriptFiles.erase(_scriptFiles.begin() + i);
			return;
		}
	}

	Logger::throwError("Cannot remove script file with ID: \"" + ID + "\", not existing!");
}

void Script::reset()
{
	_scriptFiles.clear();
}

unsigned int Script::getScriptFileCount()
{
	return static_cast<unsigned int>(_scriptFiles.size());
}

unsigned int Script::getTotalLineCount()
{
	unsigned int total = 0;

	for (const auto& scriptFile : _scriptFiles)
	{
		total += scriptFile->getLineCount();
	}

	return total;
}

bool Script::isScriptFileExisting(const string& ID)
{
	for (const auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

shared_ptr<ScriptFile> Script::getScriptFile(const string& ID)
{
	for (const auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			return file;
		}
	}

	Logger::throwError("Cannot retrieve script file with ID: \"" + ID + "\"");
}

const vector<string> Script::getAllScriptFileIDs()
{
	vector<string> result;

	for (const auto& file : _scriptFiles)
	{
		result.push_back(file->getID());
	}

	return result;
}

const vector<pair<string, unsigned int>> Script::findKeyword(const string& keyword)
{
	// Temporary values
	vector<pair<string, unsigned int>> result;

	// For every scriptfile
	for (const auto& file : _scriptFiles)
	{
		// For every line
		for (unsigned int lineNumber = 0; lineNumber < file->getLines().size(); lineNumber++)
		{
			// Temporary values
			string line = file->getLines()[lineNumber];

			// For every line
			for (size_t i = 0; i < line.size(); i++)
			{
				// Check if keyword occurs
				if (line.substr(i, keyword.size()) == keyword)
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