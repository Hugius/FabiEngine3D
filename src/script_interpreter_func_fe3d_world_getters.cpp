#include "script_interpreter.hpp"
#include "tools.hpp"
#include "configuration.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWorldGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:world_get_current_id")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _worldEditor.getLoadedWorldID();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:world_is_custom_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Compose file path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\custom\\");
			const string filePath = string(directoryPath + arguments[0].getString() + ".fe3d");

			// Return
			auto result = Tools::isFileExisting(filePath);
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute world functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:world` functionality as networking server!");
	}

	return true;
}