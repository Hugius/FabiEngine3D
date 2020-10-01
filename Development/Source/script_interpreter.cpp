#include "script_interpreter.hpp"

#include <sstream>

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d, Script& script) :
	_fe3d(fe3d),
	_script(script)
{

}

void ScriptInterpreter::load()
{
	// For every scriptfile
	for (auto& scriptID : _script.getAllScriptFileIDs())
	{
		// Extract first line
		auto scriptFile = _script.getScriptFile(scriptID);
		std::istringstream iss(scriptFile->getLineText(0));
		string type, name;
		iss >> type >> name;

		// Determine script type
		if (type == "META" && name == "script_type_init")
		{
			_initScriptIDs.push_back(scriptID);
		}
		else if (type == "META" && name == "script_type_update")
		{
			_updateScriptIDs.push_back(scriptID);
		}
		else if (type == "META" && name == "script_type_destroy")
		{
			_destroyScriptIDs.push_back(scriptID);
		}
		else
		{
			_fe3d.logger_throwWarning("No META variable found in script \"" + scriptID + "\"");
		}
	}
}

void ScriptInterpreter::executeInitialization()
{
	for (auto& ID : _initScriptIDs)
	{
		_executeScript(ID);
	}
}

void ScriptInterpreter::executeUpdate()
{
	for (auto& ID : _updateScriptIDs)
	{
		_executeScript(ID);
	}
}

void ScriptInterpreter::executeDestruction()
{
	for (auto& ID : _destroyScriptIDs)
	{
		_executeScript(ID);
	}
}

void ScriptInterpreter::unload()
{
	_initScriptIDs.clear();
	_updateScriptIDs.clear();
	_destroyScriptIDs.clear();
}

void ScriptInterpreter::_executeScript(const string& ID)
{
	auto scriptFile = _script.getScriptFile(ID);

	// Interpret every line from top to bottom in script
	for (unsigned int i = 0; i < scriptFile->getLineCount(); i++)
	{
		string scriptLine = scriptFile->getLineText(i);
		std::istringstream iss(scriptLine);


	}
}