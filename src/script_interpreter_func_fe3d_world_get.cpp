#include "script_interpreter.hpp"
#include "tools.hpp"
#include "configuration.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWorldGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:world_get_current_id")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _worldEditor->getLoadedWorldID();
			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:world_is_custom_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\custom\\");
			const auto filePath = string(directoryPath + args[0].getString() + ".fe3d");

			const auto result = Tools::isFileExisting(filePath);
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:world` functionality as networking server!");
	}

	return true;
}