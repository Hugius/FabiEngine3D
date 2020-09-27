#include "script.hpp"
#include "logger.hpp"

Script::Script(FabiEngine3D& fe3d) :
	_fe3d(fe3d)
{

}

void Script::addScriptFile(const string& ID)
{
	// Check if non-existent
	for (auto& file : _scriptFiles)
	{
		if(file->getID() == ID)
		{
			Logger::getInst().throwError("Could not add script file, already exists: " + ID);
		}
	}

	// Add new script file
	_scriptFiles.push_back(make_shared<ScriptFile>(_fe3d, ID));
}

void Script::removeScriptFile(const string& ID)
{
	int index = 0;

	for (auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			_scriptFiles.erase(_scriptFiles.begin() + index);
			return;
		}
		index++;
	}

	Logger::getInst().throwError("Could not remove script file with ID: " + ID);
}

void Script::execute()
{

}

void Script::reset()
{

}

int Script::getScriptFileCount()
{
	return _scriptFiles.size();
}

bool Script::isScriptFileExisting(const string& ID)
{
	for (auto& file : _scriptFiles)
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
	for (auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			return file;
		}
	}

	Logger::getInst().throwError("Could not find script file with ID: " + ID);
}

vector<string> Script::getAllScriptFileIDs()
{
	vector<string> result;

	for (auto& file : _scriptFiles)
	{
		result.push_back(file->getID());
	}

	return result;
}