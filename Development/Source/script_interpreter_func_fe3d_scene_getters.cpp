#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dSceneGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:scene_get_current_id")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _sceneEditor.getLoadedSceneID();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:scene_is_custom_existing")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
				("projects\\" + _currentProjectID)) + "\\scenes\\custom\\");
			string filePath = (directoryPath + arguments[0].getString() + ".fe3d");

			// Return
			auto result = _fe3d.misc_isFileExisting(filePath);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute scene functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:scene` functionality as a networking server!");
	}

	return true;
}